#include "DLList.h"
#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
typedef void* Pointer;

int main(void) {
	//Test 1
	Pointer p;
	p = dlist_create(4);
	dlist_append(p);
	dlist_append(p);
	dlist_append(p);
	dlist_removeFirst(p, 0);
	dlist_destroy(p, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	//Test2
	p = dlist_create(4);
	dlist_append(p);
	dlist_append(p);
	dlist_append(p);
	assert(dlist_count(p) == 3);
	//assert(dlist_init(p, 0, NULL) == NULL);
	dlist_destroy(p, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	p = dlist_create(4);
	assert((p = dlist_init(p, 3, NULL)) != NULL);
	assert(dlist_count(p) == 0);
	dlist_destroy(p, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	assert((p = dlist_init(NULL, 3, NULL)) == NULL);
	dlist_destroy(p, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	//Test 3
	assert((p = dlist_create(3)) != NULL);
	assert(dlist_count(p) == 0);
	dlist_destroy(p, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	//Test 4
	dlist_destroy(NULL, NULL);
	//Test 5
	dlist_destroy(NULL, free);
	//Test 6
	assert(dlist_init(NULL, 0, NULL) == NULL);
	//Test 7
	assert(dlist_init(NULL, 0, NULL) == NULL);
	//Test 8
	dlist_clear(NULL, NULL);
	//Test 9
	assert(dlist_count(NULL) == INVALID);
	//Test 10
	assert(dlist_item(NULL, 0) == NULL);
	assert(dlist_item(NULL, -1) == NULL);
	assert(dlist_item(NULL, 1) == NULL);
	//Test 11
	p = dlist_create(4);
	assert(dlist_item(p, -1) == NULL);
	dlist_destroy(p, NULL);
	//Test 12
	assert(dlist_prepend(NULL) == NULL);
	//Test 13
	assert(dlist_append(NULL) == NULL);
	//Test 14
	dlist_removeFirst(NULL, free);
	//Test 15
	dlist_removeLast(NULL, free);
	//Test 16
	dlist_removeFirst(NULL, NULL);
	//Test 17
	dlist_removeLast(NULL, NULL);
	//Test 18
	assert(dlist_stop(NULL));
	//Test 19
	assert(dlist_first(NULL) == dlist_stop(NULL));
	//Test 20
	assert(dlist_last(NULL) == dlist_stop(NULL));
	//Test 21
	assert(dlist_current(NULL, dlist_stop(NULL)) == NULL);
	//Test 22
	assert(dlist_next(NULL, dlist_stop(NULL)) == dlist_stop(NULL));
	//Test 23
	assert(dlist_prev(NULL, dlist_stop(NULL)) == dlist_stop(NULL));
	//Test 24
	for (int i = dlist_first(NULL); i != dlist_stop(NULL); i = dlist_next(NULL, i)) {}
	//Test 25
	for (int i = dlist_last(NULL); i != dlist_stop(NULL); i = dlist_prev(NULL, i)) {}
	//Test 26
	assert((dlist_insertAfter(NULL, dlist_stop(NULL))) == NULL);
	//Test 27
	assert((dlist_insertBefore(NULL, dlist_stop(NULL))) == NULL);
	//Test 28
	dlist_erase(NULL, dlist_stop(NULL), free);
	//Test 29
	dlist_erase(NULL, dlist_stop(NULL), NULL);
	//Global Test 30
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_append(p);
	dlist_append(p);
	dlist_prepend(p);
	dlist_prepend(p);
	dlist_prepend(p);
	dlist_destroy(p, 0);
	void* list = dlist_create(4);
	list = dlist_init(list, 4, NULL);
	for (int i = 0; i < 1000; i++) {
		dlist_prepend(list);
	}
	printf("%d\n", dlist_first(list));
	printf("%d\n", dlist_count(list));
	dlist_removeFirst(list, 0);
	//dlist_erase(list, 33 , 0);
	//dlist_insertAfter(list, 67);
	//dlist_insertAfter(list, 67);
	//for (int i = 1000; i > 1; i--) {
		//printf("id_next = %d\n", dlist_next(list, i));
	//}
	printf("%d\n", dlist_count(list));
	dlist_destroy(list, 0);
	//
	size_t count_0 = 1000;
	void* list_0 = dlist_create(4);
	list_0 = dlist_init(list_0, 4, NULL);
	for (size_t i = 0; i < count_0; i++) {
		dlist_prepend(list_0);
	}
	//assert(dlist_first(list_0) == count_0);
	assert(dlist_count(list_0) == count_0);
	//dlist_removeFirst(list_0, 0);
	//dlist_erase(list_0, 43, 0);
	//dlist_insertAfter(list_0, 67);
	//assert(dlist_first(list_0) == count_0 - 1);
	//assert(dlist_count(list_0) == count_0 - 1);
	//for (int i = count_0; i >= 1; i--) {
		//if (i == 43) {
			//assert(dlist_next(list_0, i) == 0);
		//}
		//else if (i == 67) {
			//assert(dlist_next(list_0, i) == 1001);
		//}
		//else if (i == 1000) {
			//assert(dlist_next(list_0, i) == 0);
		//}
		//else if (i == 44) {
			//assert(dlist_next(list_0, i) == 42);
		//}
		//else {
			//assert(dlist_next(list_0, i) == i - 1);
		//}
	//}
	//assert(dlist_count(list_0) == count_0 - 1);
	dlist_destroy(list_0, 0);

	void* list_1 = dlist_create(0);
	list_1 = dlist_init(list_1, 0, NULL);
	dlist_prepend(list_1);
	dlist_removeFirst(list_1, 0);
	dlist_destroy(list_1, 0);

	void* list_2 = dlist_create(100);
	list_2 = dlist_init(list_2, 0, NULL);
	for (int i = 0; i < 50; i++) {
		dlist_prepend(list_2);
	}
	assert(dlist_count(list_2) == 50);
	for (int i = 0; i < 20; i++) {
		dlist_removeFirst(list_2, 0);
	}
	assert(dlist_count(list_2) == 30);
	//dlist_insertAfter(list_2, 30);
	//assert(dlist_next(list_2, 30) == 51);
	//dlist_insertAfter(list_2, 30);
	//assert(dlist_next(list_2, 30) == 52);
	//dlist_insertAfter(list_2, 0);
	//assert(dlist_next(list_2, 0) == 0);
	//dlist_insertAfter(list_2, 1);
	//assert(dlist_next(list_2, 1) == 53);
	//dlist_erase(list_2, 20, 0);
	//assert(dlist_next(list_2, 21) == 19);
	//dlist_erase(list_2, 10, 0);
	//assert(dlist_next(list_2, 11) == 9);
	//assert(dlist_count(list_2) == 31);
	dlist_destroy(list_2, 0);

	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}