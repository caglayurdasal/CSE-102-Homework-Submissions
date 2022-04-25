#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 15
#define COLUMN 15

int main(void)
{
    FILE *fp;
    int size_file;     // Size of wordlist.txt
    int wordCount = 0; // Word count selected for the board
    char board[ROW][COLUMN];
    fp = fopen("wordlist.txt", "r+");

    fseek(fp, 0, SEEK_END); /* Go to end of file to find size */
    size_file = ftell(fp);  /* Store the current position of file
                             * pointer to get the size of file*/

    srand(time(NULL)); // Seed

    if (fp != NULL)
    {
        while (wordCount <= 7) /* Select random 7 words for the board */
        {

            fseek(fp, -1 * (rand() % size_file), SEEK_CUR); /* Move the position of file pointer back
                                                             * random number of times */
            fgets(board[ROW][COLUMN], 10, fp);              /* Store the word at which file pointer currently is */
            fseek(fp, 0, SEEK_END);                         /* Go to end of file for the next iteration */
        }
    }
}
