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
    int check = 0, i = 0;

    for (i = 0; i < n - 2; i++)
    {

        if (check == 1)
        {
            return 1;
        }
        if (arr[i] == arr[i + looplen])
        {
            for (int j = 1; j < looplen; j++)
            {
                if (arr[i + j] == arr[i + looplen + j])
                {
                    *ls = i;
                    *le = i + looplen;
                    check = 1;
                }
                else
                {
                    check = 0;
                }
            }
        }
    }

    return check;
}
void check_loop_iterative(void (*f)(int, int, int, int *), int xs, int seqlen, int *loop, int *looplen)
{
    int *ls, *le;
    static int start, end;
    ls = &start;
    le = &end;
    int check;
    static int display_check = 0;
    int len = *looplen;
    static int len_check = 0;
    if (len_check == 0)
    {
        *looplen = seqlen / 2;
        len_check = 1;
    }

    int *seq;
    printf("Seqlen: %d\n", seqlen);
    // seq = (int *)malloc(seqlen * sizeof(int)); // Allocating enough memory in the heap for the sequence
    seq = calloc(seqlen, sizeof(int));
    seq[0] = xs; // First member of sequence is given by user
    /* Generate the sequence */
    f(xs, 0, seqlen, seq);
    /* Display the sequence */
    if (display_check == 0)
    {
        printf("\nSequence: {");
        for (int i = 0; i < seqlen; i++)
        {
            // loop[i] = seq[i]; // Fill the array to check loop count later
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

        // free(seq);
    }
    /* After displaying the sequence, check for loop count recursively*/
    // for (int i = 0; i < seqlen; i++)
    // {
    //     printf("Seq[%d]=%d\n", i, seq[i]);
    // }
    if (len >= 2)
    {
        printf("Checking if there is a loop of length %d...\n", *looplen);
        int temp_len = *looplen;
        check = has_loop(seq, seqlen, temp_len, &start, &end);
    }

    if (len <= 2 || check == 1) // base case
    {
        if (check != 0)
        {

            printf("\nLoop detected with a length of %d.\n", *looplen);
            printf("The indexes of the loop's first occurrence: %d(first digit), %d(last digit)\n", *ls, *le);
            for (int i = 0; i < *looplen; i++)
            {
                loop[i] = seq[start];
                start++;
            }
        }
    }
    else // recursive part
    {
        (*looplen)--;
        check_loop_iterative(f, xs, seqlen, loop, looplen);
    }
}
int firstDigit(int num)
{
    int first_digit;
    while (num > 0)
    {
        first_digit = num;
        num /= 10;
    }
    return first_digit;
}
void hist_of_firstdigits(void (*f)(int, int, int, int *), int xs, int seqlen, int *h, int digit)
{
    /* Generate the sequence */

    int count_num;

    int *sequence = (int *)malloc(seqlen * sizeof(int)); // Allocating enough memory in the heap for the sequence
    sequence[0] = xs;                                    // First member of sequence is given by user
    /* Call function f to generate the sequence */
    f(xs, 0, seqlen, sequence);

    for (int i = 0; i < seqlen; i++)
    {
        count_num = firstDigit(sequence[i]);

        if (count_num == digit)
        {

            h[digit]++;
        }
    }
    free(sequence);
    if (digit == 1) // base case
    {
        ;
    }
    else // recursive part
    {
        digit--;
        hist_of_firstdigits(generate_sequence, xs, seqlen, h, digit);
    }
}