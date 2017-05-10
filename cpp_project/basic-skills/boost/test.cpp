/*************************************************************************
	> File Name: boost.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Wed 10 May 2017 01:04:39 AM PDT
 ************************************************************************/

#include<iostream>
#include <boost/thread.hpp>   
#include <iostream>   
     
void task1() {    

    std::cout << "This is task1!" << std::endl;   
}   
     
void task2() {    

    std::cout << "This is task2!" << std::endl;   
}   
     
int main (int argc, char ** argv) {   
    using namespace boost;    
    thread thread_1 = thread(task1);   
    thread thread_2 = thread(task2);   
     
 
    thread_2.join();   
    thread_1.join();   
    return 0;   
}   
