#include "AVLTree.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

//low left turn
/*avl_insert(testTree, &rooter);
avl_insert(testTree, &l1);
avl_insert(testTree, &r1);*/
//
//big left turn
/*avl_insert(testTree, &rooter);
avl_insert(testTree, &r1);
avl_insert(testTree, &l1);*/
//
//low right turn
/*avl_insert(testTree, &r1);
avl_insert(testTree, &l1);
avl_insert(testTree, &rooter);*/
//big right turn
/*avl_insert(testTree, &r1);
avl_insert(testTree, &rooter);
avl_insert(testTree, &l1);*/
//


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



int print_level(AVLTreeNode* root, int level)
{
	if (root == NULL) {
		printf("null ");
		return 0;
	}
	if (level == 0) {
		printf("%d ", root->data);
		return 1;
	}
	else
		return(print_level(root->left, level - 1) + print_level(root->right, level - 1));
}


void printing(AVLTreeNode* root)
{
	int count = 0;
	while (1) {
		if (print_level(root, count) == 0) {
			printf("\n");
			break;
		}
		printf("\n");
		count++;
	}
}

int main(void)
{
	AVLTree* testTree;
	int (*cmp)(void* x, void* y) = Sdatacmp;
	Sdata rooter = { 6, "sobaka" };
	Sdata l1 = { 3, "pes" };
	Sdata r1 = { 0, "Stepa" };
	Sdata l2 = { 4, "pes" };
	Sdata r2 = { 5, "delete" };
	Sdata r10 = { 10, "delete" };
	Sdata r3 = { 40, "pes" };
	Sdata r4 = { 17, "Stepa" };
	Sdata r5 = { 16, "pes" };
	Sdata r6 = { 12, "Stepa" };
	Sdata r7 = { 13, "Stepa" };
	Sdata r8 = { 14, "pes" };
	Sdata r9 = { 15, "Stepa" };
	testTree = avl_create(cmp);
	avl_insert(testTree, &rooter); //6
	avl_insert(testTree, &l1); //3
	avl_insert(testTree, &r1); //0
	avl_insert(testTree, &l2); //4
	avl_insert(testTree, &r2); //5
	avl_insert(testTree, &r10); //10
	avl_insert(testTree, &r3); //40
	avl_insert(testTree, &r4); //17
	avl_insert(testTree, &r5); //16
	avl_insert(testTree, &r6); //12
	avl_insert(testTree, &r7); //13
	avl_insert(testTree, &r8); //14
	avl_insert(testTree, &r9); //15
	Sdata* finded = (Sdata*)avl_find(testTree, &r9);
	Sdata* deleted = (Sdata*)avl_delete(testTree, &r2);
	avl_destroy(testTree);
	AVLTree* avl = avl_create(cmp_func);
	////////////////////////////////////////////
	avl_clear(avl);
	assert(avl->root == NULL);
	avl_insert(avl, 1);
	avl_clear(avl);
	assert(avl->root == NULL);
	for (int i = 0; i < 1000; i++)
	{
		assert(i == avl_insert(avl, i));
	}
	avl_clear(avl);
	assert(avl->root == NULL);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	/////////////////////////////////////////////

	avl = avl_create(cmp_func);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	avl = avl_create(cmp_func);
	avl_insert(avl, 1);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	avl = avl_create(cmp_func);
	for (int i = 0; i < 1000; i++)
	{
		avl_insert(avl, i);
	}
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	/////////////////////////////////////////////////

	avl = avl_create(cmp_func);
	assert(avl_size(avl) == 0);
	for (int i = 1; i < 1000; i++)
	{
		avl_insert(avl, i);
		assert(avl_size(avl) == i);
	}
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());

	////////////////////////////////////////////////

	avl = avl_create(cmp_func);

	assert(avl_find(avl, 1) == NULL);

	avl_insert(avl, 678);
	assert(avl_find(avl, 678) == 678);
	for (int i = 0; i < 2000; i++)
	{
		avl_insert(avl, i);
	}
	assert(avl_find(avl, 567) == 567);
	assert(avl_find(avl, 2000) == NULL);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	////////////////////////////////////////////////

	avl = avl_create(cmp_func);
	assert(avl_delete(avl, 1) == NULL);
	avl_insert(avl, 678);
	assert(avl_find(avl, 678) == 678);
	for (int i = 0; i < 2000; i++)
	{
		avl_insert(avl, i);
	}
	assert(avl_delete(avl, 2000) == NULL);
	assert(avl_find(avl, 500) == 500);
	size_t size = avl_size(avl);
	assert(avl_delete(avl, 500) == 500);
	assert(size - avl_size(avl) == 1);
	assert(avl_find(avl, 500) == NULL);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());

	////////////////////////////////////////////////

	avl = avl_create(cmp_func);
	avl_insert(avl, 500);
	for (int i = 1; i < 1000; i++)
	{
		avl_insert(avl, i);
	}
	printf("\n");
	avl_foreach(avl, fu, 1);
	printf("\n");
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());

	avl = avl_create(cmp_func);
	int* mass = malloc(1000 * sizeof(int));
	if (mass == NULL)
		return NULL; // bad return
	for (int i = 0; i < 1000; i++) {
		mass[i] = rand() % 10000;
	}
	for (int i = 0; i < 1000; i++) {
		avl_insert(avl, &mass[i]);
	}
	for (int i = 0; i < 1000; i++) {
		if (i == 996)
			printf("");
		avl_delete(avl, &mass[i]);
	}
	printf("\n");
	//printing(avl->root);
	avl_foreach(avl, fu, 1);
	printf("\n");
	avl_destroy(avl);
	free(mass);
	assert(!_CrtDumpMemoryLeaks());

	//////////////////////////////////////////////////

	avl = avl_create(cmp_func);
	avl_insert(avl, 5);
	printing(avl->root);
	avl_insert(avl, 2);
	printing(avl->root);
	avl_insert(avl, 0);
	printing(avl->root);
	avl_insert(avl, 20);
	printing(avl->root);
	avl_insert(avl, 40);
	printing(avl->root);
	avl_insert(avl, 11);
	printing(avl->root);
	avl_insert(avl, 10);
	printing(avl->root);
	avl_insert(avl, 17);
	printing(avl->root);
	avl_insert(avl, 16);
	printing(avl->root);
	avl_insert(avl, 12);
	printing(avl->root);
	avl_insert(avl, 13);
	printing(avl->root);
	avl_insert(avl, 14);
	printing(avl->root);
	avl_insert(avl, 15);

	size = avl_size(avl);

	printing(avl->root);
	avl_delete(avl, 11);
	printing(avl->root);
	assert(size - avl_size(avl) == 1);

	assert(avl_find(avl, 11) == NULL);
	assert(avl_find(avl, 40) == 40);
	assert(avl_find(avl, 2) == 2);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	///////////////////////////////////////////////////
	avl = avl_create(cmp_func);
	avl_insert(avl, 5);
	avl_insert(avl, 2);
	avl_insert(avl, 0);
	avl_insert(avl, 20);
	avl_insert(avl, 40);
	avl_insert(avl, 11);
	avl_insert(avl, 10);
	avl_insert(avl, 17);

	size = avl_size(avl);

	avl_delete(avl, 11);

	assert(size - avl_size(avl) == 1);

	assert(avl->root->data == 5);
	assert(avl->root->right->data == 20);
	assert(avl->root->right->right->data == 40);
	assert(avl->root->right->left->data == 17);
	assert(avl_find(avl, 11) == NULL);
	assert(avl_find(avl, 40) == 40);
	assert(avl_find(avl, 2) == 2);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());

	/////////////////////////////////////////

	avl = avl_create(cmp_func);
	avl_insert(avl, 5);
	size = avl_size(avl);
	avl_delete(avl, 5);

	assert(avl->root == NULL);

	assert(avl_find(avl, 5) == NULL);

	avl_size(avl);
	assert(size - avl_size(avl) == 1);

	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	//////////////////////////////////////////////

	avl = avl_create(cmp_func);
	avl_insert(avl, 5);
	avl_insert(avl, 2);
	avl_insert(avl, 3);
	avl_insert(avl, 1);
	avl_insert(avl, 20);

	size = avl_size(avl);

	printing(avl->root);
	avl_delete(avl, 3);

	printing(avl->root);
	assert(avl_find(avl, 3) == NULL);
	assert(avl_find(avl, 5) == 5);
	assert(avl_find(avl, 2) == 2);
	assert(avl_find(avl, 1) == 1);
	assert(avl_find(avl, 20) == 20);

	assert(size - avl_size(avl) == 1);

	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	///////////////////////////////////////////////////
	avl = avl_create(cmp_func);
	avl_insert(avl, 5);
	avl_insert(avl, 2);
	avl_insert(avl, 0);
	avl_insert(avl, 20);
	avl_insert(avl, 40);
	avl_insert(avl, 11);
	avl_insert(avl, 10);

	size = avl_size(avl);

	avl_delete(avl, 20);

	size_t size2 = avl_size(avl);
	assert(size - size2 == 1);

	assert(avl_find(avl, 20) == NULL);
	assert(avl_find(avl, 40) == 40);
	assert(avl_find(avl, 2) == 2);
	assert(avl_find(avl, 11) == 11);
	assert(avl_find(avl, 10) == 10);
	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());

	///////////////////////////////////////////////////
	avl = avl_create(cmp_func);
	avl_insert(avl, 5);
	avl_insert(avl, 2);
	avl_insert(avl, 0);
	avl_insert(avl, 20);
	avl_insert(avl, 40);
	avl_insert(avl, 11);
	avl_insert(avl, 10);

	size = avl_size(avl);

	avl_delete(avl, 40);

	size2 = avl_size(avl);
	assert(size - size2 == 1);

	assert(avl_find(avl, 5) == 5);
	assert(avl_find(avl, 20) == 20);
	assert(avl_find(avl, 40) == NULL);
	assert(avl_find(avl, 2) == 2);
	assert(avl_find(avl, 11) == 11);
	assert(avl_find(avl, 10) == 10);
	assert(avl_find(avl, 0) == 0);

	avl_delete(avl, 10);

	assert(avl_find(avl, 5) == 5);
	assert(avl_find(avl, 20) == 20);
	assert(avl_find(avl, 2) == 2);
	assert(avl_find(avl, 11) == 11);
	assert(avl_find(avl, 10) == NULL);
	assert(avl_find(avl, 0) == 0);

	avl_delete(avl, 0);

	assert(avl_find(avl, 5) == 5);
	assert(avl_find(avl, 20) == 20);
	assert(avl_find(avl, 2) == 2);
	assert(avl_find(avl, 11) == 11);
	assert(avl_find(avl, 0) == NULL);

	avl_delete(avl, 5);

	assert(avl_find(avl, 5) == NULL);
	assert(avl_find(avl, 20) == 20);
	assert(avl_find(avl, 2) == 2);
	assert(avl_find(avl, 11) == 11);

	avl_delete(avl, 20);

	assert(avl_find(avl, 20) == NULL);
	assert(avl_find(avl, 2) == 2);
	assert(avl_find(avl, 11) == 11);

	avl_delete(avl, 2);

	printf("\n%d\n", avl->root->data);

	assert(avl_find(avl, 2) == NULL);
	assert(avl_find(avl, 11) == 11);

	avl_delete(avl, 11);

	assert(avl_find(avl, 11) == NULL);

	avl_destroy(avl);
	assert(!_CrtDumpMemoryLeaks());
	return _CrtDumpMemoryLeaks();
}
