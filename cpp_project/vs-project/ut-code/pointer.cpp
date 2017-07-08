#include<iostream>
#include<string>
using namespace std;
char *GetString2(void)
{
       char *p = "hello world";
		char *ptr=(char*)malloc(sizeof(char)*12);
		strcpy(ptr,p);
       return ptr;
	//char p[] = "hello world";
//	cout<<"strlen(p)"<<strlen(p)<<endl;
//	cout<<"sizeof(p)"<<sizeof(p)<<endl;
//	cout<<p<<endl;
//    return p; // 编译器将提出警告

}
void Test5(void)
{
        char *str = NULL;
        str = GetString2();
	    cout<<"strlen(str)"<<strlen(str)<<endl;
	    cout<<"sizeof(str)"<<sizeof(str)<<endl;
        cout<< str << endl;
}
int main(void){

        Test5();
		return 0;
}