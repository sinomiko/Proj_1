#include <iostream>
#include <memory>
#include <vector>
#define  TREELEN 6
using namespace std;

struct TreeNode
{
	char val;
	TreeNode* left;
	TreeNode* right;
};

void PreOrderVisit(TreeNode* pRoot)
{
	if (pRoot==nullptr)
	{
		return;
	}
	cout << pRoot->val << "\t";
	if (pRoot->left)
	{
		PreOrderVisit(pRoot->left);
	}
	if (pRoot->right)
	{
		PreOrderVisit(pRoot->right);
	}
}

void InOrderVisit(TreeNode* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	if (pRoot->left)
	{
		InOrderVisit(pRoot->left);
	}
	cout << pRoot->val << "\t";
	if (pRoot->right)
	{
		InOrderVisit(pRoot->right);
	}
}

void PostOrderVisit(TreeNode* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	if (pRoot->left)
	{
		PostOrderVisit(pRoot->left);
	}
	if (pRoot->right)
	{
		PostOrderVisit(pRoot->right);
	}
	cout << pRoot->val << "\t";
}

void RebuildTree(char* pPreOrder, char* pInOrder, int nTreeLen, TreeNode** pRoot)
{
    //检查条件
	if (pPreOrder == nullptr || pInOrder == nullptr)
	{
		return;
	}
    //设置根节点
	TreeNode* pTmp = new TreeNode;
	pTmp->val = *pPreOrder;
	pTmp->left = nullptr;
	pTmp->right = nullptr;

	if (*pRoot == nullptr )
	{
		*pRoot = pTmp;
	}

	if (nTreeLen == 1)
	{
		return;
	}

    //找出左子树长度，同理得到右子树长度
	char* pleftEnd = pInOrder;
	int nTmpLen = 0;

	while (*pPreOrder != *pleftEnd)
	{
		if (pPreOrder == nullptr ||pleftEnd == nullptr)
		{
			return;
		}
		nTmpLen++;

		if (nTmpLen > nTreeLen)
		{
			break;
		}
		pleftEnd++;
	}

	int nleftLen = 0;
	nleftLen = nTmpLen;

	int nrightLen = 0;
	nrightLen = nTreeLen - nTmpLen - 1;

    //重构左子树
	if (nleftLen>0)
	{
		RebuildTree(pPreOrder + 1, pInOrder, nleftLen, &((*pRoot)->left));
	}
    //重构优子树
	if (nrightLen>0)
	{
		RebuildTree(pPreOrder + nleftLen + 1, pInOrder + nleftLen + 1, nrightLen, &((*pRoot)->right));
	}
}

int PrintTreeNodeAtLevel(TreeNode* pRoot, int level)
{
	if (!pRoot || level <0)
	{
		return 0;
	}
	if (level ==0)
	{
		cout << pRoot->val << "\t";
		return 1;
	}

	return PrintTreeNodeAtLevel(pRoot->left, level - 1) + PrintTreeNodeAtLevel(pRoot->right, level - 1);
}

int PrintTreeNodeByLevel(TreeNode* pRoot, int depth)
{
	for (int level = 0 ; level< depth; level++)
	{
		PrintTreeNodeAtLevel(pRoot, level);
		cout << endl;
	}

	return 0;
}

void PrintTreeNodeByLevel(TreeNode* pRoot)
{
    for (int i = 0;; i++)
    {
        if (!PrintTreeNodeAtLevel(pRoot, i))
        {
            break;
        }
        cout << endl;
    }
}



/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
    struct TreeNode* trimBST(struct TreeNode* root, int L, int R) {
        bool notFound = 0;
        if (root)
        {
            if (root->val < L) {
                root = root->right;
                notFound = 1;
            }
            else if (root->val > R) {
                root = root->left;
                notFound = 1;
            }

            if (notFound) {
                root = trimBST(root, L, R);
            }

            if (root) {
                root->left = trimBST(root->left, L, R);
                root->right = trimBST(root->right, L, R);
            }
        }
        return root;
    }
    int TreeNodeAtLevel(TreeNode* pRoot, int level, double& avg, int& num)
    {
        if (!pRoot || level < 0)
        {
            return 0;
        }

        if (level == 0)
        {
            num++;
            avg = (avg + pRoot->val) / num;
            return 1;
        }
        return TreeNodeAtLevel(pRoot->left, level - 1, avg, num) + TreeNodeAtLevel(pRoot->right, level - 1, avg, num);
    }
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ret;
        for (int i = 0;; i++)
        {
            double avg = 0;
            int num = 0;
            if (!TreeNodeAtLevel(root, i, avg, num))
            {
                break;
            }
            else {
                ret.push_back(avg);
            }
        }
        return ret;
    }
};

int main()
{
	char preOder[TREELEN] = {'a','b','d','c','e','f'};
	char pInOrder[TREELEN] = {'d','b','a','e','c','f'};
	TreeNode* pRoot = nullptr;
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
	cout << "PrintTreeNodeByLevel" << endl;
	PrintTreeNodeByLevel(pRoot);
	return 0;
}