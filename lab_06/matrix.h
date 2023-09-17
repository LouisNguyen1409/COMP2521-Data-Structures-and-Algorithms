// Interface to matrix utility functions

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

#include "cell.h"

/**
 * Allocates  and  returns  a 2D array/matrix of booleans with the given
 * number of rows and columns. All entries are initialised to false.  It
 * is  the  user's  responsibility  to call `freeBoolMatrix` to free the
 * matrix.
 *
 * Example usage:
 * The following example creates a matrix with 3 rows and 5 columns, and
 * sets the top-left and bottom-right entries to true.
 *
 * bool **matrix = createBoolMatrix(3, 5);
 * matrix[0][0] = true;
 * matrix[2][4] = true;
 *
 * Complexity: O(rc) where r is the number of rows and c is the number
 *             of columns
 */
bool **createBoolMatrix(int nRows, int nCols);

/**
 * Frees the given boolean matrix.
 * Complexity: O(r) where r is the number of rows of the matrix
 */
void freeBoolMatrix(bool **matrix);

/**
 * Allocates and returns a 2D array/matrix of cell structs with the given
 * number of rows and columns. All entries are initialised to (0, 0). It
 * is the user's responsibility to call `freeCellMatrix` to free the
 * matrix.
 *
 * Complexity: O(rc) where r is the number of rows and c is the number
 *             of columns
 */
struct cell **createCellMatrix(int nRows, int nCols);

/**
 * Frees the given cell struct matrix.
 * Complexity: O(r) where r is the number of rows of the matrix
 */
void freeCellMatrix(struct cell **matrix);

#endif
