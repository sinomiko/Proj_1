#include <string>
#include <iostream>
#include <future>       // std::packaged_task, std::future
#include <list>
#include <thread>
#include <assert.h>
#include "joinThreads.h"
#include "threadSafeQueue.h"

using namespace std;
class thread_pool
{
    std::atomic_bool done;
    ThreadSafeQueue<std::function<void()> > work_queue; // 1
    std::vector<std::thread> threads; // 2
    JoinThreads joiner; // 3
    void worker_thread()
    {
        while (!done) // 4
        {
            std::function<void()> task;
            if (work_queue.TryPop(task)) // 5
            {
                task(); // 6
            }
            else
            {
                std::this_thread::yield(); // 7
            }
        }
    }

public:
    thread_pool() :
        done(false), joiner(threads)
    {
        unsigned const
            thread_count = std::thread::hardware_concurrency(); // 8
        try
        {
            cout << "thread_count:" << thread_count  <<endl;
            for (unsigned i = 0; i < thread_count; ++i)
            {
                threads.push_back(
                    std::thread(&thread_pool::worker_thread, this)); // 9
            }
        }
        catch (...)
        {
            done = true; // 10
            throw;
        }
    }
    ~thread_pool()
    {
        done = true; // 11
    }

    template<typename FunctionType>
    void submit(FunctionType f)
    {
        work_queue.Push(std::function<void()>(f)); // 12
    }
};
void add()
{
    cout << "hello world" << endl << std::flush;
}
int main(int argc, char* argv[])
{
    thread_pool thread_pool_demo;
    thread_pool_demo.submit(add);
    thread_pool_demo.submit(add);
    thread_pool_demo.submit(add);
    thread_pool_demo.submit(add);
    getchar();
    return 0;
}