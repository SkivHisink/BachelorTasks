#include "dlist.h"
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
	p = dlist_create(4);
	//assert(dlist_item(p, 0) == NULL); ????????
	dlist_destroy(p, 0);
	assert(dlist_item(NULL, (size_t)0) == NULL);
	assert(dlist_item(NULL, (size_t)-1) == NULL);
	assert(dlist_item(NULL, (size_t)1) == NULL);
	//Test 11
	p = dlist_create(4);
	assert(dlist_item(p, (size_t)-1) == NULL);
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
	assert(!dlist_stop(NULL));
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
	for (size_t i = dlist_first(NULL); i != dlist_stop(NULL); i = dlist_next(NULL, i)) {}
	//Test 25
	for (size_t i = dlist_last(NULL); i != dlist_stop(NULL); i = dlist_prev(NULL, i)) {}
	//Test 26
	assert((dlist_insertAfter(NULL, dlist_stop(NULL))) == NULL);
	//Test 27
	assert((dlist_insertBefore(NULL, dlist_stop(NULL))) == NULL);
	//Test 28
	dlist_erase(NULL, dlist_stop(NULL), free);
	//Test 29
	dlist_erase(NULL, dlist_stop(NULL), NULL);
	void* e;
	//Test 30 singleElementContainer.eraseFirst_count_OK
	p = dlist_create(4);
	dlist_append(p);
	dlist_erase(p, dlist_first(p), 0);
	assert(dlist_count(p) == 0);
	dlist_destroy(p, 0);

	//Test 31 singleElementContainer.insertAfterFirst_count_item_OK
	p = dlist_create(4);
	dlist_append(p);
	 e = dlist_insertAfter(p, dlist_first(p));
	assert(e != NULL);
	assert(dlist_count(p) == 2);
	assert(dlist_item(p, 0) != e);
	assert(dlist_item(p, 1) == e);
	dlist_destroy(p, 0);
	//Test 32 singleElementContainer.insertBeforeFirst_count_item_OK
	p = dlist_create(4);
	dlist_append(p);
	 e = dlist_insertBefore(p, dlist_first(p));
	assert(e != NULL);
	assert(dlist_count(p) == 2);
	assert(dlist_item(p, 0) == e);
	assert(dlist_item(p, 1) != e);
	dlist_destroy(p, 0);
	//Test 33 removelast empty container
	p = dlist_create(4);
	dlist_removeLast(p, 0);
	assert(0 == dlist_count(p));
	dlist_destroy(p, 0);
	//Test 34 removelast empty container with delete func
	p = dlist_create(4);
	dlist_removeLast(p, free);
	assert(0 == dlist_count(p));
	dlist_destroy(p, 0);
	//Test 35 empty container insertAfter
	p = dlist_create(4);
	e = dlist_insertAfter(p, dlist_stop(p));
	assert(e != NULL);
	assert(dlist_count(p) == 1);
	assert(dlist_item(p, 0) == e);
	dlist_destroy(p, 0);
	//Test 36 empty container insertAfter
	p = dlist_create(4);
	e = dlist_insertBefore(p, dlist_stop(p));
	assert(e != NULL);
	assert(dlist_count(p) == 1);
	assert(dlist_item(p, 0) == e);
	dlist_destroy(p, 0);
	//Test 37 clear single elem container
	p = dlist_create(4);
	dlist_append(p);
	dlist_clear(p, 0);
	dlist_destroy(p, 0);
	//Test 38 single elem container outrange item
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	assert(dlist_item(p, 1) == NULL);
	dlist_destroy(p, 0);
	//Test 39 singleElementContainer.removeFirst_count_OK
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_removeFirst(p, NULL);
	assert(dlist_count(p) == 0);
	dlist_destroy(p, NULL);
	//Test 40 singleElementContainer.currentfirst_OK
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	e = dlist_current(p, dlist_first(p));
	assert(e != NULL);
	assert(e == dlist_item(p, 0));
	dlist_destroy(p, NULL);
	//Test 41 singleElementContainer.forwardLoop_OK
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	for(size_t i= dlist_first(p); i != dlist_stop(p); i = dlist_next(p, i)) {}
	dlist_destroy(p, NULL);
	//Test 42 singleElementContainer.backwardLoop_OK
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	for (size_t i = dlist_last(p); i != dlist_stop(p); i = dlist_prev(p, i)) {}
	dlist_destroy(p, NULL);
	//Test 42 
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	e = dlist_insertBefore(p, dlist_first(p));
	assert(dlist_count(p) == 2);
	assert(dlist_item(p, 0) == e);
	assert(dlist_item(p, 1) != e);
	dlist_destroy(p, 0);
	//Test 43 
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_current(p, dlist_stop(p));
	assert(dlist_next(p, dlist_stop(p)) == dlist_stop(p));
	dlist_removeLast(p, 0);
	dlist_destroy(p, 0);
	//Test 44
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	e = dlist_current(p, dlist_first(p));
	assert(e != NULL);
	assert(dlist_first(p) == dlist_last(p));
	dlist_destroy(p, 0);
	//Test 45 
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_current(p, dlist_stop(p));
	assert(dlist_next(p, dlist_stop(p)) == dlist_stop(p));
	dlist_erase(p, dlist_first(p), 0);
	dlist_destroy(p, 0);
	//Test 46 erase(C, first(C), ~Elem)  count(C) == 0
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_item(p, 1);
	dlist_destroy(p, 0);
	//Test 47 
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_append(p);
	dlist_item(p, 1);
	dlist_destroy(p, 0);
	//Test 48 
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_append(p);
	dlist_append(p);
	dlist_prepend(p);
	dlist_prepend(p);
	dlist_prepend(p);
	dlist_destroy(p, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	//Test 49 
	p = dlist_create(4);
	p = dlist_init(p, 3, NULL);
	dlist_append(p);
	dlist_append(p);
	dlist_append(p);
	dlist_prepend(p);
	dlist_prepend(p);
	dlist_prepend(p);
	dlist_clear(p, 0);
	assert(dlist_count(p) == 0);
	dlist_destroy(p, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	//Test 50
	void* list = dlist_create(4);
	list = dlist_init(list, 4, NULL);
	for (int i = 0; i < 1000; i++) {
		dlist_prepend(list);
	}
	printf("%d\n", dlist_first(list));
	printf("%d\n", dlist_count(list));
	dlist_removeFirst(list, 0);
	printf("%d\n", dlist_count(list));
	dlist_destroy(list, 0);
	//Test 51 
	size_t count_0 = 1000;
	void* list_0 = dlist_create(4);
	list_0 = dlist_init(list_0, 4, NULL);
	for (size_t i = 0; i < count_0; i++) {
		dlist_prepend(list_0);
	}
	assert(dlist_count(list_0) == count_0);
	dlist_destroy(list_0, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	//Test 52 
	void* list_1 = dlist_create(0);
	list_1 = dlist_init(list_1, 0, NULL);
	dlist_prepend(list_1);
	dlist_removeFirst(list_1, 0);
	dlist_destroy(list_1, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	//Test 53 
	void* list_2 = dlist_create(100);
	list_2 = dlist_init(list_2, 0, NULL);
	assert(_CrtDumpMemoryLeaks() == 0);
	for (int i = 0; i < 50; i++) {
		dlist_prepend(list_2);
	}
	for (int i = 0; i < 20; i++) {
		dlist_removeFirst(list_2, 0);
	}
	dlist_destroy(list_2, 0);
	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}