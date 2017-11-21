#include <memory> // and others
#include <iostream>
using namespace std;

class B; // forward declaration 
// for clarity, add explicit destructor to see that they are not called
class A { public: shared_ptr<B> b; ~A() { cout << "~A()" << endl; } };
class B { public: shared_ptr<A> a; ~B() { cout << "~B()" << endl; } };

void testPtrScope()
{
    shared_ptr<A> x = make_shared<A>();  //x->b share_ptr is default initialized
    x->b = make_shared<B>(); // you can't do "= new B" on shared_ptr                      
    x->b->a = x;
    cout << x.use_count() << endl;
}
int main()
{
    testPtrScope();
    return 0;
}
