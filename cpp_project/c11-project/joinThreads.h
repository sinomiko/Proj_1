#pragma once
#include <vector>
#include <thread>
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
        for (ulong i = 0; i < m_threads.size(); ++i)
        {
            if (m_threads[i].joinable())
            {
                m_threads[i].join();
            }
        }
    }
};
