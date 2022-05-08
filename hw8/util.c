#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void generate_sequence(int xs, int currentlen, int seqlen, int *seq)
{
    // if x%2!=0 -> 3x+1
    // else -> x/2

    if (currentlen + 1 == seqlen)
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
        generate_sequence(*(seq + 1), currentlen + 1, seqlen, seq + 1);
    }
}
