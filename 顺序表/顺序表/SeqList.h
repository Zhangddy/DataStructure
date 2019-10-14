#pragma once

// ˳���ṹ:
// ����
// ��̬˳���: 
#if 0
typedef int DataType;
#define MAX_SIZE 100

struct SeqList
{
	DataType _array[MAX_SIZE];	// �����洢˳����е�Ԫ��
	size_t _size;	// ˳�������Ч�ռ�ĸ���
};
#endif

// ��̬��˳���
typedef int DataType;

typedef struct SeqList
{
	DataType* _array;
	int _capacity;	// ˳�����ܴ�С
	int _size;		// ˳�������ЧԪ�صĸ���
}SeqList, *PSeq;

void SeqListInit(PSeq ps, int capacity);
void SeqListPushBack(PSeq ps, DataType data);
void SeqListPopBack(PSeq ps);
void SeqListPushFront(PSeq ps, DataType data);
void SeqListPopFront(PSeq ps);
void SeqListInsert(PSeq ps, int pos, DataType data);
void SeqListErase(PSeq ps, int pos);
int SeqListEmpty(PSeq ps);
void SeqListDestroy(PSeq ps);
void SeqListPrint(PSeq ps);