#include <string>
#include <iostream>
#include <future>
#include <list>
#include <thread>
#include <assert.h>
using namespace std;


class Foo {};

template <typename T>
list<T> parrallel_quick_sort(list<T> input)
{
    if (input.empty())
    {
        return input;
    }
    list<T> result;
    result.splice(result.begin(), input, input.begin());
    T const& pivot = *result.begin();
    auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) {return t < pivot; });

    list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
    std::future<list<T>> new_lower(async(&parrallel_quick_sort<T>, move(lower_part)));
    auto new_higher( parrallel_quick_sort(move(input)));
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());

    return result;
}
void test_parrallel_quick_sort() 
{
    list<int> testList;
    for (int i = 0; i < 20; i++)
    {
        testList.push_back(rand());

    }
    for (auto it : testList)
    {
        cout << it << "\t";
    }

    cout << endl;
    list<int> res = parrallel_quick_sort<int>(testList);
    for (auto it : res)
    {
        cout << it << "\t";
    }

    cout << endl;

}
void memoryOrder()
{
    Foo some_array[5];
    std::atomic<Foo*> p(some_array);
    Foo* x = p.fetch_add(2); // p加2，并返回原始值
    assert(x == some_array);
    assert(p.load() == &some_array[2]);
    x = (p -= 1); // p减1，并返回原始值
    assert(x == &some_array[1]);
    assert(p.load() == &some_array[1]);
}

std::atomic<bool> x, y;
std::atomic<int> z;
void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed); // 1
    y.store(true, std::memory_order_relaxed); // 2
}
void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed)); // 3
    if (x.load(std::memory_order_relaxed)) // 4
        ++z;
}

void testRelax() 
{
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0); // 5
}



std::atomic<int> xx(0), yy(0), zz(0); // 1
std::atomic<bool> go(false); // 2
unsigned const loop_count = 10;
struct read_values
{
    int xx, yy, zz;
};
read_values values1[loop_count];
read_values values2[loop_count];
read_values values3[loop_count];
read_values values4[loop_count];
read_values values5[loop_count];
void increment(std::atomic<int>* var_to_inc, read_values* values)
{
    while (!go)
        std::this_thread::yield(); // 3 自旋，等待信号
    for (unsigned i = 0; i < loop_count; ++i)
    {
        values[i].xx = xx.load(std::memory_order_seq_cst);
        values[i].yy = yy.load(std::memory_order_seq_cst);
        values[i].zz = zz.load(std::memory_order_seq_cst);
        var_to_inc->store(i + 1, std::memory_order_seq_cst); // 4
        std::this_thread::yield();
    }
}

void read_vals(read_values* values)
{
    while (!go)
        std::this_thread::yield(); // 5 自旋，等待信号
    for (unsigned i = 0; i < loop_count; ++i)
    {
        values[i].xx = xx.load(std::memory_order_seq_cst);
        values[i].yy = yy.load(std::memory_order_seq_cst);
        values[i].zz = zz.load(std::memory_order_seq_cst);
        std::this_thread::yield();
    }
}
void print(read_values* v)
{
    for (unsigned i = 0; i < loop_count; ++i)
    {
        if (i)
            std::cout << ",";
        std::cout << "(" << v[i].xx << "," << v[i].yy << "," << v[i].zz << ")";
    }
    std::cout << std::endl;
}

void testRelax2()
{
    std::thread t1(increment, &xx, values1);
    std::thread t2(increment, &yy, values2);
    std::thread t3(increment, &zz, values3);
    std::thread t4(read_vals, values4);
    std::thread t5(read_vals, values5);
    go = true; // 6 开始执行主循环的信号
    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
    print(values1); // 7 打印最终结果
    print(values2);
    print(values3);
    print(values4);
    print(values5);
}
int main(int argc, char* argv[])
{

    testRelax2();


    
    cout << "end" << endl;
    getchar();
    return 0;
}
