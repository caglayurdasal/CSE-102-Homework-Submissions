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
float customer_loans[50][3];

int main()
{
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
            listCustomers();
            break;
        case 2:
            addCustomer();
            break;
        case 3:
            if (newLoan() == 0)
            {
                printf("No more loans can be given to this customer.\n");
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
    printf("Customer ID: ");
    fflush(stdin);
    scanf("%d", &account[num_customers].Customer.id);
    fprintf(fp, "%d ", account[num_customers].Customer.id);
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
    int i, auxPeriod, num_loans = 0, loan_amount = 0;
    float loan, auxAmount, auxInterestRate;
    FILE *fp, *f, *aux;
    char *ptr, loansPerLine[50];
    f = fopen("customers.txt", "r");
    fp = fopen("loans.txt", "a+");

    printf("Which customer do you want to give the loan to? Enter ID: ");
    scanf("%d", &i);
    int line = 0;
    while (line < i)
    {
        fgets("%[\n]s", 50, f);
        line++;
    }
    fread(aux, "%d %s %d %s ", );
    while (loan_amount < 3 && (ptr = fgets(loansPerLine, 50, f)))
    {
        if (*(ptr + 2) == '\n')
        {
            break;
        }
        while (*ptr)
        {
            while (*(ptr + 1) < '0' || *(ptr + 1) > '9')
            {
                ptr++;
            }
            if (*(ptr + 1) >= '0' && *(ptr + 1) <= '9')
            {
                loan_amount++;
                if (loan_amount == 3)
                {
                    return 0;
                }
            }
            while (*(ptr + 1) >= '0' && *(ptr + 1) <= '9')
            {
                ptr++;
            }
        }
    }

    printf("Enter amount: ");
    scanf("%f", &account[i].Loans[num_loans].amount);
    auxAmount = account[i].Loans[num_loans].amount;
    printf("Enter interest rate: ");
    scanf("%f", &account[i].Loans[num_loans].interestRate);
    auxInterestRate = account[i].Loans[num_loans].interestRate;
    printf("Enter period: ");
    scanf("%d", &account[i].Loans[num_loans].period);
    auxPeriod = account[i].Loans[num_loans].period;
    customer_loans[i][loan_amount] = calculateLoan(auxAmount, auxPeriod, auxInterestRate);
    fprintf(fp, "%f ", customer_loans[i][loan_amount]);
    printf("Calculated loan: %.2f\n", customer_loans[i][loan_amount]);
    fclose(fp);
    return 1;
}