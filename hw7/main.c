/*
 *  This program is a Word Puzzle: In a 15x15 board, players
 *  try to find 7 randomly selected words. Words may be placed
 *  horizontally, vertically, or diagonally.
 *
 *  Assignment #7 Submission by Çağla Nur Yurdasal
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 15
#define COLUMN 15

int main(void)
{
    FILE *fp;
    int size_file;     // size of wordlist.txt
    int wordCount = 0; // word count selected for the board
    char board[ROW][COLUMN];
    char wordList[7];
    char c;
    fp = fopen("wordlist.txt", "r+");

    int num_lines = 0; // number of lines in .txt file
    while (!feof(fp))
    {
        c = fgetc(fp);
        if (c == '\n')
        {
            num_lines++;
        }
    }
    printf("Lines: %d\n", num_lines);
}
