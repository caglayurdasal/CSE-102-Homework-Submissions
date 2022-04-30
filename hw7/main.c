#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_WORDS 7 /* Number of words to be found on the board */
#define MAX_LEN 10  /* Max length of one word */
#define ROW 15      /* Number of rows, y-axis, of the board */
#define COLUMN 15   /* Number of columns, x-axis, of the board */

void pick_words(char words[][MAX_LEN], int num_lines, FILE *fp);
int main()
{
  char words[NUM_WORDS][MAX_LEN];

  /* Open the file */
  FILE *fp;
  fp = fopen("wordlist.txt", "rw");

  /* Find the number of lines in the txt file */
  char c;
  int num_lines = 0;
  while (!feof(fp))
  {
    c = fgetc(fp);
    if (c == '\n') /* If a new line or EOF is encountered, count */
    {
      num_lines++;
    }
    else if (c == EOF)
    {
      num_lines++;
      c = '\n';
      break;
    }
  }
  pick_words(words, num_lines, fp);
  for (int i = 0; i < NUM_WORDS; i++)
  {
    printf("%d. word: %s", i + 1, words[i]);
  }

  /* Place the words */
  int dir;  /* Direction in which word to be placed */
  int x, y; /* Start point of the word */
  int temp_x, temp_y;

  /* Put 0s onto board initially for later check operations */
  char board[ROW][COLUMN];
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COLUMN; j++)
    {
      strcpy(&board[i][j], "0");
    }
  }

  for (int w = 0; w < NUM_WORDS; w++)
  {
    /* Decide the start point of the word */
    x = rand() % 15 + 1;
    y = rand() % 15 + 1;
    temp_x = x;
    temp_y = y;
    int i, j, check = 1;
    char word[MAX_LEN];

    strcpy(word, words[w]);

    while (check)
    {
      /* Decide the direction */
      dir = rand() % 8 + 1;

      switch (dir)
      {
      case 1:
        /* Check if there will be an overlap of characters */
        for (i = 0; i < strlen(word) - 2; i++)
        {

          if (board[temp_y][temp_x] != '0')
          {
            check = 1;
            break;
          }
          temp_x++;
          check = 0;
        }
        /* Place the word letter by letter */
        for (i = 0; i < strlen(word) - 2; i++)
        {
          board[y][x] = word[i];
          x++;
        }
        break;
      case 2:
        /* Place the word from right to left */
        for (int i = 0; i < strlen(word) - 2; i++)
        {
          if (board[y][x] != '0')
          {
            break;
          }
          x++;
        }
        break;
      case 3:
        /* Place the word downwards */
        for (int i = 0; i < strlen(word) - 2; i++)
        {
          if (board[y][x] != '0')
          {
            break;
          }
          x++;
        }
        break;
      case 4:
        /* Place the word from upwards */
        for (int i = 0; i < strlen(word) - 2; i++)
        {
          if (board[y][x] != '0')
          {
            break;
          }
          x++;
        }
        break;
      case 5:
        /* Place the word downwards diagonal, from left to right */
        for (int i = 0; i < strlen(word) - 2; i++)
        {
          if (board[y][x] != '0')
          {
            break;
          }
          x++;
        }
        break;
      case 6:
        /* Place the word downwards diagonal, from right to left */
        for (int i = 0; i < strlen(word) - 2; i++)
        {
          if (board[y][x] != '0')
          {
            break;
          }
          x++;
        }
        break;
      case 7:
        /* Place the word upwards diagonal, from left to right */
        for (int i = 0; i < strlen(word) - 2; i++)
        {
          if (board[y][x] != '0')
          {
            break;
          }
          x++;
        }
        break;
      case 8:
        /* Place the word upwards diagonal, from right to left */
        for (int i = 0; i < strlen(word) - 2; i++)
        {
          if (board[y][x] != '0')
          {
            break;
          }
          x++;
        }
        break;
      default:
        break;
      }
    }
  }

  /* Start placing the word */
  // printf("%d. word: %s", w + 1, word);
  // printf("Start point of %d. word: x=%d, y=%d\n", w + 1, x, y); // for debugging
  // printf("Direction of %d. word: %d\n", w + 1, dir);            // for debugging

  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COLUMN; j++)
    {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}
void pick_words(char words[][MAX_LEN], int num_lines, FILE *fp)
{
  /* Pick 7 random words and store them in an array */
  int line_rand_word;
  char rand_word[MAX_LEN];

  srand((unsigned)time(NULL)); /* Seed */
  for (int w = 0; w < NUM_WORDS; w++)
  {
    fseek(fp, 0, SEEK_SET);                  /* Move pointer to the start */
    line_rand_word = rand() % num_lines + 1; /* Pick a random line to be read */

    for (int l = 0; l < line_rand_word; l++)
    {
      fgets(rand_word, sizeof(rand_word), fp); /* Update the word that is read until target line is reached */
    }
    strcpy(words[w], rand_word); /* Put the random word in the array */
    for (int i = 0; i < w; i++)
    {
      while (words[i] == words[w])
      {
        pick_words(&words[w], num_lines, fp);
      }
    }
  }
  fclose(fp);
}