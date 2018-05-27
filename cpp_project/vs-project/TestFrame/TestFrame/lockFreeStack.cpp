#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <assert.h>
using namespace std;

template <typename T>
class LockFreeStack {

private:
 
    struct Node {
        shared_ptr<T> data;
        Node* next;
        Node(T const& data_)
            :data(make_shared<T>(data_))
        {}
    };
    std::atomic<Node*> head;
public:
    void Push(T const& data)
    {
        Node* const newNode = new Node(data);
        newNode->next = head;
        while (!head.compare_exchange_weak(newNode->next, newNode));
//         原子性加减通常是用CAS(Compare and Swap)完成的，与平台相关。CAS的基本形式是：CAS(addr, old, new), 当addr中存放的值等于old时，用new对其替换
//         当前值与期望值相等时，修改当前值为设定值，返回true
//         当前值与期望值不等时，将期望值修改为当前值，返回false
//         这个函数可能在满足true的情况下仍然返回false，所以只能在循环里使用，否则可以使用它的strong版本
    }
    void Pop(T & data)
    {
        Node* oldHead = head.load();
        while (oldHead && !head.compare_exchange_weak(oldHead, oldHead->next));
        return oldHead ? data = oldHead->data : shared_ptr<T>();
    }
};


ThreadSafeLookUpTable<int, string> gThreadSafeLookUpTable;
std::atomic_bool gFlag = ATOMIC_FLAG_INIT;
void testThreadSafeLookUpTable(int id)
{
    int val;
    std::shared_ptr<int> dataPtr;
    for (int i = 0; i < 1000; i++)
    {
        int ran = rand();
        cout << "thread：" << id << " rand: " << ran % 5 << "\n" << std::flush;

        switch (ran % 5)
        {
        case 0:
            gThreadSafeLookUpTable;
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        }
        cout << "thread：" << id << " op end" << "\n" << std::flush;
    }
    cout << "thread：" << id << " end" << endl << std::flush;
    gFlag.store(true);
}

// void addVal(int id)
// {
//     while (!gFlag.load())
//     {
//         this_thread::sleep_for(std::chrono::milliseconds(1000));
//         int input = rand();
//         cout << "thread：" << id << " input: " << input << "\n" << std::flush;
//         gThreadSafeLookUpTable.Push(input);
// 
//     }
// 
// }
void testThreadQueue()
{
#define  CreateThread(Func, val)  std::thread Thread##val(testThreadSafeLookUpTable,val)
    CreateThread(testThreadSafeLookUpTable, 1);
    CreateThread(testThreadSafeLookUpTable, 2);
    CreateThread(testThreadSafeLookUpTable, 3);
    CreateThread(testThreadSafeLookUpTable, 4);
    CreateThread(testThreadSafeLookUpTable, 5);
#define  JoinThread(i) Thread##i.join()
    JoinThread(1);
    JoinThread(2);
    JoinThread(3);
    JoinThread(4);
    JoinThread(5);
}

int main(int argc, char* argv[])
{
    testThreadQueue();
    cout << "end" << endl;

    getchar();
    return 0;
}
