
CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all:test_sort_the_trio

test_sort_the_trio: sort_the_trio.c test_sort_the_trio.c 
	$(CC) $(CFLAGS) -o test_sort_the_trio test_sort_the_trio.c sort_the_trio.c

clean:
	rm -f test_sort_the_trio

