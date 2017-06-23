#include<iostream>
#include<memory>
#include<utility>
#include<functional>
using namespace std;

int func(int x){
    cout<<"out x"<<x<<endl;
    return x+100;
}

int bind_func(int x, int y, int z){
    cout<<__func__<<" x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
    return x+y+z;
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
    cout<<"lambda out:"<<add(2,2)<<endl;
    foo(1);
    function<int(int)> bind_fu=bind(bind_func,placeholders::_1, 1,2);
    function<int(int)> func1 = func;
    
    cout<<__func__<<endl; 
    cout<<"func1:"<<func1(10)<<"\nbind_fu:"<<bind_fu(2)<<endl;
    return 0;
}
