#include <iostream>
#include <memory>
#define  TREELEN 6
using namespace std;

struct Node
{
	char value;
	Node* Left;
	Node* Right;
};

void PreOrderVisit(Node* pRoot)
{
	if (pRoot==nullptr)
	{
		return;
	}
	cout << pRoot->value << "\t";
	if (pRoot->Left)
	{
		PreOrderVisit(pRoot->Left);
	}
	if (pRoot->Right)
	{
		PreOrderVisit(pRoot->Right);
	}
}

void InOrderVisit(Node* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	if (pRoot->Left)
	{
		InOrderVisit(pRoot->Left);
	}
	cout << pRoot->value << "\t";
	if (pRoot->Right)
	{
		InOrderVisit(pRoot->Right);
	}
}

void PostOrderVisit(Node* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	if (pRoot->Left)
	{
		PostOrderVisit(pRoot->Left);
	}
	if (pRoot->Right)
	{
		PostOrderVisit(pRoot->Right);
	}
	cout << pRoot->value << "\t";
}

void RebuildTree(char* pPreOrder, char* pInOrder, int nTreeLen, Node** pRoot)
{
	if (pPreOrder == nullptr || pInOrder == nullptr)
	{
		return;
	}
	Node* pTmp = new Node;
	pTmp->value = *pPreOrder;
	pTmp->Left = nullptr;
	pTmp->Right = nullptr;

	if (*pRoot == nullptr )
	{
		*pRoot = pTmp;
	}

	if (nTreeLen == 1)
	{
		return;
	}

	char* pOrgpInOrder = pInOrder;
	char* pLeftEnd = pInOrder;
	int nTmpLen = 0;

	while (*pPreOrder != *pLeftEnd)
	{
		if (pPreOrder == nullptr ||pLeftEnd == nullptr)
		{
			return;
		}
		nTmpLen++;

		if (nTmpLen > nTreeLen)
		{
			break;
		}
		pLeftEnd++;
	}

	int nleftLen = 0;
	nleftLen = nTmpLen;

	int nRightLen = 0;
	nRightLen = nTreeLen - nTmpLen - 1;

	if (nleftLen>0)
	{
		RebuildTree(pPreOrder + 1, pInOrder, nleftLen, &((*pRoot)->Left));
	}
	if (nRightLen>0)
	{
		RebuildTree(pPreOrder + nleftLen + 1, pInOrder + nleftLen + 1, nRightLen, &((*pRoot)->Right));
	}
}

int PrintNodeAtLevel(Node* pRoot, int level)
{
	if (!pRoot || level <0)
	{
		return 0;
	}
	if (level ==0)
	{
		cout << pRoot->value << "\t";
		return 1;
	}

	return PrintNodeAtLevel(pRoot->Left, level - 1) + PrintNodeAtLevel(pRoot->Right, level - 1);
}

int PrintNodeByLevel(Node* pRoot, int depth)
{
	for (int level = 0 ; level< depth; level++)
	{
		PrintNodeAtLevel(pRoot, level);
		cout << endl;
	}

	return 0;
}

void PrintNodeByLevel(Node* pRoot)
{
for (int i=0;;i++)
{
	if (!PrintNodeAtLevel(pRoot, i))
	{
		break;
	}
	cout << endl;
}
}
int main()
{
	char preOder[TREELEN] = {'a','b','d','c','e','f'};
	char pInOrder[TREELEN] = {'d','b','a','e','c','f'};
	Node* pRoot = nullptr;
	RebuildTree(preOder, pInOrder, TREELEN, &pRoot);
	cout <<"PreOrderVisit"<< endl;
	PreOrderVisit(pRoot);
	cout << endl;
	cout << "InOrderVisit" << endl;
	InOrderVisit(pRoot);
	cout << endl;
	cout << "PostOrderVisit" << endl;
	PostOrderVisit(pRoot);
	cout << endl;
	cout << "PrintNodeByLevel" << endl;
	PrintNodeByLevel(pRoot);
	return 0;
}