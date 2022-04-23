/*
 *	This program lets user to choose an operation from
 *	the menu and does necessary calculations and drawings.
 *  In op1, it gets inputs for the equation and saves them
 *  into a .txt file, in op2 it reads saved values from the
 *  .txt file and draws its' graph and in op3, it draws the
 *  same graph without numbers and colors in an another .txt
 *  file. By using op4, user exits the program.
 *
 *  Homework #4 submission by Çağla Nur Yurdasal
 */
#include <stdio.h>

void write_to_file(int a, int b, int c);
int isAxisX(int y_val);
int isAxisY(int x_val);
int isPoint(int x_val, int y_val, int a, int b, int c);
int isNumberX(int x_val, int y_val);
int isNumberY(int x_val, int y_val);
int countDigits(int val);
void print_backspace(int val);
void cyan()
{
    printf("\033[1;36m");
}
void purple()
{
    printf("\033[1;35m");
}
void reset()
{
    printf("\033[0m");
}
int main(void)
{
    // part0
    int loop_check = 1;
    int selected_operation;
    int a, b, c;
    int x = -50;
    int y = 15;
    int point;
    FILE *fp;

    while (loop_check == 1)
    {
        printf("\nSelect an operation:\n");
        printf("1 -> Enter coefficients.\n");
        printf("2 -> Draw the graph.\n");
        printf("3 -> Print the graph into a .txt file.\n");
        printf("4 -> Exit.\n");
        scanf("%d", &selected_operation);

        switch (selected_operation)
        {
        // part1
        case 1: // getting a, b, c values for the equation and writing to .txt file
            printf("Please enter coefficients for the following equation: x = a * (y*y) + b*y + c\n");
            printf("a: ");
            scanf("%d", &a);
            printf("b: ");
            scanf("%d", &b);
            printf("c: ");
            scanf("%d", &c);
            write_to_file(a, b, c);

            printf("\ncoefficients.txt file has been created.\n");
            break;
        // part 2
        case 2: // drawing the graph based on the saved values in the txt file

            fp = fopen("coefficients.txt", "r");
            if (fp == NULL)
            {
                printf("Error while opening the file: .txt file does not exist.");
            }
            else
            {
                fscanf(fp, "%d\n", &a);
                fscanf(fp, "%d\n", &b);
                fscanf(fp, "%d\n", &c);
                fclose(fp);
                printf("Coefficients has been read from coefficients.txt file.\n");
                printf("Printing the graph of x = %d*(y*y) + %d*y + %d\n", a, b, c);

                for (int i = 0; i < 54; i++)
                {
                    printf(" ");
                }
                printf("^\n"); // starting from the upper arrow

                for (y = 15; y >= -15; y--) // starting from P(-55,15)
                {
                    printf("    "); // to not start from the edge of the terminal, it sets forward the graph
                    for (x = -50; x <= 50; x++)
                    {

                        if (x == -50 && y == 0)
                        {
                            printf("\b<"); // left arrow
                        }
                        if (isNumberX(x, y) == 1)
                        {
                            print_backspace(countDigits(x)); // prints backspace number of digit times so that it won't overwrite the graph
                            cyan();
                            printf("%d", x);
                            reset();
                        }
                        if (isNumberY(x, y) == 1)
                        {
                            print_backspace(countDigits(y));
                            cyan();
                            printf("%d", y);
                            reset();
                        }

                        char pin = ' ';      // to determine which character to print
                        if (isAxisX(y) == 1) // if  equation doesn't intercept (x,0), it will print x-axis line
                        {
                            pin = '-';
                        }
                        if (isAxisY(x) == 1) // if  equation doesn't intercept (0.y), it will print y-axis line
                        {
                            pin = '|';
                        }
                        if (isPoint(x, y, a, b, c) == 1) // if  roots of the equation intercepts a point on the plane, it will print #
                        {

                            pin = '#';
                        }

                        /* printing the value of pin: - , | , # or just a space as it's pin's initial value
                         * and indicates the blank points on the plane */
                        if (pin == '#')
                        {
                            purple();
                            printf("%c", pin);
                        }
                        else
                        {
                            printf("%c", pin);
                        }
                        reset();

                        if (x == 50 && y == 0)
                        {
                            printf("\b>"); // right arrow
                        }
                    }
                    printf("\n");
                }
            }
            break;
        // part3
        case 3:
            fp = fopen("coefficients.txt", "r");
            if (fp == NULL)
            {
                printf("Error while opening the file: .txt file does not exist.");
            }
            else
            {
                // reading a,b,c values for the equation from the .txt file
                fscanf(fp, "%d\n", &a);
                fscanf(fp, "%d\n", &b);
                fscanf(fp, "%d\n", &c);
                fclose(fp);
                printf("Coefficients has been read from coefficients.txt file.\n");
                printf("Printing the graph of x = %d*(y*y) + %d*y + %d\n", a, b, c);

                fp = fopen("graph.txt", "w");
                for (int i = 0; i <= 50; i++)
                {
                    fprintf(fp, "%s", " ");
                }
                fprintf(fp, "%c\n", '^');

                for (y = 15; y >= -15; y--) // starting from P(-55,15)
                {
                    fprintf(fp, "%s", " ");
                    for (x = -50; x <= 50; x++)
                    {
                        char pin = ' '; // to determine which character to print

                        if (isAxisX(y) == 1) // if  equation doesn't intercept (x,0), it will print x-axis line
                        {
                            pin = '-';
                        }
                        if (isAxisY(x) == 1) // if  equation doesn't intercept (0.y), it will print y-axis line
                        {
                            pin = '|';
                        }
                        if (isPoint(x, y, a, b, c) == 1) // if  roots of the equation intercepts a point on the plane, it will print #
                        {
                            pin = '#';
                        }
                        fprintf(fp, "%c", pin); // printing the value of pin to draw the values of the graph
                        if (x == 50 && y == 0)
                        {
                            fprintf(fp, "%c", '>'); // right arrow
                        }
                    }
                    fprintf(fp, "%c", '\n');
                }
            }
            fclose(fp);
            break;
        // part 4
        case 4:
            printf("Goodbye!\n");
            loop_check = -1;
            break;
        // if user enters an invalid value, program warns it
        default:
            printf("Invalid entry. Please enter only 1-4 from the menu.\n"); // user must select from 1 to 4, inclusively.
            break;
        }
    }
}

int isAxisX(int y_val)
{
    /* This function determines whether the cursor is on a point
     * where x-axis line should be at or not */
    if (y_val == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isAxisY(int x_val)
{
    /* This function determines whether the cursor is on a point
     * where y-axis line should be at or not */
    if (x_val == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isPoint(int x_val, int y_val, int a, int b, int c)
{
    /* This function determines whether the cursor is on a point
     * where one of the roots of the equation should be at or not */
    if (x_val == a * (y_val * y_val) + b * y_val + c)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void print_backspace(int val)
{
    /* This function determines how many backspaces should be printed
     * and prints them by checking the number of digits of the number */
    for (int i = 0; i < val; i++)
    {
        printf("\b");
    }
}
int countDigits(int val)
{
    /* This function returns the number of digits, if the number is
     * less than 0, it adds 1 to number of digits as the minus sign
     * in front of the number will behave like a number while drawing
     * the graph. */
    int val_abs = val;
    if (val_abs < 0)
    {
        val_abs *= -1;
    }

    int digits = 0;
    int temp = val_abs;
    while (temp > 0)
    {
        temp /= 10;
        digits++;
    }
    if (val <= 0)
    {
        digits++;
    }

    return digits;
}
int isNumberX(int x_val, int y_val)
{
    /* This function determines whether the cursor is on a point
     * where x is one of the multiples of 10 or not */
    if (y_val == -1)
    {
        if (x_val % 10 == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
int isNumberY(int x_val, int y_val)
{
    /* This function determines whether the cursor is on a point
     * where y is one of the multiples of 5 or not */
    if (x_val == -1)
    {
        if (y_val % 5 == 0 && y_val != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
void write_to_file(int a, int b, int c)
{
    FILE *fp;
    fp = fopen("coefficients.txt", "w");

    fprintf(fp, "%d\n%d\n%d\n", a, b, c);
    fclose(fp);
}
