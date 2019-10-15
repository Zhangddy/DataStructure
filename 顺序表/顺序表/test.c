#include "SeqList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	SeqList s;
	SeqListInit(&s, 10);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 3);
	SeqListPushBack(&s, 3);
	SeqListPushBack(&s, 9);
	SeqListPushBack(&s, 3);
	SeqListRemoveAll(&s, 3);
	SeqListPrint(&s);
	SeqListDestroy(&s);

	system("pause");
	return 0;
}
