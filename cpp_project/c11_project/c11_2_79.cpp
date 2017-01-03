/*************************************************************************
	> File Name: c11_2.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Sun 01 Jan 2017 01:18:43 AM PST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cstring>
class MyString{
private:
    char* m_data;
    size_t m_len;
    void copy_data(const char* s)
    {
        m_data = new char[m_len+1];
        memcpy(m_data, s, m_len);
        m_data[m_len] = '\0';
    }
public:
    MyString()
    {
        m_data = NULL;
        m_len = 0; 
    }
    MyString(const char* p)
    {
        m_len = strlen(p);
        copy_data(p);
    }
    MyString(const MyString& str)
    {
        m_len = str.m_len;
        copy_data(str.m_data);
        std::cout << __FUNCTION__ <<" lvalue "<< str.m_data << std::endl;
    }
    MyString& operator=(const MyString& str)
    {
        if(this != &str)
        {
            m_len = str.m_len;
            copy_data(str.m_data);
        }
        std::cout << __FUNCTION__ <<" lvalue "<< str.m_data << std::endl;
        return *this;

    }
    virtual ~MyString()
    {
        if(m_data)
            delete []m_data;
    }
    MyString(MyString&& str)
    {
        std::cout << __FUNCTION__ <<" rvalue "<< str.m_data << std::endl;
        m_len = str.m_len;
        m_data = str.m_data;
        str.m_len = 0;
        str.m_data = NULL;
    }
    MyString& operator=(MyString&& str)
    {
        std::cout << __FUNCTION__ <<" rvalue "<< str.m_data << std::endl;
        if(this != &str)
        {
            m_len = str.m_len;
            m_data = str.m_data;
            str.m_len = 0;
            str.m_data = NULL;
        }
        return *this;
    }

};

int main(int argc, char* argv[])
{
    MyString str;
    str = MyString("hello");
    std::vector<MyString> vec;
    vec.push_back(MyString("world"));
}
