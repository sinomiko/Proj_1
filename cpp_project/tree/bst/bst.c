/*************************************************************************
	> File Name: bst.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Mon 01 May 2017 07:37:21 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <time.h> 

typedef struct Node{
int data;
struct Node *leftChild;
struct Node *rightChild;
}Node;

void insert(Node** root, int data)
{
    Node *tmpNode=(Node *)malloc(sizeof(Node));
    Node *current=NULL;
    Node *parent=NULL;
    tmpNode->data=data;
    tmpNode->leftChild=NULL;
    tmpNode->rightChild=NULL;

    if(*root==NULL)
        *root=tmpNode;
    else{
        current=*root;
        while(1){
            parent=current;
            if(data<parent->data){
                current=current->leftChild;
                if(current==NULL){
                    parent->leftChild=tmpNode;
                    return;
                }

            }
            else if(data>parent->data){
                current=current->rightChild;
                if(current==NULL){
                    parent->rightChild=tmpNode;
                    return;
                }
            }
            else{
                printf("equal numer:%d found in tree\n",data);
                return;
            }
        }
    }

}

void recursiveInsert(Node **root, int data)
{
    if(*root==NULL){
        Node *tmpNode=(Node *)malloc(sizeof(Node));
        tmpNode->data=data;
        tmpNode->leftChild=NULL;
        tmpNode->rightChild=NULL;
        *root=tmpNode;

    }
    else
    {
        if(data < (*root)->data) recursiveInsert(&((*root)->leftChild), data);
        else if(data >(*root)->data) recursiveInsert(&((*root)->rightChild), data);
        else return;
    }

}

Node *recursivesearch(Node* root, int data)
{
    if(root==NULL)
        return NULL;
    else if(root->data==data)
        return root;
    else{
        if(data<root->data)
          return  recursivesearch(root->leftChild,data);
        else
          return  recursivesearch(root->rightChild,data);
    }
}

void preOrderTraversal(Node* root)
{
    if(root==NULL){
        return;
    }
    printf("%lu:%d \n",root, root->data);
    preOrderTraversal(root->leftChild);
    preOrderTraversal(root->rightChild);
}

void postOrderTraversal(Node* root)
{
    if(root==NULL){
        return;
    } 
    postOrderTraversal(root->leftChild);
    postOrderTraversal(root->rightChild);
    printf("%lu:%d \n",root, root->data);
}

void inOrderTraversal(Node* root)
{
    if(root==NULL){
        return;
    }
    inOrderTraversal(root->leftChild);
    printf("%lu:%d \n",root, root->data);
    inOrderTraversal(root->rightChild);
} 

int size(Node* root)
{
     if(root==NULL){
         return 0;
     }
     return 1+size(root->leftChild)+size(root->rightChild);
}

int maxDepth(Node* root)
{
    if(root==NULL){
         return 0;
    }

    int l_depth=1+maxDepth(root->leftChild);
    int r_depth=1+maxDepth(root->rightChild);
    if(l_depth<r_depth) return r_depth;
    else return l_depth;
}

void mirror(Node** root)
{
    if(*root==NULL){
        return;
    }
    mirror(&((*root)->leftChild));
    mirror(&((*root)->rightChild));

    Node* tmpNode;
    tmpNode=(*root)->leftChild;
    (*root)->leftChild=(*root)->rightChild;
    (*root)->rightChild=tmpNode;
}

bool isBST(Node* root)
{
    if(root==NULL){
        return true;
    }
    if(root->leftChild!=NULL){
        if(root->leftChild->data<root->data)
            isBST(root->leftChild);
        else return false;
    }
    if(root->rightChild!=NULL)
    {
        if(root->rightChild->data<root->data){
            isBST(root->rightChild);
        }
        else return false;
    }
    return true;
}

int main(void)
{   int irand;
    srand (time(NULL));
    Node* root=NULL;
    for(int i=0;i<20;i++){
        irand=rand() % 20; 
        printf("%d \n",irand);
        recursiveInsert(&root,irand);
    }
    printf("preOrderTraversal--------------------\n");
    preOrderTraversal(root);
    printf("postOrderTraversal--------------------\n");
    postOrderTraversal(root);
    printf("inOrderTraversal--------------------\n");
    inOrderTraversal(root);
    printf("recursivesearch--------------------\n");
    if(recursivesearch(root, 10)!=NULL)
        printf("found 10 \n");     

    printf("size of tree:%d \n",size(root));    
    printf("maxDepth :%d \n",maxDepth(root));
    printf("isBst--------------------\n");
    if(isBST(root))
         printf("isBst correct \n");
    else
         printf("isBst wrong \n");
    mirror(&root);
    preOrderTraversal(root);
    return 0;       
}
