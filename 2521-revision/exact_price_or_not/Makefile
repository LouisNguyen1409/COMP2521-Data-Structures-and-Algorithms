
CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

all: test_exact_price_or_not

test_exact_price_or_not: test_exact_price_or_not.c exact_price_or_not.c
	$(CC) $(CFLAGS) -o test_exact_price_or_not test_exact_price_or_not.c exact_price_or_not.c

clean:
	rm -f test_exact_price_or_not

