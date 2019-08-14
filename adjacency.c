#include <stdio.h>
#define N 6 /* array size */
#define TRUE 1
#define FALSE 0
#define max(a,b) a > b ? a : b /* gets the bigger of the 2 parameters. if they're equal, returns the first parameter. */
typedef int adjmat[N][N]; /* type to define adjacenty matrixes */

int path(adjmat treemap, int u, int v);

int main() {
	int row = 0, col = 0, u, v; 				/* row & col:  u & v: indexes to pass to function path*/
	int run = TRUE; 							/* defines whether or not the loop at the end of the file should be running*/
	char treemapText[N * N + N]; 				/* holds the text representation of the array treemap*/
	adjmat treemap; 							/* an adjacenty array */
	printf("Please enter values for the array. it is a %d * %d array.\n", N, N);
	for (row = 0; row < N; row++) { 			/*| for each column 				  |*/
		treemapText[N + row + (row * N)] = '\n';/*|	  in each row		   		      |*//* places \n at the end of each line in the text representation of treemap*/
		for (col = 0; col < N; col++) { 		/*|   in treemap  					  |*/
			scanf("%d", &treemap[row][col]);    /*| read value and set the cell to it |*/
			if(treemap[row][col] == EOF) 		/*if input's over */
				col = row = N;					/* stop reading   */
			else treemapText[row * (N + 1) + col] = treemap[row][col] + '0'; /* add the value to the text representation of the array*/
		} /* end of for */
	} /* end of for*/
	treemapText[N * N + N - 1] = '\0';			 /* set the end of string charachter at the end of the srring representation of the array */
	printf("\n%s\n", treemapText); 				/* print the array */
	while(run){									/* read indexes and check for a path between them */
		printf("\nTo search for a possible path, please enter the origin index and the target index: ");
		scanf("%d %d", &u, &v); 				/* read indexes */
		if((v == -1 && u == -1) || v == EOF || u == EOF){ /* if input is EOF or -1 */
			run = FALSE;								 /* stop running */
			printf("-1 -1\nClosing...");
		} /* end of if */
		else printf("\nOrigin index: %d\nTarget index: %d \nResult: %s\n", u, v, path(treemap, u, v) == FALSE ? "FALSE" : "TRUE"); /* print result */
	} /* end of while */
	return 0;
} /* end of main*/


int path(adjmat treemap, int u, int v) { 			/*| int path: returns TRUE if there is a downward-heading path from intersection u to intersection v. otherwise, returns FALSE |*/
	int col = 0;    /* used to manipulate arrays */	/*| treemap: the adjacenty array to check. u: the sorrce index. v: the target index    |*/
	int toReturn = FALSE;							 /* holds the value that the function will return */
	if (u == v)										/*| if the origin and the target index are the same index |*/
		return TRUE;   								/*| return true 										  |*/
	else if (u < 0 || u >= N || v < 0 || v >= N)	 	/*| if index is illegal |*/
		return FALSE;								 	/*| return false 		|*/
	if (treemap[u][v]) 								/*| if target index is a child of the source |*/
		return TRUE;  								/*| return true 							 |*/
	for (col = 0; col < N; col++) { 						 /*| for each son of index u |*/
		if (treemap[u][col])	   						     /*|		check if	     |*/
			toReturn = max(toReturn, path(treemap, col, v)); /*| 		v is it's son	 |*/
	} /* end of for */
	return toReturn; /* return the conclusion */
} /* end of path */