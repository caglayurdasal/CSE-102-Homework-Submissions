#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_WORDS 7 /* Number of words to be found on the board */
#define MAX_LEN 10	/* Max length of one word */
#define ROW 15		/* Number of rows, y-axis, of the board */
#define COLUMN 15	/* Number of columns, x-axis, of the board */

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

int main()
{
	/* Open the file */
	FILE *fp;
	fp = fopen("wordlist.txt", "rw");

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

	for (int i = 0; i < NUM_WORDS; i++)
	{
		printf("%d. word: %s", i + 1, words[i]);
		printf("\n");
	}

	/* Place the words */
	int dir;  /* Direction in which word to be placed */
	int x, y; /* Start point of the word */
	int temp_x, temp_y;
	char board[ROW][COLUMN];
	board[0][0] = 0;
	/* Put 0s on the board initially to check during later operations */

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			board[i][j] = '\0';
		}
	}

	for (int w = 0; w < NUM_WORDS; w++)
	{
		int i, j;
		char word[MAX_LEN];
		strcpy(word, words[w]);

		int len_word = strlen(words[w]);
		printf("Len of %d. word: %d\n", w + 1, len_word);

		/* Decide the direction */
		dir = rand() % 8 + 1;
		/* Decide the start point of the word */
		x = rand() % 15;
		y = rand() % 15;
		temp_x = x;
		temp_y = y;
		switch (dir)
		{
		case 1:
			/* Check if there will be an overlap of characters */
			if (x + len_word > 14)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (x + len_word > 14);
			}

			for (i = 0; i < len_word; i++)
			{
				if (board[y][x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;

					} while (x + len_word > 14);
				}
				x++;
			}
			left_to_right(board, word, x, y);
			break;

		case 2:
			/* Place the word from right to left */
			if (x - len_word < 0)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (x - len_word < 0);
			}

			for (int i = 0; i < len_word; i++)
			{
				if (board[y][x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;

					} while (x - len_word < 0);
				}
				x--;
			}
			right_to_left(board, word, x, y);
			break;

		case 3:
			/* Place the word downwards */
			if (y + len_word > 14)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (y + len_word > 14);
			}

			for (int i = 0; i < len_word; i++)
			{
				if (board[temp_y][temp_x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;
						temp_x = x;
						temp_y = y;
					} while (y + len_word > 14);
				}
				temp_y++;
			}
			downwards(board, word, x, y);
			break;

		case 4:
			/* Place the word upwards */
			if (y - len_word < 0)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (y - len_word < 0);
			}

			for (int i = 0; i < len_word; i++)
			{
				if (board[temp_y][temp_x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;
						temp_x = x;
						temp_y = y;
					} while (y - len_word < 0);
				}
				temp_y--;
			}
			upwards(board, word, x, y);
			break;
		case 5:
			/* Place the word downwards diagonal, from left to right */
			if (y + len_word > 14 || x + len_word > 14)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (y + len_word > 14 || x + len_word > 14);
			}

			for (int i = 0; i < len_word; i++)
			{
				if (board[temp_y][temp_x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;
						temp_x = x;
						temp_y = y;
					} while (y + len_word > 14 || x + len_word > 14);
				}
				temp_x++;
				temp_y++;
			}
			diag_down_left_to_right(board, word, x, y);
			break;

		case 6:
			/* Place the word downwards diagonal, from right to left */
			if (y + len_word > 14 || x - len_word < 0)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (y + len_word > 14 || x - len_word < 0);
			}

			for (int i = 0; i < len_word; i++)
			{
				if (board[temp_y][temp_x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;
						temp_x = x;
						temp_y = y;
					} while (y + len_word > 14 || x - len_word < 0);
				}
				temp_y++;
				temp_y--;
			}
			diag_down_right_to_left(board, word, x, y);
			break;

		case 7:
			/* Place the word upwards diagonal, from left to right */
			if (y + len_word > 14 || x + len_word > 14)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (y + len_word > 14 || x + len_word > 14);
			}

			for (int i = 0; i < len_word; i++)
			{
				if (board[temp_y][temp_x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;
						temp_x = x;
						temp_y = y;
					} while (y + len_word > 14 || x + len_word > 14);
				}
				temp_x++;
				temp_y--;
			}
			diag_up_left_to_right(board, word, x, y);
			break;

		case 8:
			/* Place the word upwards diagonal, from right to left */
			if (y - len_word < 0 || x - len_word < 0)
			{
				do
				{
					x = rand() % 15;
					y = rand() % 15;
					temp_x = x;
					temp_y = y;
				} while (y - len_word < 0 || x - len_word < 0);
			}

			for (int i = 0; i < len_word; i++)
			{
				if (board[temp_y][temp_x] != '\0')
				{
					do
					{
						x = rand() % 15;
						y = rand() % 15;
						temp_x = x;
						temp_y = y;
					} while (y - len_word < 0 || x - len_word < 0);
				}
				temp_x--;
				temp_y--;
			}
			diag_up_right_to_left(board, word, x, y);
			break;

		default:
			break;
		}
	}

	print_board(board);
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
		fseek(fp, 0, SEEK_SET);					 /* Move pointer to the start */
		line_rand_word = rand() % num_lines + 1; /* Pick a random line to be read */

		for (int l = 0; l < line_rand_word; l++)
		{
			fgets(rand_word, sizeof(rand_word), fp); /* Update the word that is read until target line is reached */
		}
		fscanf(fp, "%s", rand_word);
		strcpy(words[w], rand_word); /* Put the random word in the array */
		for (int i = 0; i < w; i++)
		{
			while (strcmp(words[i], words[w]) == 0)
			{
				pick_words(&words[w], num_lines, fp);
			}
		}
	}
	fclose(fp);
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