#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#define MAX 100
int main()
{
	int seqlen, xs, loop[MAX];
	printf("Please enter the sequence length: ");
	scanf("%d", &seqlen);

	printf("Please enter the first element: ");
	scanf("%d", &xs);

	/* Generate the sequence and check for the loop count */
	check_loop_iterative(generate_sequence, xs, seqlen, loop, 0);

	return 0;
}