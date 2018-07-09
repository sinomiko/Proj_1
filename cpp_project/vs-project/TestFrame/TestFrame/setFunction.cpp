#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;
void print(set<int> a)
{
    if (a.begin() == a.end())
        cout << "}" << endl;
    for (set<int>::iterator it = a.begin(); it != a.end(); it++)
    {
        if (++it == a.end())
        {
            it--;
            cout << *it << "}\n";
        }
        else
        {
            it--;
            cout << *it << ", ";
        }
    }
}
/*
std::set_intersection() :这个函数是求两个集合的交集。
std::set_union() :求两个集合的并集
std::set_difference（）：差集
std::set_symmetric_difference（）：得到的结果是 第一个迭代器相对于第二个的差集 并上第二个相对于第一个的差集

A∪B={x|x∈A∨x∈B}
A∩B={x|x∈A∧x∈B}
A-B={x|x∈A∧x不属于 B}
SA ={x|x∈(A∪B)∧x 不属于A}
SB ={x|x∈(A∪B)∧x 不属于B}

*/

template<typename ...Args>
constexpr int sum17(Args... args) {
    return (0 + ... + args);
}

int main()
{
//    int sum = sum17<>();
//    cout << sum << endl;
    int T, cou = 0;
    set<int> a, b, c;
    cin >> T;
    while (T--)
    {
        cou++;
        a.clear(), b.clear(), c.clear();
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            a.insert(x);
        }
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            b.insert(x);
        }
        cout << "Case# " << cou<< ":" << endl;
        cout << "A = {";
        print(a);
        cout << "B = {";
        print(b);
        set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
        cout << "A u B = {";
        print(c);
        c.clear();
        set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
        cout << "A n B = {";
        print(c);
        c.clear();
        set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
        cout << "A - B = {";
        print(c);
        c.clear();
        set_difference(b.begin(), b.end(), a.begin(), a.end(), inserter(c, c.begin()));
        cout << "SA = {";
        print(c);
        c.clear();
        set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
        cout << "SB = {";
        print(c);
    }

    return 0;
}