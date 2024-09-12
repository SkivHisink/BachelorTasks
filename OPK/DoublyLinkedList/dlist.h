#pragma once

#include <stdbool.h> // bool
#include <stddef.h>  // size_t


static const size_t INVALID = ~((size_t)0);

/*dlist_create -- Создать новый пустой двусвязный список. Размер элемента -- itemSize байт.*/
void* dlist_create(size_t itemSize);
/*dlist_destroy -- Удалить существующий двусвязный список. 
Если указана функция destroy, то вызвать её для каждого удаляемого элемента.*/
void dlist_destroy(void* dlist, void(*destroy)(void*));

/*dlist_init -- Инициализировать двусвязный список. Размер элемента -- itemSize байт.*/
void* dlist_init(void* dlist, size_t itemSize, void(*destroy)(void*));
/*dlist_clear -- Удалить все элементы из двусвязного списка. 
Если указана функция destroy, то вызвать её для каждого удаляемого элемента. */
void dlist_clear(void* dlist, void(*destroy)(void*));
/*dlist_count -- Количество элементов в списке.*/
size_t dlist_count(const void* dlist);
/*dlist_item -- Получить элемент по индексу в списке.*/
void* dlist_item(void* dlist, size_t i);
/*dlist_append -- Добавить элемент в хвост двусвязного списка. В случае успеха, функция возвращает указатель на добавленный элемент, иначе -- NULL.*/
void* dlist_append(void* dlist);
/*dlist_prepend -- Добавить элемент в голову двусвязного списка. В случае успеха, функция возвращает указатель на добавленный элемент, иначе -- NULL.*/
void* dlist_prepend(void* dlist);
/*dlist_removeFirst -- Удалить элемент из головы двусвязного списка.Если указана функция destroy, то вызвать её для удаляемого элемента.*/
void dlist_removeFirst(void* dlist, void(*destroy)(void*));
/*dlist_removeLast -- Удалить элемент из хвоста двусвязного списка. Если указана функция destroy, то вызвать её для удаляемого элемента.*/
void dlist_removeLast(void* dlist, void(*destroy)(void*));
/*dlist_first -- Идентификатор для первого элемента из двусвязного списка. Идентификатор может стать невалидным при модификации списка.*/
size_t dlist_first(const void* dlist);
/*dlist_last -- Идентификатор для последнего элемента из двусвязного списка. Идентификатор может стать невалидным при модификации списка.*/
size_t dlist_last(const void* dlist);
/*dlist_next -- По идентификатору текущего элемента получить идентификатор следующего элемента списка.*/
size_t dlist_next(const void* dlist, size_t item_id);
/*dlist_prev -- По идентификатору текущего элемента получить идентификатор предыдущего элемента списка.*/
size_t dlist_prev(const void* dlist, size_t item_id);
/*dlist_stop -- Идентификатор, получаемый при попытке обратиться к элементу за пределами списка.*/
size_t dlist_stop(const void* dlist);
/*dlist_current -- Получить указатель на элемент списка по его идентификатору.*/
void* dlist_current(const void* dlist, size_t item_id);
/*dlist_insertAfter -- Вставка нового элемента списка после указанного по идентификатору. 
В случае успеха, функция возвращает указатель на вставленный элемент, иначе -- NULL.*/
void* dlist_insertAfter(void* dlist, size_t item_id);
/*dlist_insertBefore -- Вставка нового элемента списка перед указанным по идентификатору. 
В случае успеха, функция возвращает указатель на вставленный элемент, иначе -- NULL.*/
void* dlist_insertBefore(void* dlist, size_t item_id);
/*dlist_erase -- Удаление элемента по его идентификатору. Если указана функция destroy, то вызвать её для удаляемого элемента.
После удаления элемента из списка, идентификаторы любых элементов из этого массива могут стать невалидным.*/
void dlist_erase(void* dlist, size_t item_id, void(*destroy)(void*));