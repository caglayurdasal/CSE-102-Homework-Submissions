#include <stdio.h>

int listCustomers();

int addCustomer();

int newLoan();

float calculateLoan(float amount, int period, float interestRate);

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
    union Person Customer[3];
    union Loan Loans[3];
};

int main()
{
    FILE *fp;
    struct BankAccount account;
    fp = fopen("customers.txt", "a+");

    int sel, num_lines = 0;
    float amount = 10000;
    int period = 3;
    float interest_rate = 0.05;
    float loan = calculateLoan(amount, period, interest_rate);
    printf("Calculated loan: %f\n", loan);
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
            rewind(fp);
            while (!feof(fp))
            {
                fscanf(fp, "%s ", account.Customer->name);
                printf("Customer ID = %d\n", num_lines + 1);
                printf("Customer Name = %s\n", account.Customer->name);
                // fscanf(fp, "%d %[^\n]s", &account.Customer->phone, account.Customer->address);
                fscanf(fp, "%d ", &account.Customer->phone);
                printf("Customer Phone = %d\n", account.Customer->phone);
                fscanf(fp, "%[^\n]s", account.Customer->address);
                printf("Customer Address = %s\n", account.Customer->address);
                num_lines++;
            }
            break;
        case 2:
            /* Add new customer information from the user */
            // Save the customer information in the database
            printf("Customer Name: ");
            fflush(stdin);
            scanf("%[^\n]s", account.Customer->name);
            fprintf(fp, "%s ", account.Customer->name);
            printf("Customer Phone: ");
            fflush(stdin);
            scanf("%d", &account.Customer->phone);
            fprintf(fp, "%d ", account.Customer->phone);
            printf("Customer Address: ");
            fflush(stdin);
            scanf("%[^\n]s", account.Customer->address);
            fprintf(fp, "%s\n", account.Customer->address);

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

float calculateLoan(float amount, int period, float interestRate)
{
    /* FV = PV (1 + i)^n
     * For example, the future value of $10,000 compounded at 5% annually for three years:
     *      = $10,000 (1 + 0.05)^3
     *      = $10,000 (1.157625)
     *      = $11,576.25 */
    float loan = amount;

    if (period == 1)
    {
        loan = amount * (1 + interestRate) * period;
        return loan;
    }
    else
    {
        return ((1 + interestRate) * calculateLoan(amount, period - 1, interestRate));
    }
}