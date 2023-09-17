// Main program for testing the multiset ADT
// COMP2521 23T2 Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Mset.h"

// These functions are deliberately not static to make testing more
// convenient.

void testMsetInsert(void);
void testMsetInsertMany(void);
void testMsetSize(void);
void testMsetTotalCount(void);
void testMsetGetCount(void);
void testMsetShow(void);

void testMsetUnion(void);
void testMsetIntersection(void);
void testMsetSum(void);
void testMsetDifference(void);
void testMsetIncluded(void);
void testMsetEquals(void);
void testMsetMostCommon(void);

void testMsetCursor1(void);
void testMsetCursor2(void);

int main(int argc, char *argv[]) {
	testMsetInsert();
	testMsetInsertMany();
	testMsetSize();
	testMsetTotalCount();
	testMsetGetCount();
	testMsetShow();
	
	testMsetUnion();
	testMsetIntersection();
	testMsetSum();
	testMsetDifference();
	testMsetIncluded();
	testMsetEquals();
	testMsetMostCommon();
	
	testMsetCursor1();
	testMsetCursor2();
	
}

void testMsetInsert(void) {
	// NOTE: MsetInsert can't be tested on its own unless you have
	//       direct access to the ADT structs, so you should either
	//       #include "MsetStructs.h" or wait until you have implemented
	//       some of the other functions.

	Mset s = MsetNew();

	MsetInsert(s, 4);
	MsetInsert(s, 7);
	MsetInsert(s, 1);
	MsetInsert(s, 3);
	MsetInsert(s, 7);
	MsetInsert(s, 3);
	MsetInsert(s, 7);
	assert(MsetSize(s) == 4);
	assert(MsetTotalCount(s) == 7);
	MsetFree(s);
	printf("MsetInsert passed\n");
}

void testMsetInsertMany(void) {
	// NOTE: The note in testMsetInsert also applies to MsetInsertMany

	Mset s = MsetNew();

	MsetInsertMany(s, 4, 2); // insert two 4's
	MsetInsertMany(s, 7, 3); // insert three 7's
	MsetInsertMany(s, 1, 5); // insert five 1's
	MsetInsertMany(s, 3, 1); // insert one 3

	assert(MsetSize(s) == 4);
	assert(MsetTotalCount(s) == 11);
	MsetFree(s);
	printf("MsetInsertMany passed\n");
}

void testMsetSize(void) {
	Mset s = MsetNew();
	assert(MsetSize(s) == 0);

	MsetInsert(s, 4);
	MsetInsert(s, 7);
	MsetInsert(s, 1);
	MsetInsert(s, 3);
	assert(MsetSize(s) == 4);

	MsetInsert(s, 8);
	MsetInsert(s, 1);
	assert(MsetSize(s) == 5);

	MsetInsertMany(s, 2, 5);
	MsetInsertMany(s, 4, 2);
	assert(MsetSize(s) == 6);

	MsetFree(s);
	printf("MsetSize passed\n");
}

void testMsetTotalCount(void) {
	Mset s = MsetNew();

	MsetInsert(s, 4);
	MsetInsert(s, 7);
	MsetInsert(s, 1);
	MsetInsert(s, 3);
	assert(MsetTotalCount(s) == 4);

	MsetInsert(s, 8);
	MsetInsert(s, 1);
	assert(MsetTotalCount(s) == 6);

	MsetInsertMany(s, 2, 5);
	MsetInsertMany(s, 4, 2);
	assert(MsetTotalCount(s) == 13);

	MsetFree(s);
	printf("MsetTotalCount passed\n");
}

void testMsetGetCount(void) {
	Mset s = MsetNew();

	MsetInsert(s, 4);
	MsetInsert(s, 7);
	MsetInsert(s, 1);
	MsetInsert(s, 3);
	assert(MsetGetCount(s, 1) == 1);
	assert(MsetGetCount(s, 3) == 1);
	assert(MsetGetCount(s, 4) == 1);
	assert(MsetGetCount(s, 7) == 1);
	assert(MsetGetCount(s, 8) == 0);

	MsetInsert(s, 8);
	MsetInsert(s, 1);
	assert(MsetGetCount(s, 1) == 2);
	assert(MsetGetCount(s, 8) == 1);

	MsetInsertMany(s, 2, 5);
	MsetInsertMany(s, 4, 2);
	assert(MsetGetCount(s, 2) == 5);
	assert(MsetGetCount(s, 4) == 3);

	MsetFree(s);
	printf("MsetGetCount passed\n");
}

void testMsetShow(void) {
	Mset s = MsetNew();

	MsetInsert(s, 4);
	MsetInsert(s, 7);
	MsetInsert(s, 1);
	MsetInsert(s, 3);
	MsetInsert(s, 7);
	MsetInsert(s, 3);
	MsetInsert(s, 7);

	MsetShow(s);
	printf("\n");

	MsetFree(s);
	printf("MsetShow passed\n");
}

////////////////////////////////////////////////////////////////////////

void testMsetUnion(void) {
	Mset a = MsetNew();
	MsetInsertMany(a, 4, 2);
	MsetInsertMany(a, 7, 3);
	MsetInsertMany(a, 1, 5);
	MsetInsertMany(a, 3, 1);

	Mset b = MsetNew();
	MsetInsertMany(b, 4, 4);
	MsetInsertMany(b, 7, 1);
	MsetInsertMany(b, 3, 2);
	MsetInsertMany(b, 8, 3);

	Mset c = MsetUnion(a, b);
	assert(MsetGetCount(c, 1) == 5);
	assert(MsetGetCount(c, 3) == 2);
	assert(MsetGetCount(c, 4) == 4);
	assert(MsetGetCount(c, 7) == 3);
	assert(MsetGetCount(c, 8) == 3);
	assert(MsetSize(c) == 5);
	assert(MsetTotalCount(c) == 17);

	MsetFree(a);
	MsetFree(b);
	MsetFree(c);
	printf("MsetUnion passed\n");
}

void testMsetIntersection(void) {
	Mset a = MsetNew();
	MsetInsertMany(a, 4, 2);
	MsetInsertMany(a, 7, 3);
	MsetInsertMany(a, 1, 5);
	MsetInsertMany(a, 3, 1);

	Mset b = MsetNew();
	MsetInsertMany(b, 4, 4);
	MsetInsertMany(b, 7, 1);
	MsetInsertMany(b, 3, 2);
	MsetInsertMany(b, 8, 3);

	Mset c = MsetIntersection(a, b);
	assert(MsetGetCount(c, 1) == 0);
	assert(MsetGetCount(c, 3) == 1);
	assert(MsetGetCount(c, 4) == 2);
	assert(MsetGetCount(c, 7) == 1);
	assert(MsetGetCount(c, 8) == 0);
	assert(MsetSize(c) == 3);
	assert(MsetTotalCount(c) == 4);

	MsetFree(a);
	MsetFree(b);
	MsetFree(c);
	printf("MsetIntersection passed\n");
}

void testMsetSum(void) {
	Mset a = MsetNew();
	MsetInsertMany(a, 4, 2);
	MsetInsertMany(a, 7, 3);
	MsetInsertMany(a, 1, 5);
	MsetInsertMany(a, 3, 1);

	Mset b = MsetNew();
	MsetInsertMany(b, 4, 4);
	MsetInsertMany(b, 7, 1);
	MsetInsertMany(b, 3, 2);
	MsetInsertMany(b, 8, 3);

	Mset c = MsetSum(a, b);
	assert(MsetGetCount(c, 1) == 5);
	assert(MsetGetCount(c, 3) == 3);
	assert(MsetGetCount(c, 4) == 6);
	assert(MsetGetCount(c, 7) == 4);
	assert(MsetGetCount(c, 8) == 3);
	assert(MsetSize(c) == 5);
	assert(MsetTotalCount(c) == 21);

	MsetFree(a);
	MsetFree(b);
	MsetFree(c);
	printf("MsetSum passed\n");
}

void testMsetDifference(void) {
	Mset a = MsetNew();
	MsetInsertMany(a, 4, 2);
	MsetInsertMany(a, 7, 3);
	MsetInsertMany(a, 1, 5);
	MsetInsertMany(a, 3, 1);

	Mset b = MsetNew();
	MsetInsertMany(b, 4, 4);
	MsetInsertMany(b, 7, 1);
	MsetInsertMany(b, 3, 2);
	MsetInsertMany(b, 8, 3);

	Mset c = MsetDifference(a, b);
	assert(MsetGetCount(c, 1) == 5);
	assert(MsetGetCount(c, 3) == 0);
	assert(MsetGetCount(c, 4) == 0);
	assert(MsetGetCount(c, 7) == 2);
	assert(MsetGetCount(c, 8) == 0);
	assert(MsetSize(c) == 2);
	assert(MsetTotalCount(c) == 7);

	MsetFree(a);
	MsetFree(b);
	MsetFree(c);
	printf("MsetDifference passed\n");
}

void testMsetIncluded(void) {
	Mset a = MsetNew();
	MsetInsertMany(a, 4, 2);
	MsetInsertMany(a, 7, 3);
	MsetInsertMany(a, 1, 5);

	Mset b = MsetNew();
	MsetInsertMany(b, 4, 5);
	MsetInsertMany(b, 7, 3);
	MsetInsertMany(b, 1, 6);
	MsetInsertMany(b, 3, 1);

	Mset c = MsetNew();
	MsetInsertMany(c, 4, 5);
	MsetInsertMany(c, 7, 3);
	MsetInsertMany(c, 1, 4);
	MsetInsertMany(c, 3, 1);

	assert(MsetIncluded(a, b));
	assert(!MsetIncluded(a, c));

	MsetFree(a);
	MsetFree(b);
	MsetFree(c);
	printf("MsetIncluded passed\n");
}

void testMsetEquals(void) {
	Mset a = MsetNew();
	MsetInsertMany(a, 4, 2);
	MsetInsertMany(a, 7, 3);
	MsetInsertMany(a, 1, 5);
	MsetInsertMany(a, 3, 1);

	Mset b = MsetNew();
	MsetInsertMany(b, 3, 1);
	MsetInsertMany(b, 1, 5);
	MsetInsertMany(b, 7, 3);
	MsetInsertMany(b, 4, 2);

	Mset c = MsetNew();
	MsetInsertMany(c, 4, 2);
	MsetInsertMany(c, 7, 3);
	MsetInsertMany(c, 1, 5);
	MsetInsertMany(c, 3, 4);

	assert(MsetEquals(a, b));
	assert(!MsetEquals(a, c));

	MsetFree(a);
	MsetFree(b);
	MsetFree(c);
	printf("MsetEquals passed\n");
}

void testMsetMostCommon(void) {
	Mset s = MsetNew();

	MsetInsertMany(s, 4, 2);
	MsetInsertMany(s, 7, 3);
	MsetInsertMany(s, 1, 5);
	MsetInsertMany(s, 3, 1);
	MsetInsertMany(s, 8, 3);

	int count = 0;
	struct item items[10];

	count = MsetMostCommon(s, 1, items);

	assert(count == 1);
	assert(items[0].item == 1);
	assert(items[0].count == 5);

	count = MsetMostCommon(s, 2, items);
	assert(count == 2);
	assert(items[0].item  == 1);
	assert(items[0].count == 5);
	assert(items[1].item  == 7);
	assert(items[1].count == 3);

	count = MsetMostCommon(s, 3, items);
	assert(count == 3);
	assert(items[0].item  == 1);
	assert(items[0].count == 5);
	assert(items[1].item  == 7);
	assert(items[1].count == 3);
	assert(items[2].item  == 8);
	assert(items[2].count == 3);

	count = MsetMostCommon(s, 8, items);
	assert(count == 5);
	assert(items[0].item  == 1);
	assert(items[0].count == 5);
	assert(items[1].item  == 7);
	assert(items[1].count == 3);
	assert(items[2].item  == 8);
	assert(items[2].count == 3);
	assert(items[3].item  == 4);
	assert(items[3].count == 2);
	assert(items[4].item  == 3);
	assert(items[4].count == 1);

	MsetFree(s);
	printf("MsetMostCommon passed\n");
}

////////////////////////////////////////////////////////////////////////

void testMsetCursor1(void) {
	Mset s = MsetNew();

	MsetInsertMany(s, 4, 2);
	MsetInsertMany(s, 7, 3);
	MsetInsertMany(s, 1, 5);
	MsetInsertMany(s, 3, 1);

	MsetCursor cur = MsetCursorNew(s);

	struct item a;
	
	// start  1  3  4  7  end
	//   ^
	a = MsetCursorGet(cur);
	assert(a.item == UNDEFINED);
	assert(MsetCursorNext(cur));
	// start  1  3  4  7  end
	//        ^
	a = MsetCursorGet(cur);
	assert(a.item == 1);
	assert(a.count == 5);

	assert(MsetCursorNext(cur));
	// start  1  3  4  7  end
	//           ^
	a = MsetCursorGet(cur);
	assert(a.item == 3);
	assert(a.count == 1);

	assert(MsetCursorNext(cur));
	// start  1  3  4  7  end
	//              ^
	a = MsetCursorGet(cur);
	assert(a.item == 4);
	assert(a.count == 2);

	assert(MsetCursorNext(cur));
	// start  1  3  4  7  end
	//                 ^
	a = MsetCursorGet(cur);
	assert(a.item == 7);
	assert(a.count == 3);

	assert(!MsetCursorNext(cur));
	// start  1  3  4  7  end
	//                     ^

	assert(MsetCursorPrev(cur));
	// start  1  3  4  7  end
	//                 ^
	a = MsetCursorGet(cur);
	assert(a.item == 7);
	assert(a.count == 3);

	assert(MsetCursorPrev(cur));
	// start  1  3  4  7  end
	//              ^
	a = MsetCursorGet(cur);
	assert(a.item == 4);
	assert(a.count == 2);

	assert(MsetCursorPrev(cur));
	// start  1  3  4  7  end
	//           ^
	a = MsetCursorGet(cur);
	assert(a.item == 3);
	assert(a.count == 1);

	assert(MsetCursorPrev(cur));
	// start  1  3  4  7  end
	//        ^
	a = MsetCursorGet(cur);
	assert(a.item == 1);
	assert(a.count == 5);

	assert(!MsetCursorPrev(cur));
	// start  1  3  4  7  end
	// ^

	MsetCursorFree(cur);
	MsetFree(s);
	printf("MsetCursor 1 passed\n");
}

void testMsetCursor2(void) {
	Mset s = MsetNew();

	MsetInsertMany(s, 4, 2);
	MsetInsertMany(s, 7, 3);
	MsetInsertMany(s, 1, 5);
	MsetInsertMany(s, 3, 1);

	MsetCursor cur = MsetCursorNew(s);

	struct item a;
	
	// start  1  3  4  7  end
	//   ^
	a = MsetCursorGet(cur);
	assert(a.item == UNDEFINED);

	assert(MsetCursorNext(cur));
	// start  1  3  4  7  end
	//        ^
	a = MsetCursorGet(cur);
	assert(a.item == 1);
	assert(a.count == 5);
	MsetInsertMany(s, 2, 4);
	// start  1  2  3  4  7  end
	//        ^
	assert(MsetCursorNext(cur));
	// start  1  2  3  4  7  end
	//           ^
	a = MsetCursorGet(cur);
	assert(a.item == 2);
	assert(a.count == 4);

	MsetCursorFree(cur);
	MsetFree(s);
	printf("MsetCursor 2 passed\n");
}

