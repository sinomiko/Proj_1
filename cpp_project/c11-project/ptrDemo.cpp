#include <string>
#include <iostream>
#include <memory>
using namespace std;
class Test
{
public:
	Test(string s)
	{
		str = s;
		cout<<"Test creat\n";
	}
	~Test()
	{
		cout<<"Test delete:"<<str<<endl;
	}
	string& getStr()
	{
		return str;
	}
	void setStr(string s)
	{
		str = s;
	}
	void print()
	{
		cout<<str<<endl;
	}
private:
	string str;
};


#include<stdio.h>                                                                                                                                                      
typedef struct tableVport {                                                                                                                                                
	int dz_id;                                                                                                                                                         
	int dp_id;                                                                                                                                                         
	int vport_id;                                                                                                                                                      

	tableVport *next;                                                                                                                                         
}tableVport;                                                                                                                                                                 
	

/*
static struct tableVport* new_table_vport()                                                                                                                       
{                                                                                                                                                                 
    struct tableVport *table_vport = (struct tableVport *)malloc(sizeof(struct tableVport));                                                                      
    if (!table_vport) {                                                                                                                                           
//        LTT_LOG(ERROR,VNET,"new_table_vport failed\n");                                                                                                         
        return NULL;                                                                                                                                              
    }                                                                                                                                                             
                                                                                                                                                                  
    memset(table_vport, 0, sizeof(struct tableVport));                                                                                                           
    return table_vport;                                                                                                                                           
}   

                                                                                                                                                                  
void main(void)                                                                                                                                                   
{                                                                                                                                                                 
    struct tableVport* table_vport[16];                                                                                                                           
    int i = 0;                                                                                                                                                    
    for( ; i < 16; i++)                                                                                                                                           
    {                                                                                                                                                             
        table_vport[i]=new_table_vport();                                                                                                                         
    }                                                                                                                                                             
}                                                                                                                                                                 
	          
*/

void new_table_vport(tableVport *table_vport[16])                                                                                                                       
{   
	int i = 0;                                                                                                                                                    
	for( ; i < 16; i++)                                                                                                                                           
	{                                                                                                                                                             
		table_vport[i]=(tableVport *)malloc(sizeof(tableVport));  
		if (!table_vport[i]) {                                                                                                                                           
			//        LTT_LOG(ERROR,VNET,"new_table_vport failed\n");                                                                                                                                                                                                                                                      
		}                                                                                                                                                             
		memset(table_vport[i], 0, sizeof(tableVport));    
	}	                                                                	                                                                                                                                                                                                                                             
}   

void free_table_vport(tableVport *table_vport[16])                                                                                                                       
{   
	int i = 0;                                                                                                                                                    
	for( ; i < 16; i++)                                                                                                                                           
	{                                                                                                                                                             
		free(table_vport[i]); 
	}	                                                                	                                                                                                                                                                                                                                             
}   


void main(void)                                                                                                                                                   
{                                                                                                                                                                 
	tableVport* table_vport[16];                                                                                                                           
    new_table_vport(table_vport);  
	printf("begin \n");
	free_table_vport(table_vport);
	printf("over \n");
}  

/*
int main()
{

	auto_ptr<Test> ptest(new Test("123"));
	ptest->setStr("hello ");
	ptest->print();
	ptest.get()->print();
	ptest->getStr() += "world !";
	(*ptest).print();
	ptest.reset(new Test("123"));
	ptest->print();

	shared_ptr<Test> share_ptest(new Test("123"));
	shared_ptr<Test> share_ptest2(new Test("456"));
	cout<<share_ptest2->getStr()<<endl;
	cout<<share_ptest2.use_count()<<endl;
	share_ptest = share_ptest2;//"456"引用次数加1，“123”销毁
	ptest->print();
	cout<<share_ptest2.use_count()<<endl;//2
	cout<<share_ptest.use_count()<<endl;//2
	ptest.reset();
	share_ptest2.reset();//此时“456”销毁
	cout<<"done !\n";

	return 0;
}
*/