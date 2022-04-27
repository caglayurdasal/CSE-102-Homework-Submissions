/*
 *  This program is a Word Puzzle: In a 15x15 board, players
 *  try to find 7 randomly selected words. Words may be placed
 *  horizontally, vertically, or diagonally.
 *
 *  Assignment #7 Submission by Çağla Nur Yurdasal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROW 15
#define COLUMN 15
#define MAX_LEN 10

void
buildBoard (char board[ROW][COLUMN], char word[MAX_LEN])
{
  /* Put spaces initially inside the board for later check with characters */
  for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < ROW; c++)
        {
          board[r][c] = " ";
        }
    }
  int dir[8], y_axis, x_axis, len_word; //(y,x)=(row,column)
  srand (time (NULL));                  // seed
  for (int i = 0; i < 7; i++)
    {
      /* Get the start point of the word on the board */
      y_axis = rand () % 15; // index 0-14
      x_axis = rand () % 15; // index 0-14
      len_word = strlen (word[i]);
      dir[i] = rand () % 8 + 1; // directions 1-8

      switch (dir[i])
        {
        case 1:
          /* Place the word from left to right */
          left_to_right (board, word, y_axis, x_axis, len_word);
          while (left_to_right == -1)
            {
            }
          break;
        case 2:
          /* Place the word from right to left */
          right_to_left (board, word, y_axis, x_axis, len_word);
          break;
        case 3:
          /* Place the word upwards */
          upwards (board, word, y_axis, x_axis, len_word);
          break;
        case 4:
          /* Place the word downwards */
          downwards (board, word, y_axis, x_axis, len_word);
          break;
        case 5:
          /* Place the word downward diagonal, left to right */
          diag_down_left_to_right (board, word, y_axis, x_axis, len_word);
          break;
        case 6:
          /* Place the word downward diagonal, right to left */
          diag_down_right_to_left (board, word, y_axis, x_axis, len_word);
          break;
        case 7:
          /* Place the word upward diagonal, left to right */
          diag_up_left_to_right (board, word, y_axis, x_axis, len_word);
          break;
        case 8:
          /* Place the word upward diagonal, right to left */
          diag_up_right_to_left (board, word, y_axis, x_axis, len_word);
          break;
        default:
          break;
        }
    }
}

int
diag_down_left_to_right (char board[ROW][COLUMN], char word[], int y_axis,
                         int x_axis, int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if ((y_axis + i) > 14 || (x_axis + i) > 14)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;
  while (i < len_word)
    {
      board[y_axis][x_axis] = word[i];
      y_axis++;
      x_axis++;
      i++;
    }
  return 0;
}

int
diag_down_right_to_left (char board[ROW][COLUMN], char word[], int y_axis,
                         int x_axis, int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if ((y_axis + i) > 14 || (x_axis - i) < 0)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;
  while (i < len_word)
    {
      board[y_axis][x_axis] = word[i];
      y_axis++;
      x_axis--;
      i++;

      return -1;
    }
  return 0;
}
int
diag_up_left_to_right (char board[ROW][COLUMN], char word[], int y_axis,
                       int x_axis, int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if ((y_axis - i) < 0 || (x_axis + i) > 14)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;
  while (i < len_word)
    {
      board[y_axis][x_axis] = word[i];
      y_axis--;
      x_axis++;
      i++;
    }
  return 0;
}
int
diag_up_right_to_left (char board[ROW][COLUMN], char word[], int y_axis,
                       int x_axis, int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if ((y_axis - i) < 0 || (x_axis - i) < 0)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;
  while (i < len_word)
    {
      board[y_axis][x_axis] = word[i];
      y_axis--;
      x_axis--;
      i++;
    }
  return 0;
}
int
left_to_right (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
               int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if (x_axis + i > 14)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;
  while (i < len_word)
    {
      board[y_axis][x_axis] = word[i];
      x_axis++;
      i++;
    }
  return 0;
}
int
right_to_left (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
               int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if (x_axis - i < 0)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;
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
int
upwards (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
         int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if (y_axis - i < 0)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;
  while (i < len_word)
    {
      board[y_axis][x_axis] = word[i];
      y_axis--;
      i++;
    }
  return 0;
}
int
downwards (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
           int len_word)
{
  int i = 0;
  while (i < len_word)
    {
      if (y_axis + i > 14)
        {
          return -1;
        }
      else if (board[y_axis][x_axis] != " ")
        {
          return -1;
        }
      i++;
    }
  i = 0;

  while (i < len_word)
    {
      board[y_axis][x_axis] = word[i];
      y_axis++;
      i++;
    }
  return 0;
}

int
main (void)
{
  FILE *fp;
  int size_file;     // size of wordlist.txt
  int wordCount = 0; // word count selected for the board
  char board[ROW][COLUMN];
  char wordList[7][MAX_LEN];
  char temp[7][MAX_LEN];

  fp = fopen ("wordlist.txt", "r+");

  fseek (fp, 0, SEEK_END); /* Go to end of file to find size */
  size_file = ftell (fp);  /* Store the current position of file
                              pointer to get the size of file */

  if (fp != NULL)
    {
      srand (time (NULL));  // seed
      while (wordCount < 7) /* Select random 7 words for the board */
        {
          fseek (fp, -1 * (rand () % size_file),
                 SEEK_CUR); /* Move the position of file pointer back
                              to a random position */

          fscanf (fp, "%s",
                  temp[wordCount]); /* In case pointer is not at the start of a
                                     word, scan until end of line and put the
                                     scanned word in temp to discard it, then
                                     read the next word from the start and
                                     put it in the word list  */

          fscanf (fp, "%s", wordList[wordCount]); /* Get the actual word */

          printf ("%d. word: %s\n", wordCount + 1, wordList[wordCount]);
          fseek (fp, 0,
                 SEEK_END); /* Go to end of file for the next iteration */
          wordCount++;
        }
    }
  /* Build the initial board */
  for (int i = 0; i < 7; i++)
    {
      buildBoard (board, wordList[i]);
    }
  /* Display the initial board */
  for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COLUMN; c++)
        {
          printf ("%c ", board[r][c]);
        }
      printf ("\n");
    }
}
