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

int listSum(struct list *list);

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

	int sum = listSum(list);
	printf("The sum of the values in the list is: %d\n", sum);

	freeList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

int listSum(struct list *list) {
	// TODO
	struct node *curr = list->head;

	if (curr == NULL) {
		return 0;
	}

	if (curr->next == NULL) {
		return curr->value;
	}
	struct node *remove = list->head;
	list->head = curr->next;
	int value = curr->value;
	free(remove);
	return value + listSum(list);
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

