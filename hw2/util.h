#ifndef _UTIL_H_
#define _UTIL_H_

#define CLOSE_ENOUGH 0.001

/* Example decision tree */
int dt0(int t, double p, double h, int s, int w);

char dt1a(double pl, double pw, double sl, double sw);
char dt1b(double pl, double pw, double sl, double sw);

double dt2a(double x1, double x2, double x3, unsigned int x4, unsigned int x5);
double dt2b(double x1, double x2, double x3, unsigned int x4, unsigned int x5);

int dt3a(double bmi, double drinks_per_week, unsigned int is_smoking, int race, int gen_group);
int dt3b(double bmi, double drinks_per_week, unsigned int is_smoking, int race, int gen_group);

#endif /* _UTIL_H_ */