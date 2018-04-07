#include <memory> // and others
#include <map>
#include <iostream>
using namespace std;

class B; // forward declaration 
		 // for clarity, add explicit destructor to see that they are not called
class A { public: shared_ptr<B> b; ~A() { cout << "~A()" << endl; } };
class B { public: weak_ptr<A> a; ~B() { cout << "~B()" << endl; } };

void testPtrScope()
{
	shared_ptr<A> x = make_shared<A>();  //x->b share_ptr is default initialized
	x->b = make_shared<B>(); // you can't do "= new B" on shared_ptr                      
	x->b->a = x;
	cout << x.use_count() << endl;
}

class BB;
class AA : public enable_shared_from_this<AA>
{
public:
	AA();
	void Add(int index)
	{
		shared_ptr<BB> newB = make_shared<BB>(dynamic_pointer_cast<AA>(shared_from_this()));
		testMap[index] = newB;
	}
	~AA();

private:
	//map<int, weak_ptr<BB>> testMap;//no memory leak
    map<int, shared_ptr<BB>> testMap;//memory leak
};

AA::AA()
{
	cout << "AA()" << endl;
}

AA::~AA()
{
	cout << "~AA()" << endl;
}

class BB
{
public:
	BB(shared_ptr<AA> a);
	~BB();

private:
	shared_ptr<AA> m_a;
};

BB::BB(shared_ptr<AA> a)
	:
	m_a(a)
{
	cout << "BB()" << endl;
}

BB::~BB()
{
	cout << "~BB()" << endl;
}

void testSharedtr()
{
	auto testA = make_shared<AA>();
	testA->Add(1);
	testA->Add(2);
	testA->Add(3);
}

template <typename T>
class TD;
int main()
{
	//testPtrScope();
	testSharedtr();
    getchar();
	return 0;
}
