#include "BST.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

BST* bst_create(CmpFunc cmp_func)
{
	BST* tree = (BSTNode*)malloc(sizeof(BSTNode));
	if (tree == NULL)
		return NULL;
	tree->cmp_func = cmp_func;
	tree->root = NULL;
	return tree;
}

static BSTNode* bst_add_in_tree(Pointer data)
{
	BSTNode* leaf = (BSTNode*)malloc(sizeof(BSTNode));
	if (leaf == NULL)
		return NULL;
	leaf->data = data;
	leaf->left = NULL;
	leaf->right = NULL;
	return leaf;
}

static BSTNode* destructor(BSTNode* node)
{
	if (node == NULL)
		return NULL;
	if (node->left != NULL)
		destructor(node->left);
	if (node->right != NULL)
		destructor(node->right);
	free(node);
	return NULL;
}

void bst_clear(BST* tree)
{
	if (tree == NULL)
		return;
	tree->root = destructor(tree->root);
}

void bst_destroy(BST* tree)
{
	if (tree == NULL)
		return;
	bst_clear(tree);
	free(tree);
}

static int counter(BSTNode* node)
{
	if (node == NULL)
		return 0;
	int count = 1;
	count += counter(node->left) + counter(node->right);
	return count;
}

size_t bst_size(BST* tree)
{
	if (tree == NULL)
		return 0;
	if (tree->root == NULL)
		return 0;
	return counter(tree->root);
}

static BSTNode* find_node_by_data(BST* tree, Pointer data)
{
	int is_left = 0;
	int cmpRes = 0;
	BSTNode* temp = tree->root;
	BSTNode* prev = tree->root;
	while (temp != NULL) {
		cmpRes = tree->cmp_func(data, temp->data);
		if (tree->cmp_func(prev->data, data) == NULL)
			break;
		prev = temp;
		if (cmpRes < 0) {
			is_left = 1;
			temp = temp->left;
		}
		else if (cmpRes > 0) {
			is_left = 0;
			temp = temp->right;
		}
	}
	return prev;
}

Pointer bst_find(BST* tree, Pointer data)
{
	BSTNode* prev = find_node_by_data(tree, data);
	if (prev == NULL)
		return NULL;
	if (tree->cmp_func(prev->data, data) == NULL)
		return prev->data;
	return NULL;
}

Pointer bst_insert(BST* tree, Pointer data)
{
	if (tree->root == NULL) {
		tree->root = bst_add_in_tree(data);
		return NULL;
	}
	else {
		int is_left = 0;
		int cmpRes = 0;
		BSTNode* temp = tree->root;
		BSTNode* prev = NULL;
		while (temp != NULL) {
			cmpRes = tree->cmp_func(data, temp->data);
			prev = temp;
			if (cmpRes < 0) {
				is_left = 1;
				temp = temp->left;
			}
			else if (cmpRes > 0) {
				is_left = 0;
				temp = temp->right;
			}
			else if (cmpRes == 0) {
				Pointer old_data = prev->data;
				prev->data = data;
				return old_data;
			}
		}
		if (is_left) {
			prev->left = bst_add_in_tree(data);
			return prev->left->data;
		}
		else {
			prev->right = bst_add_in_tree(data);
			return prev->right->data;
		}
	}
	return NULL;//bad return
}

Pointer bst_delete(BST* tree, Pointer data)
{
	int is_left = 0;
	int cmpRes = 0;
	BSTNode* temp = tree->root;
	BSTNode* prev = tree->root;
	BSTNode* prev2 = prev;
	int prev_pos = 0;//0 - left, 1 - right
	while (temp != NULL) {
		cmpRes = tree->cmp_func(data, temp->data);
		if (tree->cmp_func(prev->data, data) == NULL)
			break;
		prev2 = prev;
		prev = temp;
		if (cmpRes < 0) {
			is_left = 1;
			temp = temp->left;
		}
		else if (cmpRes > 0) {
			is_left = 0;
			temp = temp->right;
		}
	}
	if (prev == NULL)
		return NULL;
	if (tree->cmp_func(prev->data, data) != NULL)
		return NULL;
	if (prev2->left == prev)
		prev_pos = 0;
	if (prev2->right == prev)
		prev_pos = 1;
	BSTNode* to_delete = prev;
	Pointer to_return = prev->data;
	if (prev->left == NULL && prev->right == NULL) {
		if (tree->cmp_func(prev->data, tree->root->data) == NULL) {
			tree->root = NULL;
			free(to_delete);
			return to_return;
		}
		if (prev_pos)
			prev2->right = NULL;
		else
			prev2->left = NULL;
	}
	else if (prev->right == NULL) { //Right branch is empty
		if (prev_pos)
			prev2->right = prev->left;
		else
			prev2->left = prev->left;
	}
	else if (prev->left == NULL) { //Right branch is empty
		if (prev_pos)
			prev2->right = prev->right;
		else
			prev2->left = prev->right;

	}
	else {						   // Two branches aren't empty
		BSTNode* next_prev = prev->right->right;
		temp = prev->right;
		BSTNode* temp_prev = temp;
		while (temp->left != NULL) {
			temp_prev = temp;
			temp = temp->left;
		}
		if (temp->right != NULL)
			temp_prev->left = temp->right;
		if (prev->right == temp)
			temp->right = NULL;
		else
			temp->right = prev->right;
		temp->left = prev->left;
		if (prev2 == tree->root && prev == tree->root) {
			BSTNode* temp2=tree->root;
			while (temp2!=NULL) {
				cmpRes = tree->cmp_func(temp->data, temp2->data);
				if (tree->cmp_func(prev->data, temp->data) == NULL)
					break;
				prev2 = prev;
				prev = temp2;
				if (cmpRes < 0) {
					is_left = 1;
					temp2 = temp2->left;
				}
				else if (cmpRes > 0) {
					is_left = 0;
					temp2 = temp2->right;
				}
			}
			if (!is_left)
				prev2->right = NULL;
			else
				prev2->left = NULL;
			tree->root->data = temp->data;
			free(temp);
			return to_return;
		}
		if (prev_pos)
			prev2->right = temp;
		else
			prev2->left = temp;
	}
	free(to_delete);
	return to_return;
}

static void summon_beast(BSTNode* node, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data)
{
	if (node == NULL)
		return;
	if (node->left != NULL)
		summon_beast(node->left, foreach_func, extra_data);
	if (node->right != NULL)
		summon_beast(node->right, foreach_func, extra_data);
	foreach_func(node->data, extra_data);
}

void bst_foreach(BST* tree, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data)
{
	if (tree == NULL)
		return;
	summon_beast(tree->root, foreach_func, extra_data);
}


//
//static void deleter(BSTNode* preroot, BSTNode* root)
//{
//	if ((root->left == NULL) && (root->right == NULL)) {
//		if (preroot->left == root)
//			preroot->left = NULL;
//		if (preroot->right == root)
//			preroot->right = NULL;
//		free(root);
//		root = NULL;
//		return(0);
//	}
//	if ((root->left == NULL)) {
//		if (preroot->left == root)
//			preroot->left = root->right;
//		if (preroot->right == root)
//			preroot->right = root->right;
//		free(root);
//		root = NULL;
//		return(0);
//	}
//	if ((root->right == NULL)) {
//		if (preroot->left == root)
//			preroot->left = root->left;
//		if (preroot->right == root)
//			preroot->right = root->left;
//		free(root);
//		root = NULL;
//		return(0);
//	}
//
//	BSTNode* pretemp = root;
//	BSTNode* temp = root->right;
//	while (1) {
//		if (temp->left == NULL) {
//			root->data = temp->data;
//			deleter(pretemp, temp);
//			break;
//		}
//		pretemp = temp;
//		temp = temp->left;
//	}
//}
//
//Pointer bst_delete(BST* tree, Pointer data)
//{
//	if (tree->root == NULL) {
//		return(0);
//	}
//	BSTNode* temp;
//	BSTNode* pretemp = memalloc();
//	BSTNode* memory_flag = pretemp;
//
//	temp = tree->root;
//	pretemp->right = temp;
//	pretemp->left = temp;
//	while (1) {
//		if (tree->cmp_func(temp->data, data) == 1) {
//			if (temp->left == NULL) {
//				free(memory_flag);
//				return(NULL);
//			}
//			pretemp = temp;
//			temp = temp->left;
//		}
//		if (tree->cmp_func(temp->data, data) == -1) {
//			if (temp->right == NULL) {
//				free(memory_flag);
//				return(NULL);
//			}
//			pretemp = temp;
//			temp = temp->right;
//		}
//		if (tree->cmp_func(temp->data, data) == 0)
//			break;
//	}
//
//	Pointer buffer = temp->data;
//	deleter(pretemp, temp);
//	tree->root = memory_flag->right;
//	free(memory_flag);
//	return(buffer);
//}
