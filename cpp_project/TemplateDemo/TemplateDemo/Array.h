#include <iostream>
using namespace std;

template <typename T, int size>
class Array
{
public:
	Array();
	void display() const;
	bool push(T mem);
	T pop();
	~Array();
private:
	int m_size;
	int m_length;
	T*  m_pMem;
};

template <typename T, int size>
Array<T,size>::Array()
{
	m_size=size;
	m_length=0;
	m_pMem=new T[m_size];
 
}

template <typename T, int size>
Array<T,size>::~Array()
{

	delete []m_pMem;

}

template <typename T, int size>
void Array<T,size>::display() const
{
	cout<<"display====================================="<<endl;
	for (int i=0;i<m_length;i++)
	{
		cout<<m_pMem[i]<<endl;
	}
	

}

template <typename T, int size>
bool Array<T,size>::push(T mem)
{
	if (m_length>m_size)
	{
		return false;
	}

	m_pMem[m_length]=mem;
	m_length++;

	return true;
}

template <typename T, int size>
T Array<T,size>::pop()
{
	if (m_length< 0)
	{
		return  NULL;
	}

	T tmp=m_pMem[--m_length];
	cout<<m_pMem[m_length]<<endl;
	m_pMem[m_length]=NULL;
	return tmp;
}