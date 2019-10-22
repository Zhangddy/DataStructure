#pragma once

// 二叉树的链式存储方式---孩子表示法
// 二叉树的非递归遍历在c++中使用stack最好
typedef char BTDataType;

typedef struct BTNode
{
	struct BTNode* _pLeft;
	struct BTNode* _pRight;
	BTDataType _data;
}BTNode;

BTNode* BinTreeCreate(char* array, int size, char invalid);

void BinTreeDestroy(BTNode** pRoot);
void PreOrder(BTNode* pRoot);
void InOrder(BTNode* pRoot);
void PostOrder(BTNode* pRoot);

BTNode* BinTreeCopy(BTNode* pRoot);
int BinTreeGetSize(BTNode* pRoot);
int BinTreeGetKLevelNodeCount(BTNode* pRoot, int k);
int BinTreeGetLeafCount(BTNode* pRoot);
int BinTreeGetHeight(BTNode* pRoot); // 求深度
BTNode* BinTreeFind(BTNode* pRoot, BTDataType x);



void test();