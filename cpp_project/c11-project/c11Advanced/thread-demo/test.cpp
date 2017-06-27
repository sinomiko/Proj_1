#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>

int main()
{
    // producer mount
    std::queue<int> produced_nums;

    // mutex   
    std::mutex m;
    
    // condition
    std::condition_variable cond_var;

    // done flag
    bool done = false;

    // notify flag
    bool notified = false;

    // producer thread
    std::thread producer([&]() {
        while(!done){
            for (int i = 0; i < 5; ++i) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                // create producer lock
                std::unique_lock<std::mutex> lock(m);
                std::cout << "producing " << i << '\n';
                produced_nums.push(i);
                notified = true;
                // notify one thread
                cond_var.notify_one();
            }   
            done = true;
            cond_var.notify_one();
        }
    }); 
    
    // consumer thread

    std::thread consumer([&]() {
        std::unique_lock<std::mutex> lock(m);
        while (!done) {
            while (!notified) {  // avoid fake notify
                cond_var.wait(lock);
            }
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << '\n';
                produced_nums.pop();
            }   
            notified = false;
            done = false;
        }   
    }); 

    producer.join();
    consumer.join();
}

