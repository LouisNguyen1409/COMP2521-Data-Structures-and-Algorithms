#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <a> <b>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int a = 0;
	int b = 0;
	char c;
	if (sscanf(argv[1], "%d %c", &a, &c) != 1
			|| sscanf(argv[2], "%d %c", &b, &c) != 1) {
		fprintf(stderr, "error: invalid integer(s)\n");
		exit(EXIT_FAILURE);
	} else if (a < 0 || b < 0 || (a == 0 && b == 0)) {
		fprintf(stderr, "error: invalid integer(s)\n");
		exit(EXIT_FAILURE);
	}

	int ans = gcd(a, b);
	printf("The GCD of %d and %d is %d\n", a, b, ans);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

// Returns the GCD of a and b
int gcd(int a, int b) {
	// TODO
	if (b > a) {
		int temp = a;
		a = b;
		b = temp;
	}
	if (a == 0) {
		return b;
	} else if (b == 0) {
		return a;
	}

	if (a % b == 0 ) {
		return b;
	} 
	int remainder = a % b;
	a = b;
	b = remainder;
	return gcd(a, b);
}

