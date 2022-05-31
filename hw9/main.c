/*
 * Assignment #9 submission by Çağla Nur Yurdasal
 */
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
struct BankAccount account[50]; // struct to keep customer and loan information
static int num_customers = 0;   // number of customers
int loan_check[50][3] = {0};    // check number of loans
int periods[50][3];             // check periods

int main()
{
    int sel,        // user selection
        loan_check; // variable to check if selected customer can apply for a new loan

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
            /* List all customers saved in the database */
            listCustomers();
            break;
        case 2:
            /* Add a new customer to be saved in the database */
            addCustomer();
            break;
        case 3:
            loan_check = newLoan();
            if (loan_check == 0)
            {
                /* Inform the user if a new loan can't be given to chosen customer */
                printf("No more loans can be given to this customer.\n");
            }
            else if (loan_check == -1)
            {
                /* Inform the user if an ID that is not saved in the database is entered */
                printf("You have entered an invalid ID\n");
            }
            break;
        case 4:
            /* Give the report on customer or credit details */
            getReport();
            break;
        case 5:
            /* Stop the program if user enters 5 to exit */
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
     * save it in the database
     */
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
    fclose(fp);
}
void listCustomers()
{
    /* List customer ID and names */
    for (int i = 0; i < num_customers; i++)
    {
        printf("Customer ID = %d\n", i + 1);
        printf("Customer Name = %s\n", account[i].Customer.name);
    }
}
float calculateLoan(float amount, int period, float interestRate)
{
    /* Calculate the loan using the formula FV = PV (1 + i)^n
     * For example, the future value of $10,000 compounded at 5% annually for three years:
     *      = $10,000 (1 + 0.05)^3
     *      = $10,000 (1.157625)
     *      = $11,576.25 */
    float loan = amount;

    if (period == 1) // base case
    {
        /* if period==1, multiply it by the rest of the formula as n^1==n*1 */
        loan = amount * (1 + interestRate) * period;
        return loan;
    }
    else
    {
        /* Keep calling the function to multiply the (1+interestRate) with itself period times */
        return ((1 + interestRate) * calculateLoan(amount, period - 1, interestRate));
    }
}
void getReport()
{
    FILE *fp;
    fp = fopen("customers.txt", "r");
    int sel,            // user selection
        which_credit,   // credit of which details to be displayed
        which_customer, // customer whom details to be displayed
        i = 0;          // variable to keep track of saved customers in the database
    printf("Enter 1 for customer details, 2 for credit details: ");
    scanf("%d", &sel);
    if (sel == 1)
    {
        rewind(fp);
        /* Display all the saved customers' details saved in the customers.txt
         * database using the struct account */
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
        /* Display the chosen loan details of the chosen customer */
        printf("Total credit value = %.4f\n", account[which_customer - 1].Loans->arr[which_credit - 1]);
        /* Display all the installements of the chosen loan */
        for (int m = 0; m < periods[which_customer - 1][which_credit - 1]; m++)
        {
            printf("%d. month installment = %.4f\n", m + 1, account[which_customer - 1].Loans->arr[which_credit - 1] / (float)periods[which_customer - 1][which_credit - 1]);
        }
    }
}
int newLoan()
{
    int customer_id,     // customer to apply for a new loan
        loan_amount = 0, // number of loans given to the customer so far
        current_id = 1,  // variable to check if entered ID is valid
        id_check = 0;    // variable to validate the entered ID
    float loan,          // loan to be given
        auxAmount,       // amount of credit
        auxPeriod,       // number of months
        auxInterestRate; // interest rate
    char buffer[50];
    FILE *fp;
    fp = fopen("customers.txt", "r");

    printf("Which customer do you want to give the loan to? Enter ID: ");
    scanf("%d", &customer_id);

    /* Check whether the entered customer ID is a valid one by searching the database */
    while (!feof(fp))
    {
        fgets(buffer, 50, fp);
        /* If entered ID is found in the database, ID is valid */
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
    /* If entered ID is not saved in the database, return -1 to give an error message */
    if (id_check == 0)
    {
        return -1;
    }
    /* Check whether the chosen customer can apply for a new loan */
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
            /* Save the periods in another database */
            periods[customer_id - 1][i] = auxPeriod;
            printf("Enter interest rate: ");
            fflush(stdin);
            scanf("%f", &auxInterestRate);

            /* Calculate the loan */
            loan = calculateLoan(auxAmount, auxPeriod, auxInterestRate);
            loan_check[customer_id - 1][i] = loan;
            /* Save the loan to customer loan union */
            account[customer_id - 1].Loans->arr[i] = loan;

            return 1;
        }
    }
}