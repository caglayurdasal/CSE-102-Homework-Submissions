#include <stdio.h>

void listCustomers();

void addCustomer();

int newLoan();

float calculateLoan(float amount, int period, float interestRate);

void getReport();

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
int periods[50][3];

int main()
{
    int sel, loan_check;

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
            getReport();
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
    char buffer[100];
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
    fprintf(fp, "%s\n", account[num_customers].Customer.name);

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
void getReport()
{
    FILE *fp;
    fp = fopen("customers.txt", "r");
    int sel, which_credit, which_customer, i = 0;
    printf("Enter 1 for customer details, 2 for credit details: ");
    scanf("%d", &sel);
    if (sel == 1)
    {
        rewind(fp);
        while (i < num_customers)
        {
            printf("Customer ID = %d\n", i + 1);
            fscanf(fp, "%d ", &account[i].Customer.phone);
            printf("Customer Phone = %d\n", account[i].Customer.phone);
            fscanf(fp, "%s ", account[i].Customer.address);
            printf("Customer Address = %s\n", account[i].Customer.address);
            fscanf(fp, "%s ", account[i].Customer.name);
            printf("Customer Name = %s\n", account[i].Customer.name);
            i++;
        }
    }
    else if (sel == 2)
    {
        printf("Which customer's credit do you want to display? ");
        scanf("%d", &which_customer);
        printf("Which credit do you want to display? ");
        scanf("%d", &which_credit);
        printf("Total credit value = %.4f\n", account[which_customer - 1].Loans->arr[which_credit - 1]);
        for (int m = 0; m < periods[which_customer - 1][which_credit - 1]; m++)
        {
            printf("%d. month installment = %.4f\n", m + 1, account[which_customer - 1].Loans->arr[which_credit - 1] / (float)periods[which_customer - 1][which_credit - 1]);
        }
    }
}
int newLoan()
{
    int customer_id, loan_amount = 0, current_id = 1, id_check = 0;
    float loan, auxAmount, auxPeriod, auxInterestRate;
    char buffer[50];
    FILE *fp;
    fp = fopen("customers.txt", "r");

    printf("Which customer do you want to give the loan to? Enter ID: ");
    scanf("%d", &customer_id);

    while (!feof(fp))
    {
        fgets(buffer, 50, fp);
        if (current_id == customer_id)
        {
            id_check++;
        }
        else
        {
            current_id++;
        }
    }
    fclose(fp);
    if (id_check == 0)
    {
        return -1;
    }

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
            periods[customer_id - 1][i] = auxPeriod;
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