#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utilities.h"
 
#define MAX_DEPARTMENTS 20
#define MAX_NAME        50
 

static char   names[MAX_DEPARTMENTS][MAX_NAME];
static double allocated[MAX_DEPARTMENTS];
static double expenditure[MAX_DEPARTMENTS];
 
static int count = 0;    
 
 

static double calculateRemaining(double alloc, double spent)
{
    return alloc - spent;
}
 
 

static void addBudget(void)
{
    printHeading("ADD DEPARTMENTAL BUDGET");
 
   
    if (count == MAX_DEPARTMENTS) {
        printf("The budget list is full (%d departments).\n", MAX_DEPARTMENTS);
        return;
    }
 
    readText("Department name       : ", names[count], MAX_NAME);
    allocated[count]   = readMoney("Allocated budget  N$: ");
    expenditure[count] = readMoney("Expenditure       N$: ");
 
    count++;    
 
    printf("\nBudget recorded. Total departments: %d\n", count);
}
 
 

static void displayBudgets(void)
{
    int i;
    double remaining;
 
    printHeading("ALL DEPARTMENTAL BUDGETS");
 
    if (count == 0) {
        printf("No budgets have been recorded yet.\n");
        return;
    }
 
    printf("%-20s %14s %14s %14s   %s\n",
           "DEPARTMENT", "ALLOCATED", "EXPENDITURE", "REMAINING", "STATUS");
    printf("-------------------------------------------------------------------------------\n");
 
    
    for (i = 0; i < count; i++) {
        remaining = calculateRemaining(allocated[i], expenditure[i]);
 
        printf("%-20s %14.2f %14.2f %14.2f   ",
               names[i], allocated[i], expenditure[i], remaining);
 
        
        if (expenditure[i] > allocated[i]) {
            printf("OVER BUDGET\n");
        } else {
            printf("WITHIN BUDGET\n");
        }
    }
 
    printf("-------------------------------------------------------------------------------\n");
    printf("Total departments: %d\n", count);
}
 
 

static void searchBudget(void)
{
    char target[MAX_NAME];
    int i;
    int found = 0;        
    double remaining;
 
    printHeading("SEARCH DEPARTMENT");
 
    if (count == 0) {
        printf("No budgets have been recorded yet.\n");
        return;
    }
 
    readText("Enter the department name: ", target, MAX_NAME);
 
    for (i = 0; i < count; i++) {
 
        
        if (strcmp(names[i], target) == 0) {
 
            remaining = calculateRemaining(allocated[i], expenditure[i]);
 
            printf("\nDepartment found at position %d:\n", i);
            printf("  Department       : %s\n",     names[i]);
            printf("  Allocated Budget : N$%.2f\n", allocated[i]);
            printf("  Expenditure      : N$%.2f\n", expenditure[i]);
            printf("  Remaining Budget : N$%.2f\n", remaining);
 
            if (expenditure[i] > allocated[i]) {
                printf("  Status           : OVER BUDGET\n");
            } else {
                printf("  Status           : WITHIN BUDGET\n");
            }
 
            found = 1;
            break;        
        }
    }
 
    if (found == 0) {
        printf("\nNo department named \"%s\" was found.\n", target);
        printf("Note: the search is case sensitive.\n");
    }
}
 
 

static void displayOverBudget(void)
{
    int i;
    int overCount = 0;
 
    printHeading("DEPARTMENTS EXCEEDING THEIR BUDGET");
 
    if (count == 0) {
        printf("No budgets have been recorded yet.\n");
        return;
    }
 
    for (i = 0; i < count; i++) {
        if (expenditure[i] > allocated[i]) {
            printf("  %-20s overspent by N$%.2f\n",
                   names[i], expenditure[i] - allocated[i]);
            overCount++;
        }
    }
 
    if (overCount == 0) {
        printf("  All departments are within budget.\n");
    } else {
        printf("\n%d department(s) exceeded their allocation.\n", overCount);
    }
}
 
 

void budgetMenu(void)
{
    int choice;
 
    do {
        printf("\n----------------------------------\n");
        printf("      BUDGET MANAGEMENT\n");
        printf("----------------------------------\n");
        printf("1. Add departmental budget\n");
        printf("2. Display all budgets\n");
        printf("3. Search department\n");
        printf("4. Departments over budget\n");
        printf("5. Back to main menu\n\n");
 
        choice = readInt("Enter your choice: ", 1, 5);
 
        switch (choice) {
            case 1: addBudget();         break;
            case 2: displayBudgets();    break;
            case 3: searchBudget();      break;
            case 4: displayOverBudget(); break;
            case 5: printf("Returning to the main menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
 
    } while (choice != 5);
}
 
 

 
int getDepartmentCount(void)
{
    return count;
}
 
double getAllocated(int i)
{
    if (i < 0 || i >= count) {   
        return 0;
    }
    return allocated[i];
}
 
double getExpenditure(int i)
{
    if (i < 0 || i >= count) {
        return 0;
    }
    return expenditure[i];
}
 
const char* getDepartmentName(int i)
{
    if (i < 0 || i >= count) {
        return "";
    }
    return names[i];
}
 