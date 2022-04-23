#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/*
 * Assignment #2 Submission by Çağla Nur Yurdasal
 *
 * This program uses decision trees and regression to reach an
 * output using user-entered inputs and compares the results
 * that are obtained from different decision tree models.
 */

int main()
{
    /*** EXAMPLE DECISION TREE IMPLEMENTATION ***/
    int temperature, sunny_or_not, day_of_the_week;
    double pressure, humidity;

    printf("Temperature: ");
    scanf("%d", &temperature);
    printf("Is it sunny? Enter 1 for yes 0 for no: ");
    scanf("%d", &sunny_or_not);
    printf("Monday:1, Tuesday:2, Wednesday:3, Thursday:4, Friday:5, Saturday:6, Sunday:7\nDay of the week? Enter the number associated with the day as above: ");
    scanf("%d", &day_of_the_week);
    printf("Pressure: ");
    scanf("%lf", &pressure);
    printf("Humidity: ");
    scanf("%lf", &humidity);

    int ac = dt0(temperature, pressure, humidity, sunny_or_not, day_of_the_week);
    if (ac) // Determining whether turn on the AC or not
    {
        printf("AC is turned on.\n");
    }
    else
    {
        printf("AC is NOT turned on.\n");
    }
    /*** END OF THE EXAMPLE CASE ***/

    int selected_prob;                 // the problem which user will select
    char test1a, test1b;               // test results for dt1a and dt1b
    double pw, pl, sl, sw, x1, x2, x3; // real number values for dt1a, dt1b, dt2a, dt2b
    unsigned int x4, x5;               // binary values for dt2a and dt2b
    double test2a, test2b;             // test results for dt2a and dt2b
    double bmi, drinks_per_week;       // real numbers for dt3a and dt3b
    unsigned int is_smoking;           // binary value for dt3a and dt3b
    int race, gen_group;               // categorical variables for dt3a and dt3b
    int test3a, test3b;                // test results for dt3a and dt3b
    float risk_level;                  // calculated risk level for problem 3

    printf("Select a problem to solve, enter 1, 2 or 3: ");
    scanf("%d", &selected_prob);

    switch (selected_prob)
    {
    case 1:

        printf("Enter values of PL and PW, respectively:\n");
        scanf("%lf", &pl);
        scanf("%lf", &pw);

        printf("Enter values of SL and SW, respectively:\n");
        scanf("%lf", &sl);
        scanf("%lf", &sw);

        test1a = dt1a(pl, pw, sl, sw);
        test1b = dt1b(pl, pw, sl, sw);

        if (test1a == test1b)
        {
            printf("Test results are the same. Iris type: ");
        }
        else
        {
            // if test results are different, result of test2 will be printed first
            printf("Test results are different.\nIris types for <<dt1b>> and <<dt1a>> respectively:\ndt1b: ");
            if (test1b == 's')
            {
                printf("Setosa\n");
            }
            else if (test1b == 'g')
            {
                printf("Versicolor\n");
            }
            else
            {
                printf("Virginica\n");
            }
            printf("dt1a: ");
        }

        // test result 1 will be printed no matter results of dt1a and dt1b are the same or not
        if (test1a == 's')
        {
            printf("Setosa\n");
        }
        else if (test1a == 'g')
        {
            printf("Versicolor\n");
        }
        else
        {
            printf("Virginica\n");
        }
        break;

    case 2:

        printf("Enter real numbers for x1, x2 and x3, respectively:\n");
        scanf("%lf", &x1);
        scanf("%lf", &x2);
        scanf("%lf", &x3);

        printf("Enter binary values for x4 and x5, respectively:\n");
        scanf("%u", &x4);
        scanf("%u", &x5);

        test2a = dt2a(x1, x2, x3, x4, x5);
        test2b = dt2b(x1, x2, x3, x4, x5);
        double diff = test2a - test2b;
        if (diff < 0)
        {
            diff = -diff;
        }

        if (test2a == test2b)
        {
            printf("Test results are the same. Result: %lf\n", test2a);
        }
        else
        {

            if (diff <= CLOSE_ENOUGH) // if results are within the threshold, average will be printed
            {
                printf("Results are within threshold.\nResult: %lf\n", (test2a + test2b) / 2.0);
            }
            else
            {
                printf("Results are different and not within the threshold.\ndt2a: %lf\ndt2b: %lf\n", test2a, test2b);
            }
        }
        break;

    case 3:
        /*
         * In this problem, program gets 5 dimensional user input to calculate
         * the heart disease risk of the user based on body mass index(BMI),
         * alcohol consumation, smoking, race and age group. Result will be
         * an integer 1-5 and average value will be printed.
         */
        printf("\n***** Heart Disease Prediction *****\n************************************\n");
        printf("These tests give you an unofficial hint about your heart disease risk.\n1-2(low), 3(moderate), 4-5(high)\n\n");

        // People with BMI of 35.0 and higher are more likely to have a heart disease
        printf("#1 What is your body mass index(BMI)? (eg. 12.5, 33.6, 58.1...)\n");
        scanf("%lf", &bmi);

        // People who drink more than 2-3 days a week are more likely to have a heart disease
        printf("#2 How many days a week do you consume alcohol?\n");
        scanf("%lf", &drinks_per_week);

        // Smokers have higher risk of having a heart disease than non-smokers do
        printf("#3 Do you smoke? Enter 1 for yes, 0 for no: "); // binary variable
        scanf("%u", &is_smoking);

        // White people have the most death rate related to heart diseases whereas Indian Americans have the least
        printf("#4 What is your race?\nIndian American(1), Hispanic(2), Asian(3), Black(4), White(5): ");
        scanf("%d", &race);

        // Older people have higher risk of having a heart disease
        printf("#5 What is your generation group?\nGen Z(1), Millenials(2), Gen X(3), Boomer(4), Post-War/WW2(5): ");
        scanf("%d", &gen_group);

        test3a = dt3a(bmi, drinks_per_week, is_smoking, race, gen_group);
        test3b = dt3b(bmi, drinks_per_week, is_smoking, race, gen_group);

        risk_level = (float)(test3a + test3b) / 2;

        printf("****************************\nRISK LEVEL: ");
        if (risk_level > 3)
        {
            printf("HIGH\n");
        }
        else if (risk_level == 3)
        {
            printf("MODERATE\n");
        }
        else
        {
            printf("LOW\n");
        }

        if (test3a == test3b)
        {
            printf("Test results are the same.\n****************************\nResult: %.2f\n", risk_level);
        }
        else
        {
            printf("Test results are different.\n****************************\ndt3a: %d\ndt3b: %d\nAverage: %.2f\n", test3a, test3b, risk_level);
        }
        break;

    default:
        printf("You have entered an invalid character.\n");
    }

    return 0;
}
