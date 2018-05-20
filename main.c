/*
 * Author: James Wu
 * Date: 23 January 2018
 * Purpose: To implement a Gauss-Jordan Elimination algorithm
 *          for an arbitraily sized m x n matrix A
 */

/* Header files */
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define FALSE 0
#define TRUE 1
#define m 4
#define n 4

#define SHOW_WORK 0

/* Function Prototypes */
void rref(double A[m][n]);
void swap(double A[m][n], int a, int b);
void mult(double A[m][n], int a, double c);
void add(double A[m][n], int a, int b, double c);
void printMatrix(double A[m][n]);

int main(void) {

	/* INIT m x n matrix */										
	double A[m][n] = { {2, -5, -3, 16},
	                   {5, -6, 6, -13},
					   {-2, -3, 6, 10},
					   {23, -19, -33, 27} };

	printf("Original matrix:\n");
	printMatrix(A);
	printf("\n");

	rref(A);

	printf("Reduced matrix:\n");
	printMatrix(A);
	printf("\n");

	system("PAUSE");
	return 0;

}

/*
 * The master Gauss-Jordan Elimination algorithm.
 * Parameters: A (double[m][n]) - the m x n matrix to be put into rref
 */
void rref(double A[m][n]) {

	int anchor = 0; // row # that next anchor should be
	int anchorExists; // true if anchor for given column exists, false otherwise

	/* Loop through columns in outer loop */
	for (int j = 0; j < n; j++) {
		
		/* Swap rows to position anchor */
		anchorExists = FALSE;
		for (int a = anchor; a < m; a++) {
			if (A[a][j] != 0) {

				swap(A, a, anchor);
				anchorExists = TRUE;

				/* Show some work */
				if (SHOW_WORK == TRUE) {
					printf("Swap to position anchor for column %d:\n", j+1);
					printMatrix(A);
					printf("\n");
				}

				break;

			}
		}

		/* If anchor doesn't exist, move onto next column */
		if (anchorExists == FALSE) {
			continue;
		}

		/* Loop through rows to scalar add by anchor i.e. "eliminate" */
		for (int i = 0; i < m; i++) {

			if (i == anchor) {

				mult(A, i, 1.0 / A[i][j]);

				/* Show some work */
				if (SHOW_WORK == TRUE) {
					printf("Scale anchor for column %d:\n", j+1);
					printMatrix(A);
					printf("\n");
				}


			}
			else {

				add(A, i, anchor, -A[i][j]/A[anchor][j]);

				/* Show some work */
				if (SHOW_WORK == TRUE) {
					printf("Reduce row %d for column %d\n", i+1, j+1);
					printMatrix(A);
					printf("\n");
				}


			}

		}

		/* Since anchor exists, inc anchor for next col */
		anchor++;

		/* If columns don't "run out" but rows do */
		if (anchor > m) {
			break;
		}

	}

}

/*
 * Row operation: swaps two rows
 * Parameters: A (double[m][n]) - the matrix to be operated upon
 *             a (int)          - row # of one row to swap
 *             b (int)          - row # of the other row to swap
 */
void swap(double A[m][n], int a, int b) {

	/* Create a temporary array to store row a */
	double temp[n];

	for (int i = 0; i < n; i++) {

		temp[i]   = A[a][i]; // Copy row a onto temp
		A[a][i] = A[b][i]; // Copy row b onto a
		A[b][i] = temp[i]; // Copy temp onto b

	}

}

/*
 * Row operation: multiplies a row by a constant
 * Parameters: A (double[m][n]) - the matrix to be operated upon
 *             a (int)          - the row to be operated upon
 *             c (double)       - scalar multiple to multiply row a by
 */
void mult(double A[m][n], int a, double c) {

	/* Loop through columns of row a */
	for (int i = 0; i < n; i++) {

		A[a][i] *= c; // multiply element by c

	}

}

/*
 * Row operation: adds a constant multiple of a row onto another
 * Parameters: A (double[m][n]) - the matrix to be operated upon
 *             a (int)          - the row to be added onto (a = a + cb)
 *             b (int)          - the 'unmodified' row
 *             c (double)       - the scalar multiplier
 */
void add(double A[m][n], int a, int b, double c) {

	/* Loop through the columns */
	for (int i = 0; i < n; i++) {

		A[a][i] += c * A[b][i]; // add scalar multiple of b onto a

	}

}

/*
 * Prints a double 2D array
 * Parameters: A (double[m][n]) - matrix to print
 */
void printMatrix(double A[m][n]) {

	printf("\n");

	/* Loop through rows in outer loop */
	for (int i = 0; i < m; i++) {

		/* Loop through columns in inner loop */
		for (int j = 0; j < n; j++) {
			printf("%14.6f ", A[i][j]);
		}

		printf("\n");

	}

}