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

/*
#include <iostream>
#include <list>
using namespace std;
std::list<int> mylist;

void updateList(bool operation, int code, bool expire)
{
    if(!operation)
    {
        mylist.pop_front();
    }
    
    if(expire)
    {
        mylist.remove(code);
    }
    else
    {
        mylist.push_back(code);
    }
    
    if (mylist.empty())
    { 
        cout << " mylist is empty"<< endl;
        return;
    }
    else
    {
        cout << " code: "<< code;
        int curCode = mylist.front();
        cout << " send curCode: "<< curCode<< endl;
    }
    
  cout << "=== mylist contains:";
  for (list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
  {
    cout << ' ' << *it;
  }
  cout << " ==="<<endl<<endl;
}
int main ()
{

  updateList(true, 1, false);
  updateList(true, 2, false);
  updateList(false, 1, false);
  mylist.push_back(3);
  updateList(false, 2, false);
  updateList(false, 1, false);
  updateList(false, 3, false);
  updateList(false, 2, true);
  updateList(false, 1, true);
  updateList(false, 3, true);
  
  return 0;
}
*/

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
