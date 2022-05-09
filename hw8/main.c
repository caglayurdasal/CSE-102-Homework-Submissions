/*
 * Assignment #8 submission by Çağla Nur Yurdasal
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main()
{
	int xs;			   // First number in sequence
	int *looplen;	   // Length of loop the sequence if found
	static int seqlen; // Length of sequence

	/* Get sequence length and first number of the sequence from the user */
	printf("Please enter the sequence length: ");
	scanf("%d", &seqlen);
	looplen = &seqlen;
	int hist_len = seqlen; // Length of sequence to be used in creating histogram

	printf("Please enter the first element: ");
	scanf("%d", &xs);
	int *loop;										  // Loop array
	loop = (int *)malloc(sizeof(int) * (seqlen / 2)); // Length of the loop can be seqlen/2 at most

	/* Generate the sequence and check for the loop count */
	check_loop_iterative(generate_sequence, xs, seqlen, loop, looplen);

	if (seqlen > 2) // Length of a loop can be at least 2
	{
		/* If a loop exists in the sequence print it */
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
	/* If a loop doesn't exist in the sequence, inform the user */
	else
	{
		printf("No loop is found.\n");
	}

	/* Create histogram */
	int h[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int digit = 9; // Start with searching numbers that start with 9

	hist_of_firstdigits(generate_sequence, xs, hist_len, h, digit);

	/* Display the histogram */
	printf("\nHistogram: {");
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
