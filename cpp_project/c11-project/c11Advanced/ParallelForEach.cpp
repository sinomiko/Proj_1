#include <string>
#include <iostream>
#include <future>       // std::packaged_task, std::future
#include <list>
#include <thread>
#include <assert.h>
using namespace std;

typedef unsigned long ulong;
class JoinThreads {
    std::vector<std::thread>& m_threads;
public:
    explicit JoinThreads(std::vector<std::thread>& threads_) :
        m_threads(threads_)
    {}
    ~JoinThreads() 
    {
        for (ulong i=0;i<m_threads.size();++i)
        {
            if (m_threads[i].joinable())
            {
                m_threads[i].join();
            }
        }
    }
};
int add(int a, int b)
{
    return a + b;
}
template<class Iterator, typename Func>
void ParallelForEach(Iterator first, Iterator last, Func func)
{
    ulong const length = std::distance(first, last);
    if (!length)
    {
        return;
    }
    ulong const min_per_thread = 25;
    ulong const max_threads = (length + min_per_thread - 1) / min_per_thread;

    ulong const hardware_threads = std::thread::hardware_concurrency();

    ulong const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    ulong const block_size = length / num_threads;

    std::vector<std::future<void> > futures(num_threads - 1);
    std::vector<std::thread> threadsAsync;

    JoinThreads joiner(threadsAsync);

    Iterator block_start = first;
    for (ulong i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = first;
        std::advance(block_end, block_size);
        std::packaged_task<void(void)> task( // 2
            [=]()
        {
            std::for_each(block_start, block_end, func);
        });

        futures[i] = task.get_future();
        threadsAsync.emplace_back(std::move(task));

        block_start = block_end;
    }
    std::for_each(block_start, last, func);
    for (ulong i=0;i<(num_threads - 1);++i)
    {
        futures[i].get();
    }
}
template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    unsigned long const length = std::distance(first, last);
    if (!length)
        return;
    unsigned long const min_per_thread = 25;
    if (length < (2 * min_per_thread))
    {
        std::for_each(first, last, f); // 1
    }
    else
    {
        auto mid_point = first;
        std::advance(mid_point,length / 2);
        std::future<void> first_half = // 2
            std::async(std::launch::async, &parallel_for_each<Iterator, Func>,
                first, mid_point, f);
        parallel_for_each(mid_point, last, f); // 3
        std::cout << "waiting...\n";
        std::future_status status;
        do {
            status = first_half.wait_for(std::chrono::seconds(1));
            if (status == std::future_status::deferred) {
                std::cout << "deferred\n";
            }
            else if (status == std::future_status::timeout) {
                std::cout << "timeout\n";
            }
            else if (status == std::future_status::ready) {
                std::cout << "ready!\n";
                break;
            }
        } while (status != std::future_status::ready);
        first_half.get(); // 4
    }
}
template<typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType
    match)
{
    struct find_element // 1
    {
        void operator()(Iterator begin, Iterator end,
            MatchType match,
            std::promise<Iterator>* result,
            std::atomic<bool>* done_flag)
        {
            try
            {
                for (; (begin != end) && !done_flag->load(); ++begin) // 2
                {
                    if (*begin == match)
                    {
                        result->set_value(begin); // 3
                        done_flag->store(true); // 4
                        return;
                    }
                }
            }
            catch (...) // 5
            {
                try
                {
                    result->set_exception(std::current_exception()); // 6
                    done_flag->store(true);
                }
                catch (...) // 7
                {
                }
            }
        }
    };
    unsigned long const length = std::distance(first, last);

    if (!length)
        return last;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads =
        (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads =
        std::thread::hardware_concurrency();
    unsigned long const num_threads =
        std::min(hardware_threads != 0 ?
            hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;
    std::promise<Iterator> result; // 8
    std::atomic<bool> done_flag(false); // 9
    std::vector<std::thread> threads(num_threads - 1);

    { // 10
        join_threads joiner(threads);
        Iterator block_start = first;
        for (unsigned long i = 0; i < (num_threads - 1); ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            threads[i] = std::thread(find_element(), // 11
                block_start, block_end, match,
                &result, &done_flag);
            block_start = block_end;
        }
        find_element()(block_start, last, match, &result, &done_flag);
        // 12
    }
    if (!done_flag.load()) //13
    {
        return last;
    }
    return result.get_future().get(); // 14
}
void testAsync()
{
    std::future<int> future = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });

    std::cout << "waiting...\n";
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) {
            std::cout << "deferred\n";
        }
        else if (status == std::future_status::timeout) {
            std::cout << "timeout\n";
        }
        else if (status == std::future_status::ready) {
            std::cout << "ready!\n";
            
        }
    } while (status != std::future_status::ready);

    std::cout << "result is " << future.get() << '\n';
}
 int main(int argc, char* argv[])
 {
     vector<ulong> values(100000);
     for (ulong i=0;i<=100;++i)
     {
         values[i] = i;
     }
     ulong sum = 0;
     //ParallelForEach(values.begin(), values.end(), [&](ulong val) { return sum += val; });
     parallel_for_each(values.begin(), values.end(), [&](ulong val) { return sum += val; });
     //testAsync();
     cout << "sum:" <<sum << endl;
     getchar();
     return 0;
 }
