/*
 * This program generates the minimum steps required for a successful
 * Tower of Hanoi game.
 *
 * CSE102 Assignment#10 Submission by Çağla Nur Yurdasal
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_BLOCK_SIZE 10 // Initial size of the stack array

typedef struct stack
{
    int *array;
    int maxsize;
    int currentsize;

} stack;

/* Calculates the number of minimum steps required for the game */
int minimumMoves(int num_disks)
{
    /* The minimal number of moves required to solve a Tower of
     * Hanoi puzzle is 2^n − 1, where n is the number of disks. */
    int total_steps = 1;

    for (int i = 0; i < num_disks; i++)
    {
        total_steps *= 2;
    }
    return total_steps - 1;
}

/* Initializes an empty stack */
stack *init_return()
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->currentsize = 0;            // Initially stack is empty so size is 0
    s->maxsize = STACK_BLOCK_SIZE; // Maximum size the stack can be
    s->array = (int *)malloc(STACK_BLOCK_SIZE * sizeof(int));
    return s;
}
/* Checks whether the stack is initialized correctly */
int init(stack *s)
{
    int top = 0; // Top element index is initially set to 0
    if (s->currentsize == top)
    {
        return 1;
    }
    return -1;
}

/* Adds a new element to the stack */
int push(stack *s, int d)
{
    if (s->currentsize == s->maxsize - 1) // Check if stack is full
    {
        return 1000; // Returns 1000 to indicate stack is full
    }

    s->array[s->currentsize] = d; // Add the new element from the top of stack
    s->currentsize += 1;          // Stack array grows by 1
    return 1;                     // Return 1 to indicate successful operation
}

/* Removes the top element from the stack */
int pop(stack *s)
{
    if (s->currentsize == 0) // Check if stack is empty
    {
        return -1; // Returns -1 to indicate stack is empty
    }
    int popped_element = s->array[s->currentsize - 1];
    s->currentsize--;        // Top index is decremented by 1
    return (popped_element); // Return the popped element
}

/* Prints the moves */
void displayMoves(int disk, char srcPole, char destPole)
{
    printf("Move the disk %d from pole '%c' to pole '%c'.\n", disk, srcPole, destPole);
}

/* Moves a disk between two poles */
void moveDisks(stack *src, stack *dest, char poleSrc, char poleDest)
{
    int topSrcDisk,          // Top disk on the source pole
        topDestDisk;         // Top disk on the destination pole
    topSrcDisk = pop(src);   // Gets the top disk on the source pole
    topDestDisk = pop(dest); // Gets the top disk on the destination pole

    if (topSrcDisk == -1) // If there are no disks on the destination pole
    {
        push(src, topDestDisk);
        displayMoves(topDestDisk, poleDest, poleSrc);
    }
    else if (topDestDisk == -1) // If there are no disks on the source pole
    {
        push(dest, topSrcDisk);
        displayMoves(topSrcDisk, poleSrc, poleDest);
    }
    else if (topSrcDisk > topDestDisk)
    {
        /* If top disk of source pole > top disk of dest pole then the movement
        between the poles will be reversed and disk will be pushed to source pole */
        push(src, topSrcDisk); // Put the larger disk first
        push(src, topDestDisk);
        displayMoves(topDestDisk, poleDest, poleSrc);
    }
    else
    {
        /* If top disk of source pole < top disk of dest pole then disk
        will be pushed to destination pole as intended */
        push(dest, topDestDisk);
        push(dest, topSrcDisk);
        displayMoves(topSrcDisk, poleSrc, poleDest);
    }
}
int main()
{
    stack *dest_pole, *src_pole, *aux_pole;
    int num_disks;
    do
    {
        printf("Enter number of disks: ");
        scanf("%d", &num_disks);
        if (num_disks <= 0)
        {
            printf("Error! Invalid number of disks.\nPlease enter at least 1 disk.\n");
        }
    } while (num_disks <= 0);

    int total_steps = minimumMoves(num_disks);
    printf("Total number of moves: %d\n", total_steps);

    src_pole = init_return(); // Source pole which the disks will be moved from
    if (init(src_pole) == -1)
    {
        printf("Error! Initializing the source pole stack.\n");
        return 0;
    }

    aux_pole = init_return(); // Auxiliary pole to be used while moving the disks
    if (init(aux_pole) == -1)
    {
        printf("Error! Initializing the auxiliary pole stack.\n");
        return 0;
    }
    dest_pole = init_return(); // Destination pole which the disks will be moved to
    if (init(dest_pole) == -1)
    {
        printf("Error! Initializing the destination pole stack.\n");
        return 0;
    }

    /* Put disks to the source pole */
    int i = num_disks; // Initialize i to be the largest disk
    while (i > 0)
    {
        push(src_pole, i); // Put larger disks first
        i--;               // Keep placing disks with smaller ones until no disks left
    }

    char a = '1', b = '2', c = '3'; // Pole names

    if (num_disks % 2 == 0)
    {
        /*
            For even number of disks:
            Step 1: Legal move(small disk will be placed on larger disk) between poles 1 and 2
            Step 2: Legal move between poles 1 and 3
            Step 3: Legal move between poles 2 and 3
            Repeat until all disks are at the destination pole
        */
        for (int i = 0; i < total_steps; i++)
        {
            if (i % 3 == 0) // Step 1
            {
                moveDisks(src_pole, aux_pole, a, b);
            }
            else if (i % 3 == 1) // Step 2
            {
                moveDisks(src_pole, dest_pole, a, c);
            }
            else if (i % 3 == 2) // Step 3
            {
                moveDisks(aux_pole, dest_pole, b, c);
            }
        }
    }
    else
    {
        /*
            For odd number of disks:
            Step 1: Legal move(small disk will be placed on larger disk) between poles 1 and 3
            Step 2: Legal move between poles 1 and 2
            Step 3: Legal move between poles 2 and 3
            Repeat until all disks are at the destination pole
        */
        for (int i = 0; i < total_steps; i++)
        {
            if (i % 3 == 0) // Step 1
            {
                moveDisks(src_pole, dest_pole, a, c);
            }
            else if (i % 3 == 1) // Step 2
            {
                moveDisks(src_pole, aux_pole, a, b);
            }
            else if (i % 3 == 2) // Step 3
            {
                moveDisks(aux_pole, dest_pole, b, c);
            }
        }
    }

    return 0;
}