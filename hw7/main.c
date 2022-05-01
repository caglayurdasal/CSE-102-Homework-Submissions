/*
 * This program is a word puzzle. In each round,
 * 7 random words are picked from a wordlist and
 * put randomly in a 15x15 board, along with other
 * random letters. Player tries to find hidden words
 * by entering word and start point.
 */

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
int searchWord(char board[][COLUMN], char word[MAX_LEN], int x, int y, int len);

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
    printf("%d. word: %s [%d,%d]\n", w + 1, words[w], temp_y, temp_x);
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
      }
    }
  }
  /* Display the initial board at the beginning */
  print_board(board);
  printf("\n");
  int mistakes = 0, foundedWords = 0; /* Check how many mistakes are done and words are founded */
  int row, column;                    /* Row and column */
  char foundWord[MAX_LEN];            /* User entered word */
  int len, len_buff = 0;

  int totalPoints = 0;
  char buffer[50];
  while (foundedWords < 7 && mistakes < 3)
  {
    printf("Enter raw (y-coordinate), column (x-coordinate) and word, respectively: ");
    scanf("%d", &row);
    scanf("%d", &column);
    scanf("%s", foundWord);

    if (strcmp(foundWord, ":q") == 0) /* Terminate if user enters :q command */
    {
      printf("You chose to give up:/ Goodbye!\n");
      printf("Total points: %d\n", totalPoints);
      return 0;
    }
    /* Search the board, if word is found update the board and score */
    len = strlen(foundWord);
    int isfounded = searchWord(board, foundWord, column, row, len);
    if (!isfounded)
    {
      mistakes++;
      print_board(board);
      printf("Wrong choice! You have only %d lefts.\n", (3 - mistakes));
      if (mistakes == 3) /* Player can only make 3 mistakes */
      {
        printf("You have lost:( Try better next time!\n");
        printf("Total points: %d\n", totalPoints);
      }
    }
    else
    {
      foundedWords++;
      totalPoints += 2;
      print_board(board);

      printf("Founded! You got 2 points. Your total points: %d\n", totalPoints);
      if (foundedWords == 7)
      {
        printf("You have found all the hidden words:) Congrats!\n");
        printf("Total points: %d\n", totalPoints);
      }
    }
  }
  return 0;
}
int searchWord(char board[][COLUMN], char word[MAX_LEN], int x, int y, int len)
{
  /* This function searches for the user entered word starting from user entered
   * point on the board.
   * int x, y: Coordinates of the first letter
   * int len: Length of the word
   * char word: Word to be searched for on the board
   * char board: Game board
   */
  int found = 0;
  int temp_x = x, temp_y = y;
  char xWord[len];
  for (int i = 0; i < len; i++)
  {
    xWord[i] = 'X';
  }

  /* Search from left to right */
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1; /* Keep searching using the current direction
                    if letters match */
    }
    else
    {
      found = 0; /* If letters don't match, stop searching with current
                    direction and try next direction */
      break;
    }
    x++;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    left_to_right(board, xWord, x, y);
    return 1;
  }

  /* Search from right to left */
  x = temp_x;
  y = temp_y;
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1;
    }
    else
    {
      found = 0;
      break;
    }
    x--;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    right_to_left(board, xWord, x, y);
    return 1;
  }

  /* Search downwards */
  x = temp_x;
  y = temp_y;
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1;
    }
    else
    {
      found = 0;
      break;
    }
    y++;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    downwards(board, xWord, x, y);
    return 1;
  }

  /* Search upwards */
  x = temp_x;
  y = temp_y;
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1;
    }
    else
    {
      found = 0;
      break;
    }
    y--;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    upwards(board, xWord, x, y);
    return 1;
  }

  /* Search upwards diagonal, from right to left */
  x = temp_x;
  y = temp_y;
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1;
    }
    else
    {
      found = 0;
      break;
    }
    y--;
    x--;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    diag_up_right_to_left(board, xWord, x, y);
    return 1;
  }

  /* Search upwards diagonal, from left to right */
  x = temp_x;
  y = temp_y;
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1;
    }
    else
    {
      found = 0;
      break;
    }
    x++;
    y--;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    diag_up_left_to_right(board, xWord, x, y);
    return 1;
  }

  /* Search downwards diagonal, from left to right */
  x = temp_x;
  y = temp_y;
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1;
    }
    else
    {
      found = 0;
      break;
    }
    x++;
    y++;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    diag_down_left_to_right(board, xWord, x, y);
    return 1;
  }

  /* Search downwards diagonal, from right to left */
  x = temp_x;
  y = temp_y;
  for (int i = 0; i < len; i++)
  {
    if (word[i] == board[y][x])
    {
      found = 1;
    }
    else
    {
      found = 0;
      break;
    }
    x--;
    y++;
  }
  if (found == 1)
  {
    x = temp_x;
    y = temp_y;
    diag_down_right_to_left(board, xWord, x, y);
    return 1;
  }
  return 0;
}

int check_overlapped_word(int x, int y, int dir, int l, int len_word, char board[][COLUMN], char word[MAX_LEN])
{
  /* This function checks any word that would cause an overlap of characters.
   * int x, y: Coordinates of the first letter
   * int dir: Direction in which the word is placed
   * char board: Game board
   * char word: Word whose place to be checked
   */

  /* Check if the word fits on the board */
  int len_check = check_len(x, y, len_word, dir);

  /* If word does not fit, return 1 to main to delete the placed
  characters and pick new location and direction */
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
      if (board[y][x] != '\0') /* If there is a character other than NULL, return to avoid overlap */
      {
        return 1;
      }
      x++; /* Update only x-coordinate whiling moving from left to right */
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
      x--; /* Update only x-coordinate whiling moving from right to left */
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
      y++; /* Update only y-coordinate whiling moving downwards */
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
      y--; /* Update only y-coordinate whiling moving upwards */
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
      x++; /* Update both coordinates whiling moving diagonal */
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
      x--; /* Update both coordinates whiling moving diagonal */
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
      x++; /* Update both coordinates whiling moving diagonal */
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
      x--; /* Update both coordinates whiling moving diagonal */
      y--;
    }
    break;
  }
  return 0;
}
void delete_overlapping_word(int x, int y, int dist, int dir, char board[][COLUMN])
{
  /* This function deletes any word that would cause an overlap of characters.
   * int x, y: Coordinates of the first letter
   * int dist: Number of points that the letter moved on the board when it caused overlap
   * int dir: Direction in which the word is placed
   * char board: Game board
   */
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
  /* This function check whether the word fits on the board
   * int x, y: Coordinates of the first letter
   * int len_word: Length of the word
   * int dir: Direction in which the word to be placed
   */
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
  /* This function picks random 7 words from a .txt file.
   * char words: Array in which randomly picked words to be put
   * int num_lines: Number of lines in .txt file
   * FILE *fp: File pointer
   */

  int line_rand_word, flag = 1;
  char rand_word[MAX_LEN];

  while (flag)
  {
    srand((unsigned)time(NULL)); /* Seed */
    for (int w = 0; w < NUM_WORDS; w++)
    {
      fseek(fp, 0, SEEK_SET);                  /* Move pointer to the start */
      line_rand_word = rand() % num_lines + 1; /* Pick a random line to be read */

      for (int line = 0; line < line_rand_word; line++)
      {
        /* Update the word that is read until target line is reached */
        fscanf(fp, "%s", words[w]);
      }

      int i = 0;
      for (int i = 0; i < w; i++)
      {
        /* Check if picked word has a duplicate in the array */
        if (strcmp(words[i], words[w]) == 0)
        {
          flag = 1;
        }
        else
        {
          flag = 0;
        }
      }
    }
  }
}
void print_board(char board[][COLUMN])
{
  /* This function displays the board.
   * char board: Game board
   */
  printf("\n");
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COLUMN; j++)
    {
      if (board[i][j] != '.' || board[i][j] == 'X')
      {
        printf("%c ", board[i][j]);
      }
      else
      {
        /* If an index has no letter on it, place a random letter */
        board[i][j] = (char)(97 + rand() % 26);
        printf("%c ", board[i][j]);
      }
    }
    printf("\n");
  }
}

void left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  /* This function places the word from left to right.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {

    board[y][x] = word[i];
    x++;
  }
}
void right_to_left(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  /* This function places the word from right to left.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {
    board[y][x] = word[i];
    x--;
  }
}
void downwards(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  /* This function places the word downwards.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {
    board[y][x] = word[i];
    y++;
  }
}
void upwards(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  /* This function places the word upwards.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {
    board[y][x] = word[i];
    y--;
  }
}
void diag_up_left_to_right(char board[][COLUMN], char word[MAX_LEN], int x, int y)
{
  /* This function places the word upwards diagonal, from left to right.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
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
  /* This function places the word upwards diagonal, from right to left.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
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
  /* This function places the word downwards diagonal, from left to right.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
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
  /* This function places the word downwards diagonal, from right to left.
   * char board: Game board
   * char word: Word to be placed
   * int x, y: Coordinate of the first character of the word
   */
  int len_word = strlen(word);
  for (int i = 0; i < len_word; i++)
  {
    board[y][x] = word[i];
    x--;
    y++;
  }
}
