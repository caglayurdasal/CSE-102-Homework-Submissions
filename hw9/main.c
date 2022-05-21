#include <stdio.h>

void listCustomers();

void addCustomer();

void newLoan();

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
    union Person Customer;
    union Loan Loans[3];
};
struct BankAccount account[50];
static int num_customers = 0;

int main()
{

    int sel;
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
            listCustomers();
            break;
        case 2:
            addCustomer();
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

    return 0;
}
void addCustomer()
{
    /* Add new customer information from the user and
     * save the customer information in the database*/

    FILE *fp;
    fp = fopen("customers.txt", "a+");

    printf("Customer Phone: ");
    fflush(stdin);
    scanf("%d", &account[num_customers].Customer.phone);
    fprintf(fp, "%d ", account[num_customers].Customer.phone);
    printf("Customer Address: ");
    fflush(stdin);
    scanf("%[^\n]s", account[num_customers].Customer.address);
    fprintf(fp, "%s ", account[num_customers].Customer.address);
    printf("Customer Name: ");
    fflush(stdin);
    scanf("%[^\n]s", account[num_customers].Customer.name);
    fprintf(fp, "%s\n", account[num_customers].Customer.name);
    num_customers++;
}
void listCustomers()
{

    for (int i = 0; i < num_customers; i++)
    {
        printf("Customer ID = %d\n", i + 1);
        printf("Customer Name = %s\n", account[i].Customer.name);
    }

    // FILE *fp;
    // fp = fopen("customers.txt", "r");
    // rewind(fp);
    // while (!feof(fp))
    // {
    //     fscanf(fp, "%s ", account.Customer.name);
    //     printf("Customer ID = %d\n", num_lines + 1);
    //     printf("Customer Name = %s\n", account.Customer.name);
    //     fscanf(fp, "%d ", &account.Customer.phone);
    //     printf("Customer Phone = %d\n", account.Customer.phone);
    //     fscanf(fp, "%[^\n]s", account.Customer.address);
    //     printf("Customer Address = %s\n", account.Customer.address);
    //     num_lines++;
    // }
    // fclose(fp);
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
void newLoan()
{
}