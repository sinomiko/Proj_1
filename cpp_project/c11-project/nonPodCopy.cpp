#include<iostream>
#include<string>
using namespace std;
class A
{
public:
    A(const & a);
    A(){ cout << __FUNCTION__ << " default" << endl; }
    A(const string& name_, int num_);
    virtual ~A(){ ; }
private:
    string name = "abc";
    int num =0;
};
A::A(const A&a)
{
    if (this == &a)
    {
        return *this;
    }
    name = a.name;
    num = a.num;
}
A::A(const string& name_, int num_)
{
    name = name_;
    num = num_;
    cout << __FUNCTION__ << " 2 param"  << endl;
}

class B : public A
{
public:
    B(){ cout << __FUNCTION__ << " default" << endl; }
    B(const A& a);
    B& operator=(const A& a);
/*    void operator=(const A& a);*/
    int num2;
 
};

B::B(const A& a) :
A::A(a)
{
    num2 = 1;
    cout << __FUNCTION__ << " from A" << endl;
}

B& B::operator=(const A& a)
{
    A::operator=(a);
    num2 = 1;
    cout << __FUNCTION__ <<"from A" << endl;
    return *this;
}
// void B::operator=(const A& a)
// {
//     *(static_cast<B*>(this)) = a;
// }

int main(int argc, char* argv[])
{

    A testA("name",100);
    //A testA2 = testA;
//     B testB;
//     testB = testA;
    B testc = testA;
    return 0;
/* output: 

*/
}
