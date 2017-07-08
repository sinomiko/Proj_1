#include <stdlib.h> //需要用到C式内存分配函数
#include<iostream>
class Resource{
public:
	Resource()
	{
		m_num=0;
	}
	Resource(int num)
	{
		m_num=num;
	}
	void setNum(int num)
	{
		m_num=num;
	}
	void printNum()const
	{
		std::cout<<m_num<<std::endl;
	}
private:
	int m_num;
}; //代表需要被封装的资源类
class NoHashObject
{
private:
	Resource* ptr ;//指向被封装的资源
	void* operator new(size_t size) //非严格实现，仅作示意之用
	{
			return malloc(size) ;
	}
	void operator delete(void* pp) //非严格实现，仅作示意之用
	{
		free(pp) ;
	}
public:
	NoHashObject()
	{
		//此处可以获得需要封装的资源，并让ptr指针指向该资源
		ptr = new Resource() ;
	}
	~NoHashObject()
	{
		delete ptr ; //释放封装的资源
	}
	void setResource(int num)
	{
		ptr->setNum(num);
	}
	void printResource()const
	{
		ptr->printNum();
	}
};

int main(void)
{
//NoHashObject现在就是一个禁止堆对象的类了，如果你写下如下代码：
//	NoHashObject* fp = new NoHashObject() ; //编译期错误！
//	delete fp ;

	char* temp = new char[sizeof(NoHashObject)] ;
//强制类型转换，现在ptr是一个指向NoHashObject对象的指针
	NoHashObject* obj_ptr = (NoHashObject*)temp ;
	temp = NULL ; //防止通过temp指针修改NoHashObject对象
//再一次强制类型转换，让rp指针指向堆中NoHashObject对象的ptr成员
	Resource* rp = (Resource*)obj_ptr ;
//初始化obj_ptr指向的NoHashObject对象的ptr成员
	rp = new Resource() ;
//现在可以通过使用obj_ptr指针使用堆中的NoHashObject对象成员了
	rp->setNum(4);
//	rp->printNum();
//	obj_ptr->setResource(4);
	obj_ptr->printResource();
	delete rp ;//释放资源
	temp = (char*)obj_ptr ;
	obj_ptr = NULL ;//防止悬挂指针产生
	delete [] temp ;//释放NoHashObject对象所占的堆空间。
}