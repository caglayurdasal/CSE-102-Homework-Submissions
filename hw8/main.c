#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main()
{
	int xs, looplen;
	static int seqlen;
	printf("Please enter the sequence length: ");
	scanf("%d", &seqlen);
	looplen = seqlen / 2;

	printf("Please enter the first element: ");
	scanf("%d", &xs);
	int *loop = (int *)malloc((seqlen) * sizeof(int));
	int myArr[9] = {3, 55, 6, 23, 2, 4, 23, 2, 4};
	// has_loop(arr, 9, 3, ls, le);
	/* Generate the sequence and check for the loop count */
	check_loop_iterative(generate_sequence, xs, seqlen, loop, looplen);
	// printf("Looplen=%d\n", looplen);
	// printf("Seqlen=%d\n", seqlen);

	free(loop);
	return 0;
}