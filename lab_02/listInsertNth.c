
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

struct list {
	struct node *head;
};

void listInsertNth(struct list *list, int n, int value);

struct list *readList(int size);
struct node *newNode(int value);
void printList(struct list *l);
void freeList(struct list *l);

int main(void) {
	printf("Enter list size: ");
	int size = 0;
	if (scanf("%d", &size) == 0) {
		fprintf(stderr, "error: failed to read list size\n");
		exit(EXIT_FAILURE);
	} else if (size < 0) {
		fprintf(stderr, "error: invalid list size\n");
		exit(EXIT_FAILURE);
	}

	if (size > 0) {
		printf("Enter list values: ");
	}
	struct list *list = readList(size);

	printf("List: ");
	printList(list);
	printf("\n");

	printf("Enter position and value to insert: ");
	int n = 0;
	int value = 0;
	if (scanf("%d %d", &n, &value) != 2) {
		fprintf(stderr, "error: failed to read position/value\n");
		exit(EXIT_FAILURE);
	}

	listInsertNth(list, n, value);
	printf("List after inserting %d at position %d: ", value, n);
	printList(list);
	printf("\n");

	freeList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

void listInsertNth(struct list *list, int n, int value) {
	// TODO
	n -= 1;
	struct node *curr = list->head;
	if (curr == NULL) {
		struct node *new_node = newNode(value);
		list->head = new_node;
	} else if (n < 0) {
		struct node *new_node = newNode(value);
		new_node->next = list->head;
		list->head = new_node;
	} else if (n == 0) {
		struct node *new_node = newNode(value);
		new_node->next = curr->next;
		curr->next = new_node;
	} else if (curr->next == NULL) {
		struct node *new_node = newNode(value);
		curr->next = new_node;
	}
	else {
		struct list *clone_list = malloc(sizeof(struct list));
		clone_list->head = curr->next;
		listInsertNth(clone_list, n, value);
		free(clone_list);
	}
}

////////////////////////////////////////////////////////////////////////
// !!! DO NOT MODIFY THE CODE BELOW !!!

struct list *readList(int size) {
	struct list *list = malloc(sizeof(struct list));
	if (list == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;

	struct node *curr = NULL;

	for (int i = 0; i < size; i++) {
		int value;
		if (scanf("%d", &value) != 1) {
			break;
		}

		struct node *n = newNode(value);

		if (list->head == NULL) {
			list->head = n;
		} else {
			curr->next = n;
		}
		curr = n;
	}

	return list;
}

struct node *newNode(int value) {
	struct node *n = malloc(sizeof(struct node));
	if (n == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	n->value = value;
	n->next = NULL;
	return n;
}

void printList(struct list *l) {
	printf("[");
	for (struct node *curr = l->head; curr != NULL; curr = curr->next) {
		printf("%d", curr->value);
		if (curr->next != NULL) {
			printf(", ");
		}
	}
	printf("]");
}

void freeList(struct list *l) {
	struct node *curr = l->head;
	while (curr != NULL) {
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(l);
}

