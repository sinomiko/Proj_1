#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#define PRINT_CSTR(no) printf("cstr" #no " addr:\t%p\n",cstr##no)
#define PRINT_T_CSTR(no) printf("t_cstr" #no " addr:\t%p\n",t_cstr##no)

int main()
{
    stringstream ss("012345678901234567890123456789012345678901234567890123456789");
    stringstream t_ss("abcdefghijklmnopqrstuvwxyz");
    string str1(ss.str());

    const char* cstr1 = str1.c_str();
    const char* cstr5 = str1.c_str();
    const char* cstr2 = ss.str().c_str();
    const char* cstr3 = ss.str().c_str();
    const char* cstr4 = ss.str().c_str();
    const char* t_cstr = t_ss.str().c_str();

    cout << "------ The results ----------" << endl
        << "cstr1:\t" << cstr1 << endl
        << "cstr2:\t" << cstr2 << endl
        << "cstr3:\t" << cstr3 << endl
        << "cstr4:\t" << cstr4 << endl
        << "t_cstr:\t" << t_cstr << endl
        << "-----------------------------" << endl;
    printf("\n------ Char pointers ----------\n");
    PRINT_CSTR(1);
    PRINT_CSTR(5);
    PRINT_CSTR(2);
    PRINT_CSTR(3);
    PRINT_CSTR(4);
    PRINT_T_CSTR();

    return 0;
}