
CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all: bstree_kth_largest

bstree_kth_largest: test_bstree_kth_largest.c bstree.c bstree_kth_largest.c
	$(CC) $(CFLAGS) -o test_bstree_kth_largest test_bstree_kth_largest.c bstree.c bstree_kth_largest.c

clean:
	rm -f test_bstree_kth_largest

