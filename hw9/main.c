#include <stdio.h>
int listCustomers();
int addCustomer();
int newLoan();
int calculateLoan(float amount, int period, float interestRate);
int getReport();
union Person
{
    char name[50];
    char address[50];
    int phone;
};
union Loan
{
    float amount;
    float interestRate;
    int period;
};
struct BankAccount
{
    union Person Customer;
    union Loan Loans[3];
};
int main()
{
    printf("Hello, World!\n");
    return 0;
}