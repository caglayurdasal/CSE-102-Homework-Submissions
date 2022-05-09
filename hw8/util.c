#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void generate_sequence(int xs, int currentlen, int seqlen, int *seq)
{
    /*
     * int xs: First number in the sequence
     * int currentlen: Current length of the sequence at the time it's being generated
     * int seqlen: Length of the sequence to be
     * int *seq: Sequence to be generated
     */
    if (seqlen == 1) // Base case
    {
        *(seq + 1) = *seq / 2; // Last item will be 1
    }
    else // Recursive part
    {
        /* Check if number is even or odd */
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
        /* Find the rest of the sequence */
        generate_sequence(*(seq + 1), currentlen, seqlen, seq + 1);
    }
}
int has_loop(int *arr, int n, int looplen, int *ls, int *le)
{
    /*
     * int *arr: Array in which the loop to be searched
     * int n: Array boundary will be n-1
     * int looplen: Length of the loop to be searched
     * int *ls: Start index of the loop
     * int *le: End index of the loop
     */
    int check = 0, i = 0;

    for (i = 0; i < n - 2; i++)
    {

        if (check == 1)
        {
            return 1; // If a loop is found, return check
        }
        /* If a number is equal to the next number, search for a loop at the rest of the sequence */
        if (arr[i] == arr[i + looplen])
        {
            /* Search the duplicated numbers until length of loop is reached */
            for (int j = 1; j < looplen; j++)
            {
                if (arr[i + j] == arr[i + looplen + j])
                {
                    *ls = i;           // Mark the start index of the loop in the sequence
                    *le = i + looplen; // Mark the end index of the loop in the sequence
                    check = 1;         // Loop is found
                }
                else
                {
                    check = 0; // Seacrh is interrupted by a non-duplicated number, loop is not found
                }
            }
        }
    }

    return check;
}
void check_loop_iterative(void (*f)(int, int, int, int *), int xs, int seqlen, int *loop, int *looplen)
{
    /*
     * void (*f)(int, int, int, int *): The function to be called
     * int xs: First number in teh sequence
     * int seqlen: Length of the sequence to be
     * int *loop: Loop to be searched in the sequence
     * int *looplen: Length of the loop to be searched
     */
    int *ls, *le; // Start and end index of the loop
    static int start, end;
    ls = &start;
    le = &end;
    int check;                    // Loop check
    static int display_check = 0; // Check value for displaying the sequence
    int len = *looplen;
    static int len_check = 0; // Check value for length of loop
    if (len_check == 0)
    {
        // Length of loop can be length of sequence/2 at most at the beginning of the search
        *looplen = seqlen / 2;
        len_check = 1;
    }

    int *seq; // Sequence to be generated

    seq = calloc(seqlen, 2 * sizeof(int)); // Allocating enough memory in the heap for the sequence
    seq[0] = xs;                           // First member of sequence is given by user
    /* Generate the sequence */
    f(xs, 0, seqlen, seq);
    /* Display the sequence only once */
    if (display_check == 0)
    {
        printf("\nSequence: {");
        for (int i = 0; i < seqlen; i++)
        {

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

    if (len >= 2)
    {
        /* Check for the loop of length seqlen/2, seqlen/2-1, seqlen/2-2,..., 2 */
        printf("Checking if there is a loop of length %d...\n", *looplen);
        int temp_len = *looplen; // Temporary length to store the length of loop
        check = has_loop(seq, seqlen, temp_len, &start, &end);
    }

    if (len <= 2 || check == 1) // Base case
    {
        if (check != 0)
        {
            /* If a loop is found, display the start and end indexes and inform the user */
            printf("\nLoop detected with a length of %d.\n", *looplen);
            printf("The indexes of the loop's first occurrence: %d(first digit), %d(last digit)\n", *ls, *le);
            for (int i = 0; i < *looplen; i++)
            {
                loop[i] = seq[start];
                start++;
            }
        }
    }
    else // Recursive part
    {
        /* If no loop of searched length is found, keep searching for a loop of length-1 */
        (*looplen)--;
        check_loop_iterative(f, xs, seqlen, loop, looplen);
    }
}
int firstDigit(int num)
{
    /*
     * int num: Number of which first digit to be founded
     */
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
    /*
     * void (*f)(int, int, int, int *): The function to be called
     * int xs: First number in teh sequence
     * int seqlen: Length of the sequence to be
     * int *h: Array of histogram to be updated in the function
     * int digit: Digit to be searched as the first digit of a number in the sequence
     */
    int first_digit; // First digit of the current number in the sequence

    int *sequence = (int *)malloc(seqlen * 2 * sizeof(int)); // Allocating enough memory in the heap for the sequence
    sequence[0] = xs;                                        // First number int the sequence is given by user

    /* Call function f to generate the sequence */
    f(xs, 0, seqlen, sequence);

    /* Check first digits of each number in the sequence */
    for (int i = 0; i < seqlen; i++)
    {
        first_digit = firstDigit(sequence[i]);

        /* If first digit of the number is equal to the digit that's being looked for,
         * increment that digit in the histogram */
        if (first_digit == digit)
        {
            h[digit]++;
        }
    }
    free(sequence);

    if (digit != 1) // Recursive part
    {
        /* Keep searching for the other digits */
        digit--;
        hist_of_firstdigits(generate_sequence, xs, seqlen, h, digit);
    }
}