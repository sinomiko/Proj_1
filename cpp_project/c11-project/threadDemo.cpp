#include<iostream>
#include <thread>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <iterator>
using namespace std;
template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = distance(first, last);
    if (!length)
    {
        return init;
    }
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hard_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hard_threads != 0 ? hard_threads : 4, max_threads);
    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    Iterator block_start = first;
    for (unsigned long i=0;i<(num_threads-1);++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }

    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
    std::for_each(threads.begin(), threads.end(), mem_fun(&std::thread::join));
    return accumulate(results.begin(), results.end(), init);
}

int main(int argc, char* argv[])
{
    vector<int> tmp;
    for (int i =0;i<2500000;i++)
    {
        tmp.push_back(rand());
    }
    unsigned long init = 0;
    using iterator_type = decltype(std::begin(tmp));
    
    accumulate_block<typename std::vector<int>::iterator, int>(tmp.begin(), tmp.end(), init);
//    std::thread::get_id()
    getchar();
    return 0;
}