#include "BST.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include <stdbool.h>

typedef struct tEntry {
	Pointer key;
	Pointer value;
} Sdata;

int Sdatacmp(const void* x, const void* y)
{
	Sdata* a = (Sdata*)x;
	Sdata* b = (Sdata*)y;
	return (a->key > b->key) - (a->key < b->key);
}

CmpFunc* cmp_func(Pointer data1, Pointer data2)
{
	if (data1 > data2)return 1;
	if (data1 < data2)return -1;
	if (data1 = data2)return 0;
}

void fu(Pointer data1, Pointer data2)
{
	printf("%d ", (int)data1 + (int)data2);
}

int main(void)
{
	BST* testTree;
	int(*cmp)(void* x, void* y) = Sdatacmp;
	Sdata rooter = { 5, "sobaka" };
	Sdata l1 = { 2, "pes" };
	Sdata r1 = { 0, "Stepa" };
	Sdata l2 = { 20, "pes" };
	Sdata r2 = { 11, "delete" };
	Sdata r10 = { 10, "delete" };
	Sdata r3 = { 40, "pes" };
	Sdata r4 = { 17, "Stepa" };
	Sdata r5 = { 16, "pes" };
	Sdata r6 = { 12, "Stepa" };
	Sdata r7 = { 13, "Stepa" };
	Sdata r8 = { 14, "pes" };
	Sdata r9 = { 15, "Stepa" };
	testTree = bst_create(cmp);
	bst_insert(testTree, &rooter);
	bst_insert(testTree, &l1);
	bst_insert(testTree, &r1);
	bst_insert(testTree, &l2);
	bst_insert(testTree, &r2);
	bst_insert(testTree, &r10);
	bst_insert(testTree, &r3);
	bst_insert(testTree, &r4);
	bst_insert(testTree, &r5);
	bst_insert(testTree, &r6);
	bst_insert(testTree, &r7);
	bst_insert(testTree, &r8);
	bst_insert(testTree, &r9);
	Sdata* finded = (Sdata*)bst_find(testTree, &r1);
	Sdata* deleted = (Sdata*)bst_delete(testTree, &r2);
	bst_destroy(testTree);
	BST* bst = bst_create(cmp_func);
	////////////////////////////////////////////
	bst_clear(bst);
	assert(bst->root == NULL);
	bst_insert(bst, 1);
	bst_clear(bst);
	assert(bst->root == NULL);
	for (int i = 0; i < 1000; i++)
	{
		assert(i == bst_insert(bst, i));
	}
	bst_clear(bst);
	assert(bst->root == NULL);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	/////////////////////////////////////////////

	bst = bst_create(cmp_func);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	bst = bst_create(cmp_func);
	bst_insert(bst, 1);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	bst = bst_create(cmp_func);
	for (int i = 0; i < 1000; i++)
	{
		bst_insert(bst, i);
	}
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	/////////////////////////////////////////////////

	bst = bst_create(cmp_func);
	assert(bst_size(bst) == 0);
	for (int i = 1; i < 1000; i++)
	{
		bst_insert(bst, i);
		assert(bst_size(bst) == i);
	}
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());

	////////////////////////////////////////////////

	bst = bst_create(cmp_func);

	assert(bst_find(bst, 1) == NULL);

	bst_insert(bst, 678);
	assert(bst_find(bst, 678) == 678);
	for (int i = -1000; i < 1000; i++)
	{
		bst_insert(bst, i);
	}
	assert(bst_find(bst, 567) == 567);
	assert(bst_find(bst, 2000) == NULL);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	////////////////////////////////////////////////

	bst = bst_create(cmp_func);
	assert(bst_delete(bst, 1) == NULL);
	bst_insert(bst, 678);
	assert(bst_find(bst, 678) == 678);
	for (int i = -1000; i < 1000; i++)
	{
		bst_insert(bst, i);
	}
	assert(bst_delete(bst, 2000) == NULL);
	assert(bst_find(bst, 500) == 500);
	size_t size = bst_size(bst);
	assert(bst_delete(bst, 500) == 500);
	assert(size - bst_size(bst) == 1);
	assert(bst_find(bst, 500) == NULL);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());

	////////////////////////////////////////////////

	bst = bst_create(cmp_func);
	bst_insert(bst, 500);
	for (int i = 1; i < 1000; i++)
	{
		bst_insert(bst, i);
	}
	printf("\n");
	bst_foreach(bst, fu, -500);
	printf("\n");
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());

	//////////////////////////////////////////////////

	bst = bst_create(cmp_func);
	bst_insert(bst, 5);
	bst_insert(bst, 2);
	bst_insert(bst, 0);
	bst_insert(bst, 20);
	bst_insert(bst, 40);
	bst_insert(bst, 11);
	bst_insert(bst, 10);
	bst_insert(bst, 17);
	bst_insert(bst, 16);
	bst_insert(bst, 12);
	bst_insert(bst, 13);
	bst_insert(bst, 14);
	bst_insert(bst, 15);

	size = bst_size(bst);

	bst_delete(bst, 11);
	assert(size - bst_size(bst) == 1);

	assert(bst->root->data == 5);
	assert(bst->root->right->data == 20);
	assert(bst->root->right->right->data == 40);
	assert(bst->root->right->left->data == 12);
	assert(bst_find(bst, 11) == NULL);
	assert(bst_find(bst, 40) == 40);
	assert(bst_find(bst, 2) == 2);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	///////////////////////////////////////////////////
	bst = bst_create(cmp_func);
	bst_insert(bst, 5);
	bst_insert(bst, 2);
	bst_insert(bst, 0);
	bst_insert(bst, 20);
	bst_insert(bst, 40);
	bst_insert(bst, 11);
	bst_insert(bst, 10);
	bst_insert(bst, 17);


	size = bst_size(bst);

	bst_delete(bst, 11);

	assert(size - bst_size(bst) == 1);

	assert(bst->root->data == 5);
	assert(bst->root->right->data == 20);
	assert(bst->root->right->right->data == 40);
	assert(bst->root->right->left->data == 17);
	assert(bst_find(bst, 11) == NULL);
	assert(bst_find(bst, 40) == 40);
	assert(bst_find(bst, 2) == 2);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());


	/////////////////////////////////////////

	bst = bst_create(cmp_func);
	bst_insert(bst, 5);
	size = bst_size(bst);
	bst_delete(bst, 5);

	assert(bst->root == NULL);

	assert(bst_find(bst, 5) == NULL);

	bst_size(bst);
	assert(size - bst_size(bst) == 1);

	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	//////////////////////////////////////////////

	bst = bst_create(cmp_func);
	bst_insert(bst, 5);
	bst_insert(bst, 2);
	bst_insert(bst, 3);
	bst_insert(bst, 1);
	bst_insert(bst, 20);

	size = bst_size(bst);
	bst_delete(bst, 3);


	assert(bst_find(bst, 3) == NULL);
	assert(bst_find(bst, 5) == 5);
	assert(bst_find(bst, 2) == 2);
	assert(bst_find(bst, 1) == 1);
	assert(bst_find(bst, 20) == 20);

	assert(size - bst_size(bst) == 1);

	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	///////////////////////////////////////////////////
	bst = bst_create(cmp_func);
	bst_insert(bst, 5);
	bst_insert(bst, 2);
	bst_insert(bst, 0);
	bst_insert(bst, 20);
	bst_insert(bst, 40);
	bst_insert(bst, 11);
	bst_insert(bst, 10);


	size = bst_size(bst);

	bst_delete(bst, 20);

	size_t size2 = bst_size(bst);
	assert(size - size2 == 1);

	assert(bst_find(bst, 20) == NULL);
	assert(bst_find(bst, 40) == 40);
	assert(bst_find(bst, 2) == 2);
	assert(bst_find(bst, 11) == 11);
	assert(bst_find(bst, 10) == 10);
	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());

	///////////////////////////////////////////////////
	bst = bst_create(cmp_func);
	bst_insert(bst, 5);
	bst_insert(bst, 2);
	bst_insert(bst, 0);
	bst_insert(bst, 20);
	bst_insert(bst, 40);
	bst_insert(bst, 11);
	bst_insert(bst, 10);


	size = bst_size(bst);

	bst_delete(bst, 40);

	size2 = bst_size(bst);
	assert(size - size2 == 1);

	assert(bst_find(bst, 5) == 5);
	assert(bst_find(bst, 20) == 20);
	assert(bst_find(bst, 40) == NULL);
	assert(bst_find(bst, 2) == 2);
	assert(bst_find(bst, 11) == 11);
	assert(bst_find(bst, 10) == 10);
	assert(bst_find(bst, 0) == 0);
	
	bst_delete(bst, 10);

	assert(bst_find(bst, 5) == 5);
	assert(bst_find(bst, 20) == 20);
	assert(bst_find(bst, 2) == 2);
	assert(bst_find(bst, 11) == 11);
	assert(bst_find(bst, 10) == NULL);
	assert(bst_find(bst, 0) == 0);

	bst_delete(bst, 0);

	assert(bst_find(bst, 5) == 5);
	assert(bst_find(bst, 20) == 20);
	assert(bst_find(bst, 2) == 2);
	assert(bst_find(bst, 11) == 11);
	assert(bst_find(bst, 0) == NULL);

	bst_delete(bst, 5);

	assert(bst_find(bst, 5) == NULL);
	assert(bst_find(bst, 20) == 20);
	assert(bst_find(bst, 2) == 2);
	assert(bst_find(bst, 11) == 11);

	bst_delete(bst, 20);

	assert(bst_find(bst, 20) == NULL);
	assert(bst_find(bst, 2) == 2);
	assert(bst_find(bst, 11) == 11);

	bst_delete(bst, 2);

	printf("\n%d\n", bst->root->data);

	assert(bst_find(bst, 2) == NULL);
	assert(bst_find(bst, 11) == 11);

	bst_delete(bst, 11);

	assert(bst_find(bst, 11) == NULL);

	bst_destroy(bst);
	assert(!_CrtDumpMemoryLeaks());
	return _CrtDumpMemoryLeaks();
}