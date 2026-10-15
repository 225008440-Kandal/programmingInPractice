#include <stdio.h>

#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "utilities.h"


/* ---------- employee report ---------- */
static void employeeReport(void)
{
    int i;
    int n;
    double salary, total = 0, highest, lowest, average;

    printHeading("EMPLOYEE REPORT");

    n = getEmployeeCount();

    if (n == 0) {
        printf("No employees have been added yet.\n");
        return;
    }

    highest = getEmployeeSalary(0);
    lowest  = highest;

    for (i = 0; i < n; i++) {
        salary = getEmployeeSalary(i);

        total = total + salary;

        if (salary > highest) {
            highest = salary;
        }
        if (salary < lowest) {
            lowest = salary;
        }
    }

    average = total / n;

    printf("Total Employees : %d\n",      n);
    printf("Total Payroll   : N$%.2f\n",  total);
    printf("Average Salary  : N$%.2f\n",  average);
    printf("Highest Salary  : N$%.2f\n",  highest);
    printf("Lowest Salary   : N$%.2f\n",  lowest);
}


/* ---------- budget report ---------- */
static void budgetReport(void)
{
    int i;
    int n;
    int overCount = 0;
    double totalAllocated = 0, totalSpent = 0;

    printHeading("BUDGET REPORT");

    n = getDepartmentCount();

    if (n == 0) {
        printf("No departmental budgets have been recorded yet.\n");
        return;
    }

    /* First pass: add up the totals. */
    for (i = 0; i < n; i++) {
        totalAllocated = totalAllocated + getAllocated(i);
        totalSpent     = totalSpent     + getExpenditure(i);
    }

    printf("Departments            : %d\n",     n);
    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Remaining Budget       : N$%.2f\n", totalAllocated - totalSpent);

    /* Second pass: list the departments that overspent. */
    printf("\nDepartments exceeding their allocation:\n");

    for (i = 0; i < n; i++) {
        if (getExpenditure(i) > getAllocated(i)) {
            printf("  %-20s over by N$%.2f\n",
                   getDepartmentName(i),
                   getExpenditure(i) - getAllocated(i));
            overCount++;
        }
    }

    if (overCount == 0) {
        printf("  None - all departments are within budget.\n");
    }
}


/* ---------- full report ---------- */
static void fullReport(void)
{
    employeeReport();
    budgetReport();
}


/* ---------- module menu ---------- */
void reportsMenu(void)
{
    int choice;

    do {
        printf("\n----------------------------------\n");
        printf("            REPORTS\n");
        printf("----------------------------------\n");
        printf("1. Employee report\n");
        printf("2. Budget report\n");
        printf("3. Full municipal report\n");
        printf("4. Back to main menu\n\n");

        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: fullReport();     break;
            case 4: printf("Returning to the main menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);
}