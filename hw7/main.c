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

int diag_down_left_to_right(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
int diag_down_right_to_left(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
int diag_up_left_to_right(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
int diag_up_right_to_left(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
int left_to_right(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
int right_to_left(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
int upwards(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
int downwards(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word);
void buildBoard(char board[ROW][COLUMN], char word[MAX_LEN]);

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
                               pointer to get the size of file */

    if (fp != NULL)
    {
        srand(time(NULL));
        while (wordCount < 7) /* Select random 7 words for the board */
        {
            // seed
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
void buildBoard(char board[ROW][COLUMN], char word[MAX_LEN])
{
    /* Put spaces initially inside the board for later check with characters */
    char board[ROW][COLUMN];
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < ROW; c++)
        {
            board[r][c] = " ";
        }
    }
    int dir[8], y_axis, x_axis, len_word; //(y,x)=(row,column)
    srand(time(NULL));                    // seed
    for (int i = 0; i < 7; i++)
    {
        /* Mark start point of the word at the board */
        y_axis = rand() % 15;
        x_axis = rand() % 15;
        len_word = strlen(words[i]);
        dir[i] = rand() % 8 + 1;

        switch (dir[i])
        {
        case 1:
            /* Place the word from left to right */
            left_to_right(board, word, y_axis, x_axis, len_word);
            break;
        case 2:
            /* Place the word from right to left */
            right_to_left(board, word, y_axis, x_axis, len_word);
            break;
        case 3:
            /* Place the word upwards */
            upwards(board, word, y_axis, x_axis, len_word);
            break;
        case 4:
            /* Place the word downwards */
            downwards(board, word, y_axis, x_axis, len_word);
            break;
        case 5:
            /* Place the word downward diagonal, left to right */
            diag_down_left_to_right(board, word, y_axis, x_axis, len_word);
            break;
        case 6:
            /* Place the word downward diagonal, right to left */
            diag_down_right_to_left(board, word, y_axis, x_axis, len_word);
            break;
        case 7:
            /* Place the word upward diagonal, left to right */
            diag_up_left_to_right(board, word, y_axis, x_axis, len_word);
            break;
        case 8:
            /* Place the word upward diagonal, right to left */
            diag_up_right_to_left(board, word, y_axis, x_axis, len_word);
            break;
        default:
            break;
        }
    }
}

int diag_down_left_to_right(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            y_axis++;
            x_axis++;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

int diag_down_right_to_left(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            y_axis++;
            x_axis--;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
int diag_up_left_to_right(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            y_axis--;
            x_axis++;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
int diag_up_right_to_left(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            y_axis--;
            x_axis--;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
int left_to_right(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            x_axis++;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
int right_to_left(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            x_axis--;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
int upwards(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            y_axis--;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
int downwards(char board[ROW][COLUMN], char word[], int y_axis, int x_axis, int len_word)
{
    int i = 0;
    while (i < len_word)
    {
        if (board[y_axis][x_axis] == " ")
        {
            board[y_axis][x_axis] = word[i];
            y_axis++;
            i++;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
