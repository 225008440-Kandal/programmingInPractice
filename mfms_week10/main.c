/* ============================================================
   main.c  -  Program entry point and main menu
   PAP521S Week 10 - Modular MFMS with persistent storage

   This file stays deliberately small. It shows the menu, reads
   the user's choice, and calls the right module.
   ============================================================ */

#include <stdio.h>

#include "employees.h"    /* Employee Management  */
#include "budget.h"       /* Budget Management    */
#include "reports.h"      /* Reports              */
#include "utilities.h"    /* shared input helpers */

static void displayWelcome(void)
{
    printf("\n==========================================\n");
    printf("  MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("  PAP521S - Week 10 - Persistent Storage\n");
    printf("==========================================\n\n");
}

static void displayMainMenu(void)
{
    printf("\n========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Reports\n");
    printf("4. Save Data\n");
    printf("5. Load Data\n");
    printf("6. Save Data (binary)\n");
    printf("7. Load Data (binary)\n");
    printf("8. Exit\n\n");
}

int main(void)
{
    int choice;

    displayWelcome();

    do {
        displayMainMenu();

        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                reportsMenu();
                break;
            case 4:
                saveEmployees();
                saveBudgets();
                break;
            case 5:
                loadEmployees();
                loadBudgets();
                break;
                        case 6:
                saveEmployeesBinary();
                break;
            case 7:
                loadEmployeesBinary();
                break;
            case 8:
                printf("\nThank you for using the system. Goodbye.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}