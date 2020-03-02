#include <cassert>
#include <iostream>
using namespace std;
#include "AVLTree.h"

int main()
{
	//int arr[] = {5,3,4,1,7,8,2,6,0,9};
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14, };
	AVLTree<int> a;

	for (auto& e : arr)
	{
		a.insert(e);
	}

	cout << a.IsBalance() << endl;;
	return 0;
}