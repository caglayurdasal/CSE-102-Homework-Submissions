/*
 *  This program is a Word Puzzle: In a 15x15 board, players
 *  try to find 7 randomly selected words. Words may be placed
 *  horizontally, vertically, or diagonally.
 *
 *  Assignment #7 Submission by Çağla Nur Yurdasal
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ROW 15
#define COLUMN 15
#define MAX_LEN 10

void buildBoard(char *words[][MAX_LEN])
{
    char board[ROW][COLUMN];
    int dir[8], y_axis, x_axis, len; //(y,x)=(row,column)
    srand(time(NULL));               // seed
    for (int i = 0; i < 7; i++)
    {
        /* Mark start point of the word at the board */
        y_axis = rand() % 15;
        x_axis = rand() % 15;
        len = strlen(words[i]);

        switch (dir[i])
        {
        case 1:
            /* Place the word from left to right */

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
        }
    }
}

int main(void)
{
    FILE *fp;
    int size_file;     // size of wordlist.txt
    int wordCount = 0; // word count selected for the board
    char board[ROW][COLUMN];
    char wordList[7][MAX_LEN];
    char temp[7][MAX_LEN];

    fp = fopen("wordlist.txt", "r+");

    fseek(fp, 0, SEEK_END); /* Go to end of file to find size */
    size_file = ftell(fp);  /* Store the current position of file
                               pointer to get the size of file*/

    srand(time(NULL)); // seed

    if (fp != NULL)
    {
        while (wordCount < 7) /* Select random 7 words for the board */
        {

            fseek(fp, -1 * (rand() % size_file), SEEK_CUR); /* Move the position of file pointer back
                                                               to a random position */

            fscanf(fp, "%s", temp[wordCount]); /* In case pointer is not at the start of a word,
                                                  scan until end of line and put the scanned word
                                                  in temp to discard it, then read the next word
                                                  from the start and put it in the word list  */

            fscanf(fp, "%s", wordList[wordCount]); /* Get the actual word */

            printf("%d. word: %s\n", wordCount + 1, wordList[wordCount]);
            fseek(fp, 0, SEEK_END); /* Go to end of file for the next iteration */
            wordCount++;
        }
    }
}
