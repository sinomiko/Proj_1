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

class /**
 * \brief 
 */

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

//清单9.2 可等待任务的线程池
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
//清单9.7 基于锁的任务窃取队列
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

//清单9.7 基于锁的任务窃取队列
class work_stealing_queue
{
private:
    typedef function_wrapper data_type;
    std::deque<data_type> the_queue; // 1
    mutable std::mutex the_mutex;
public:
    work_stealing_queue()
    {}
    work_stealing_queue(const work_stealing_queue& other) = delete;
    work_stealing_queue& operator=(
        const work_stealing_queue& other) = delete;
    void push(data_type data) // 2
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        the_queue.push_front(std::move(data));
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        return the_queue.empty();
    }
    bool try_pop(data_type& res) // 3
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        if (the_queue.empty())
        {
            return false;
        }
        res = std::move(the_queue.front());
        the_queue.pop_front();
        return true;
    }
    bool try_steal(data_type& res) // 4
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        if (the_queue.empty())
        {
            return false;
        }
        res = std::move(the_queue.back());
        the_queue.pop_back();
        return true;
    }
};

//清单9.8 使用任务窃取的线程池
class thread_pool3
{
    typedef function_wrapper task_type;
    std::atomic_bool done;
    ThreadSafeQueue<task_type> pool_work_queue;
    std::vector<std::unique_ptr<work_stealing_queue> > queues; //1
        std::vector<std::thread> threads;
    JoinThreads joiner;
    static thread_local work_stealing_queue* local_work_queue; //2

    static thread_local unsigned my_index;
    void worker_thread(unsigned my_index_)
    {
        my_index = my_index_;
        local_work_queue = queues[my_index].get(); // 3
        while (!done)
        {
            run_pending_task();
        }
    }

    bool pop_task_from_local_queue(task_type& task)
    {
        return local_work_queue && local_work_queue->try_pop(task);
    }
    bool pop_task_from_pool_queue(task_type& task)
    {
        auto ret = pool_work_queue.TryPop(task);
        return ret.get();
    }
    bool pop_task_from_other_thread_queue(task_type& task) // 4
    {
        for (unsigned i = 0; i < queues.size(); ++i)
        {
            unsigned const index = (my_index + i + 1) % queues.size(); // 5
            if (queues[index]->try_steal(task))
            {
                return true;
            }
        }
        return false;
    }
public:
    thread_pool3() :
        done(false), joiner(threads)
    {
        unsigned const
            thread_count = std::thread::hardware_concurrency();
        try
        {
            for (unsigned i = 0; i < thread_count; ++i)
            {
                queues.push_back(std::unique_ptr<work_stealing_queue>(
                    // 6
                    new work_stealing_queue));
                threads.push_back(
                    std::thread(&thread_pool3::worker_thread, this, i));
            }
        }
        catch (...)
        {
            done = true;
            throw;
        }
    }
    ~thread_pool3()
    {
        done = true;
    }
    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type>
        submit(
            FunctionType f)
    {
        typedef typename std::result_of<FunctionType()>::type
            result_type;
        std::packaged_task<result_type()> task(f);
        std::future<result_type> res(task.get_future());
        if (local_work_queue)
        {
            local_work_queue->push(std::move(task));
        }
        else
        {
            pool_work_queue.push(std::move(task));
        }
        return res;
    }
    void run_pending_task()
    {
        task_type task;
        if (pop_task_from_local_queue(task) || // 7
            pop_task_from_pool_queue(task) || // 8
            pop_task_from_other_thread_queue(task)) // 9
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
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


/**
 * \清单10.1 对一个队列并发调用push()和pop()的测试用例 
 */
void test_concurrent_push_and_pop_on_empty_queue()
{
    ThreadSafeQueue<int> q; // 1
    std::promise<void> go, push_ready, pop_ready; // 2
    std::shared_future<void> ready(go.get_future()); // 3
    std::future<void> push_done; // 4
    std::future<int> pop_done;
    try
    {
        push_done = std::async(std::launch::async, // 5
            [&q, ready, &push_ready]()
        {
            push_ready.set_value();
            ready.wait();
            q.Push(42);
        }
        );
        pop_done = std::async(std::launch::async, // 6
            [&q, ready, &pop_ready]()
        {
            pop_ready.set_value();
            ready.wait();
            return q.pop(); // 7
        }
        );
        push_ready.get_future().wait(); // 8
        pop_ready.get_future().wait();
        go.set_value(); // 9
        push_done.get(); // 10
        assert(pop_done.get() == 42); // 11
        assert(q.empty());
    }
    catch (...)
    {
        go.set_value(); // 12
        throw;
    }
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