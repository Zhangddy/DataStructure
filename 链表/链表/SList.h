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
// 用于保存链表, 但不是头结点!也不是第一个节点!
// _pHead指向第一个节点

void SListInit(SList* s);
void SListDestory(SList* s);
void SListPushBack(SList* s, SDataType data);
void SListPopBack(SList* s);
void SListPushFront(SList* s, SDataType data);
void SListPopFront(SList* s);
void SListInsert(PNode pos, SDataType data);
void SListErase(SList* s, PNode pos);
PNode SListFind(SList* s, SDataType data);
void SListRemove(SList* s, SDataType data);	// 移除链表中第一个内容为data的元素
void SListRemoveAll(SList* s, SDataType data);	// 移除链表中所有内容为data的元素
size_t SListSize(SList* s);
int SListEmpty(SList* s);
void PrintSList(SList* s);

void TestSlist();



