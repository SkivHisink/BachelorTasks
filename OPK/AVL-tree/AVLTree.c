#include "AVLTree.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>
AVLTree* avl_create(CmpFunc cmp_func)
{
	AVLTree* tree = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
	if (tree == NULL)
		return NULL;
	tree->cmp_func = cmp_func;
	tree->root = NULL;
	return tree;
}

static AVLTreeNode* avl_add_in_tree(Pointer data)
{
	AVLTreeNode* leaf = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
	if (leaf == NULL)
		return NULL;
	leaf->data = data;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->parent = NULL;
	leaf->high = 1;
	return leaf;
}

static AVLTreeNode* destructor(AVLTreeNode* node)
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

void avl_clear(AVLTree* tree)
{
	if (tree == NULL)
		return;
	tree->root = destructor(tree->root);
}

void avl_destroy(AVLTree* tree)
{
	if (tree == NULL)
		return;
	avl_clear(tree);
	free(tree);
}

int avl_check_mid_hook(AVLTreeNode* node, CmpFunc cmp, Pointer data, int i)
{
	if (node == NULL)
		return 1;
	assert(cmp(node->data, data) == i);
	avl_check_mid_hook(node->left, cmp, data, i);
	avl_check_mid_hook(node->right, cmp, data, i);
}

int avl_check_all_elem(AVLTreeNode* node, CmpFunc cmp)
{
	if (node == NULL)
		return 1;
	avl_check_mid_hook(node->left, cmp, node->data, -1);
	avl_check_mid_hook(node->right, cmp, node->data, 1);
}

int avl_check_high(AVLTreeNode* root)
{
	if (root == NULL)
		return 0;
	return 1 + max(avl_check_high(root->left), avl_check_high(root->right));
}

int avl_check(AVLTreeNode* root, CmpFunc cmp)
{
	if (root == NULL)
		return 1;
	avl_check_all_elem(root, cmp);
	assert(avl_get_balance(root) < 2 && avl_get_balance(root) > -2);
	assert(root->high = avl_check_high(root));
	if (root->left != NULL) {
		assert(cmp(root->left->data, root->data) == -1);
		assert(avl_check(root->left, cmp));
	}
	if (root->right != NULL) {
		assert(cmp(root->right->data, root->data) == 1);
		assert(avl_check(root->right, cmp));
	}
}

static int counter(AVLTreeNode* node)
{
	if (node == NULL)
		return 0;
	int count = 1;
	count += counter(node->left) + counter(node->right);
	return count;
}

size_t avl_size(AVLTree* tree)
{
	if (tree == NULL)
		return 0;
	if (tree->root == NULL)
		return 0;
	return counter(tree->root);
}

static AVLTreeNode* find_node_by_data(AVLTree* tree, Pointer data)
{
	int is_left = 0;
	int cmpRes = 0;
	AVLTreeNode* temp = tree->root;
	AVLTreeNode* prev = tree->root;
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

Pointer avl_find(AVLTree* tree, Pointer data)
{
	AVLTreeNode* prev = find_node_by_data(tree, data);
	if (prev == NULL)
		return NULL;
	if (tree->cmp_func(prev->data, data) == NULL)
		return prev->data;
	return NULL;
}

static int avl_get_balance(AVLTreeNode* node)
{
	if (node->left != NULL && node->right != NULL)
		return node->left->high - node->right->high;
	else if (node->left != NULL)
		return node->left->high;
	else if (node->right != NULL)
		return -node->right->high;
	else
		return 0;
}

static int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

static int avl_high(AVLTreeNode* temp)
{
	if (temp != NULL) {
		if ((temp->left != NULL) && (temp->right != NULL))
			return max(temp->left->high, temp->right->high) + 1;
		else if (temp->left != NULL)
			return temp->left->high + 1;
		else if (temp->right != NULL)
			return temp->right->high + 1;
		else
			return 1;
	}
	return 0;
}

static AVLTreeNode* avl_rebalance(AVLTreeNode* node)
{
	if (node == NULL)
		return NULL;
	AVLTreeNode* temp = node;
	AVLTreeNode* virt_parent = NULL;
	int is_left = 0;
	if (temp == NULL)
		return node;
	if ((temp->parent == NULL) && (avl_get_balance<1 && avl_get_balance>-1)) {
		return temp;
	}
	while (temp != NULL) {
		int balance;
		AVLTreeNode* A, * B, * C;
		if (temp->left != NULL) {
			temp->left->high = avl_high(temp->left);
			balance = avl_get_balance(temp->left);
			if (balance > 1 || balance < -1) {
				temp = temp->left;
				assert(0);
			}
		}
		if (temp->right != NULL) {
			temp->right->high = avl_high(temp->right);
			balance = avl_get_balance(temp->right);
			if (balance > 1 || balance < -1) {
				temp = temp->right;
				assert(0);
			}
		}
		temp->high = avl_high(temp);
		if (temp->parent == NULL) {
			virt_parent = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
			if (virt_parent == NULL)
				return NULL; // bad allocation
			virt_parent->left = temp;
			virt_parent->right = temp;
			virt_parent->parent = NULL;
			temp->parent = virt_parent;
		}
		if (avl_get_balance(temp) > 1) { //left turns
			A = temp->left;
			if (temp == temp->parent->left)
				is_left = 1;
			if (avl_get_balance(A) >= 0) { //low left
				B = temp;
				if (is_left)
					B->parent->left = A;
				else
					B->parent->right = A;
				A->parent = B->parent;
				B->parent = A;
				B->left = A->right;
				if (B->left != NULL)
					B->left->parent = B;
				A->right = B;
				B->high = avl_high(B);
				A->high = avl_high(A);
				if (A->parent != NULL)
					A->parent->high = avl_high(A->parent);
			}
			else { //big left
				C = temp;
				B = A->right;
				if (is_left)
					C->parent->left = B;
				else
					C->parent->right = B;
				B->parent = C->parent;
				A->right = B->left;
				if (A->right != NULL)
					A->right->parent = A;
				B->left = A;
				A->parent = B;
				C->left = B->right;
				if (B->right != NULL)
					B->right->parent = C;
				B->right = C;
				C->parent = B;
			}
		}
		else if (avl_get_balance(temp) < -1) { // right turns
			A = temp->right;
			if (temp == temp->parent->left)
				is_left = 1;
			if (avl_get_balance(temp->right) <= 0) { //low right
				B = temp;
				if (is_left)
					B->parent->left = A;
				else
					B->parent->right = A;
				A->parent = B->parent;
				B->parent = A;
				B->right = A->left;
				if (B->right != NULL)
					B->right->parent = B;
				A->left = B;
				B->high = avl_high(B);
				A->high = avl_high(A);
				if (A->parent != NULL)
					A->parent->high = avl_high(A->parent);
			}
			else { //big right
				C = temp;
				B = A->left;
				if (is_left)
					C->parent->left = B;
				else
					C->parent->right = B;
				B->parent = C->parent;
				A->left = B->right;
				if (A->left != NULL)
					A->left->parent = A;
				B->right = A;
				A->parent = B;
				C->right = B->left;
				if (B->left != NULL)
					B->left->parent = C;
				B->left = C;
				C->parent = B;
			}
		}
		else {}
		if (temp->left != NULL) {
			if (temp->left->left != NULL)
				temp->left->left->high = avl_high(temp->left->left);
			if (temp->left->right != NULL)
				temp->left->right->high = avl_high(temp->left->right);
		}
		if (temp->right != NULL) {
			if (temp->right->left != NULL)
				temp->right->left->high = avl_high(temp->right->left);
			if (temp->right->right != NULL)
				temp->right->right->high = avl_high(temp->right->right);
		}
		if (temp->left != NULL)
			temp->left->high = avl_high(temp->left);
		if (temp->right != NULL)
			temp->right->high = avl_high(temp->right);
		if (temp != NULL)
			temp->high = avl_high(temp);
		if (temp->parent != NULL && virt_parent == NULL)
			temp->parent->high = avl_high(temp->parent);
		if (virt_parent != NULL) {
			AVLTreeNode* buffer = virt_parent->left;
			buffer->parent = NULL;
			free(virt_parent);
			return buffer;
		}
		temp = temp->parent;
	}
	assert(NULL); //bad trip
	return NULL; //bad return
}

Pointer avl_insert(AVLTree* tree, Pointer data)
{
	if (tree->root == NULL) {
		tree->root = avl_add_in_tree(data);
		tree->root->parent = NULL;
		return NULL;
	}
	else {
		int is_left = 0;
		int cmpRes = 0;
		AVLTreeNode* temp = tree->root;
		AVLTreeNode* prev = NULL;
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
			else if (!cmpRes)
				break;
		}
		if (cmpRes == 0) {
			Pointer old_data = temp->data;
			temp->data = data;
			return old_data;
		}
		if (is_left) {
			prev->left = avl_add_in_tree(data);
			prev->left->parent = prev;
			tree->root = avl_rebalance(prev->left);
			avl_check(tree->root, tree->cmp_func);
			return data;
		}
		else {
			prev->right = avl_add_in_tree(data);
			prev->right->parent = prev;
			tree->root = avl_rebalance(prev->right);
			avl_check(tree->root, tree->cmp_func);
			return data;
		}
	}
	assert(NULL);
}

static AVLTreeNode* deleter(AVLTree* tree, AVLTreeNode* root)
{
	if ((root->left == NULL) && (root->right == NULL)) {
		if (root->parent != NULL) {
			if (root->parent->left == root)
				root->parent->left = NULL;
			if (root->parent->right == root)
				root->parent->right = NULL;
		}
		AVLTreeNode* buffer = root->parent;
		free(root);
		root = NULL;
		if (buffer != NULL)
			buffer->high = avl_high(buffer);
		return buffer;
	}
	if ((root->left == NULL)) {
		if (root->parent != NULL) {
			if (root->parent->left == root)
				root->parent->left = root->right;
			if (root->parent->right == root)
				root->parent->right = root->right;
		}
		root->right->parent = root->parent;
		AVLTreeNode* buffer = root->right;
		free(root);
		root = NULL;
		buffer->high = avl_high(buffer);
		return buffer;
	}
	if ((root->right == NULL)) {
		if (root->parent != NULL) {
			if (root->parent->left == root)
				root->parent->left = root->left;
			if (root->parent->right == root)
				root->parent->right = root->left;
		}
		root->left->parent = root->parent;
		AVLTreeNode* buffer = root->left;
		free(root);
		root = NULL;
		buffer->high = avl_high(buffer);
		return buffer;
	}
	AVLTreeNode* temp = root->right;
	temp->high = avl_high(temp);
	while (1) {
		if (temp->left == NULL) {
			root->data = temp->data;
			return deleter(tree, temp);
			break;
		}
		temp = temp->left;
		temp->high = avl_high(temp);
	}
}

Pointer avl_delete(AVLTree* tree, Pointer data)
{
	if (tree->root == NULL)
		return NULL;
	AVLTreeNode* temp;
	temp = tree->root;
	while (1) {
		if (tree->cmp_func(temp->data, data) == 1) {
			if (temp->left == NULL) {
				return NULL;
			}
			temp = temp->left;
		}
		if (tree->cmp_func(temp->data, data) == -1) {
			if (temp->right == NULL) {
				return NULL;
			}
			temp = temp->right;
		}
		if (tree->cmp_func(temp->data, data) == 0)
			break;
	}
	Pointer buffer = temp->data;
	tree->root = avl_rebalance(deleter(tree, temp));
	avl_check(tree->root, tree->cmp_func);
	return buffer;
}

static void summon_beast(AVLTreeNode* node, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data)
{
	if (node == NULL)
		return;
	if (node->left != NULL)
		summon_beast(node->left, foreach_func, extra_data);
	if (node->right != NULL)
		summon_beast(node->right, foreach_func, extra_data);
	foreach_func(node->data, extra_data);
}

void avl_foreach(AVLTree* tree, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data)
{
	if (tree == NULL)
		return;
	summon_beast(tree->root, foreach_func, extra_data);
}
