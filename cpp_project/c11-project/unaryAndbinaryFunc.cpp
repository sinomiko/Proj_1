//unary_function跟binary_function详解
/*******
unary_function和binary_function详解

1.unary_function和binary_function介绍
1.1 unary_function介绍
unary_function可以作为一个一元函数对象的基类，它只定义了参数和返回值的类型，本身并不重载（）操作符，这个任务应该交由派生类去完成。

1.2 unary_function源码
 template <class Arg, class Result>
 struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

成员类型	定义	注释
argument_type	第一个模板参数(Arg)	()重载函数的参数类型
result_type	第二个模板参数(Result)	()重载函数的返回值类型
*/

// unary_function example
#include <iostream>     // std::cout, std::cin
#include <functional>   // std::unary_function
#include <vector>
#include <map>
#include <string>
using namespace std;
struct IsOdd : public std::unary_function<int,bool> {
  bool operator() (int number) {return (number%2!=0);}
};

class vector_finder
{
public:
    vector_finder(const int a) :m_i_a(a) {}
    bool operator ()(const std::vector<struct value_t>::value_type &value)
    {
        return value.a == m_i_a;
    }
private:
    int m_i_a;
};


int main () {
  IsOdd IsOdd_object;
  IsOdd::argument_type input;
  IsOdd::result_type result;

  std::cout << "Please enter a number: ";
  std::cin >> input;

  result = IsOdd_object (input);

  std::cout << "Number " << input << " is " << (result?"odd":"even") << ".\n";

  vector<int> test1;
  test1.push_back(1);
  test1.push_back(2);
  auto xx = find(test1.begin(),test1.end(),2);

  map<int,string> test_map;
  test_map.insert(make_pair());
  test_map.push_back(2);
  find(test_map.begin(),test_map.end(),);

  getchar();
  getchar();
  return 0;
}
/*
2. binary_function介绍
2.1 binary_function介绍
binary_function可以作为一个二元函数对象的基类，它只定义了参数和返回值的类型，本身并不重载（）操作符，这个任务应该交由派生类去完成。

2.2 binary_function源码
1 template <class Arg1, class Arg2, class Result>
2   struct binary_function {
    3     typedef Arg1 first_argument_type;
    4     typedef Arg2 second_argument_type;
    5     typedef Result result_type;
    6
};

成员类型	定义	注释
first_argument_type	第一个模板参数(Arg1)	()重载函数的第一个参数类型
second_argument_type	第一个模板参数(Arg2)	()重载函数的第二个参数类型
return_type	第一个模板参数(Result)	()重载函数的返回值类型
2.3 例子
*/

/*
// binary_function example
#include <iostream>     // std::cout, std::cin
#include <functional>   // std::binary_function

struct Compare : public std::binary_function<int,int,bool> {
  bool operator() (int a, int b) {return (a==b);}
};

int main () {
  Compare Compare_object;
  Compare::first_argument_type input1;
  Compare::second_argument_type input2;
  Compare::result_type result;

  std::cout << "Please enter first number: ";
  std::cin >> input1;
  std::cout << "Please enter second number: ";
  std::cin >> input2;

  result = Compare_object (input1,input2);

  std::cout << "Numbers " << input1 << " and " << input2;
  if (result)
      std::cout << " are equal.\n";
  else
      std::cout << " are not equal.\n";

  return 0;
}
*/

