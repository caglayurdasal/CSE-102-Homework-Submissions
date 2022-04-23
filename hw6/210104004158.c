/*
 * This program is a mini racing game. It decides which player moves first
 * and prints the game area and positions of the players.
 * Homework#6 submission by Çağla Nur Yurdasal
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 15
#define COLUMN 30

int dice(int player);
int startGame(int dice1, int dice2);
void printMap(int pose1X, int pose1Y, int pose2X, int pose2Y);
int moveXright(int s, int poseX);
int moveXleft(int s, int poseX);
int moveYdown(int s, int poseY);
int moveYup(int s, int poseY);
void cyan();
void purple();
void red();
void green();
void reset();

int main(void)
{
	int pose1x = 1, pose1y = 1, pose2x = 3, pose2y = 3;
	printMap(pose1x, pose1y, pose2x, pose2y);
	printf("To start the game, players should dice and decide who's going to move first.\n");
	int player1, player2, second, first, firstToMove, secondToMove, check = 0, isFinished = 0;

	do
	{
		player1 = dice(1);
		player2 = dice(2);
		check = startGame(player1, player2); // deciding who will move first
	} while (check == 0);					 // keeps rolling dice until one is greater than the other
	// deciding in which turn players will move
	if (check == 1)
	{
		first = 1;
		second = 2;
	}
	else
	{
		first = 2;
		second = 1;
	}

	do
	{
		if (first == 1) // if player1 moves first, it will dice first
		{
			player1 = dice(first);
			player2 = dice(second);

			/* Moving Player 1 */
			if (pose1x < 28 && pose1y == 1) // if there is no obstacles on the road, move forward
			{
				pose1x = moveXright(player1, pose1x); // if player1 is at y=1, move right to move forward
				if (pose1x == 14)
				{
					printf("Penalty for Player 1.\n");
					pose1x -= 2;
				}
				if (pose1x > 28) // if player1 encounters an obstacle,i.e an edge, move down
				{
					pose1y = moveYdown(pose1x - 28, 1); // if player 1 is at y=1, move down to move forward
					pose1x = 28;
				}
			}
			else if (pose1x == 28 && pose1y < 13)
			{
				pose1y = moveYdown(player1, pose1y); // if player1 is at x=28, move down to go forward
				if (pose1y == 7)
				{
					printf("Penalty for Player 1.\n");
					pose1y -= 2;
				}
				if (pose1y > 13)
				{
					pose1x = moveXleft(pose1y - 13, 28); // if player1 encounters an obstacle,i.e an edge, move left
					pose1y = 13;
				}
			}
			else if (pose1y == 13 && pose1x > 1)
			{
				pose1x = moveXleft(player1, pose1x); // if y=13, move left to go forward
				if (pose1x == 14)
				{
					printf("Penalty for Player 1.\n");
					pose1x += 2;
				}
				if (pose1x < 1)
				{
					pose1y = moveYup(1 - pose1x, 13); // if player1 encounters an obstacle,i.e an edge, go up
					pose1x = 1;
				}
			}
			else if (pose1x == 1 && pose1y > 2)
			{
				pose1y = moveYup(player1, pose1y);
				if (pose1y <= 2) // if player1 is on or ahead of the finish line, stop moving on y=1
				{
					pose1y = 1;
					printf("\n\n*** PLAYER 1 HAS WON! ***\n\n");
					printMap(pose1x, pose1y, pose2x, pose2y);
					return 0;
				}
			}
			/* Moving Player 2 */
			if (pose2x < 26 && pose2y == 3) // if there is no obstacles on the road, go forward
			{
				pose2x = moveXright(player2, pose2x); // move right to go forward if player2 is at y=3
				if (pose2x == 10 || pose2x == 18)
				{
					printf("Penalty for Player 2.\n");
					pose2x -= 2;
				}
				if (pose2x > 26) // if player2 encounters an obstacle,i.e an edge, move down
				{
					pose2y = moveYdown((pose2x - 26), 3);
					pose2x = 26;
				}
			}
			else if (pose2x == 26 && pose2y < 11)
			{
				pose2y = moveYdown(player2, pose2y); // if player2 is at x=26, move down to go forward
				if (pose2y == 5 || pose2y == 10)
				{
					printf("Penalty for Player 2.\n");
					pose2y -= 2;
				}
				if (pose2y > 11)
				{
					pose2x = moveXleft((pose2y - 11), 26); // if player2 encounters an obstacle, i.e an edge, go left
					pose2y = 11;
				}
			}
			else if (pose2y == 11 && pose2x > 3)
			{
				pose2x = moveXleft(player2, pose2x); // if player2 is at y=11, move left to go forward
				if (pose2x == 10 || pose2x == 18)
				{
					printf("Penalty for Player 2.\n");
					pose2x += 2;
				}
				if (pose2x < 3)
				{
					pose2y = moveYup((3 - pose2x), 11); // if player2 encounters an obstacle, i.e an edge, go up
					pose2x = 3;
				}
			}
			else if (pose2x == 3 && pose2y > 4)
			{
				pose2y = moveYup(player2, pose2y);
				if (pose2y <= 4) // if player2 is at or ahead of the finish line, stop moving on y=3
				{
					pose2y = 3;
					printf("\n\n*** PLAYER 2 HAS WON! ***\n\n");
					printMap(pose1x, pose1y, pose2x, pose2y);
					return 0;
				}
			}
			printMap(pose1x, pose1y, pose2x, pose2y);
		}
		else
		{
			player2 = dice(first);
			player1 = dice(second);
			/* Moving Player 2 */
			if (pose2x < 26 && pose2y == 3) // if there is no obstacles on the road, go forward
			{
				pose2x = moveXright(player2, pose2x); // move right to go forward if player2 is at y=3
				if (pose2x == 10 || pose2x == 18)
				{
					printf("Penalty for Player 2.\n");
					pose2x -= 2;
				}
				if (pose2x > 26) // if player2 encounters an obstacle,i.e an edge, move down
				{
					pose2y = moveYdown((pose2x - 26), 3);
					pose2x = 26;
				}
			}
			else if (pose2x == 26 && pose2y < 11)
			{
				pose2y = moveYdown(player2, pose2y); // if player2 is at x=26, move down to go forward
				if (pose2y == 5 || pose2y == 10)
				{
					printf("Penalty for Player 2.\n");
					pose2y -= 2;
				}
				if (pose2y > 11)
				{
					pose2x = moveXleft((pose2y - 11), 26); // if player2 encounters an obstacle, i.e an edge, go left
					pose2y = 11;
				}
			}
			else if (pose2y == 11 && pose2x > 3)
			{
				pose2x = moveXleft(player2, pose2x); // if player2 is at y=11, move left to go forward
				if (pose2x == 10 || pose2x == 18)
				{
					printf("Penalty for Player 2.\n");
					pose2x += 2;
				}
				if (pose2x < 3)
				{
					pose2y = moveYup((3 - pose2x), 11); // if player2 encounters an obstacle, i.e an edge, go up
					pose2x = 3;
				}
			}
			else if (pose2x == 3 && pose2y > 4)
			{
				pose2y = moveYup(player2, pose2y);
				if (pose2y <= 4) // if player2 is at or ahead of the finish line, stop moving on y=3
				{
					pose2y = 3;
					printf("\n\n*** PLAYER 2 HAS WON! ***\n\n");
					printMap(pose1x, pose1y, pose2x, pose2y);
					return 0;
				}
			}
			/* Moving Player 1 */
			if (pose1x < 28 && pose1y == 1) // if there is no obstacles on the road, move forward
			{
				pose1x = moveXright(player1, pose1x); // if player1 is at y=1, move right to move forward
				if (pose1x == 14)
				{
					printf("Penalty for Player 1.\n");
					pose1x -= 2;
				}
				if (pose1x > 28) // if player1 encounters an obstacle,i.e an edge, move down
				{
					pose1y = moveYdown(pose1x - 28, 1); // if player 1 is at y=1, move down to move forward
					pose1x = 28;
				}
			}
			else if (pose1x == 28 && pose1y < 13)
			{
				pose1y = moveYdown(player1, pose1y); // if player1 is at x=28, move down to go forward
				if (pose1y == 7)
				{
					printf("Penalty for Player 1.\n");
					pose1y -= 2;
				}
				if (pose1y > 13)
				{
					pose1x = moveXleft(pose1y - 13, 28); // if player1 encounters an obstacle,i.e an edge, move left
					pose1y = 13;
				}
			}
			else if (pose1y == 13 && pose1x > 1)
			{
				pose1x = moveXleft(player1, pose1x); // if y=13, move left to go forward
				if (pose1x == 14)
				{
					printf("Penalty for Player 1.\n");
					pose1x += 2;
				}
				if (pose1x < 1)
				{
					pose1y = moveYup(1 - pose1x, 13); // if player1 encounters an obstacle,i.e an edge, go up
					pose1x = 1;
				}
			}
			else if (pose1x == 1 && pose1y > 2)
			{
				pose1y = moveYup(player1, pose1y);
				if (pose1y <= 2) // if player1 is on or ahead of the finish line, stop moving on y=1
				{
					pose1y = 1;
					printf("\n\n*** PLAYER 1 HAS WON! ***\n\n");
					printMap(pose1x, pose1y, pose2x, pose2y);
					return 0;
				}
			}

			printMap(pose1x, pose1y, pose2x, pose2y);
		}
	} while (isFinished == 0);

	return 0;
}

int dice(int player)
{
	/* This function rolls the dice and returns the result */
	int roll;
	char input;

	printf("\nPlayer %d, press enter to dice...", player);
	input = fgetc(stdin); // getting the character that user pressed on keyboard
	if (input == 0x0A)	  // checking if user pressed enter
	{
		srand(time(NULL));

		roll = (rand() % 6) + 1; // generating random number between 1 and 6
		printf("DICE: %d\n", roll);
	}
	return roll;
}
int startGame(int dice1, int dice2)
{
	int check = 0;
	if (dice1 > dice2)
	{
		printf("*** PLAYER 1 WILL START THE GAME ***\n");
		return 1;
	}
	else if (dice2 > dice1)
	{
		printf("*** PLAYER 2 WILL START THE GAME ***\n");
		return 2;
	}
	else
	{
		printf("IT'S A TIE. PLEASE DICE AGAIN.\n");
		return 0;
	}
}
void printMap(int pose1X, int pose1Y, int pose2X, int pose2Y)
{
	char map[ROW][COLUMN];

	/* Iterate over each row */
	for (int r = 0; r < 15; r++) // rows
	{
		/* Iterate over each column */
		for (int c = 0; c < 30; c++) // columns
		{

			/*** DRAWING OUTER SQUARE ***/
			// Drawing top and bottom edges
			if (0 <= c && c <= 29) // Left and right borders
			{
				if (r == 0 || r == 14) // Top and bottom borders
				{
					if (map[r][c] != '|') // Avoiding conflict with an existing character
					{
						map[r][c] = '-';
					}
				}
				else
				{
					if (map[r][c] != '|')
					{
						map[r][c] = ' ';
					}
				}
			}
			// Drawing left and right edges
			if (1 <= r && r <= 13)
			{
				if (c == 0 || c == 29)
				{
					if (map[r][c] != '-')
					{
						map[r][c] = '|';
					}
				}
				else
				{
					if (map[r][c] != '-') // Avoiding conflict with an existing character
					{
						map[r][c] = ' ';
					}
				}
			}

			/*** DRAWING MIDDLE SQUARE ***/
			// Drawing top and bottom edges
			if (2 <= c && c <= 27) // Left and right borders
			{
				if (map[r][c] != '-' || map[r][c] != '|')
				{
					if (r == 2 || r == 12) // Top and bottom borders
					{
						map[r][c] = '-';
					}
				}
				else
				{
					if (map[r][c] != '-' || map[r][c] != '|')
					{
						map[r][c] = ' ';
					}
				}
			}
			// Drawing left and right edges
			if (3 <= r && r <= 11) // Top and bottom borders
			{
				if (map[r][c] != '-' || map[r][c] != '|') // Avoiding conflict
				{
					if (c == 2 || c == 27) // Left and right borders
					{
						map[r][c] = '|';
					}
				}
				else
				{
					if (map[r][c] != '-' || map[r][c] != '|') // Avoiding conflict
					{
						map[r][c] = ' ';
					}
				}
			}

			/*** DRAWING INNER SQUARE ***/

			// Drawing top and bottom edges
			if (4 <= c && c <= 25) // Left and right borders
			{
				if (map[r][c] != '-' || map[r][c] != '|')
				{
					if (r == 4 || r == 10) // Top and bottom borders
					{
						map[r][c] = '-';
					}
				}
				else
				{
					if (map[r][c] != '-' || map[r][c] != '|')
					{
						map[r][c] = ' ';
					}
				}
			}
			// Drawing left and right edges
			if (5 <= r && r <= 9) // Top and bottom borders
			{
				if (map[r][c] != '-' || map[r][c] != '|') // Avoiding conflict
				{
					if (c == 4 || c == 25) // Left and right borders
					{
						map[r][c] = '|';
					}
				}
				else
				{
					if (map[r][c] != '-' || map[r][c] != '|') // Avoiding conflict
					{
						map[r][c] = ' ';
					}
				}
			}
		}
	}

	/* Penalty points for Player 1 */
	map[1][14] = 'X';
	map[7][28] = 'X';
	map[13][14] = 'X';

	/* Penalty points for Player 2 */
	map[3][10] = 'X';
	map[3][18] = 'X';
	map[5][26] = 'X';
	map[10][26] = 'X';
	map[11][10] = 'X';
	map[11][18] = 'X';

	/* Marking the finish lines */
	map[2][1] = '_'; // Player 1 finish line
	map[4][3] = '_'; // Player 2 finish line

	/* Marking the positions of Player 1 and Player 2 */
	map[pose1Y][pose1X] = '1';
	map[pose2Y][pose2X] = '2';

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (map[i][j] == '_')
			{
				green();
			}
			else if (map[i][j] == '1')
			{
				cyan();
			}
			else if (map[i][j] == '2')
			{
				purple();
			}
			else if (map[i][j] == 'X')
			{
				red();
			}
			printf("%c", map[i][j]);
			reset();
		}
		printf("\n");
	}
}
int moveXright(int s, int poseX)
{
	poseX += s;
	return poseX;
}
int moveXleft(int s, int poseX)
{
	poseX -= s;
	return poseX;
}
int moveYdown(int s, int poseY)
{
	poseY += s;
	return poseY;
}
int moveYup(int s, int poseY)
{
	poseY -= s;
	return poseY;
}
void cyan()
{
	printf("\033[1;36m");
}
void purple()
{
	printf("\033[1;35m");
}
void green()
{
	printf("\033[0;32m");
}
void red()
{
	printf("\033[0;31m");
}
void reset()
{
	printf("\033[0m");
}
