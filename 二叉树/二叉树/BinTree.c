#include "BinTree.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

BTNode* BuyBinTeeNode(BTDataType data)
{
	BTNode* newBTNode = (BTNode*)malloc(sizeof(BTNode));
	if (NULL == newBTNode)
	{
		assert(0);
		return NULL;
	}
	newBTNode->_data = data;
	newBTNode->_pLeft = NULL;
	newBTNode->_pRight = NULL;
	return newBTNode;
}

BTNode* DealBinTreeCreate(char* array, int size, int* index, char invalid)
{
	BTNode* pRoot = NULL;
	if (*index < size && invalid != array[*index])
	{
		pRoot = BuyBinTeeNode(array[*index]);

		(*index)++;
		pRoot->_pLeft = DealBinTreeCreate(array, size, index, invalid);

		(*index)++;
		pRoot->_pRight = DealBinTreeCreate(array, size, index, invalid);
	}
	return pRoot;
}

BTNode* BinTreeCreate(char* array, int size, char invalid)
{
	//封装一层, 少写一个Index
	int index = 0;
	return DealBinTreeCreate(array, size, &index, invalid);
}

void BinTreeDestroy(BTNode** pRoot)
{
	// 因为无法改变根节点的指向, 故传二级指针
	assert(pRoot);
	// 销毁思想为后续遍历, 否则会丢失节点
	if (*pRoot)
	{
		BinTreeDestroy(&(*pRoot)->_pLeft);
		BinTreeDestroy(&(*pRoot)->_pRight);
		free(*pRoot);
		pRoot = NULL;
	}
}

void PreOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		printf("%c ", pRoot->_data);
		PreOrder(pRoot->_pLeft);
		PreOrder(pRoot->_pRight);
	}
}
void InOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		InOrder(pRoot->_pLeft);
		printf("%c ", pRoot->_data);
		InOrder(pRoot->_pRight);
	}
}

void PostOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		PostOrder(pRoot->_pLeft);
		PostOrder(pRoot->_pRight);
		printf("%c ", pRoot->_data);
	}
}

int BinTreeGetKLevelNodeCount(BTNode* pRoot, int k)
{
	if (NULL == pRoot || k <= 0)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return BinTreeGetKLevelNodeCount(pRoot->_pLeft, k - 1) +
		   BinTreeGetKLevelNodeCount(pRoot->_pRight, k - 1);
}

BTNode* BinTreeFind(BTNode* pRoot, BTDataType x)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	if (pRoot->_data == x)
	{
		return pRoot;
	}
	BTNode* pRet = NULL;

	if (pRet = BinTreeFind(pRoot->_pLeft, x))
	{
		return pRet;
	}
	return BinTreeFind(pRoot->_pRight, x);
}

int BinTreeGetHeight(BTNode* pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}

	int left = BinTreeGetHeight(pRoot->_pLeft);
	int right = BinTreeGetHeight(pRoot->_pRight);
	return (left > right) ? left + 1 : right + 1;
}


void test()
{
	char* str = "ABD###CE##F##";
	BTNode* tree = BinTreeCreate(str, strlen(str), '#');
	PreOrder(tree);
	putchar('\n');
	InOrder(tree);
	putchar('\n');

	PostOrder(tree);
	putchar('\n');
	printf("%d \n", BinTreeGetKLevelNodeCount(tree, 2));
	printf("%d \n", BinTreeGetHeight(tree));
	
	BinTreeDestroy(&tree);
}
