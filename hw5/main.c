/*
 * This program prompts user to select a shape and a calculator type
 * from the given menu and does the calculations. It doesnt accept
 * negative or non-numeric character inputs and checks the validity
 * of the given inputs.
 * Homework #5 submission by Çağla Nur Yurdasal
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14

int select_shape();
int select_calc();
int calculate(int (*f1)(), int (*f2)());
int calc_triangle(int calculator);
int calc_quadrilateral(int calculator);
int calc_circle(int calculator);
int calc_pyramid(int calculator);
int calc_cylinder(int calculator);

enum shapes
{
	triangle = 1,
	quadrilateral = 2,
	circle = 3,
	pyramid = 4,
	cylinder = 5
};
enum calculators
{
	area = 1,
	perimeter = 2,
	volume = 3
};
int main()
{
	int check = 1;
	printf("Welcome to the geometric calculator!\n\n");
	do
	{
		/*based on return value, it will keep prompting the user or exit the program */
		check = calculate(select_shape, select_calc);
	} while (check);
	return 0;
}

int select_shape()
{
	enum shapes shape;
	int shape_selection;
	printf("Select shape to calculate: \n-----------------------\n");
	printf("1.Triangle\n2.Quadrilateral\n3.Circle\n");
	printf("4.Pyramid\n5.Cylinder\n0.Exit\n-----------------------\n");

	while (!scanf("%d", &shape_selection)) // it keeps prompting until a numeric value is entered
	{
		/* if scanf doesnt return any integer, buffer will be cleared to
		   get rid of the unused value collected by scanf */
		printf("Error!Invalid entry.\n");
		printf("Select shape to calculate: \n-----------------------\n");
		printf("1.Triangle\n2.Quadrilateral\n3.Circle\n");
		printf("4.Pyramid\n5.Cylinder\n0.Exit\n-----------------------\n");
		while ((getchar()) != '\n') // clearing the buffer
			;
	}
	/* Deciding which shape the calculations will be made for*/
	switch (shape_selection) // based on input, value from enum will be selected
	{
	case 0:
		return 0;
	case 1:
		shape = triangle;
		break;
	case 2:
		shape = quadrilateral;
		break;
	case 3:
		shape = circle;
		break;
	case 4:
		shape = pyramid;
		break;
	case 5:
		shape = cylinder;
		break;
	default:
		shape = -1; // if an invalid character is entered
		break;
	}
	return shape;
}
int select_calc()
{
	enum calculators calculator;
	int calc_selection;
	printf("Select calculator:\n-----------------------\n");
	printf("1.Area\n2.Perimeter\n3.Volume\n0.Exit\n");
	while (!scanf("%d", &calc_selection)) // keeps prompting if an invalid character is entered
	{
		printf("Error!Invalid entry.\n");
		printf("Select calculator:\n-----------------------\n");
		printf("1.Area\n2.Perimeter\n3.Volume\n0.Exit\n");
		while ((getchar()) != '\n') // clearing the buffer if an invalid character is entered
			;
	}
	/* Deciding using which calculator type the calculations will be made */
	switch (calc_selection) // based on input, value from enum will be selected
	{
	case 0:
		return 0;
	case 1:
		calculator = area;
		break;
	case 2:
		calculator = perimeter;
		break;
	case 3:
		calculator = volume;
		break;
	default:
		calculator = -1;
		break;
	}
	return calculator;
}
int calculate(int (*f1)(), int (*f2)())
{
	/* This function takes two other functions as parameters.
	   Based on the returned values from those functions,
	   program decides whether to exit or prompt the user again. */
	int check;

	int shape = (*f1)();
	if (shape == 0) // if user selects 0, program is terminated.
	{
		return 0;
	}
	else if (shape == -1)
	{
		return -1;
	}

	int calculator = (*f2)();
	if (calculator == 0) // if user selects 0, program is terminated.
	{
		return 0;
	}
	else if (calculator == -1)
	{
		return -1;
	}

	else if (calculator == 3) // checking if volume can be measured for the selected shape
	{
		if (shape == 1)
		{
			printf("ERROR! Cannot calculate volume of triangle.\n");
			return 1; // returns to shape selection
		}
		else if (shape == 2)
		{
			printf("ERROR! Cannot calculate volume of quadrilateral.\n");
			return 1;
		}
		else if (shape == 3)
		{
			printf("ERROR! Cannot calculate volume of circle.\n");
			return 1;
		}
	}
	/* Deciding for which shape the calculations will be made for by the program */
	switch (shape)
	{
	case 1:
		check = calc_triangle(calculator);
		break;
	case 2:
		check = calc_quadrilateral(calculator);
		break;
	case 3:
		check = calc_circle(calculator);
		break;
	case 4:
		check = calc_pyramid(calculator);
		break;
	case 5:
		check = calc_cylinder(calculator);
		break;
	default:
		return -1;
	}

	return check;
}
int calc_cylinder(calculator)
{
	/* Calculations for the cylinder */
	float area, perimeter, volume, h, r, base_area, lateral_area;
	int check = 0;

	while (check == 0) // prompting until user enters valid values
	{
		if (calculator == 2) // if perimeter is wanted, only radius will be asked
		{
			while (check == 0)
			{
				printf("Please enter the radius of the cylinder:\n");
				while (!scanf("%f", &r))
				{
					printf("Error!Invalid entry.\nPlease enter the radius again:\n");
					while ((getchar()) != '\n') // clearing the buffer if non-numeric character is entered
						;
				}
				if (r <= 0) // checking if user entered negative value for the radius
				{
					printf("ERROR! Please enter a valid cylinder.\n");
				}
				else
				{
					check = 1;
				}
			}
		}
		else // if area or volume is wanted, both radius and height will be asked
		{
			while (check == 0)
			{
				printf("Please enter the radius and height of the cylinder:\n");
				while (!scanf("%f", &r))
				{
					printf("Error!Invalid entry.\nPlease enter radius again:\n");
					while ((getchar()) != '\n') // clearing the buffer
						;
				}
				while (!scanf("%f", &h))
				{
					printf("Error!Invalid entry.\nPlease enter the height again:\n");
					while ((getchar()) != '\n') // clearing the buffer
						;
				}
				if (r <= 0 || h <= 0) // checking if negative values are entered
				{
					printf("ERROR! Please enter a valid cylinder.\n");
				}
				else
				{
					check = 1;
				}
			}
		}
	}
	switch (calculator)
	{
	case 0: // program terminates if user enters 0
		return 0;
	case 1:
		/* Calculating the area of the cylinder */
		base_area = PI * (r * r);
		lateral_area = (2.0 * PI * r) * h;
		area = 2.0 * base_area + lateral_area;
		printf("Base surface area of the cylinder: %.2f\n\n", base_area);
		printf("Lateral surface area of the cylinder: %.2f\n\n", lateral_area);
		printf("Surface area of the cylinder: %.2f\n\n", area);
		return 1; // 1 for succesful operation
	case 2:
		/* Calculating the perimeter of the cylinder */
		perimeter = (4.0 * PI * r) + (2 * h);
		printf("Perimeter of the cylinder: %.2f\n\n", perimeter);
		return 1;
	case 3:
		/* Calculating the volume of the cylinder */
		volume = PI * (r * r) * h;
		printf("Volume of cylinder: %.2f\n\n", volume);
		return 1;
	default:
		return -1;
	}
}
int calc_pyramid(calculator)
{
	float area, perimeter, volume, h, a, l, base_area, lateral_area;
	int check = 0;
	if (calculator == 3)
	{
		while (check == 0)
		{
			printf("Please enter the base side and height of the pyramid:\n");
			while (!scanf("%f", &a))
			{
				printf("Error!Invalid entry.\nPlease enter the base side again:\n");
				while ((getchar()) != '\n') // clearing the buffer
					;
			}
			while (!scanf("%f", &h))
			{
				printf("Error!Invalid entry.\nPlease enter the height again:\n");
				while ((getchar()) != '\n')
					;
			}
			if (a <= 0 || h <= 0) // checking if user entered negative values
			{
				printf("ERROR! Please enter a valid pyramid.\n");
			}
			else
			{
				check = 1;
			}
		}
	}
	else
	{
		while (check == 0)
		{
			printf("Please enter the base side and slant height of a Pyramid:\n");
			while (!scanf("%f", &a))
			{
				printf("Error!Invalid entry.\nPlease enter the base side again:\n");
				while ((getchar()) != '\n') // clearing the buffer
					;
			}
			while (!scanf("%f", &l))
			{
				printf("Error!Invalid entry.\nPlease enter the slant height again:\n");
				while ((getchar()) != '\n') // clearing the buffer
					;
			}
			if (a <= 0 || l <= 0) // checking if user entered negative values
			{
				printf("ERROR! Please enter a valid pyramid.\n");
			}
			else
			{
				check = 1;
			}
		}
	}
	switch (calculator)
	{
	case 0: // program terminates if 0 is entered
		return 0;
	case 1:
		/* Calculating the area of the pyramid */
		base_area = a * a;
		lateral_area = 2.0 * a * l;
		area = base_area + lateral_area;
		printf("Base surface area of the pyramid: %.2f\n\n", base_area);
		printf("Lateral surface area of the pyramid: %.2f\n\n", lateral_area);
		printf("Surface area of the pyramid: %.2f\n\n", area);
		return 1;
	case 2:
		/* Calculating the base perimeter of the pyramid */
		perimeter = (4 * a);
		printf("Base perimeter the pyramid: %.2f\n\n", perimeter);
		return 1;
	case 3:
		/* Calculating the volume of the pyramid */
		volume = ((a * a) * h) / 3.0;
		printf("Volume of a pyramid: %.2f\n\n", volume);
	default:
		return -1;
	}
}
int calc_circle(calculator)
{
	/* Calculations for the circle */
	float r, area, circumference;
	int check = 0;

	printf("Please enter the radius of Circle:\n");

	/* Keep prompting the user until a valid character is entered */
	while (check == 0)
	{
		while (!scanf("%f", &r))
		{
			printf("Error!Invalid entry.\nPlease enter the radius of the circle again:\n");
			while ((getchar()) != '\n') // clearing the buffer
				;
		}
		if (r <= 0)
		{
			printf("ERROR! Please enter a valid circle.\n");
		}
		else
		{
			check = 1;
		}
	}
	switch (calculator)
	{
	case 0: // if 0 is entered, program terminates
		return 0;
	case 1:
		/* Calculating the area of the circle */
		area = (float)PI * (float)(r * r);
		printf("Area of a circle: %.2f\n\n", area);
		return 1;
	case 2:
		/* Calculating the perimeter of the circle */
		circumference = 2.0 * PI * r;
		printf("Circumference of the circle: %.2f\n\n", circumference);
		return 1;
	default:
		return -1;
	}
	/* Program won't calculate the volume of the circle */
}
int calc_quadrilateral(int calculator)
{
	/* Calculations for the quadrilateral */
	float s, a, b, c, d, area, perimeter;
	int check = 0;
	printf("Please enter four sides of quadrilateral:\n");

	/* Keep prompting the user until a valid character is entered*/
	while (check == 0)
	{
		while (!scanf("%f", &a))
		{
			printf("Error!Invalid entry.\nPlease enter 1. side of quadrilateral again:\n");
			while ((getchar()) != '\n') // clearing the buffer if non-numeric value is entered
				;
		}
		while (!scanf("%f", &b))
		{
			printf("Error!Invalid entry.\nPlease enter 2. side of quadrilateral again:\n");
			while ((getchar()) != '\n') // clearing the buffer if non-numeric value is entered
				;
		}
		while (!scanf("%f", &c))
		{
			printf("Error!Invalid entry.\nPlease enter 3. side of quadrilateral again:\n");
			while ((getchar()) != '\n') // clearing the buffer if non-numeric value is entered
				;
		}
		while (!scanf("%f", &d))
		{
			printf("Error!Invalid entry.\nPlease enter 4. side of quadrilateral again:\n");
			while ((getchar()) != '\n') // clearing the buffer if non-numeric value is entered
				;
		}
		/* If edges are less than or equal to 0, prompting the user again */
		if (a <= 0 || b <= 0 || c <= 0 || d <= 0)
		{
			printf("ERROR! Please enter a valid quadrilateral.\n");
		}
		else
		{
			check = 1;
		}
	}
	switch (calculator)
	{
	case 0:
		return 0;
	case 1:
		/* Calculating the area of quadrilateral */
		s = (float)(a + b + c + d) / 2.0;
		area = sqrt(s * (s - a) * (s - b) * (s - c) * (s - d));
		printf("Area of quadrilateral: %.2f\n\n", area);
		return 1;

	case 2:
		/* Calculating the perimeter of quadrilateral */
		perimeter = (float)(a + b + c + d);
		printf("Perimeter of a quadrilateral: %.2f\n\n", perimeter);
		return 1;
	default:
		return -1;
	}
	/* Program won't calculate th volume of quadrilateral */
}
int calc_triangle(int calculator)
{
	/* Calculations for the triangle */
	int check = 0;
	float a, b, c, s, area, perimeter;
	printf("Please enter three sides of triangle:\n");

	while (check == 0)
	{
		while (!scanf("%f", &a))
		{
			printf("Error!Invalid entry.\nPlease enter first side of triangle again:\n");
			while ((getchar()) != '\n') // clearing the buffer
				;
		}
		while (!scanf("%f", &b))
		{
			printf("Error!Invalid entry.\nPlease enter second side of triangle again:\n");
			while ((getchar()) != '\n')
				; // clearing the buffer
		}
		while (!scanf("%f", &c))
		{
			printf("Error!Invalid entry.\nPlease enter third side of triangle again:\n");
			while ((getchar()) != '\n')
				;
		}
		/* If sum of two edges are equal or less than the third edge, it will prompt the user again */
		if (a + b <= c || a + c <= b || b + c <= a || a <= 0 || b <= 0 || c <= 0)
		{
			printf("ERROR! Please enter a valid triangle.\n");
		}
		else
		{
			check = 1;
		}
	}

	switch (calculator)
	{
	case 0:
		return 0;
	case 1:
		/* Calculating the area of triangle */
		s = (float)(a + b + c) / 2.0;
		area = sqrt(s * (s - a) * (s - b) * (s - c));
		printf("Area of triangle: %.2f\n\n", area);
		return 1;

	case 2:
		/* Calculating the perimeter of triangle */
		perimeter = (float)(a + b + c);
		printf("Perimeter of triangle: %.2f\n\n", perimeter);
		return 1;
	default:
		return -1;
	}
	// program won't calculate the volume of triangle
}
