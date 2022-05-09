#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main()
{
	int xs, *looplen;
	static int seqlen;
	printf("Please enter the sequence length: ");
	scanf("%d", &seqlen);
	looplen = &seqlen;
	int hist_len = seqlen;

	printf("Please enter the first element: ");
	scanf("%d", &xs);
	int *loop;
	loop = (int *)malloc(sizeof(int) * (seqlen / 2));

	/* Generate the sequence and check for the loop count */
	check_loop_iterative(generate_sequence, xs, seqlen, loop, looplen);

	if (seqlen > 2)
	{
		printf("Loop: {");
		for (int i = 0; i < seqlen; i++)
		{

			if (i == seqlen - 1)
			{
				printf("%d}\n", loop[i]);
			}
			else
			{
				printf("%d,", loop[i]);
			}
		}
	}
	else
	{
		printf("No loop is found.\n");
	}

	/* Create histogram */
	int h[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int digit = 9;

	hist_of_firstdigits(generate_sequence, xs, hist_len, h, digit);
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
