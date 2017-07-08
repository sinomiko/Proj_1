#include<string>
#include<iostream>
using namespace std;
struct ListNode{
	int value;
	struct ListNode* Next;
}ListNode;

int n=0;
typedef struct ListNode* List;

void init(List pHead)
{
	List p;
	p=(List)malloc(sizeof(ListNode));
	pHead=p;
	p->Next=NULL;
}

void insert(List pHead)
{
	
}
int main(int argc,char* argv[])
{
	List pHead=(List)malloc(sizeof(ListNode));
	n=0;
	List p,q;
	cout<<"please input the size of List"<<endl;
	cin>>n;
	p=pHead;q=p;
	pHead->Next=p;
	while (n)
	{
		p=(List)malloc(sizeof(ListNode));
		cout<<"please input the value"<<n<<endl;
		n--;
		cin>>p->value;
	    q->Next=p;
		q=q->Next;
	}
	q->Next=NULL;
	cout<<"the value n is"<<n<<endl;
	p=pHead->Next;
	while(p!=NULL)
	{
		cout<<"index"<<n++<<"-->"<<p->value<<endl;
		p=p->Next;
	}

	cout<<"please delete index:";
	cin>>n;
	cout<<n<<endl;
	p=pHead->Next;
	if(n==0)
	{
		pHead->Next=p->Next;
		free(p);
	
	}

	while(n-->=0)
	{
		q=p;
		p=p->Next;
		if(n==0)
		  q->Next=p->Next;;
	}

	n=0;
	p=pHead->Next;
	while(p!=NULL)
	{
		cout<<"index"<<n++<<"-->"<<p->value<<endl;
		p=p->Next;
	}
	
	return 0;


}