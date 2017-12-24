#include <iostream>                // std::cout
#include <thread>                // std::thread
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable
#include <windows.h>
std::mutex mtx; // ȫ�ֻ�����.
std::condition_variable cv; // ȫ����������.
bool ready = false; // ȫ�ֱ�־λ.

void do_print_id(int id)
{
    std::unique_lock <std::mutex> lck(mtx);
    while (!ready) // �����־λ��Ϊ true, ��ȴ�...
    {
        cv.wait(lck); 
        std::cout << '.';
        std::cout.flush();
        Sleep(1000);

    }  // ��ǰ�̱߳�����, ��ȫ�ֱ�־λ��Ϊ true ֮��,
    // �̱߳�����, ��������ִ�д�ӡ�̱߳��id.
    std::cout << "thread " << id << '\n';
}

void go()
{
    std::unique_lock <std::mutex> lck(mtx);
    ready = true; // ����ȫ�ֱ�־λΪ true.
    cv.notify_all(); // ���������߳�.
}

int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(do_print_id, i);

    std::cout << "10 threads ready to race...\n";
    go(); // go!

    for (auto & th : threads)
        th.join();

    return 0;
}