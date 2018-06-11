#include <iostream>
#include <chrono>
#include <windows.h>
#include <map>
using namespace std;

template <class T> struct greater : binary_function <T, T, bool> {
    bool operator() (const T& x, const T& y) const
    {
        return x > y;
    }
};

int main()
{
    map<int, string, greater<int>> test;
    test.insert(make_pair(1, "aaa"));
    test.insert(make_pair(2, "bbb"));
    test.insert(make_pair(3, "ccc"));
    test.insert(make_pair(4, "ddd"));
    for (auto& it : test)
    {
        cout << it.first << " ";
        cout << it.second.c_str() << endl;
    }

    for (int i=1;i<10;i++)
    {
        for (int j =1;j<10;j++)
        {
            for (int ii = 1; ii < 10; ii++)
            {
                for (int jj = 1; jj < 10; jj++)
                {
                    if ((i*10+i)*(j*10+j) == ii*1000+ii*100+jj*10+jj )
                    {

                        cout << (i * 10 + i)<<"*"<< (j * 10 + j)<<"="<<\
                            ii * 1000 + ii * 100 + jj * 10 + jj <<":i=" \
                            << i << " j=" << j << " ii= " << ii << " jj=" \
                            << jj << endl;;
                    }
                }
            }
        }
    }
// 	unsigned int long long tick1 = GetTickCount64();
// 	//std::cout << "tick Time  :" << tick1 << std::endl;
// 	for (long long int i =0; i< 10000000;i++)
// 	{
// 		unsigned long long int ms = chrono::duration_cast<chrono::milliseconds>(
// 			chrono::system_clock::now().time_since_epoch()).count();
// 	}
// 	unsigned int long long tick2 = GetTickCount64();
// 	std::cout << "tick Time  :" << tick2 - tick1 << std::endl;
// 
// 	unsigned int long long tick3 = GetTickCount64();
// 	//std::cout << "tick Time  :" << tick1 << std::endl;
// 	for (long long int i = 0; i < 10000000;i++)
// 	{
// 		unsigned long long int ms = GetTickCount64();
// 	}
// 	unsigned int long long tick4 = GetTickCount64();
// 	std::cout << "tick Time  :" << tick4 - tick3 << std::endl;
	getchar();
}