#include<iostream>  
using namespace std;

class A
{
public:
    A(int a);
    void foo()
    {
        vfun();
        printf("1\n");
    }
    virtual void vfun()
    {
        printf("A::vfun:2\n");
    }
protected:
    int m_a;

};

A::A(int a)
    :
    m_a(a)
{
    printf("A::A\n");

}

class B : public A
{
public:
    B(int);
    // 	void foo()
    // 	{
    // 		vfun();
    // 		printf("3\n");
    // 	}
    void vfun()
    {
        printf("B::vfun:4\n");
    }
    int getMember()
    {
        return m_a;
    }
};

B::B(int b)
    :
    A(b)
{

}

int main(void)
{
    A a(1);
    B b(2);
    A *p = &a;
    p->foo();
    p->vfun();
    printf("=====================\n");
    p = &b;
    p->foo();
    p->vfun();

    printf("=====================\n");
    a.foo();
    printf("=====================\n");
    b.foo();
    printf("B:a:%d\n", b.getMember());
    return 0;
}
/*output:

A::vfun:2
1
A::vfun : 2
== == == == == == == == == == =
B::vfun : 4
1
B::vfun : 4
== == == == == == == == == == =
A::vfun : 2
1
== == == == == == == == == == =
B::vfun : 4
1

*/
