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
int has_loop(int *arr, int n, int looplen, int *ls, int *le)
{

    int check = 0, check_len = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (check == 1)
        {
            break;
        }

        for (int i = 0; i < n - 2; i++)
        {
            if (check == 1)
            {
                break;
            }
            for (int x = 1; x < n - i; x++)
            {
                if (arr[i] == arr[i + x])
                {
                    /* Check if there is a loop of a sequence of numbers */
                    for (int m = 0; m < looplen; m++)
                    {
                        if (arr[i + m] == arr[i + x + m])
                        {
                            // printf("Same values: arr[%d]==arr[%d+%d]->%d\n", i + m, i + x, m, arr[i + m]); -> I have printed these values for debugging
                            check_len++;
                            if (check_len == looplen)
                            {
                                break;
                            }
                        }
                        else
                        {
                            check_len = 0;
                        }
                    }

                    if (check_len == looplen)
                    {
                        *ls = i;
                        *le = i + looplen;

                        check = 1;
                        break;
                    }
                }
            }
        }

        return check;
    }
}
void check_loop_iterative(void (*f)(int, int, int, int *), int xs, int seqlen, int *loop, int looplen)
{

    int *ls, *le;
    static int start, end;
    ls = &start;
    le = &end;
    int check;
    static int display_check = 0;

    /* Display the sequence first */
    if (display_check == 0)
    {
        int *seq = (int *)malloc(seqlen * sizeof(int)); // Allocating enough memory in the heap for the sequence
        seq[0] = xs;                                    // First member of sequence is given by user
        /* Generate the sequence */
        f(xs, 0, seqlen, seq);
        /* Display the sequence */
        printf("\nSequence: {");
        for (int i = 0; i < seqlen; i++)
        {
            loop[i] = seq[i]; // Fill the array to check loop count later
            if (i == seqlen - 1)
            {
                printf("%d}\n\n", seq[i]);
            }
            else
            {
                printf("%d, ", seq[i]);
            }
        }
        display_check = 1; // Display the sequence only once

        free(seq);
    }
    /* After displaying the sequence, check for loop count recursively*/
    printf("Checking if there is a loop of length %d...\n", looplen);
    check = has_loop(loop, seqlen, looplen, &start, &end);

    if (looplen < 2 || check == 1) // base case
    {
        if (check == 0)
        {
            printf("No loop found.\n");
        }
        else
        {
            printf("\nLoop detected with a length of %d.\n", looplen);
            printf("The indexes of the loop's first occurrence: %d(first digit), %d(last digit)\n", *ls, *le);
            printf("Loop: {");
            for (int i = 0; i < looplen; i++)
            {
                if (i == looplen - 1)
                {
                    printf("%d}\n", loop[start + i]);
                }
                else
                {
                    printf("%d,", loop[start + i]);
                }
            }
        }
    }
    else // recursive part
    {
        looplen--;
        check_loop_iterative(generate_sequence, xs, seqlen, loop, looplen);
    }
}