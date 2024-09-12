#include "DLList.h"
#include <malloc.h>

typedef struct ListNode {
	void* data;
	struct ListNode* next;
	struct ListNode* prev;
}ListNode;

typedef struct List {
	size_t itemSize;
	ListNode* head;
	ListNode* tail;
	size_t size;
}List;

void* dlist_create(size_t itemSize) {
	if (itemSize == 0) {
		return NULL;
	}
	List* dlist = (List*)malloc(sizeof(List));
	if (dlist == NULL) {
		return NULL;
	}
	dlist->size = 0;
	dlist->itemSize = itemSize;
	((List*)dlist)->head = NULL;
	((List*)dlist)->tail = NULL;
	return dlist;
}

void* dlist_init(void* dlist, size_t itemSize, void(*destroy)(void*)) {
	if (dlist == NULL) {
		return NULL;
	}
	if (((List*)dlist)->head != NULL) {
		dlist_destroy(dlist, destroy);
		dlist = dlist_create(itemSize);

	}
	else {
		((List*)dlist)->itemSize = itemSize;
	}
	return dlist;
}

void dlist_destroy(void* dlist, void(*destroy)(void*)) {
	if (dlist == NULL) {
		return;
	}
	dlist_clear(dlist, destroy);
	free(dlist);
}

static void delete_node(ListNode* tmp, void delete_func(void*)) {
	if (tmp != NULL) {
		if (tmp->data != NULL) {
			if (delete_func != NULL) {
				delete_func(tmp->data);
			}
			free(tmp->data);
		}
		free(tmp);
	}
}

void dlist_clear(void* dlist, void(*destroy)(void*)) {
	if (dlist == NULL) {
		return;
	}
	ListNode* tmp;
	while (((List*)dlist)->tail != ((List*)dlist)->head) {
		tmp = ((List*)dlist)->tail;
		((List*)dlist)->tail = ((List*)dlist)->tail->prev;
		delete_node(tmp, destroy);
	}
	if (((List*)dlist)->tail != NULL) {
		if (((List*)dlist)->tail->data != NULL) {
			if (destroy != NULL) {
				destroy(((List*)dlist)->tail->data);
			}
			free(((List*)dlist)->tail->data);
		}
		free(((List*)dlist)->tail);
	}
	//free(dlist);
}

size_t dlist_count(const void* dlist)
{
	if (dlist == NULL) {
		return INVALID;
	}
	return ((List*)dlist)->size;
}

void* dlist_item(void* dlist, size_t i) {
	if (dlist == NULL) {
		return NULL;
	}
	ListNode* tmp = NULL;
	if (((List*)dlist)->size < i || i < 0) {
		return NULL;
	}
	else if ((size_t)((List*)dlist)->size / 2 >= i) {
		tmp = ((List*)dlist)->head;
		for (int j = 0; j != i; j++) {
			tmp = tmp->next;
		}
		return tmp->data;
	}
	else if (((List*)dlist)->size / 2 <= i) {
		tmp = ((List*)dlist)->tail;
		for (int j = ((List*)dlist)->size; i + 1 != j; j--) {
			tmp = tmp->prev;
		}
		return tmp->data;
	}
	return NULL;
}

void* dlist_append(void* dlist) {
	if (dlist == NULL) {
		return NULL;
	}
	ListNode* tmp;
	tmp = (ListNode*)malloc(sizeof(ListNode));
	if (tmp == NULL) {
		return NULL;
	}
	tmp->data = (void*)malloc(((List*)dlist)->itemSize * sizeof(char));
	if (tmp->data == NULL) {
		return NULL;
	}
	tmp->next = NULL;
	tmp->prev = ((List*)dlist)->tail;
	if (((List*)dlist)->tail == NULL) {
		((List*)dlist)->tail = tmp;
		((List*)dlist)->head = tmp;
		((List*)dlist)->size = 1;
	}
	else {
		((List*)dlist)->tail->next = tmp;
		((List*)dlist)->tail = tmp;
		((List*)dlist)->size++;
	}
	return ((List*)dlist)->tail->data;
}

void* dlist_prepend(void* dlist) {
	if (dlist == NULL) {
		return NULL;
	}
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	if (tmp == NULL) {
		return NULL;
	}
	tmp->data = (void*)malloc(((List*)dlist)->itemSize * sizeof(char));
	if (tmp->data == NULL) {
		return NULL;
	}
	tmp->prev = NULL;
	tmp->next = ((List*)dlist)->head;
	if (((List*)dlist)->head != 0) {
		((List*)dlist)->head->prev = tmp;
	}
	if (((List*)dlist)->size == 0) {
		((List*)dlist)->head = ((List*)dlist)->tail = tmp;
	}
	else {
		((List*)dlist)->head = tmp;
	}
	((List*)dlist)->size++;
	return ((List*)dlist)->head->data;
}

void dlist_removeFirst(void* dlist, void(*destroy)(void*)) {
	if (((List*)dlist) == NULL) {
		return;
	}
	if (((List*)dlist)->head == NULL) {
		return;
	}
	if (((List*)dlist)->head->next == NULL) {
		return;
	}
	ListNode* temp = ((List*)dlist)->head->next;
	delete_node(((List*)dlist)->head, destroy);
	temp->prev = NULL;
	((List*)dlist)->head = temp;
	((List*)dlist)->size--;
}

void dlist_removeLast(void* dlist, void(*destroy)(void*)) {
	if (dlist == NULL) {
		return;
	}
	ListNode* temp = ((List*)dlist)->tail->prev;
	if (destroy == NULL) {
		destroy = free;
	}
	delete_node(((List*)dlist)->tail, destroy);
	temp->next = NULL;
	((List*)dlist)->tail = temp;
	((List*)dlist)->size--;
}

size_t dlist_first(const void* dlist) {
	if (((List*)dlist) != NULL) {
		if (((List*)dlist)->head != NULL) {
			return (size_t)((List*)dlist)->head;
		}
	}
	return INVALID;
}

size_t dlist_last(const void* dlist) {
	if (((List*)dlist) != NULL) {
		if (((List*)dlist)->tail != NULL) {
			return (size_t)((List*)dlist)->tail;
		}
	}
	return INVALID;
}

//static ListNode* dlist_find_with_id(List* dlist, size_t item_id) {
//	ListNode* tmp = dlist->head;
//	while (tmp != NULL) {
//		if (tmp == (ListNode*)item_id)
//			return tmp;
//		tmp = tmp->next;
//	}
//	return NULL;
//}

size_t dlist_next(const void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return INVALID;
	}

	ListNode* tmp = (ListNode*)item_id;
	if (tmp != NULL) {
		if (tmp->next != NULL) {
			return (size_t)tmp->next;
		}
	}
	return INVALID;
}

size_t dlist_prev(const void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return INVALID;
	}
	ListNode* tmp = (ListNode*)item_id;
	if (tmp != NULL) {
		if (tmp->prev != NULL) {
			return (size_t)tmp->prev;
		}
	}
	return INVALID;
}

size_t dlist_stop(const void* dlist) {
	return INVALID;
}

void* dlist_current(const void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return NULL;
	}
	return (void*)((ListNode*)item_id);
}

static ListNode* dlist_add_elem(void* dlist, ListNode* tmp, ListNode* tempNextt, ListNode* tempPrevv) {
	ListNode* tempNext = tempNextt;
	ListNode* tempPrev = tempPrevv;
	tmp = (ListNode*)malloc(sizeof(ListNode));
	if (tmp != NULL) {
		tmp->data = malloc(((List*)dlist)->itemSize * sizeof(char));
	}
	if (tmp == NULL || tmp->data) {
		return NULL;
	}
	if (tempPrev != NULL) {
		tempPrev->next = tmp;
	}
	tmp->prev = tempPrev;
	if (tempNext != NULL) {
		tempNext->prev = tmp;
	}
	tmp->next = tempNext;
	((List*)dlist)->size++;
	return tmp;
}

void* dlist_insertAfter(void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return NULL;
	}
	ListNode* tmp = dlist_current(dlist, item_id);
	if (tmp == NULL) {
		return NULL;
	}
	if (tmp->next == NULL) {
		tmp = dlist_append(dlist);
		return tmp->data;
	}
	else {
		return dlist_add_elem(dlist, tmp, tmp->next, tmp);
	}
	return NULL;
}

void* dlist_insertBefore(void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return NULL;
	}
	ListNode* tmp = dlist_current(dlist, item_id);
	if (tmp == NULL) {
		return NULL;
	}
	if (tmp->prev == NULL) {
		tmp = dlist_prepend(dlist);
		return tmp->data;
	}
	else {
		return dlist_add_elem(dlist, tmp, tmp, tmp->prev);
	}
	return NULL;
}
static void dlist_int_delete(List* list, ListNode* node, void delete_func(void*)) {
	if (node == list->head) {
		list->head = node->next;
		if (list->head != NULL)
			list->head->prev = NULL;
	}

	else if (node == list->tail) {
		list->tail = node->prev;
		if (list->tail != NULL)
			list->tail->next = NULL;
	}
	else {
		ListNode* nodePrev = node->prev;
		ListNode* nodeNext = node->next;
		nodePrev->next = nodeNext;
		nodeNext->prev = nodePrev;
	}
	delete_node(node, delete_func);
	list->size -= 1;
}

void dlist_erase(void* dlist, size_t item_id, void(*destroy)(void*)) {
	if (dlist == NULL) {
		return;
	}
	ListNode* node = dlist_current(dlist, item_id);
	if (node != NULL) {
		dlist_int_delete((List*)dlist, node, destroy);
	}
}

////
//ListNode* list_get_part(List* list, int num) {
//	ListNode* tmp = NULL;
//	if (list->size < num || num < 0) {
//		return NULL;
//	}
//	else if (list->size / 2 >= num) {
//		tmp = list->head;
//		for (int i = 0; num != i; i++) {
//			tmp = tmp->next;
//		}
//		return tmp;
//	}
//	else if (list->size / 2 <= num) {
//		tmp = list->tail;
//		for (int i = list->size; num + 1 != i; i--) {
//			tmp = tmp->prev;
//		}
//		return tmp;
//	}
//}
//void int_delete(List* list, ListNode* node, void delete_func(void*)) {
//	if (node == list->head) {
//		list->head = node->next;
//		if (list->head != NULL)
//			list->head->prev = NULL;
//	}
//
//	if (node == list->tail) {
//		list->tail = node->prev;
//		if (list->tail != NULL)
//			list->tail->next = NULL;
//	}
//	delete_node(node, delete_func);
//	list->size -= 1;
//}
//void list_delete_part(List* list, int var, void delete_func(void*)) {
//	ListNode* node = list_get_part(list, var);
//	int_delete(list, node, delete_func);
//}
//void delete_list(List* list, void delete_func(void*)) {
//
//}
//void* list_get_data(List* list, int var) {
//	ListNode* myList1 = list_get_part(list, var);
//	return myList1->data;
//}
//void list_data_changer(List* list, int i, int j) {
//	void* tmp;
//	ListNode* myList1 = list_get_part(list, i);
//	ListNode* myList2 = list_get_part(list, j);
//	tmp = myList1->data;
//	myList1->data = myList2->data;
//	myList2->data = tmp;
//}