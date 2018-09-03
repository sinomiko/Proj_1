#pragma once
#include <vector>
#include <thread>
using namespace std;
class interrupt_flag
{
public:
    void set();
    bool is_set() const;
};
thread_local interrupt_flag this_thread_interrupt_flag; // 1
class interruptible_thread
{
public:
    void join();
    void detach();
    bool joinable() const;
    void interrupt();

    std::thread internal_thread;
    interrupt_flag* flag;
public:
    template<typename FunctionType>
    interruptible_thread(FunctionType f)
    {
        std::promise<interrupt_flag*> p; // 2
        internal_thread = std::thread([f, &p] { // 3
            p.set_value(&this_thread_interrupt_flag);
            f(); // 4
        });
        flag = p.get_future().get(); // 5
    }
    /**
     * \brief 
     */
    void interrupt()
    {
        if (flag)
        {
            flag->set(); // 6
        }
    }
};