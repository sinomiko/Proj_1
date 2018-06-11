#include<threadSafeQueue.h>
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