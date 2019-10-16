#pragma once
#include <stdio.h>
typedef int SDataType;

typedef struct SListNode
{
	SDataType _data;
	struct SListNode* _pNext;
}Node, *PNode;

typedef struct SList
{
	PNode _pHead;
}SList;
// ���ڱ�������, ������ͷ���!Ҳ���ǵ�һ���ڵ�!
// _pHeadָ���һ���ڵ�

void SListInit(SList* s);
void SListDestory(SList* s);
void SListPushBack(SList* s, SDataType data);
void SListPopBack(SList* s);
void SListPushFront(SList* s, SDataType data);
void SListPopFront(SList* s);
void SListInsert(PNode pos, SDataType data);
void SListErase(SList* s, PNode pos);
PNode SListFind(SList* s, SDataType data);
void SListRemove(SList* s, SDataType data);	// �Ƴ������е�һ������Ϊdata��Ԫ��
void SListRemoveAll(SList* s, SDataType data);	// �Ƴ���������������Ϊdata��Ԫ��
size_t SListSize(SList* s);
int SListEmpty(SList* s);
void PrintSList(SList* s);

void TestSlist();



