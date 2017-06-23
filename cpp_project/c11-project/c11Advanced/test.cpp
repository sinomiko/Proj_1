#include<memory>    //std::auto_ptr
#include<functional>//std::function  std::bind  std::placeholders
#include <iostream> // std::cout
#include <utility>  // std::move
#include <vector>   // std::vector
#include <array>    // std::array
#include <string>   // std::string
#include <algorithm>    // std::sort
using namespace std;

class A {
    public:
        int *pointer;
        A():pointer(new int(1)) { std::cout << "construct "<< pointer << std::endl; }
        A(const A& a):pointer(new int(*a.pointer)) { std::cout << "copy construct "<< pointer << std::endl; }    //
        A(A&& a):pointer(a.pointer) { a.pointer = nullptr;std::cout << "move copy construct "<< pointer << std::endl; }
        ~A(){ std::cout << "destructor " << pointer << std::endl; delete pointer; }
};

A return_rvalue(bool test) {
    A a,b;
    if(test) return a;
    else return b;
}

int func(int x){
    cout<<__func__<<"out x"<<x<<endl;
    return x+100;
}

int bind_func(int x, int y, int z){
    cout<<__func__<<" x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
    
    return x+y+z;
}

void reference(int& v) {
        std::cout << "left value"<<std::endl;
}

void reference(int&& v) {
        std::cout << "right value"<<std::endl;
}

template <typename T>
void pass(T&& v) {
    std::cout <<"comman parameter"<<endl;
    reference(v);
    std::cout << "std::move"<<endl;
    reference(std::move(v));
    std::cout << "std::forwaed"<<endl;
    reference(std::forward<T>(v));

}

void funvp(int *p, int len) {
        return;
}



int main(void){
    cout<<"begin"<<endl;
    auto important = make_shared<int>(1);
    
    auto add = [v1 =9, v2 = move(important)](int x, int y)->int{
        return  x+y+v1*(*v2);
    };
  
    auto foo=[](int x){
        cout<< x+9 <<endl;
    };

    std::cout << "======= lambda    ==============================="<< std::endl;
    cout<<"lambda out:"<<add(2,2)<<endl;
    foo(1);
    function<int(int)> bind_fu=bind(bind_func,placeholders::_1, 1,2);
    function<int(int)> func1 = func;
    
    cout<<__func__<<endl; 
    cout<<"func1:"<<func1(10)<<"\nbind_fu:"<<bind_fu(2)<<endl;
     
    std::cout << "=======return_rvalue==============================="<< std::endl;
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;

    std::cout << "=======std::move=================================="<< std::endl;  
    A obj_a;
    std::vector<A> v;
    //string obj_a = "Hello world.";
    //std::vector<string> v;
    std::cout << "obj_a: " << obj_a.pointer << std::endl;
    v.push_back(obj_a);
    std::cout <<"v.push_back(obj_a)" << "obj_a: " << obj_a.pointer << std::endl;
    v.push_back(std::move(obj_a));
    std::cout <<"v.push_back(std::move(obj_a))"<< "obj_a: " << obj_a.pointer << std::endl;

    std::cout << "=======forward=================================="<< std::endl;
    std::cout << "right value begin"<<endl;
    pass(1);
    std::cout << "left value begin"<<endl;
    int value = 1;
    pass(value);
    std::cout << "=======end=================================="<< std::endl;

    array<int, 4> arr = {1,2,3,4};
    funvp(&arr[0], arr.size());
    funvp(arr.data(), arr.size());
    std::sort(arr.begin(), arr.end());
    return 0;

}
