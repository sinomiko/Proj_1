#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <memory>
#include <assert.h>
using namespace std;

template <typename T>
class ThreadSafeQueue {
public:
    struct Node 
    {
        shared_ptr<T> data;
        unique_ptr<Node> next;
    };

    mutex headMutex;
    unique_ptr<Node> head;
    mutex tailMutex;
    Node* tail;
    condition_variable dataCond;
public:
    ThreadSafeQueue() :
        head(new Node), tail(head.get())
    {}
    ThreadSafeQueue(const ThreadSafeQueue& other) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue& other) = delete;

    void Push(T newValue);

    Node* GetTail();
    unique_ptr<Node> PopHead();

    unique_lock<mutex> WaitForData();

    unique_ptr<Node> WaitPopHead();
    unique_ptr<Node> WaitPopHead(T& value)
    {
        unique_lock<std::mutex> headLock(WaitForData());
        value = std::move(*(head->next));
        return PopHead();
    }
    shared_ptr<T> WaitAndPop();
    void  WaitAndPop(T& value);

    unique_ptr<Node> TryPopHead();

    unique_ptr<Node> TryPopHead(T& value);

    shared_ptr<T> TryPop();

    unique_ptr<Node> TryPop(T& value);


    bool Empty();

    
};

template <typename T>
/*
Note: typename ThreadSafeQueue<T>::Node
对模板参数有依赖的符号，编译器在编译模板时不会自动去顺着依赖查找匹配的，所以在需要你显示指明它到底是不是一个类型，如果不加typename，它有可能是类型，也有可能是静态成员。

https://bbs.csdn.net/topics/392265542
http://en.cppreference.com/w/cpp/language/dependent_name

*/
std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::TryPop(T& value)
{
    unique_ptr<Node> oldHead = TryPopHead(value);
    return oldHead;
}

template <typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::TryPop()
{
    unique_ptr<Node> oldHead = TryPopHead();
    return oldHead ? oldHead->data : shared_ptr<T>();
}

template <typename T>
std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::TryPopHead(T& value)
{
    std::unique_lock<std::mutex> headLock(headMutex);
    if (GetTail() == head.get())
    {
        return unique_ptr<Node>();
    }
    value = move(*(head->data));
    return PopHead();
}

template <typename T>
std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::TryPopHead()
{
    std::unique_lock<std::mutex> headLock(headMutex);
    if (GetTail() == head.get())
    {
        return unique_ptr<Node>();
    }
    unique_ptr<Node> oldHead = std::move(head);
    head = move(oldHead->next);
    return oldHead;
/*    return PopHead();*/
}

template <typename T>
std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::WaitPopHead()
{
    std::unique_lock<std::mutex> headLock(WaitForData());
    unique_ptr<Node> oldHead = std::move(head);
    head = move(oldHead->next);
    return oldHead;
/*    return PopHead();*/
}

template <typename T>
std::unique_lock<std::mutex> ThreadSafeQueue<T>::WaitForData()
{
    std::unique_lock<std::mutex> headLock(headMutex);
    dataCond.wait(headLock, [&] {return GetTail() != head.get(); });
    return move(headLock);
}

template <typename T>
std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::PopHead()
{
    std::unique_lock<std::mutex> headLock(headMutex);
    if (GetTail() == head.get())
    {
        return unique_ptr<Node>();
    }
    unique_ptr<Node> oldHead = std::move(head);
    head = move(oldHead->next);
    return oldHead;
}

template <typename T>
typename ThreadSafeQueue<T>::Node* ThreadSafeQueue<T>::GetTail()
{
    lock_guard<mutex> tailLock(tailMutex);
    return tail;
}

template <typename T>
void ThreadSafeQueue<T>::Push(T newValue)
{
    std::shared_ptr<T> newData = make_shared<T>(std::move(newValue));
    std::unique_ptr<Node> p(new Node);
    {
        lock_guard<mutex> tailLock(tailMutex);
        tail->data = newData;
        Node* const newTail = p.get();
        tail->next = std::move(p);
        tail = newTail;
    }
    dataCond.notify_one();
}

template<typename T>
shared_ptr<T> ThreadSafeQueue<T>::WaitAndPop()
{
    unique_ptr<Node> const oldHead = WaitPopHead();
    return oldHead->data;
}

template <typename T>
void ThreadSafeQueue<T>::WaitAndPop(T& value)
{
    WaitPopHead(value);
}

template <typename T>
bool ThreadSafeQueue<T>::Empty()
{
    lock_guard<mutex> headLock(headMutex);
    return GetTail() == head.get();
}

ThreadSafeQueue<int> gThreadSafeQueue;
std::atomic_bool gFlag = ATOMIC_FLAG_INIT;
void testQueue(int id)
{
    std::unique_ptr<ThreadSafeQueue<int>::Node>  nodePtr;
    int val;
    ThreadSafeQueue<int>::Node* node;
    std::unique_lock<std::mutex> g_lock;
    std::shared_ptr<int> dataPtr;
    for (int i=0;i<1000;i++)
    {
        int ran = rand();
        cout << "thread：" << id << " rand: " << ran % 5 << "\n" << std::flush;

        switch (ran %5)
        {
        case 0:
            nodePtr = gThreadSafeQueue.WaitPopHead();
            cout << "thread：" << id << " WaitPopHead: data:" << *(nodePtr->data) << "\n" << std::flush;
            break;
        case 1:
            gThreadSafeQueue.Push(rand());
        	break;
        case 2:
            gThreadSafeQueue.Push(rand());
            break;
        case 3:
            node = gThreadSafeQueue.GetTail();
            if (node&&node->data)
            {

                cout << "thread：" << id << " GetTail: data:" << *(node->data) << "\n" << std::flush;
            }
            break;
        case 4:
            dataPtr = gThreadSafeQueue.TryPop();
            if (dataPtr)
            {
                cout << "thread：" << id << " TryPop: data:" << *(dataPtr) << "\n" << std::flush;
            }
            break;
        }
        cout << "thread：" << id << " op end" << "\n" << std::flush;
    }
    cout << "thread：" << id << " end" << endl << std::flush;
    gFlag.store(true);
}

void addVal(int id)
{
    while (!gFlag.load())
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        int input = rand();
        cout << "thread：" << id << " input: "<< input << "\n" << std::flush;
        gThreadSafeQueue.Push(input);

    }

}
void testThreadQueue()
{
    std::thread Thread1(testQueue, 1);
    std::thread Thread2(testQueue, 2);
    std::thread Thread3(testQueue, 3);
    std::thread Thread4(testQueue, 4);
    std::thread Thread5(testQueue, 5);
    std::thread Thread6(addVal, 0);
#define  jthread(i) Thread##i.join()
    jthread(1);
    jthread(2);
    jthread(3);
    jthread(4);
    jthread(5);
    jthread(6);
}

int main(int argc, char* argv[])
{
    testThreadQueue();
    cout << "end" << endl;

    getchar();
    return 0;
}
