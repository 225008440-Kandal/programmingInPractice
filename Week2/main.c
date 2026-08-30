#include <stdio.h>

int main()
{
    double revenue;
    double expenses;
    double balance;
    int departments;
    double payroll;
    double procurement;
    double assets;

    printf("MUNICIPAL BUDGET CALCULATOR\n\n");

    printf("Enter Total Revenue: ");
    scanf("%lf", &revenue);

    printf("Enter Total Expenses: ");
    scanf("%lf", &expenses);

    printf("Enter Number of Departments: ");
    scanf("%d", &departments);

    printf("Enter Payroll: ");
    scanf("%lf", &payroll);

    printf("Enter Procurement: ");
    scanf("%lf", &procurement);

    printf("Enter Assets: ");
    scanf("%lf", &assets);

    balance = revenue - expenses;

    printf("\n---------------------------------\n");
    printf("Revenue     : %.2f\n", revenue);
    printf("Expenses    : %.2f\n", expenses);
    printf("Balance     : %.2f\n", balance);
    printf("Departments : %d\n", departments);
    printf("Payroll     : %.2f\n", payroll);
    printf("Procurement : %.2f\n", procurement);
    printf("Assets      : %.2f\n", assets);

    return 0;
}