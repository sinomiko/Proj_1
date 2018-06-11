#include <string>
#include <iostream>
#include <future>       // std::packaged_task, std::future
#include <list>
#include <queue>
#include <thread>
#include <assert.h>
#include "joinThreads.h"
#include "threadSafeQueue.h"

using namespace std;

class function_wrapper
{
    struct impl_base {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };
    std::unique_ptr<impl_base> impl;
    template<typename F>
    struct impl_type : impl_base
    {
        F f;
        impl_type(F&& f_) : f(std::move(f_)) {}
        void call() { f(); }
    };
public:
    template<typename F>
    function_wrapper(F&& f) :
        impl(new impl_type<F>(std::move(f)))
    {}

    void operator()() { impl->call(); }
    function_wrapper() = default;
    function_wrapper(function_wrapper&& other) :
        impl(std::move(other.impl))
    {}
    function_wrapper& operator=(function_wrapper&& other)
    {
        impl = std::move(other.impl);
        return *this;
    }
    function_wrapper(const function_wrapper&) = delete;
   // function_wrapper(function_wrapper&) = delete;
    function_wrapper& operator=(const function_wrapper&) = delete;
};

class thread_pool
{
    std::atomic_bool done;
    std::vector<std::thread> threads; // 2
    JoinThreads joiner; // 3
    ThreadSafeQueue<function_wrapper> work_queue; // 使用function_wrapper，而非使用std::function
public:
    thread_pool() :
        done(false), joiner(threads)
    {
        unsigned const
            thread_count = std::thread::hardware_concurrency(); // 8
        try
        {
            cout << "thread_count:" << thread_count << endl;
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

    void worker_thread()
    {
        while (!done)
        {
            function_wrapper task;
            if (work_queue.TryPop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }
public:
    template<typename FunctionType>
    std::future < typename std::result_of<FunctionType()>::type> // 1
        submit(FunctionType f)
    {
        typedef typename std::result_of<FunctionType()>::type
            result_type; // 2
        std::packaged_task<result_type()> task(std::move(f)); // 3
        std::future<result_type> res(task.get_future()); // 4
        work_queue.Push(std::move(task)); // 5
        return res; // 6
    }
    // 休息一下

    void run_pending_task()
    {
        function_wrapper task;
        if (work_queue.TryPop(task))
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
};
class thread_pool2
{
    ThreadSafeQueue<function_wrapper> pool_work_queue;
    typedef std::queue<function_wrapper> local_queue_type; // 1
    static thread_local std::unique_ptr<local_queue_type> local_work_queue; // 2
    std::atomic_bool done;
    std::vector<std::thread> threads; // 2
    JoinThreads joiner; // 3
public:
    thread_pool2() :
        done(false), joiner(threads)
    {
        unsigned const
            thread_count = std::thread::hardware_concurrency(); // 8
        try
        {
            cout << "thread_count:" << thread_count << endl;
            for (unsigned i = 0; i < thread_count; ++i)
            {
                threads.push_back(std::move(std::thread(&thread_pool2::worker_thread, this))); // 9
            }
        }
        catch (...)
        {
            done = true; // 10
            throw;
        }
    }

    ~thread_pool2()
    {
        done = true; // 11
    }
    void worker_thread()
    {
        local_work_queue.reset(new local_queue_type); // 3
        while (!done)
        {
            run_pending_task();
        }
    }
public:
    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type>
        submit(FunctionType f)
    {
        typedef typename std::result_of<FunctionType()>::type
            result_type;
        std::packaged_task<result_type()> task(f);
        std::future<result_type> res(task.get_future());
        if (local_work_queue) // 4
        {
            local_work_queue->push(std::move(task));
        }
        else
        {
            pool_work_queue.Push(std::move(task)); // 5
        }
        return res;
    }

    void run_pending_task()
    {
        function_wrapper task;
        if (local_work_queue && !local_work_queue->empty()) // 6
        {
            task = std::move(local_work_queue->front());
            local_work_queue->pop();
            task();
        }
        else if (pool_work_queue.TryPop(task)) // 7
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
    // rest as before
};

void add()
{
    cout << "hello world" << endl << std::flush;
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);
    if (!length)
        return init;
    unsigned long const block_size = 25;
    unsigned long const num_blocks = (length + block_size - 1) / block_size; // 1
    std::vector<std::future<T> > futures(num_blocks - 1);
    thread_pool pool;

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        futures[i] = pool.submit(accumulate_block<Iterator, T>()); //2
            
        block_start = block_end;
    }
    T last_result = accumulate_block<Iterator, T>()
        (block_start, last);
    T result = init;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i)
    {
        result += futures[i].get();
    }
    result += last_result;
    return result;
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