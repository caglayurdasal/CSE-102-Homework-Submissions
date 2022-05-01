#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_WORDS 7 /* Number of words to be found on the board */
#define MAX_LEN 10  /* Max length of one word */
#define ROW 15      /* Number of rows, y-axis, of the board */
#define COLUMN 15   /* Number of columns, x-axis, of the board */

void pick_words(char words[][MAX_LEN], int num_lines, FILE *fp);
void print_board(char board[][COLUMN]);
void left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y);
void right_to_left(char board[][COLUMN], char word[MAX_LEN], int x, int y);
void downwards(char board[][COLUMN], char word[MAX_LEN], int x, int y);
void upwards(char board[][COLUMN], char word[MAX_LEN], int x, int y);
void diag_up_left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y);
void diag_up_right_to_left(char board[][COLUMN], char word[MAX_LEN], int x, int y);
void diag_down_left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y);
void diag_down_right_to_left(char board[][COLUMN], char word[MAX_LEN], int x, int y);
int check_len(int x, int y, int len_word, int dir);
int check_overlapped_word(int x, int y, int dir, int l, int len_word, char board[][COLUMN], char word[MAX_LEN]);
void delete_overlapping_word(int x, int y, int dist, int dir, char board[][COLUMN]);

int main()
{
  /* Open the file */
  FILE *fp;
  fp = fopen("wordlist.txt", "r");

  /* Find the number of lines in the txt file */
  char c;
  int num_lines = 0;

  while (!feof(fp))
  {
    c = fgetc(fp);
    if (c == '\n' || c == EOF) /* If a new line or EOF is encountered, count */
    {
      num_lines++;
    }
  }

  char words[NUM_WORDS][MAX_LEN];

  pick_words(words, num_lines, fp);
  fclose(fp);

  /* Place the words */
  int dir;  /* Direction in which word to be placed */
  int x, y; /* Start point of the word */
  int temp_x, temp_y;
  char board[ROW][COLUMN];

  /* Put \0 characters on the board initially to check during later operations */
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COLUMN; j++)
    {
      board[i][j] = '\0';
    }
  }

  for (int w = 0; w < NUM_WORDS; w++)
  {
    int i, j, len_check;
    char word[MAX_LEN];
    int len_word = strlen(words[w]); /* Length of one word */
    // printf("Len of %d. word: %d\n", w + 1, len_word);

    /* Check if there will be an overlap of characters or overflow due to length of word */
    int dist = 0;
    x = rand() % 15;
    y = rand() % 15;
    temp_x = x;
    temp_y = y;
    dir = rand() % 8 + 1; /* Direction in which word will be placed */
    int overlap_check = check_overlapped_word(x, y, dir, dist, len_word, board, words[w]);
    if (overlap_check == 1)
    {
      while (overlap_check == 1)
      {
        delete_overlapping_word(x, y, dist, dir, board);
        do
        {
          /* Start point of the word */
          x = rand() % 15;
          y = rand() % 15;
          temp_x = x;
          temp_y = y;
          dir = rand() % 8 + 1; /* Direction in which word will be placed */
          len_check = check_len(x, y, len_word, dir);
        } while (len_check == -1);
        overlap_check = check_overlapped_word(x, y, dir, dist, len_word, board, words[w]);
      }
    }

    switch (dir)
    {
    case 1:
      /* Check if there will be an overlap of characters */
      left_to_right(board, words[w], temp_x, temp_y);
      break;

    case 2:
      /* Place the word from right to left */
      right_to_left(board, words[w], temp_x, temp_y);
      break;

    case 3:
      /* Place the word downwards */
      downwards(board, words[w], temp_x, temp_y);
      break;

    case 4:
      /* Place the word upwards */
      upwards(board, words[w], temp_x, temp_y);
      break;
    case 5:
      /* Place the word downwards diagonal, from left to right */
      diag_down_left_to_right(board, words[w], temp_x, temp_y);
      break;

    case 6:
      /* Place the word downwards diagonal, from right to left */
      diag_down_right_to_left(board, words[w], temp_x, temp_y);
      break;

    case 7:
      /* Place the word upwards diagonal, from left to right */
      diag_up_left_to_right(board, words[w], temp_x, temp_y);
      break;

    case 8:
      /* Place the word upwards diagonal, from right to left */
      diag_up_right_to_left(board, words[w], temp_x, temp_y);
      break;
    }
  }

  for (int r = 0; r < ROW; r++)
  {
    for (int c = 0; c < COLUMN; c++)
    {
      if (board[r][c] == '\0')
      {
        board[r][c] = '.';
        // board[r][c] = (char)(97 + rand() % 26);
      }
    }
  }

  print_board(board);
  return 0;
}
int check_overlapped_word(int x, int y, int dir, int l, int len_word, char board[][COLUMN], char word[MAX_LEN])
{
  int len_check = check_len(x, y, len_word, dir);
  if (len_check == -1)
  {
    return 1;
  }
  switch (dir)
  {
  case 1:
    /* From left to right */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      x++;
    }
    break;
  case 2:
    /* From right to left */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      x--;
    }
    break;
  case 3:
    /* Downwards */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      y++;
    }
    break;
  case 4:
    /* Upwards */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      y--;
    }
    break;
  case 5:
    /* Downwards diagonal, from left to right */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      x++;
      y++;
    }
    break;
  case 6:
    /* Downwards diagonal, from right to left */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      x--;
      y++;
    }
    break;
  case 7:
    /* Upwards diagonal, from left to right */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      x++;
      y--;
    }
    break;
  case 8:
    /* Upwards diagonal, from right to left */
    for (l = 0; l < len_word; l++)
    {
      if (board[y][x] != '\0')
      {
        return 1;
      }
      x--;
      y--;
    }
    break;
  }
  return 0;
}
void delete_overlapping_word(int x, int y, int dist, int dir, char board[][COLUMN])
{
  switch (dir)
  {
  case 1:
    // delete from right to left
    x--;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (x != 0)
      {
        x--;
      }
    }
    break;
  case 2:
    // delete from left to right
    x++;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (x != 14)
      {
        x++;
      }
    }
    break;
  case 3:
    // delete upwards
    y--;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (y != 0)
      {
        y--;
      }
    }
    break;
  case 4:
    // delete downwards
    y++;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (y != 14)
      {
        y++;
      }
    }
    break;
  case 5:
    /* Delete upwards diagonal, from right to left */
    y--;
    x--;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (y != 0 || x != 0)
      {
        y--;
        x--;
      }
    }
    break;
  case 6:
    /* Delete upwards diagonal, from left to right */
    y--;
    x++;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (y != 0 || x != 14)
      {
        y--;
        x++;
      }
    }
    break;
  case 7:
    /* Delete downwards diagonal, from right to left */
    y++;
    x--;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (y != 14 && x != 0)
      {
        y++;
        x--;
      }
    }
    break;
  case 8:
    /* Delete downwards diagonal, from left to right */
    y++;
    x++;
    for (int i = 0; i < dist; i++)
    {
      board[y][x] = '\0';
      if (y != 14 || x != 14)
      {
        y++;
        x++;
      }
    }
    break;
  }
}
int check_len(int x, int y, int len_word, int dir)
{
  switch (dir)
  {
  case 1:
    // from left to right
    if (x + len_word > 14)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  case 2:
    // from right to left
    if (x - len_word < 0)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  case 3:
    // downwards
    if (y + len_word > 14)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  case 4:
    // upwards
    if (y - len_word < 0)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  case 5:
    // downwards diagonal, from left to right
    if (x + len_word > 14 || y + len_word > 14)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  case 6:
    // downwards diagonal, from right to left
    if (x - len_word < 0 || y + len_word > 14)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  case 7:
    // upwards diagonal, from left to right
    if (x + len_word > 14 || y - len_word < 0)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  case 8:
    // upwards diagonal, from right to left
    if (x - len_word < 0 || y - len_word < 0)
    {
      return -1;
    }
    else
    {
      return 1;
    }
    break;
  }
}

void pick_words(char words[][MAX_LEN], int num_lines, FILE *fp)
{
  /* Pick 7 random words and store them in an array */
  int line_rand_word, flag = 1;
  char rand_word[MAX_LEN];

  while (flag)
  {
    srand((unsigned)time(NULL)); /* Seed */
    for (int w = 0; w < NUM_WORDS; w++)
    {
      fseek(fp, 0, SEEK_SET);                  /* Move pointer to the start */
      line_rand_word = rand() % num_lines + 1; /* Pick a random line to be read */
      printf("%d. word rand line: %d\n", w + 1, line_rand_word);

      for (int line = 0; line < line_rand_word; line++)
      {
        /* Update the word that is read until target line is reached */
        fscanf(fp, "%s", words[w]);
      }

      int i = 0;
      for (int i = 0; i < w; i++)
      {
        if (strcmp(words[i], words[w]) == 0)
        {
          flag = 1;
        }
        else
        {
          flag = 0;
        }
      }

      printf("%d. word: %s\n", w + 1, words[w]);
    }
  }
}
void print_board(char board[][COLUMN])
{
  printf("\n");
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COLUMN; j++)
    {

      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

void left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    x++;
  }
}
void right_to_left(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {
    board[y][x] = word[i];
    x--;
  }
}
void downwards(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    y++;
  }
}
void upwards(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    y--;
  }
}
void diag_up_left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    x++;
    y--;
  }
}
void diag_up_right_to_left(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    x--;
    y--;
  }
}
void diag_down_left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    x++;
    y++;
  }
}
void diag_down_right_to_left(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    x--;
    y++;
  }
}
