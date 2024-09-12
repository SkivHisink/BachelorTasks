# Задача «Бинарное дерево поиска (BST)»
## Описание
Реализовать модуль для работы с бинарными деревьями поиска (binary search tree). Подразумеваются обычные деревья, без балансировки.

*C interface*:
```C
typedef void * Pointer;

typedef int (*CmpFunc)(Pointer data1, Pointer data2);

typedef struct tBSTNode {
    Pointer data;
    /* ... */
} BSTNode;

typedef struct tBST {
    BSTNode *root;
    CmpFunc cmp_func; /* all data comparisons should be done
                         with help of this func! */
    /* ... */
} BST;

// Create empty tree
BST * bst_create(CmpFunc cmp_func);

// Clear tree but do not destroy tree struct
void bst_clear(BST *tree);

// Completely destroy tree
void bst_destroy(BST *tree);

size_t bst_size(BST *tree);

// Find element with equal data and return its data if any else NULL
Pointer bst_find(BST *tree, Pointer data);

// Return data which was replaced by this insertion if any else NULL
Pointer bst_insert(BST *tree, Pointer data);

// Delete node with equal data and return its data if any else NULL
Pointer bst_delete(BST *tree, Pointer data);

// Call foreach_func for every node's data in tree passing given extra_data
void bst_foreach(BST *tree,
                 void (*foreach_func)(Pointer data, Pointer extra_data),
                 Pointer extra_data);
```
## Применение
* Для лучшего понимания нужно реализовать абстрактный тип данных ассоциативный массив (отображение, словарь, map) с использованием данного дерева.

### C interface: 
* В таком случае в дереве будут храниться указатели на Entry, содержащие ключ, по которому работает функция сравнения, и некоторое значение, соответствующее ключу.
```C
typedef struct tEntry {
    Pointer key;
    Pointer value;
}
```
* Каждая функция модуля должна быть протестирована с помощью `assert`. Также предусмотреть нагрузочное тестирование: добавление большого числа случайных элементов в дерево, затем извлечение всех элементов, которые были добавлены.

## Ссылка
Оригинал: https://opk.afti.ru/tasks/binarnoe-derevo-poiska-bst