#include "Array.h"
#include "Coordinator.h"
using namespace std;
int main(int argc, char *argv[])
{
	Array<int, 10> myArray;
	myArray.push(1);
	myArray.push(2);
	myArray.push(3);
	myArray.push(4);
	myArray.push(5);
	myArray.push(6);
	myArray.display();
	cout<<"================"<<endl;


	Array<int, 10>*  pMyArray=new Array<int, 10>;
	pMyArray->push(2);
	pMyArray->push(3);
	pMyArray->push(4);
	pMyArray->push(5);
	pMyArray->push(6);
	pMyArray->display();
	cout<<"****************"<<endl;


	Array<Coordinator, 10>*  pMyArrayCood=new Array<Coordinator, 10>;
	Coordinator cood1(1,1);
	Coordinator cood2(2,2);
	Coordinator cood3(3,3);
	pMyArrayCood->push(cood1);
	pMyArrayCood->push(cood2);
	pMyArrayCood->push(cood3);
	pMyArrayCood->pop();
	pMyArrayCood->display();

	cout<<"----------------"<<endl;
	system("pause");

	return 0;
}