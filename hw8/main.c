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

	/* Generate the sequence and check for the loop count */
	check_loop_iterative(generate_sequence, xs, seqlen, loop, &seq_len);

	/* Create histogram */
	int h[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int digit = 9;
	hist_of_firstdigits(generate_sequence, xs, seqlen, h, digit);
	printf("Histogram: {");
	for (int i = 1; i <= 9; i++)
	{
		if (i == 9)
		{
			printf("%d} ", h[i]);
		}
		else
		{
			printf("%d, ", h[i]);
		}
	}

	free(loop);

	return 0;
}
