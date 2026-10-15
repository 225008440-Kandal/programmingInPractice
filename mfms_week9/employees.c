



#include <stdio.h>      /* printf, scanf, fgets  */
#include <string.h>     /* strlen, strcmp, strcpy, strcat, strcspn */
#include "employees.h"  /* our own header - so the compiler checks that the
                           functions we write here match what we promised */


#define MAX_EMPLOYEES 50
#define MAX_NAME      50
#define TAX_RATE      0.15  


static int    ids[MAX_EMPLOYEES];
static char   names[MAX_EMPLOYEES][MAX_NAME];        
static char   departments[MAX_EMPLOYEES][MAX_NAME];
static double basicSalary[MAX_EMPLOYEES];
static double housing[MAX_EMPLOYEES];
static double transport[MAX_EMPLOYEES];

static int count = 0;   



static void readLine(const char *prompt, char *out, int size)
{
    printf("%s", prompt);
    fgets(out, size, stdin);

    
    out[strcspn(out, "\n")] = '\0';
}


static void readName(const char *prompt, char *out, int size)
{
    
    do {
        readLine(prompt, out, size);

        
        if (strlen(out) == 0) {
            printf("  Error: this cannot be empty. Please try again.\n");
        }
    } while (strlen(out) == 0);
}


static int readInt(const char *prompt, int min, int max)
{
    int value;
    int ch;

    while (1) {                       /* 1 is always true -> infinite loop, */
        printf("%s", prompt);         /* we leave it with 'return'          */

        
        if (scanf("%d", &value) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF) { }   /* clear buffer */
            printf("  Error: please enter a number.\n");
            continue;                 /* go back to the top of the loop */
        }

        while ((ch = getchar()) != '\n' && ch != EOF) { }  /* eat the Enter key */

        if (value >= min && value <= max) {   /* && is the logical AND operator */
            return value;
        }

        printf("  Error: please enter a value between %d and %d.\n", min, max);
    }
}

/* Reads an amount of money and refuses negative values
   so that a negative salary can never be stored. */
static double readMoney(const char *prompt)
{
    double value;
    int ch;

    while (1) {
        printf("%s", prompt);

        
        if (scanf("%lf", &value) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            printf("  Error: please enter a number.\n");
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF) { }

        if (value < 0) {
            printf("  Error: the amount cannot be negative.\n");
            continue;
        }

        return value;
    }
}



static double calculateGross(double basic, double house, double trans)
{
    return basic + house + trans;
}

/* Net salary = gross - tax, where tax is 15% of the gross. */
static double calculateNet(double gross)
{
    return gross - (gross * TAX_RATE);
}




/* ---- Add an employee ---- */
static void addEmployee(void)
{
    printf("\n--- ADD EMPLOYEE ---\n");

    
    if (count == MAX_EMPLOYEES) {
        printf("The employee list is full (%d employees).\n", MAX_EMPLOYEES);
        return;               /* leave the function early */
    }

    
    ids[count]         = readInt("Employee ID           : ", 1, 99999);
    readName           ("Name                  : ", names[count], MAX_NAME);
    readName           ("Department            : ", departments[count], MAX_NAME);
    basicSalary[count] = readMoney("Basic salary        N$: ");
    housing[count]     = readMoney("Housing allowance   N$: ");
    transport[count]   = readMoney("Transport allowance N$: ");

    count++;              /* one more employee stored */

    printf("\nEmployee added successfully. Total employees: %d\n", count);
}

/* ---- Display all employees ---- */
static void displayEmployees(void)
{
    int i;
    double gross, net;
    char label[MAX_NAME * 2 + 10];   /* room for "Name (Department)" */

    printf("\n--- ALL EMPLOYEES ---\n");

    
    if (count == 0) {
        printf("No employees have been added yet.\n");
        return;
    }

    
    printf("%-6s %-20s %-15s %12s %12s\n",
           "ID", "NAME", "DEPARTMENT", "GROSS", "NET");
    printf("--------------------------------------------------------------------------\n");

    
    for (i = 0; i < count; i++) {
        gross = calculateGross(basicSalary[i], housing[i], transport[i]);
        net   = calculateNet(gross);

        printf("%-6d %-20s %-15s %12.2f %12.2f\n",
               ids[i], names[i], departments[i], gross, net);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Total employees: %d\n", count);

    /* strcpy COPIES a string into another, strcat APPENDS to it.
       Here we build the label "Name (Department)" for the last employee. */
    strcpy(label, names[count - 1]);      /* label = "John"               */
    strcat(label, " (");                  /* label = "John ("             */
    strcat(label, departments[count - 1]);/* label = "John (Finance"      */
    strcat(label, ")");                   /* label = "John (Finance)"     */
    printf("Most recently added: %s\n", label);
}

/* ---- Search for an employee by name ---- */
static void searchEmployee(void)
{
    char target[MAX_NAME];
    int i;
    int found = 0;      /* a "flag": 0 means not found yet, 1 means found */
    double gross, net;

    printf("\n--- SEARCH EMPLOYEE ---\n");

    if (count == 0) {
        printf("No employees have been added yet.\n");
        return;
    }

    readName("Enter the employee name to search: ", target, MAX_NAME);

    for (i = 0; i < count; i++) {

        
        if (strcmp(names[i], target) == 0) {

            gross = calculateGross(basicSalary[i], housing[i], transport[i]);
            net   = calculateNet(gross);

            printf("\nEmployee found at position %d:\n", i);
            printf("  ID                  : %d\n",      ids[i]);
            printf("  Name                : %s\n",      names[i]);
            printf("  Department          : %s\n",      departments[i]);
            printf("  Basic salary        : N$%.2f\n",  basicSalary[i]);
            printf("  Housing allowance   : N$%.2f\n",  housing[i]);
            printf("  Transport allowance : N$%.2f\n",  transport[i]);
            printf("  Gross salary        : N$%.2f\n",  gross);
            printf("  Tax (15%%)           : N$%.2f\n", gross * TAX_RATE);
            printf("  Net salary          : N$%.2f\n",  net);

            found = 1;
            break;      /* stop the loop - we already found the employee */
        }
    }

    /* The flag tells us what happened after the loop finished. */
    if (found == 0) {
        printf("\nNo employee named \"%s\" was found.\n", target);
        printf("Note: the search is case sensitive - \"john\" is not \"John\".\n");
    }
}

/* ---- Salary summary for this module ---- */
static void salarySummary(void)
{
    int i;
    double gross, total = 0, highest, lowest, average;

    printf("\n--- SALARY SUMMARY ---\n");

    if (count == 0) {
        printf("No employees have been added yet.\n");
        return;   /* this guard also stops a division by zero below */
    }

    
    highest = calculateGross(basicSalary[0], housing[0], transport[0]);
    lowest  = highest;

    for (i = 0; i < count; i++) {
        gross = calculateGross(basicSalary[i], housing[i], transport[i]);

        total = total + gross;

        if (gross > highest) {
            highest = gross;
        }
        if (gross < lowest) {
            lowest = gross;
        }
    }

    average = total / count;

    printf("Total employees : %d\n",      count);
    printf("Total payroll   : N$%.2f\n",  total);
    printf("Average salary  : N$%.2f\n",  average);
    printf("Highest salary  : N$%.2f\n",  highest);
    printf("Lowest salary   : N$%.2f\n",  lowest);
}




void employeeMenu(void)
{
    int choice;

    do {
        printf("\n==================================\n");
        printf("      EMPLOYEE MANAGEMENT\n");
        printf("==================================\n");
        printf("1. Add employee\n");
        printf("2. Display all employees\n");
        printf("3. Search employee\n");
        printf("4. Salary summary\n");
        printf("5. Back to main menu\n\n");

        choice = readInt("Enter your choice: ", 1, 5);

        
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                salarySummary();
                break;
            case 5:
                printf("Returning to the main menu...\n");
                break;
            default:
                
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);      /* repeat until the user chooses to go back */
}




int getEmployeeCount(void)
{
    return count;
}

double getEmployeeSalary(int i)
{
    
    if (i < 0 || i >= count) {
        return 0;
    }
    return calculateGross(basicSalary[i], housing[i], transport[i]);
}

const char* getEmployeeName(int i)
{
    if (i < 0 || i >= count) {
        return "";
    }
    return names[i];
}