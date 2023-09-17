// Implementation of the Multiset ADT using a balanced BST
// COMP2521 23T2 Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Mset.h"
#include "MsetStructs.h"

int cnt = 0;

////////////////////////////////////////////////////////////////////////
// Helper Functions
static struct mset *new_tree();
static struct node *new_node(int item, int count);
static int height_diff(struct node *root);
static int compare_max(int left_h, int right_h);
static int compare_min(int left_h, int right_h);
static int balance(struct node *root);
static struct node *rotate_right(struct node *curr);
static struct node *rotate_left(struct node *curr);
static int largest_value(struct node *curr);
static bool avl_find(struct node *root, int item);
static void union_traversal(Mset s3, struct node *root2);
static void intersection_traversal(Mset s3, struct node *root1, struct node *root2);
static struct node *avl_node_find(struct node *root, int item);
static void copy_set(Mset s3, struct node *root1);
static void sum_traveresal(Mset s3, struct node *root2);
static void diff_traversal(Mset s3, struct node *root1, struct node *root2);
static void include_traversal(struct node *root1, struct node *root2, bool *result);
static void equal_traversal(struct node *root1, struct node *root2, bool *result);
static bool in_array(struct item items[], int length, int item);
static void most_common(struct node *root, int *common, struct item items[],
						int *item,int length);
static void free_tree(struct node *root);
static struct node *insert_tree(struct node *root, int item, int *size,
								struct ll **head, struct node *parent);
static struct node *insert_many(struct node *root, int item, int amount,
								int *size, struct ll **head, struct node *parent);
static void show_traversal(struct node *root, int largest);
static struct ll *new_ll_node(int item, int count);
static void add_node(struct node *parent, struct node *new);
// Basic Operations
/**
 * Creates a new empty mset
 */
Mset MsetNew(void) {
	struct mset *new = new_tree();
	return new;
}
static struct mset *new_tree() {
	struct mset *new = malloc(sizeof(struct mset));
	if (new == NULL) {
		fprintf(stderr, "Insufficient memory\n");
        exit(EXIT_FAILURE);
	}
	new->tree = NULL;
	new->size = 0;
	new->total_count = 0;
	new->head = NULL;
	return new;
}

/**
 * Frees all memory allocated to the given mset
 */
void MsetFree(Mset s) {
	free_tree(s->tree);
	free(s);
}
static void free_tree(struct node *root) {
	if (root == NULL) {
		return;
	}
	free_tree(root->left);
	free_tree(root->right);
	free(root->node);
	free(root);
}

/**
 * Inserts one of an item into the mset. Does nothing if the item is
 * equal to UNDEFINED.
 */
void MsetInsert(Mset s, int item) {
	s->tree = insert_tree(s->tree, item, &s->size, &s->head, NULL);
	s->total_count += 1;

}
static struct node *insert_tree(struct node *root, int item, int *size,
								struct ll **head, struct node *parent) {
	if (root == NULL) {
		*size += 1;
		struct node *new = new_node(item, 1);

		if (parent != NULL) {
			add_node(parent, new);
		}
		if (new->node->pre == NULL) {
			*head = new->node;
		}
		return new;
	} else if (item < root->item) {
		root->left = insert_tree(root->left, item, size, head, root);
	} else if (item > root->item) {
		root->right = insert_tree(root->right, item, size, head, root);
	} else if (item == root->item) {
		root->count++;
		root->node->count++;
	}
	root->height = 1 + compare_max(height_diff(root->left), height_diff(root->right));
	int bal = balance(root);

	if (bal > 1 && item < root->left->item) {
		return rotate_right(root);
	} else if (bal < -1 && item > root->right->item) {
		return rotate_left(root);
	} else if (bal > 1 && item > root->left->item) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	} else if (bal < -1 && item < root->right->item) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}
static void add_node(struct node *parent, struct node *new) {
	if (parent->node->item > new->node->item) {
		new->node->next = parent->node;
		new->node->pre = parent->node->pre;
		if (parent->node->pre != NULL) {
			parent->node->pre->next = new->node;
		}
		parent->node->pre = new->node;
	} else if (parent->node->item < new->node->item) {
		new->node->pre = parent->node;
		new->node->next = parent->node->next;
		if (parent->node->next != NULL) {
			parent->node->next->pre = new->node;
		}
		parent->node->next = new->node;
	}
}
static struct ll *new_ll_node(int item, int count) {
	struct ll *new = malloc(sizeof(struct ll));
	if (new == NULL) {
		fprintf(stderr, "Insufficient memory\n");
		exit(EXIT_FAILURE);
	}
	new->item = item;
	new->count = count;
	new->next = NULL;
	new->pre = NULL;
	return new;
}
static struct node *new_node(int item, int count) {
	struct node *new = malloc(sizeof(struct node));
	if (new == NULL) {
		fprintf(stderr, "Insufficient memory\n");
		exit(EXIT_FAILURE);
	}
	new->item = item;
	new->count = count;
	new->left = NULL;
	new->right = NULL;
	new->height = 1;
	new->node = new_ll_node(item ,count);
	return new;
}
static int height_diff(struct node *root) {
	if (root == NULL) {
		return 0;
	}
	return root->height;
}
static int compare_max(int left_h, int right_h) {
	if (left_h < right_h) {
		return right_h;
	}
	return left_h;
}
static int balance(struct node *root) {
	if (root == NULL) {
		return 0;
	}
	return height_diff(root->left) - height_diff(root->right);
}
static struct node *rotate_right(struct node *curr) {
	if (curr == NULL || curr->left == NULL) {
		return curr;
	}
	struct node *left = curr->left;

	// Replace code
	struct node *t = left->right;
	left->right = curr;
	curr->left = t;
	curr->height = compare_max(height_diff(curr->left),
								height_diff(curr->right)) + 1;
	left->height = compare_max(height_diff(left->left),
								height_diff(left->right)) + 1;
	//
	// Old code
	// curr->left = left->right;
	// left->right = curr;
	// left->height = compare_max(height_diff(left->left), height_diff(left->right)) + 1;
	// curr->height = compare_max(height_diff(curr->left), height_diff(curr->right)) + 1;
	//
	return left;
}
static struct node *rotate_left(struct node *curr) {
	if (curr == NULL || curr->right == NULL) {
		return curr;
	}
	struct node *right = curr->right;
	// Replace
	struct node *t = right->left;
	right->left = curr;
	curr->right = t;
	curr->height = compare_max(height_diff(curr->left),
								height_diff(curr->right)) + 1;
	right->height = compare_max(height_diff(right->left),
								height_diff(right->right)) + 1;
	//
	// Old code
	// curr->right = right->left;
	// right->left = curr;
	// right->height = compare_max(height_diff(right->left), height_diff(right->right)) + 1;
	// curr->height = compare_max(height_diff(curr->left), height_diff(curr->right)) + 1;
	//
	return right;
}

/**
 * Inserts the given amount of an item into the mset. Does nothing if
 * the item is equal to UNDEFINED or the given amount is 0 or less.
 */
void MsetInsertMany(Mset s, int item, int amount) {
	if (item == UNDEFINED || amount <= 0) {
		return;
	}
	s->tree = insert_many(s->tree, item, amount, &s->size, &s->head, NULL);
	s->total_count += amount;
}
static struct node *insert_many(struct node *root, int item, int amount,
								int *size, struct ll **head, struct node *parent) {
	if (root == NULL) {
		*size += 1;
		struct node *new = new_node(item, amount);
		if (parent != NULL) {
			add_node(parent, new);
		}
		if (new->node->pre == NULL) {
			*head = new->node;
		}
		return new;
	} else if (item < root->item) {
		root->left = insert_many(root->left, item, amount, size, head, root);
	} else if (item > root->item) {
		root->right = insert_many(root->right, item, amount, size, head, root);
	} else if (item == root->item) {
		root->count += amount;
		root->node->count += amount;
	}
	root->height = 1 + compare_max(height_diff(root->left), height_diff(root->right));
	int bal = balance(root);

	if (bal > 1 && item < root->left->item) {
		return rotate_right(root);
	} else if (bal < -1 && item > root->right->item) {
		return rotate_left(root);
	} else if (bal > 1 && item > root->left->item) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	} else if (bal < -1 && item < root->right->item) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}

/**
 * Returns the number of distinct elements in the mset
 */
int MsetSize(Mset s) {
	return s->size;
}

/**
 * Returns the sum of counts of all elements in the mset
 */
int MsetTotalCount(Mset s) {
	return s->total_count;
}

/**
 * Returns the count of an item in the mset, or 0 if it doesn't occur in
 * the mset
 */
int MsetGetCount(Mset s, int item) {
	if (item == UNDEFINED) {
		return 0;
	}
	struct node *root = s->tree;
	if (avl_find(root, item) == false) {
		return 0;
	}
	struct node *node = avl_node_find(root, item);
	return node->count;
}
static bool avl_find(struct node *root, int item) {
	if (root == NULL) {
		return false;
	} else if (item < root->item) {
		return avl_find(root->left, item);
	} else if (item > root->item) {
		return avl_find(root->right, item);
	} else if (item == root->item) {
		return true;
	}
	return false;
}
static struct node *avl_node_find(struct node *root, int item) {
	if (root == NULL) {
		return NULL;
	} else if (item < root->item) {
		return avl_node_find(root->left, item);
	} else if (item > root->item) {
		return avl_node_find(root->right, item);
	} else if (item == root->item) {
		return root;
	}
	return root;
}

/**
 * Prints the given mset in the format
 * {(elem1, count1), (elem2, count2), (elem3, count3)}
 * where the elements are in increasing order
 */
void MsetShow(Mset s) {
	if (s->tree == NULL) {
		printf("{}");
		return;
	}
	printf("{");
	int largest = largest_value(s->tree);
	show_traversal(s->tree, largest);
}
static void show_traversal(struct node *root, int largest) {
	if (root == NULL) {
		return;
	}
	show_traversal(root->left, largest);
	printf("(%d, %d)", root->item, root->count);
	if (root->item != largest) {
		printf(", ");
	} else {
		printf("}");
	}
	show_traversal(root->right, largest);
}
static int largest_value(struct node *curr) {
	if (curr == NULL) {
		return UNDEFINED;
	}
	while (curr->right != NULL) {
		curr = curr->right;
	}
	return curr->item;
}

////////////////////////////////////////////////////////////////////////

// Advanced Operations

/**
 * Returns a new mset representing the union of the two msets
 */
Mset MsetUnion(Mset s1, Mset s2) {
	
	Mset s3 = MsetNew();
	struct node *root1 = s1->tree;
	struct node *root2 = s2->tree;
	if (root1 == NULL && root2 == NULL) {
		return s3;
	} else if (root1 == NULL) {
		copy_set(s3, root2);
		return s3;
	} else if (root2 == NULL) {
		copy_set(s3, root1);
		return s3;
	}
	copy_set(s3, root1);
	union_traversal(s3, root2);
	printf("%d", cnt);
	return s3;
}
static void copy_set(Mset s3, struct node *root1) {
	if (root1 == NULL) {
		return;
	}
	copy_set(s3, root1->left);
	MsetInsertMany(s3, root1->item, root1->count);
	copy_set(s3, root1->right);
}
static void union_traversal(Mset s3, struct node *root2) {
	cnt++;
	struct node *root1 = s3->tree;
	if (root2 == NULL) {
		return;
	}
	union_traversal(s3, root2->left);
	if (avl_find(root1, root2->item) == false) {
		MsetInsertMany(s3, root2->item, root2->count);
	} else if (avl_find(root1, root2->item) == true) {
		struct node *node1 = avl_node_find(root1, root2->item);
		int min = compare_min(node1->count, root2->count);
		if (min == node1->count) {
			s3->total_count += root2->count - node1->count;
		}
		node1->count = compare_max(node1->count, root2->count);
	}
	union_traversal(s3, root2->right);
}
static int compare_min(int left_h, int right_h) {
	if (left_h < right_h) {
		return left_h;
	}
	return right_h;
}

/**
 * Returns a new mset representing the intersection of two msets
 */
Mset MsetIntersection(Mset s1, Mset s2) {
	Mset s3 = MsetNew();
	struct node *root1 = s1->tree;
	struct node *root2 = s2->tree;
	if (root1 == NULL && root2 == NULL) {
		return s3;
	} else if (root1 == NULL) {
		return s3;
	} else if (root2 == NULL) {
		return s3;
	}
	intersection_traversal(s3, root1, root2);
	return s3;
}
static void intersection_traversal(Mset s3, struct node *root1, struct node *root2) {
	if (root2 == NULL) {
		return;
	}
	intersection_traversal(s3, root1, root2->left);
	if (avl_find(root1, root2->item) == true) {
		struct node *node1 = avl_node_find(root1, root2->item);
		node1->count = compare_min(node1->count, root2->count);
		MsetInsertMany(s3, root2->item, node1->count);
	}
	intersection_traversal(s3, root1, root2->right);
}

/**
 * Returns a new mset representing the addition of two msets
 */
Mset MsetSum(Mset s1, Mset s2) {
	Mset s3 = MsetNew();
	struct node *root1 = s1->tree;
	struct node *root2 = s2->tree;
	if (root1 == NULL && root2 == NULL) {
		return s3;
	} else if (root1 == NULL) {
		copy_set(s3, root2);
		return s3;
	} else if (root2 == NULL) {
		copy_set(s3, root1);
		return s3;
	}
	copy_set(s3, root1);
	sum_traveresal(s3, root2);
	return s3;
}
static void sum_traveresal(Mset s3, struct node *root2) {
	if (root2 == NULL) {
		return;
	}
	sum_traveresal(s3, root2->left);
	MsetInsertMany(s3, root2->item, root2->count);
	sum_traveresal(s3, root2->right);
}

/**
 * Returns a new mset representing the difference s1 - s2
 */
Mset MsetDifference(Mset s1, Mset s2) {
	Mset s3 = MsetNew();
	struct node *root1 = s1->tree;
	struct node *root2 = s2->tree;
	if (root1 == NULL && root2 == NULL) {
		return s3;
	} else if (root1 == NULL) {
		copy_set(s3, root2);
		return s3;
	} else if (root2 == NULL) {
		copy_set(s3, root1);
		return s3;
	}
	diff_traversal(s3, root1, root2);
	return s3;
}
static void diff_traversal(Mset s3, struct node *root1, struct node *root2) {
	if (root1 == NULL) {
		return;
	}
	diff_traversal(s3, root1->left, root2);
	if (avl_find(root2, root1->item) == false) {
		MsetInsertMany(s3, root1->item, root1->count);
	} else if (avl_find(root2, root1->item) == true) {
		struct node *node2 = avl_node_find(root2, root1->item);
		if (root1->count > node2->count) {
			MsetInsertMany(s3, root1->item, root1->count - node2->count);
		}
	}
	diff_traversal(s3, root1->right, root2);
}

/**
 * Returns true if the mset s1 is included in the mset s2, and false
 * otherwise
 */
bool MsetIncluded(Mset s1, Mset s2) {
	struct node *root1 = s1->tree;
	struct node *root2 = s2->tree;
	if (root1 == NULL && root2 == NULL) {
		return true;
	} else if (root1 == NULL) {
		return true;
	} else if (root2 == NULL) {
		return false;
	}
	bool result = true;
	include_traversal(root1, root2, &result);
	return result;
}
static void include_traversal(struct node *root1, struct node *root2, bool *result) {
	if (root1 == NULL) {
		return;
	}

	include_traversal(root1->left, root2, result);
	if (avl_find(root2, root1->item) == false) {
		*result = false;
		return;
	} else if (avl_find(root2, root1->item) == true) {
		struct node *node2 = avl_node_find(root2, root1->item);
		if (root1->count > node2->count) {
			*result = false;
			return;
		}
	}
	include_traversal(root1->right, root2, result);
}

/**
 * Returns true if the two given msets are equal, and false otherwise
 */
bool MsetEquals(Mset s1, Mset s2) {
	struct node *root1 = s1->tree;
	struct node *root2 = s2->tree;
	if (root1 == NULL && root2 == NULL) {
		return true;
	} else if (root1 == NULL) {
		return false;
	} else if (root2 == NULL) {
		return false;
	}
	bool result = true;
	equal_traversal(root1, root2, &result);
	return result;
}
static void equal_traversal(struct node *root1, struct node *root2, bool *result) {
	if (root1 == NULL) {
		return;
	}

	equal_traversal(root1->left, root2, result);
	if (avl_find(root2, root1->item) == false) {
		*result = false;
		return;
	} else if (avl_find(root2, root1->item) == true) {
		struct node *node2 = avl_node_find(root2, root1->item);
		if (root1->count != node2->count) {
			*result = false;
			return;
		}
	}
	equal_traversal(root1->right, root2, result);
}

/**
 * Stores the k most common elements in the mset into the given items
 * array in decreasing order of count and returns the number of elements
 * stored. Elements with the same count should be stored in increasing
 * order.
 */
int MsetMostCommon(Mset s, int k, struct item items[]) {
	if (k <= 0) {
		return 0;
	}
	struct node *root = s->tree;
	if (root == NULL) {
		return 0;
	}
	int length = 0;
	int item = 0;
	while (length < k && item != -1) {
		item = -1;
		int common = 0;
		most_common(root, &common, items, &item, length);
		items[length].item = item;
		items[length].count = common;
		length++;
	}
	if (item == -1) {
		return length - 1;
	}
	return length;
}
static void most_common(struct node *root, int *common, struct item items[],
						int *item, int length) {
	if (root == NULL) {
		return;
	}
	most_common(root->left, common, items, item, length);
	if (in_array(items, length, root->item) == false && root->count > *common) {
		*item = root->item;
		*common = root->count;
	}
	most_common(root->right, common, items, item, length);
}
static bool in_array(struct item items[], int length, int item) {
	for (int i = 0; i < length; i++) {
		if (items[i].item == item) {
			return true;
		}
	}
	return false;
}


////////////////////////////////////////////////////////////////////////
// Cursor Operations

typedef struct cursor *MsetCursor;

/**
 * Creates a new cursor positioned at the start of the mset
 */
MsetCursor MsetCursorNew(Mset s) {
	struct cursor *new = malloc(sizeof(struct cursor));
	if (new == NULL) {
		fprintf(stderr, "Insufficient memory\n");
		exit(EXIT_FAILURE);
	}
	new->curr = s->head->pre;
	new->next = s->head;
	new->pre = new->curr;
	return new;
}

/**
 * Frees all memory allocated to the given cursor
 */
void MsetCursorFree(MsetCursor cur) {
	free(cur);
}

/**
 * Returns the element at the cursor's position and its count, or
 * {UNDEFINED, 0} if the cursor is positioned at the start or end of
 * the mset.
 */
struct item MsetCursorGet(MsetCursor cur) {
	if (cur->curr == NULL) {
		return (struct item){UNDEFINED, 0};
	}
	return (struct item){cur->curr->item, cur->curr->count};
	return (struct item){UNDEFINED, 0};
}

/**
 * Moves the cursor to the next greatest element, or to the end of the
 * mset if there is no next greatest element. Returns false if the
 * cursor is now at the end of the mset, and true otherwise.
 */
bool MsetCursorNext(MsetCursor cur) {
	cur->pre = cur->curr;
	if (cur->curr == NULL) {
		cur->curr = cur->next;
	} else {
		cur->curr = cur->curr->next;
	}
	
	if (cur->curr != NULL) {
		cur->next = cur->curr->next;
	}
	if (cur->curr == NULL && cur->pre != NULL) {
		return false;
	}
	return true;
}

/**
 * Moves the cursor to the next smallest element, or to the start of the
 * mset if there is no next smallest element. Returns false if the
 * cursor is now at the start of the mset, and true otherwise.
 */
bool MsetCursorPrev(MsetCursor cur) {
	if (cur->curr == NULL && cur->next != NULL) {
		return false;
	}
	cur->next = cur->curr;
	cur->curr = cur->pre;
	if (cur->curr != NULL) {
		cur->pre = cur->curr->pre;
	}
	if (cur->curr == NULL && cur->next != NULL) {
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////

