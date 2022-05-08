#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main()
{
	int xs, *looplen;
	static int seqlen;
	printf("Please enter the sequence length: ");
	scanf("%d", &seqlen);
	int seq_len = seqlen;
	looplen = &seq_len;
	*looplen = seq_len / 2;

	printf("Please enter the first element: ");
	scanf("%d", &xs);
	int *loop = (int *)malloc((seqlen) * sizeof(int));
	int myArr[9] = {3, 55, 6, 23, 2, 4, 23, 2, 4};

	/* Generate the sequence and check for the loop count */
	check_loop_iterative(generate_sequence, xs, seqlen, loop, &seq_len);

	free(loop);
	return 0;
}
