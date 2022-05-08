#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void generate_sequence(int xs, int currentlen, int seqlen, int *seq)
{
    // if x%2!=0 -> 3x+1
    // else -> x/2

    if (seqlen == 1)
    {
        *(seq + 1) = *seq / 2; // Last item will be 1
    }
    else
    {
        if (xs % 2 != 0)
        {
            *(seq + 1) = 3 * xs + 1;
        }
        else
        {
            *(seq + 1) = xs / 2;
        }
        currentlen++;
        seqlen--;
        generate_sequence(*(seq + 1), currentlen, seqlen, seq + 1);
    }
}
void check_loop_iterative(void (*f)(int, int, int, int *), int xs, int seqlen, int *loop, int *looplen)
{
    /* Display the sequence first */
    if (seqlen > 0)
    {
        int *seq = (int *)malloc(seqlen * sizeof(int)); // Allocating enough memory for the sequence
        seq[0] = xs;                                    // First member of sequence is given by user
        /* Generate the sequence */
        f(xs, 0, seqlen, seq);
        /* Display the sequence */
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
    }
    /* After displaying the sequence, check for loop count */
    else
    {
    }
}