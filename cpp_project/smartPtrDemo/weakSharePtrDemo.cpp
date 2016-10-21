/*************************************************************************
	> File Name: weakSharePtrDemo.cpp
	> Author: Miko Song
	> Mail: xiaoming.song@ericsson.com 
	> Created Time: Wed 19 Oct 2016 02:30:53 AM PDT
 ************************************************************************/

#include<iostream>
#include<memory>

class A
{
public:
    A(int a)
    {
	m_a=a;
    }
    int getA()
    {
	return m_a;
    }
    

    int m_a;

};
std::shared_ptr<A> createSharedPtr()
{
   auto myShare = std::make_shared<A> (20);
   return myShare;

}

void testShared2Weak(std::weak_ptr<A> weak)
{
    auto weakTest=weak.lock();
    std::cout<<weakTest.get()->getA()<<std::endl;

}

int main()
{
    std::weak_ptr<A> myWeak = createSharedPtr();
    
    testShared2Weak(myWeak);    

    return 0;

}
