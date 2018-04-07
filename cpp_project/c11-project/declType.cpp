#include <memory> // and others
#include <map>
#include <iostream>
using namespace std;

template <typename T>
class TD;
int main()
{
    const int theAnswer = 42;
    auto x = theAnswer;
    auto y = &theAnswer;

    // 	TD<decltype(x)> xType; // elicit errors containing
    // 	TD<decltype(y)> yType; // x's and y's types

    //  display types for x and y 
    std::cout << typeid(x).name() << '\n';  //int
    std::cout << typeid(y).name() << '\n';  //int const *


    getchar();
    return 0;
}
