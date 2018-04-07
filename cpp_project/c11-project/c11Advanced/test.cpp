#include<memory>    //auto_ptr
#include<functional>//function  bind  placeholders
#include <iostream> // cout
#include <utility>  // move

#include <string>   // string

#include <algorithm>    // sort

#include <vector>   // vector
#include <array>    // array
#include <unordered_map>
#include <map>
#include <tuple>
#include <list>
using namespace std;

class View
{
public:
	void onClick(int x, int y)
	{
		cout << "X : " << x << ", Y : " << y << endl;
	}
};

class A {
	public:
		int *pointer;
		A():pointer(new int(1)) { cout << "construct "<< pointer << endl; }
		A(const A& a):pointer(new int(*a.pointer)) { cout << "copy construct "<< pointer << endl; }    //
		A(A&& a):pointer(a.pointer) { a.pointer = nullptr;cout << "move copy construct "<< pointer << endl; }
		~A(){ cout << "destructor " << pointer << endl; delete pointer; }
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
		cout << "left value"<<endl;
}

void reference(int&& v) {
		cout << "right value"<<endl;
}

template <typename T>
void pass(T&& v) {
	cout <<"comman parameter"<<endl;
	reference(v);
	cout << "move"<<endl;
	reference(move(v));
	cout << "forwaed"<<endl;
	reference(forward<T>(v));

}

void funvp(int *p, int len) {
		return;
}

auto get_student(int id)-> decltype(make_tuple(0.8, 'A', "zhangsan"))
{
	if (id == 0)
		return make_tuple(0.8, 'A', "zhangsan");
	if (id == 1)
		return make_tuple(1.8, 'B', "zhaosi");
	if (id == 2)
		return make_tuple(2.8, 'C', "wangwu");
	if (id == 3)
		return make_tuple(3.8, 'D', "zzhouliu");
	return make_tuple(0.0, 'D', "null"); 
}

template <typename T>
auto tuple_len(T &tpl) ->decltype(tuple_size<T>::value){
	return tuple_size<T>::value;
}

// template<typename T, typename ...Args>
// unique_ptr<T> make_unique( Args&& ...args ) {
//         return unique_ptr<T>( new T( forward<Args>(args)... ) );
// }

template <typename T>
void print(const T &t)
{
	cout << t<<endl;
}


template <typename T, typename...Args>
void print(const T &t, const Args&...rest)
{
	cout << t << " ";   
	print(rest...);      
}

template <typename C> void print(const string& s, const C& c) {
	cout << s;

	for (const auto& e : c) {
		cout << e << " ";
	}

	cout << endl;
}

void fillVector(vector<int>& v)
{
	// A local static variable.  
	static int nextValue = 1;

	// The lambda expression that appears in the following call to  
	// the generate function modifies and uses the local static   
	// variable nextValue.  
	generate(v.begin(), v.end(), [] { return nextValue++; });
	//WARNING: this is not thread-safe and is shown for illustration only  
}

function<void(View, int, int)> clickCallback;

int main(void){
	cout<<"begin"<<endl;
	auto important = make_shared<int>(1);
	
	auto add = [v1 =9, v2 = move(important)](int x, int y)->int{
		return  x+y+v1*(*v2);
	};
  
	auto foo=[](int x){
		cout<< x+9 <<endl;
	};

	cout << "======= lambda    ==============================="<< endl;
	cout<<"lambda out:"<<add(2,2)<<endl;
	foo(1);
	function<int(int)> bind_fu=bind(bind_func,placeholders::_1, 1,2);
	function<int(int)> func1 = func;
	
	cout<<__func__<<endl; 
	cout<<"func1:"<<func1(10)<<"\nbind_fu:"<<bind_fu(2)<<endl;
	 
	cout << "=======bind================================="<< endl;
	View button;
	clickCallback = &View::onClick;
	clickCallback(button, 10, 123);

	cout << "=======return_rvalue==============================="<< endl;
	A obj = return_rvalue(false);
	cout << "obj:" << endl;
	cout << obj.pointer << endl;
	cout << *obj.pointer << endl;

	cout << "=======move=================================="<< endl;  
	A obj_a;
	vector<A> v;
	//string obj_a = "Hello world.";
	//vector<string> v;
	cout << "obj_a: " << obj_a.pointer << endl;
	v.push_back(obj_a);
	cout <<"v.push_back(obj_a)" << "obj_a: " << obj_a.pointer << endl;
	v.push_back(move(obj_a));
	cout <<"v.push_back(move(obj_a))"<< "obj_a: " << obj_a.pointer << endl;

	cout << "=======forward=================================="<< endl;
	cout << "right value begin"<<endl;
	pass(1);
	cout << "left value begin"<<endl;
	int value = 1;
	pass(value);
	cout << "=======array=================================="<< endl;

	array<int, 4> arr = {1,2,3,4};

	funvp(&arr[0], arr.size());
	funvp(arr.data(), arr.size());
	
	sort(arr.begin(), arr.end());
	cout << "=======map=================================="<< endl;
	unordered_map<int, string> unorder_map = {
		{1, "1"},
		{3, "3"},
		{2, "2"}
	};

	map<int, string> map1 = {
		{1, "1"},
		{3, "3"},
		{2, "2"}
	};

	cout << "unordered_map" << endl;
	
	for( const auto & n : unorder_map) 
		cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

	cout << endl;
	cout << "map" << endl;
	
	for( const auto & n : map1) 
		cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

	cout << "=======tuple=================================="<< endl;
	auto student = get_student(0);
	cout<<" "<<get<0>(student)<<" "<<get<1>(student)<<" "<<get<2>(student)<<endl;
	
	double gpa;
	char grade;
	string name;
	tie(gpa, grade, name) = get_student(1);
	cout<<" "<<gpa<<" "<<grade<<" "<<name<<endl;

	tuple<double, char, string> t(3.8, 'D', "zzhouliu");
	auto new_tuple = tuple_cat(get_student(1), move(t));
	for( unsigned int i = 0; i != tuple_len(new_tuple); ++i)
		cout <<get<1>(new_tuple) << endl;
	
	cout << "=======variable template parameter========================="<< endl;
	print("string1", 2, 3.14f, "string2", 42);
	
	list<int> la;
	//la.splice;
	/*
	cout << "=======shared_ptr unique_ptr weak_ptr======================"<< endl;
	unique_ptr<int> pointer = make_unique<int>(10); 
	
	cout << "=======map=================================="<< endl;
	*/
	/*
	// The number of elements in the vector.  
	const int elementCount = 9;

	// Create a vector object with each element set to 1.  
	vector<int> v(elementCount, 1);

	// These variables hold the previous two elements of the vector.  
	int x = 1;
	int y = 1;

	// Sets each element in the vector to the sum of the   
	// previous two elements.  
	generate_n(v.begin() + 2,
		elementCount - 2,
		[=]() mutable throw() -> int { // lambda is the 3rd parameter  
		// Generate current value.  
		int n = x + y;
		// Update previous two values.  
		x = y;
		y = n;
		return n;
	});
	print("vector v after call to generate_n() with lambda: ", v);

	// Print the local variables x and y.  
	// The values of x and y hold their initial values because   
	// they are captured by value.  
	cout << "x: " << x << " y: " << y << endl;

	// Fill the vector with a sequence of numbers  
	fillVector(v);
	print("vector v after 1st call to fillVector(): ", v);
	// Fill the vector with the next sequence of numbers  
	fillVector(v);
	print("vector v after 2nd call to fillVector(): ", v);
*/
    getchar();
	return 0;

}
