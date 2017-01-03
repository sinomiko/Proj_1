#include <iostream>

using namespace std;

class A {
private:
    virtual void WhoAmI() {
        cout << "I am class A" << endl;
    }
    virtual void f0() {
        cout << "This is f0" << endl;
    }
    virtual void f1() {
        cout << "This is f1" << endl;
    }
};

class B:public A {
public:
    void WhoAmIForB() {
        cout << "I am class B" << endl;
    }
};

typedef void (*FUNC)();

int main(int argc,char * argv[])
{
    B b;

    b.WhoAmIForB();
    //b.WhoAmI();    error C2248: “A::WhoAmI”: 无法访问 private 成员(在“A”类中声明)
    FUNC func = (FUNC)((int*)(*(int*)(*(int*)(&b))));
    func();

    return 0;
}
