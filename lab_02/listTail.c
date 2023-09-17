#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

int listTail(struct node *list);

struct node *readList(int size);
void printList(struct node *list);
void freeList(struct node *list);

int main(void) {
	printf("Enter list size: ");
	int size = 0;
	if (scanf("%d", &size) == 0) {
		fprintf(stderr, "error: failed to read list size\n");
		exit(EXIT_FAILURE);
	} else if (size <= 0) {
		fprintf(stderr, "error: invalid list size\n");
		exit(EXIT_FAILURE);
	}

	printf("Enter list values: ");
	struct node *list = readList(size);

	printf("List: ");
	printList(list);
	printf("\n");

	int last = listTail(list);
	printf("The last element is: %d\n", last);

	freeList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

int listTail(struct node *list) {
	// TODO
	struct node *curr = list;
	if (curr == NULL) {
		return 0;
	}

	if (curr->next == NULL) {
		return curr->value;
	}
	return listTail(curr->next);
}

////////////////////////////////////////////////////////////////////////
// !!! DO NOT MODIFY THE CODE BELOW !!!

struct node *readList(int size) {
	struct node *head = NULL;
	struct node *curr = NULL;

	for (int i = 0; i < size; i++) {
		int value;
		if (scanf("%d", &value) != 1) {
			break;
		}

		struct node *n = malloc(sizeof(struct node));
		if (n == NULL) {
			fprintf(stderr, "error: out of memory\n");
			exit(EXIT_FAILURE);
		}
		n->value = value;
		n->next = NULL;

		if (head == NULL) {
			head = n;
		} else {
			curr->next = n;
		}
		curr = n;
	}

	return head;
}

void printList(struct node *list) {
	printf("[");
	for (struct node *curr = list; curr != NULL; curr = curr->next) {
		printf("%d", curr->value);
		if (curr->next != NULL) {
			printf(", ");
		}
	}
	printf("]");
}

void freeList(struct node *list) {
	struct node *curr = list;
	while (curr != NULL) {
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
}

