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
#define NUM_WORDS 7

// int
// diag_down_left_to_right (char board[ROW][COLUMN], char **word, int y_axis,
//                          int x_axis, int len_word)
// {
//   int i = 0, j = 0;
//   while (i < len_word)
//     {
//       if ((y_axis + i) > 14 || (x_axis + i) > 14)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//
//   while (j < len_word)
//     {
//       board[y_axis][x_axis] = word[j];
//       y_axis++;
//       x_axis++;
//       j++;
//     }
//   return 0;
// }
//
// int
// diag_down_right_to_left (char board[ROW][COLUMN], char wordList[], int
// y_axis,
//                          int x_axis, int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if ((y_axis + i) > 14 || (x_axis - i) < 0)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     int
// diag_down_left_to_right (char board[ROW][COLUMN], char **word, int y_axis,
//                          int x_axis, int len_word)
// {
//   int i = 0, j = 0;
//   while (i < len_word)
//     {
//       if ((y_axis + i) > 14 || (x_axis + i) > 14)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//
//   while (j < len_word)
//     {
//       board[y_axis][x_axis] = word[j];
//       y_axis++;
//       x_axis++;
//       j++;
//     }
//   return 0;
// }
//
// int
// diag_down_right_to_left (char board[ROW][COLUMN], char wordList[], int
// y_axis,
//                          int x_axis, int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if ((y_axis + i) > 14 || (x_axis - i) < 0)
//         {
//           return -1;
//     }
//   i = 0;
//   while (i < len_word)
//     {
//       board[y_axis][x_axis] = word[i];
//       y_axis++;
//       x_axis--;
//       i++;
//
//       return -1;
//     }
//   return 0;
// }
// int
// diag_up_left_to_right (char board[ROW][COLUMN], char word[], int y_axis,
//                        int x_axis, int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if ((y_axis - i) < 0 || (x_axis + i) > 14)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//   i = 0;
//   while (i < len_word)
//     {
//       board[y_axis][x_axis] = word[i];
//       y_axis--;
//       x_axis++;
//       i++;
//     }
//   return 0;
// }
// int
// diag_up_right_to_left (char board[ROW][COLUMN], char word[], int y_axis,
//                        int x_axis, int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if ((y_axis - i) < 0 || (x_axis - i) < 0)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//   i = 0;
//   while (i < len_word)
//     {
//       board[y_axis][x_axis] = word[i];
//       y_axis--;
//       x_axis--;
//       i++;
//     }
//   return 0;
// }
// int
// left_to_right (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
//                int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if (x_axis + i > 14)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//   i = 0;
//   while (i < len_word)
//     {
//       board[y_axis][x_axis] = word[i];
//       x_axis++;
//       i++;
//     }
//   return 0;
// }
// int
// right_to_left (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
//                int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if (x_axis - i < 0)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//   i = 0;
//   while (i < len_word)
//     {
//       if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           board[y_axis][x_axis] = word[i];
//           x_axis--;
//           i++;
//         }
//       else
//         {
//           return -1;
//         }
//     }
//   return 0;
// }
// int
// upwards (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
//          int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if (y_axis - i < 0)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//   i = 0;
//   while (i < len_word)
//     {
//       board[y_axis][x_axis] = word[i];
//       y_axis--;
//       i++;
//     }
//   return 0;
// }
// int
// downwards (char board[ROW][COLUMN], char word[], int y_axis, int x_axis,
//            int len_word)
// {
//   int i = 0;
//   while (i < len_word)
//     {
//       if (y_axis + i > 14)
//         {
//           return -1;
//         }
//       else if (strcmp (&board[y_axis][x_axis], " ") != 0)
//         {
//           return -1;
//         }
//       i++;
//     }
//   i = 0;
//
//   while (i < len_word)
//     {
//       board[y_axis][x_axis] = word[i];
//       y_axis++;
//       i++;
//     }
//   return 0;
// }

void buildBoard(char board[ROW][COLUMN], char wordList[][MAX_LEN])
{
  int j;
  /* Put spaces initially inside the board for later check with characters */
  // for (int r = 0; r < ROW; r++)
  //   {
  //     for (int c = 0; c < ROW; c++)
  //       {
  //         strcpy (&board[r][c], " ");
  //       }
  //   }
  int dir[8], y_axis, x_axis, len_word; //(y,x)=(row,column)
  for (int i = 0; i < NUM_WORDS; i++)
  {
    srand(time(NULL)); // seed

    /* Get the start point of the word on the board */
    y_axis = rand() % 15; // index 0-14
    x_axis = rand() % 15; // index 0-14
    len_word = strlen(wordList[i]);

    dir[i] = rand() % 8 + 1; // directions 1-8

    switch (dir[i])
    {
    case 1:
      /* Place the word from left to right */
      // left_to_right (board, words, y_axis, x_axis, len_word);
      j = 0;
      /* Check if spaces available for the word */
      while (j < len_word)
      {
        while ((x_axis + j > 14) || (board[y_axis][x_axis] != NULL))
        {
          y_axis = rand() % 15; // index 0-14
          x_axis = rand() % 15; // index 0-14
        }
        j++;
      }
      /*  Initialize j again to put the letters on the board */
      j = 0;
      while (j < len_word)
      {
        board[y_axis][x_axis] = wordList[i][j];
        x_axis++;
        j++;
      }
      break;
    case 2:
      /* Place the word from right to left */
      // right_to_left (board, words, y_axis, x_axis, len_word);
      break;
    case 3:
      /* Place the word upwards */
      // upwards (board, words, y_axis, x_axis, len_word);
      break;
    case 4:
      /* Place the word downwards */
      // downwards (board, words, y_axis, x_axis, len_word);
      break;
    case 5:
      /* Place the word downward diagonal, left to right */
      // diag_down_left_to_right (board, words, y_axis, x_axis,
      // len_word);
      break;
    case 6:
      /* Place the word downward diagonal, right to left */
      // diag_down_right_to_left (board, words, y_axis, x_axis,
      // len_word);
      break;
    case 7:
      /* Place the word upward diagonal, left to right */
      // diag_up_left_to_right (board, words, y_axis, x_axis,
      // len_word);
      break;
    case 8:
      /* Place the word upward diagonal, right to left */
      // diag_up_right_to_left (board, words, y_axis, x_axis,
      // len_word);
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
  char wordList[NUM_WORDS][MAX_LEN];
  char word[MAX_LEN];
  char temp[7][MAX_LEN];

  fp = fopen("wordlist.txt", "r+");
  /* Go to end of file to find size */
  // fseek (fp, 0, SEEK_END);
  /* Store the current position of file pointer to get the size of file */
  // size_file = ftell (fp);

  /* Count words in file */
  while (fgets(word, sizeof(word), fp) != NULL)
  {
    wordCount++;
  }
  // printf ("Words: %d\n", wordCount);
  /* Store random words in array */
  srand((unsigned)time(NULL)); // seed
  for (int i = 0; i < NUM_WORDS; i++)
  {
    rewind(fp);

    int sel = rand() % wordCount + 1;
    for (int j = 0; j < sel; j++)
    {
      fgets(word, sizeof(word), fp);
    }
    strcpy(wordList[i], word);
    for (int j = 0; j < i; j++)
    {
      while (strcmp(wordList[i], wordList[j]) == 0)
      {
        // printf ("Duplicate word: %s in index: %d\n", wordList[j], j);
        srand((unsigned)time(NULL)); // seed
        for (int i = 0; i < NUM_WORDS; i++)
        {
          rewind(fp);

          int sel = rand() % wordCount + 1;
          for (int j = 0; j < sel; j++)
          {
            fgets(word, sizeof(word), fp);
          }
          strcpy(wordList[i], word);
        }
      }
    }
  }

  fclose(fp);

  /* Display results */
  for (int i = 0; i < NUM_WORDS; i++)
  {
    printf("%d. word: %s", i + 1, wordList[i]);
  }

  // if (fp != NULL)
  //   {
  //     srand (time (NULL)); // seed
  //
  //     /* Select random 7 words for the board */
  //     while (wordCount < 7)
  //       {
  //         /* Move the position of file pointer back to a random position
  //         */ fseek (fp, -1 * (rand () % size_file), SEEK_CUR);
  //
  //         /* In case pointer is not at the start of a word, scan until
  //         end of the line and put the scanned word in temp to discard
  //         it, then read the next word from the start andput it in the
  //         word list  */ fscanf (fp, "%s", temp[wordCount]);
  //
  //         /* Get the actual word */
  //         fscanf (fp, "%s", wordList[wordCount]);
  //
  //         printf ("%d. word: %s\n", wordCount + 1, wordList[wordCount]);
  //
  //         /* Go to end of file for the next iteration */
  //         fseek (fp, 0, SEEK_END);
  //         wordCount++;
  //       }
  //   }
  /* Build the initial board */

  buildBoard(board, wordList);

  /* Display the initial board */
  for (int r = 0; r < ROW; r++)
  {
    for (int c = 0; c < COLUMN; c++)
    {
      printf("%c ", board[r][c]);
    }
    printf("\n");
  }

  return 0;
}
