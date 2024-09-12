#include "dlist.h"
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
	if (itemSize == 0) {
		dlist_destroy(dlist, destroy);
		return 0;
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
		if (tmp != NULL) {
			((List*)dlist)->tail = ((List*)dlist)->tail->prev;
			delete_node(tmp, destroy);
		}
		else {
			if (((List*)dlist)->head != NULL) {
				((List*)dlist)->head = NULL;
			}
		}
	}
	if (((List*)dlist)->tail != NULL && ((List*)dlist)->head != NULL) {
		if (((List*)dlist)->tail->data != NULL) {
			if (destroy != NULL) {
				destroy(((List*)dlist)->tail->data);
			}
			free(((List*)dlist)->tail->data);
			((List*)dlist)->tail->data = NULL;
		}
		free(((List*)dlist)->tail);
		((List*)dlist)->tail = NULL;
	}
	((List*)dlist)->size = 0;
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
	if (((List*)dlist)->head == NULL) {
		return NULL;
	}
	ListNode* tmp = NULL;
	if (((List*)dlist)->size < i) {
		return NULL;
	}
	tmp = ((List*)dlist)->head;
	for (size_t j = 0; j != i; j++) {
		if (tmp != NULL) {
			tmp = tmp->next;
		}
	}
	if (tmp != NULL) {
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
	if (((List*)dlist)->head == NULL || ((List*)dlist)->tail == NULL) {
		return;
	}
	if (((List*)dlist)->tail == ((List*)dlist)->head) {
		((List*)dlist)->tail = NULL;
	}
	ListNode* temp = ((List*)dlist)->head->next;
	delete_node(((List*)dlist)->head, destroy);
	if (((List*)dlist)->tail == NULL) {
		((List*)dlist)->head = NULL;
	}
	if (temp != NULL) {
		temp->prev = NULL;
		((List*)dlist)->head = temp;
		if (((List*)dlist)->tail == NULL) {
			((List*)dlist)->tail = ((List*)dlist)->head;
		}
	}
	((List*)dlist)->size--;
}

void dlist_removeLast(void* dlist, void(*destroy)(void*)) {
	if (dlist == NULL) {
		return;
	}
	if (((List*)dlist)->tail == NULL) {
		return;
	}
	if (((List*)dlist)->tail == ((List*)dlist)->head) {
		((List*)dlist)->head = NULL;
	}
	ListNode* temp = ((List*)dlist)->tail->prev;
	delete_node(((List*)dlist)->tail, destroy);
	if (((List*)dlist)->head == NULL) {
		((List*)dlist)->tail = NULL;
	}
	if (temp != NULL) {
		temp->next = NULL;
		((List*)dlist)->tail = temp;
	}
	((List*)dlist)->size--;
}

size_t dlist_first(const void* dlist) {
	if (((List*)dlist) != NULL) {
		if (((List*)dlist)->head != NULL) {
			return (size_t)((List*)dlist)->head;
		}
	}
	return 0;
}

size_t dlist_last(const void* dlist) {
	if (((List*)dlist) != NULL) {
		if (((List*)dlist)->tail != NULL) {
			return (size_t)((List*)dlist)->tail;
		}
	}
	return 0;
}

size_t dlist_next(const void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return 0;
	}
	if (item_id == 0) {
		return 0;
	}
	ListNode* tmp = (ListNode*)item_id;
	if (tmp != NULL) {
		if (tmp->next != NULL) {
			return (size_t)tmp->next;
		}
	}
	return 0;
}

size_t dlist_prev(const void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return 0;
	}
	if (item_id == 0) {
		return 0;
	}
	ListNode* tmp = (ListNode*)item_id;
	if (tmp != NULL) {
		if (tmp->prev != NULL) {
			return (size_t)tmp->prev->data;
		}
	}
	return 0;
}

size_t dlist_stop(const void* dlist) {
	return 0;
}

void* dlist_current(const void* dlist, size_t item_id) {
	if (dlist == NULL || item_id == dlist_stop(dlist)) {
		return NULL;
	}
	return (void*)((ListNode*)item_id)->data;
}

static ListNode* dlist_add_elem(void* dlist, ListNode* tmp, ListNode* tempNextt, ListNode* tempPrevv) {
	ListNode* tempNext = tempNextt;
	ListNode* tempPrev = tempPrevv;
	tmp = (ListNode*)malloc(sizeof(ListNode));
	if (tmp == NULL) {
		return NULL;
	}
	tmp->data = malloc(((List*)dlist)->itemSize * sizeof(char));
	if (tmp->data == NULL) {
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
	return tmp->data;
}

static void* dlist_find_by_id(const void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return NULL;
	}
	return (void*)((ListNode*)item_id);
}

void* dlist_insertAfter(void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return NULL;
	}
	if (item_id == 0 && ((List*)dlist)->head != NULL) {
		return 0;
	}
	else if (item_id == 0 && ((List*)dlist)->head == NULL) {
		return dlist_append(dlist);
	}
	ListNode* tmp = dlist_find_by_id(dlist, item_id);
	if (tmp == NULL) {
		return NULL;
	}
	if (tmp->next == NULL) {
		return dlist_append(dlist);
	}
	else {
		return dlist_add_elem(dlist, tmp, tmp->next, tmp);
	}
}

void* dlist_insertBefore(void* dlist, size_t item_id) {
	if (dlist == NULL) {
		return NULL;
	}
	if (item_id == 0 && ((List*)dlist)->head != NULL) {
		return NULL;
	}
	else if (item_id == 0 && ((List*)dlist)->head == NULL) {
		return dlist_prepend(dlist);
	}
	ListNode* tmp = dlist_find_by_id(dlist, item_id);
	if (tmp == NULL) {
		return NULL;
	}
	if (tmp->prev == NULL) {
		return dlist_prepend(dlist);
	}
	else {
		return dlist_add_elem(dlist, tmp, tmp, tmp->prev);
	}
}
static void dlist_int_delete(List* list, ListNode* node, void delete_func(void*)) {
	if (node == list->head && node == list->tail) {
		list->head = NULL;
		list->tail = NULL;
		list->size = 0;
	}
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
		if (nodePrev != NULL)
			nodePrev->next = nodeNext;
		if (nodeNext != NULL)
			nodeNext->prev = nodePrev;
	}
	delete_node(node, delete_func);
}

void dlist_erase(void* dlist, size_t item_id, void(*destroy)(void*)) {
	if (dlist == NULL) {
		return;
	}
	if (item_id == 0) {
		return;
	}
	ListNode* node = dlist_find_by_id(dlist, item_id);
	if (node != NULL) {
		dlist_int_delete((List*)dlist, node, destroy);
	}
	if (((List*)dlist)->size != 0) {
		((List*)dlist)->size--;
	}
}