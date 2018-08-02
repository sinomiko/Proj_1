#include <iostream>
#include <experimental/filesystem>

#include <type_traits>
using namespace std;
#include <cstring>

// maximum of two values of any type (call-by-reference)
template<typename T>
T const& mmmax(T const& a, T const& b)
{
    return b < a ? a : b;
}
// maximum of two C-strings (call-by-value)
char const* mmmax(char const* a, char const* b)
{
    int ai = 2;

    return std::strcmp(b, a) < 0 ? a : b;
}

// maximum of three values of any type (call-by-reference)
template<typename T>
T const& mmmax(T const&  a, T const& b, T const& c)
{
    return mmmax(mmmax(a, b), c);            // error if max(a,b) uses call-by-value
}

#include <iostream>
#include <memory>

class BaseClass {
public: 
    virtual void vfun() 
    {
        std::cout << "BaseClass vfun\n";;
    }
};

class DerivedClass : BaseClass
{
public:
    void f() const
    {
        std::cout << "Hello World!\n";
    }
    ~DerivedClass() { // 注意：它不是虚的
        std::cout << "~DerivedClass\n";
    }

    virtual void vfun() override
    {
        std::cout << "DerivedClass vfun\n";;
    }

};

int main(int argc, char* argv[])
{
    auto der = make_unique<DerivedClass>();
    unique_ptr<BaseClass> ptr_to_base = <BaseClass>(der); 
    ptr_to_base->vfun(); 

//     char const* s1 = "frederic";
//     char const* s2 = "anica";
//     char const* s3 = "lucas";
//     auto m2 = mmmax(s1, s2, s3);       //run-time ERROR


//     int a = 1;
//     int& ar = a;
//     int b = 2;
//     cout<<is_reference<decltype(<int&, int>(ar, b))>::value<<endl;
//     namespace fs = std::experimental::filesystem; // In C++17 use std::filesystem.
// 
//     try {
//         fs::create_directories("path/with/directories/that/might/not/exist");
//     }
//     catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
//         std::cout << e.what() << std::endl;
//     }

//     std::error_code ec;
//     bool success = fs::create_directories("path/with/directories/that/might/not/exist", ec);
// 
//     if (!success) {
//         std::cout << ec.message() << std::endl; // Fun fact: In case of success ec.message() returns "The operation completed successfully." using vc++.
//     }
    return 0;
}