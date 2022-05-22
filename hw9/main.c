#include <stdio.h>

void listCustomers();

void addCustomer();

int newLoan();

float calculateLoan(float amount, int period, float interestRate);

int getReport();

union Person
{
    char name[50];
    char address[50];
    int phone;
    int id;
};
union Loan
{
    float arr[3]; // amount, period, interestRate
};
struct BankAccount
{
    union Person Customer;
    union Loan Loans[3];
};
struct BankAccount account[50];
static int num_customers = 0;
int loan_check[50][3] = {0};

int main()
{
    int sel, loan_check;
    FILE *flp;
    flp = fopen("loans.txt", "w");
    for (int i = 0; i < 50; i++)
    {
        fprintf(flp, "%f \n", 1.0);
    }
    fclose(flp);
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
            loan_check = newLoan();
            if (loan_check == 0)
            {
                printf("No more loans can be given to this customer.\n");
            }
            else if (loan_check == -1)
            {
                printf("You have entered an invalid ID\n");
            }

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
    // printf("Customer ID: ");
    // fflush(stdin);
    // scanf("%d", &account[num_customers].Customer.id);
    // fprintf(fp, "%d ", account[num_customers].Customer.id);
    printf("Customer Name: ");
    fflush(stdin);
    scanf("%[^\n]s", account[num_customers].Customer.name);
    fprintf(fp, "%s \n", account[num_customers].Customer.name);

    num_customers++;
    fclose(fp);
}
void listCustomers()
{
    for (int i = 0; i < num_customers; i++)
    {
        printf("Customer ID = %d\n", i + 1);
        printf("Customer Name = %s\n", account[i].Customer.name);
    }
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
int newLoan()
{
    int customer_id, num_loans = 0, loan_amount = 0;
    float loan, auxAmount, auxPeriod, auxInterestRate;
    FILE *flp;
    char buffer[50], loans[4], *lp;

    // flp = fopen("loans.txt", "a+");
    // rewind(flp);

    printf("Which customer do you want to give the loan to? Enter ID: ");
    scanf("%d", &customer_id);

    for (int i = 0; i < 3; i++)
    {
        if (loan_check[customer_id - 1][i] > 0)
        {
            loan_amount++;
            if (loan_amount == 3)
            {
                return 0;
            }
        }
        else
        {
            printf("Enter amount: ");
            fflush(stdin);
            scanf("%f", &auxAmount);
            printf("Enter period: ");
            fflush(stdin);
            scanf("%f", &auxPeriod);
            printf("Enter interest rate: ");
            fflush(stdin);
            scanf("%f", &auxInterestRate);

            /* Calculate the loan */
            loan = calculateLoan(auxAmount, auxPeriod, auxInterestRate);
            loan_check[customer_id - 1][i] = loan;
            account[customer_id - 1].Loans->arr[i] = loan;

            return 1;
        }
    }
}