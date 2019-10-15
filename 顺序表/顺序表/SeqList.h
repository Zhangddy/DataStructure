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
int SeqListFind(PSeq ps, DataType data);
int SeqListSize(PSeq ps);
int SeqListCapacity(PSeq ps);
void SeqListClear(PSeq ps);
void SeqListRemove(PSeq ps, DataType data);
int SeqListEmpty(PSeq ps);
void SeqListDestroy(PSeq ps);
void CheckCapacity(PSeq ps);
void SeqListModify(PSeq ps, int pos, DataType data);
void SeqListPrint(PSeq ps);

/////////////////////////////////////
//������һЩ���ӹ���
void SeqListRemoveAll(PSeq ps, DataType data);
void SeqListBubbleSort(PSeq ps);