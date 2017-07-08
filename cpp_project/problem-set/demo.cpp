#include <iostream>
using namespace std;

class MyType {
public:
	MyType(int a, int b) :m_a(a), m_b(b) {
		cout << "constructor with parameters" << endl;
	}
	int operator >(const MyType &mt){ 
		return 0;;
	}
	bool operator<(const MyType &a) const{
		if (m_a < a.m_a)
		{
			return true;
		}
		else
		{
			if (m_a == a.m_a &&m_b < a.m_b) {
				return true;
			}
		}
		return false;
	}

	friend ostream& operator<< (ostream &os, const MyType &my)
	{
		os << "m_a: " << my.m_a << " ------ " << "m_b: " << my.m_b << endl;
		return os;
	}
private:
	int m_a;
	int m_b;
};

int main()
{
	MyType ma(1, 2);
	const MyType mb(2, 1);
	cout << "ma:" << ma << endl;
	cout << "mb:" << mb << endl;
	bool result = ma < mb;
	cout << result << endl;
	return 0;

}