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
    FILE *fp;
    fp = fopen("customers.txt", "a+");

    int sel;
    printf("=====================================\n");
    printf("Welcome to the Bank Management System\n");
    printf("=====================================\n");
    do
    {
        printf("\t 1. List all customers\n");
        printf("\t 2. Add new customer\n");
        printf("\t 3. New Loan Application\n");
        printf("\t 4. Report menu\n");
        printf("\t 5. Exit System\n");
        scanf("%d", &sel);
        switch (sel)
        {
        case 1:
            break;
        case 2:
            /* Add new customer information from the user */
            printf("Customer Name: ");
            scanf("%s", );
            printf("Customer Address: ");
            printf("Customer Phone: ");
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            printf("Invalid entry!\n");
            break;
        }
    } while (sel != 5);
    fclose(fp);
    return 0;
}