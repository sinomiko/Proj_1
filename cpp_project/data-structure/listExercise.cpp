#include <iostream>
#include <string>
using namespace std;

struct Node
{
	int value;
	Node* next;
};

//尾部添加
Node* Add(int n, Node* head)
{
	Node * t = new Node;
	t->value = n;
	t->next = NULL;
	if (head == NULL) {
		head = t;
	}
	else if(head->next == NULL) {
		head->next = t;
	}
	else {
		Node * p = head->next;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = t;
	}
	return head;
}

void RecurcivePrint(Node* head)
{
	if (head == nullptr)
	{
		return;
	}
	cout << head->value << "\t";
	RecurcivePrint(head->next);
}

void ReversePrint(Node* head)
{
	if (head == nullptr)
	{
		return;
	}
	
	ReversePrint(head->next);
	cout << head->value << "\t";
}

Node* RevertList(Node** head)
{
	Node* p1 = nullptr;
	Node* p2 = nullptr;
	Node* p3 = nullptr;
	if (head == NULL || *head == nullptr)
	{
		return nullptr;
	}

	p1 = *head;
	p2 = (*head)->next;
	p1->next = nullptr;

	while (p2 != nullptr)
	{
		p3 = p2;
		p2 = p2->next;
		p3->next = p1;
		p1 = p3;
	}
	return p1;

}

//递归
Node * RecursiveReverseList(Node * p) {
	if (p == NULL || p->next == NULL) {
		return p;
	}

	Node * newHead = RecursiveReverseList(p->next);
	//返回的时候，p->next为前一个node
 	p->next->next = p;
	//防止前面两个node形成circle
 	p->next = NULL;
	return newHead;
}


int main(void)
{
	Node * head = nullptr;
	for (int i = 1; i <= 5; i++) {
		head = Add(i, head);
	}
	cout << "RecurcivePrint:" << endl;
	RecurcivePrint(head);
	cout << endl;

	cout << "ReversePrint:" << endl;
	ReversePrint(head);
	cout << endl;

	Node *revertedList = RevertList(&head);
	cout << "RevertList:" << endl;
	RecurcivePrint(revertedList);
	cout << endl;

	Node *revertedList2 = RecursiveReverseList(revertedList);
	cout << "RecursiveReverseList:" << endl;
	RecurcivePrint(revertedList2);
	cout << endl;

	system("pause");
	return 0;
}