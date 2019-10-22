#pragma once

// ����������ʽ�洢��ʽ---���ӱ�ʾ��
// �������ķǵݹ������c++��ʹ��stack���
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
int BinTreeGetHeight(BTNode* pRoot); // �����
BTNode* BinTreeFind(BTNode* pRoot, BTDataType x);



void test();