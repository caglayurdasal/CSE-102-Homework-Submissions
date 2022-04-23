#include <stdio.h>
#include <math.h>
#include "util.h"

/* Example decision tree */
int dt0(int t, double p, double h, int s, int w)
{
    int r = 0;
    if (t > 35 && w != 3)
        r = 1;
    else if (t <= 35 && s == 0)
        r = 1;
    return r;
}

char dt1a(double pl, double pw, double sl, double sw)
{
    /* sl and sw values are not used in these calculations based on the
    given decision tree */
    char iris_species;
    if (pl < 2.45) // in all cases, if pl<2.45, it will be setosa
    {
        iris_species = 's'; // setosa
    }
    else
    {
        if (pw < 1.65 && pl < 4.95)
        {
            iris_species = 'g'; // versicolor
        }
        else
        {
            iris_species = 'v'; // virginica
        }
    }
    return iris_species;
}
char dt1b(double pl, double pw, double sl, double sw)
{
    /* sl and sw values are not used in these calculations based on the
    given decision tree */
    char iris_species;
    if (pl < 2.55) // in all cases, if pl<2.55, it will be setosa
    {
        iris_species = 's'; // setosa
    }
    else
    {
        if (pl < 4.85 && pw < 1.69)
        {
            iris_species = 'g'; // versicolor
        }
        else
        {
            iris_species = 'v'; // virginica
        }
    }
    return iris_species;
}

double dt2a(double x1, double x2, double x3, unsigned int x4, unsigned int x5)
{
    double result;
    if (x1 < 31.5 && x2 > -2.5)
    {
        result = 5.0;
    }
    else if (x1 < 31.5 && x2 <= 2.5)
    {
        if (x2 - 0.1 <= x1 && x1 <= x2 + 0.1)
        {
            result = 2.1;
        }
        else
        {
            result = -1.1;
        }
    }
    else
    {
        if (-1 <= x3 && x3 <= 2)
        {
            result = 1.4;
        }
        else
        {
            if (x4 && x5)
            {
                result = -2.23;
            }
            else
            {
                result = 11.0;
            }
        }
    }
    return result;
}

double dt2b(double x1, double x2, double x3, unsigned int x4, unsigned int x5)
{
    double result;
    if (x1 < 22 && x1 > 12 && x3 > (5.0 / 3.0))
    {
        result = -2.0;
    }
    else if (x1 < 22 && x1 > 12 && x3 <= (5.0 / 3.0))
    {
        if (x1 - 0.1 <= x3 && x1 + 0.1 >= x3)
        {
            result = 1.01;
        }
        else
        {
            result = -8;
        }
    }
    else
    {
        if (x4 && x5)
        {
            result = -1;
        }
        else
        {
            if (-1 <= x2 && x2 <= 2)
            {
                result = -1.0 / 7.0;
            }
            else
            {
                result = sqrt(2) / 3; // (square root of 2)/3
            }
        }
    }
    return result;
}

/* A decision tree of 13 decision nodes and 14 terminal nodes */
int dt3a(double bmi, double drinks_per_week, unsigned int is_smoking, int race, int gen_group)
{
    int risk; // the risk level to be calculated on a scale of 1 to 5

    if (gen_group >= 4)
    {
        if (is_smoking)
        {
            if (bmi >= 35.0)
            {
                risk = 5;
            }
            else
            {
                if (drinks_per_week >= 3)
                {
                    risk = 5;
                }
                else
                {
                    if (race > 2)
                    {
                        risk = 4;
                    }
                    else
                    {
                        risk = 3;
                    }
                }
            }
        }
        else
        {
            if (drinks_per_week >= 2)
            {
                if (bmi >= 35)
                {
                    risk = 5;
                }
                else
                {
                    if (race >= 3 || gen_group == 5)
                    {
                        risk = 5;
                    }
                    else
                    {
                        risk = 4;
                    }
                }
            }
            else
            {
                risk = 3;
            }
        }
    }
    else
    {
        if (drinks_per_week >= 3)
        {
            if (is_smoking)
            {
                if (gen_group >= 3)
                {
                    risk = 4;
                }
                else
                {
                    risk = 3;
                }
            }
            else
            {
                risk = 2;
            }
        }
        else
        {
            if (race >= 3)
            {
                if (is_smoking)
                {
                    risk = 3;
                }
                else
                {
                    risk = 2;
                }
            }
            else
            {
                risk = 1;
            }
        }
    }

    return risk;
}
/* A decision tree with 12 decision nodes and 12 terminal nodes */
int dt3b(double bmi, double drinks_per_week, unsigned int is_smoking, int race, int gen_group)
{
    int risk; // the risk level to be calculated on a scale of 1 to 5

    if (gen_group == 5) // 77+
    {
        if (is_smoking)
        {
            risk = 5;
        }
        else
        {
            if (drinks_per_week >= 2)
            {
                risk = 5;
            }
            else
            {
                if (bmi >= 35.0)
                {
                    risk = 4;
                }
                else
                {
                    risk = 3;
                }
            }
        }
    }
    else
    {
        if (bmi >= 35.0)
        {
            if (drinks_per_week >= 3)
            {
                risk = 3;
            }
            else
            {
                if (is_smoking)
                {
                    risk = 4;
                }
                else
                {
                    risk = 3;
                }
            }
        }
        else
        {
            if (gen_group < 3)
            {
                if (race > 2)
                {
                    risk = 2;
                }
                else
                {
                    if (is_smoking)
                    {
                        risk = 2;
                    }
                    else
                    {
                        risk = 1;
                    }
                }
            }
            else
            {
                if (is_smoking)
                {
                    if (race >= 3)
                    {
                        risk = 3;
                    }
                    else
                    {
                        risk = 2;
                    }
                }
                else
                {
                    risk = 1;
                }
            }
        }
    }

    return risk;
}
