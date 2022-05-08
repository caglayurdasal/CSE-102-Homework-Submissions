#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main()
{
	int seqlen, xs;
	printf("Please enter the sequence length: ");
	scanf("%d", &seqlen);
	int *seq = (int *)malloc(seqlen * sizeof(int)); // Allocating enough memory for the sequence

	printf("Please enter the first element: ");
	scanf("%d", &xs);
	seq[0] = xs;

	/* Generating the sequence */
	generate_sequence(xs, 1, seqlen, seq);

	/* Displaying the sequence */
	printf("Sequence: {");
	for (int i = 0; i < seqlen; i++)
	{
		if (i == seqlen - 1)
		{
			printf("%d}\n", seq[i]);
		}
		else
		{
			printf("%d, ", seq[i]);
		}
	}

	return 0;
}