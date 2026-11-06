/* ============================================================
   records.c  -  The five MFMS record types
   PAP521S Week 11 - Structures

   Every record is now a structure instead of a group of
   parallel arrays. One array per record type, plus a counter.
   ============================================================ */

#include <stdio.h>
#include <string.h>

#include "records.h"
#include "utilities.h"

/* One drawer of record cards per type, plus how many are filled. */
static Employee employees[MAX_RECORDS];   static int employeeCount = 0;
static Supplier suppliers[MAX_RECORDS];   static int supplierCount = 0;
static Asset    assets[MAX_RECORDS];      static int assetCount    = 0;
static Budget   budgets[MAX_RECORDS];     static int budgetCount   = 0;
static Project  projects[MAX_RECORDS];    static int projectCount  = 0;


/* ---------- a small helper for the nested Date ---------- */
static Date readDate(const char *label)
{
    Date d;

    printf("%s\n", label);
    d.day   = readInt("    Day   (1-31) : ", 1, 31);
    d.month = readInt("    Month (1-12) : ", 1, 12);
    d.year  = readInt("    Year         : ", 1900, 2100);

    return d;
}


/* ============================================================
   EMPLOYEES
   ============================================================ */
static void addEmployee(void)
{
    printHeading("ADD EMPLOYEE");

    if (employeeCount == MAX_RECORDS) {
        printf("The employee list is full (%d records).\n", MAX_RECORDS);
        return;
    }

    /* employees[employeeCount] is the next free card in the drawer.
       The dot operator reaches one member of that card. */
    employees[employeeCount].id = readInt("Employee ID  : ", 1, 99999);
    readText("Name         : ", employees[employeeCount].name, 30);
    readText("Department   : ", employees[employeeCount].department, 20);
    employees[employeeCount].salary = readMoney("Salary    N$: ");

    employeeCount++;

    printf("\nEmployee stored. Total employees: %d\n", employeeCount);
}

static void displayEmployees(void)
{
    int i;

    printHeading("ALL EMPLOYEES");

    if (employeeCount == 0) {
        printf("No employees have been added yet.\n");
        return;
    }

    printf("%-6s %-20s %-15s %14s\n", "ID", "NAME", "DEPARTMENT", "SALARY");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < employeeCount; i++) {
        printf("%-6d %-20s %-15s %14.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].salary);
    }

    printf("---------------------------------------------------------------\n");
    printf("Total employees: %d\n", employeeCount);
}


/* ============================================================
   SUPPLIERS
   ============================================================ */
static void addSupplier(void)
{
    printHeading("ADD SUPPLIER");

    if (supplierCount == MAX_RECORDS) {
        printf("The supplier list is full (%d records).\n", MAX_RECORDS);
        return;
    }

    suppliers[supplierCount].id = readInt("Supplier ID : ", 1, 99999);
    readText("Name        : ", suppliers[supplierCount].name,  40);
    readText("Email       : ", suppliers[supplierCount].email, 40);
    readText("Phone       : ", suppliers[supplierCount].phone, 15);
    readText("Town        : ", suppliers[supplierCount].town,  20);

    supplierCount++;

    printf("\nSupplier stored. Total suppliers: %d\n", supplierCount);
}

static void displaySuppliers(void)
{
    int i;

    printHeading("ALL SUPPLIERS");

    if (supplierCount == 0) {
        printf("No suppliers have been added yet.\n");
        return;
    }

    printf("%-6s %-22s %-24s %-14s %s\n",
           "ID", "NAME", "EMAIL", "PHONE", "TOWN");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < supplierCount; i++) {
        printf("%-6d %-22s %-24s %-14s %s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].phone,
               suppliers[i].town);
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("Total suppliers: %d\n", supplierCount);
}


/* ============================================================
   ASSETS  -  uses the nested Date structure
   ============================================================ */
static void addAsset(void)
{
    printHeading("ADD ASSET");

    if (assetCount == MAX_RECORDS) {
        printf("The asset list is full (%d records).\n", MAX_RECORDS);
        return;
    }

    assets[assetCount].id = readInt("Asset ID    : ", 1, 99999);
    readText("Description : ", assets[assetCount].description, 40);
    assets[assetCount].value = readMoney("Value    N$: ");

    /* A structure inside a structure: assets[i].acquired is itself
       a Date, so we reach its members with a second dot. */
    assets[assetCount].acquired = readDate("Date acquired:");

    assetCount++;

    printf("\nAsset stored. Total assets: %d\n", assetCount);
}

static void displayAssets(void)
{
    int i;
    double total = 0;

    printHeading("ASSET REGISTER");

    if (assetCount == 0) {
        printf("No assets have been added yet.\n");
        return;
    }

    printf("%-6s %-25s %14s   %s\n", "ID", "DESCRIPTION", "VALUE", "ACQUIRED");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++) {
        printf("%-6d %-25s %14.2f   %02d/%02d/%d\n",
               assets[i].id,
               assets[i].description,
               assets[i].value,
               assets[i].acquired.day,
               assets[i].acquired.month,
               assets[i].acquired.year);

        total = total + assets[i].value;
    }

    printf("-------------------------------------------------------------------\n");
    printf("Total assets: %d      Total value: N$%.2f\n", assetCount, total);
}


/* ============================================================
   BUDGETS  -  balance = allocated - spent
   ============================================================ */
static void addBudget(void)
{
    printHeading("ADD DEPARTMENTAL BUDGET");

    if (budgetCount == MAX_RECORDS) {
        printf("The budget list is full (%d records).\n", MAX_RECORDS);
        return;
    }

    readText("Department      : ", budgets[budgetCount].department, 20);
    budgets[budgetCount].allocated = readMoney("Allocated    N$: ");
    budgets[budgetCount].spent     = readMoney("Spent        N$: ");

    budgetCount++;

    printf("\nBudget stored. Total budgets: %d\n", budgetCount);
}

static void displayBudgets(void)
{
    int i;
    double balance;

    printHeading("DEPARTMENTAL BUDGETS");

    if (budgetCount == 0) {
        printf("No budgets have been added yet.\n");
        return;
    }

    printf("%-20s %14s %14s %14s   %s\n",
           "DEPARTMENT", "ALLOCATED", "SPENT", "BALANCE", "STATUS");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < budgetCount; i++) {
        balance = budgets[i].allocated - budgets[i].spent;

        printf("%-20s %14.2f %14.2f %14.2f   ",
               budgets[i].department,
               budgets[i].allocated,
               budgets[i].spent,
               balance);

        if (budgets[i].spent > budgets[i].allocated) {
            printf("OVER BUDGET\n");
        } else {
            printf("WITHIN BUDGET\n");
        }
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("Total budgets: %d\n", budgetCount);
}


/* ============================================================
   PROJECTS  -  two nested Date structures
   ============================================================ */
static void addProject(void)
{
    printHeading("ADD PROJECT");

    if (projectCount == MAX_RECORDS) {
        printf("The project list is full (%d records).\n", MAX_RECORDS);
        return;
    }

    projects[projectCount].id = readInt("Project ID : ", 1, 99999);
    readText("Title      : ", projects[projectCount].title, 40);
    projects[projectCount].budget = readMoney("Budget  N$: ");

    projects[projectCount].startDate = readDate("Start date:");
    projects[projectCount].endDate   = readDate("End date:");

    projectCount++;

    printf("\nProject stored. Total projects: %d\n", projectCount);
}

static void displayProjects(void)
{
    int i;

    printHeading("ALL PROJECTS");

    if (projectCount == 0) {
        printf("No projects have been added yet.\n");
        return;
    }

    printf("%-6s %-25s %14s   %-12s %s\n",
           "ID", "TITLE", "BUDGET", "START", "END");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < projectCount; i++) {
        printf("%-6d %-25s %14.2f   %02d/%02d/%-6d %02d/%02d/%d\n",
               projects[i].id,
               projects[i].title,
               projects[i].budget,
               projects[i].startDate.day,
               projects[i].startDate.month,
               projects[i].startDate.year,
               projects[i].endDate.day,
               projects[i].endDate.month,
               projects[i].endDate.year);
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("Total projects: %d\n", projectCount);
}


/* ============================================================
   BINARY FILE STORAGE  -  Task 10
   A structure is one block of memory, so the whole array goes
   to disk in a single fwrite call.
   ============================================================ */
static void saveEmployees(void)
{
    FILE *fp;

    fp = fopen("data/employees.dat", "wb");

    if (fp == NULL) {
        printf("Error: could not open data/employees.dat for writing.\n");
        printf("Make sure the 'data' folder exists.\n");
        return;
    }

    /* The count goes first so the loader knows how many to read. */
    fwrite(&employeeCount, sizeof(int), 1, fp);
    fwrite(employees, sizeof(Employee), employeeCount, fp);

    fclose(fp);

    printf("Saved %d employee record(s) to data/employees.dat\n", employeeCount);
}

static void loadEmployees(void)
{
    FILE *fp;
    int stored = 0;
    size_t read;

    fp = fopen("data/employees.dat", "rb");

    if (fp == NULL) {
        printf("No saved employee file found (data/employees.dat).\n");
        return;
    }

    /* fread returns how many items it actually read. */
    if (fread(&stored, sizeof(int), 1, fp) != 1) {
        printf("Error: data/employees.dat is empty or damaged.\n");
        fclose(fp);
        return;
    }

    if (stored < 0 || stored > MAX_RECORDS) {
        printf("Error: the record count in the file is not valid.\n");
        fclose(fp);
        return;
    }

    read = fread(employees, sizeof(Employee), (size_t)stored, fp);

    fclose(fp);

    employeeCount = (int)read;

    printf("Loaded %d employee record(s) from data/employees.dat\n", employeeCount);
}
/* ============================================================
   POINTERS  -  Week 12
   ============================================================ */

/* The employee is passed by ADDRESS, so the function changes the
   real record and not a copy. e is a pointer, so we reach its
   members with -> instead of the dot. */
static void updateSalary(Employee *e, double newSalary)
{
    e->salary = newSalary;
}


/* Returns the ADDRESS of the matching record, or NULL when no
   employee has that ID. The caller must check for NULL before
   using what comes back. */
static Employee *findEmployee(Employee list[], int n, int id)
{
    int i;

    for (i = 0; i < n; i++) {
        if (list[i].id == id) {
            return &list[i];
        }
    }

    return NULL;
}


/* ---------- menu option: update an employee salary ---------- */
static void updateEmployeeSalary(void)
{
    int id;
    double newSalary;
    Employee *found;

    printHeading("UPDATE EMPLOYEE SALARY");

    if (employeeCount == 0) {
        printf("No employees have been added yet.\n");
        return;
    }

    id = readInt("Employee ID to update : ", 1, 99999);

    found = findEmployee(employees, employeeCount, id);

    if (found == NULL) {
        printf("\nNo employee with ID %d was found.\n", id);
        return;
    }

    printf("\nFound: %s (%s) currently earning N$%.2f\n",
           found->name, found->department, found->salary);

    newSalary = readMoney("New salary         N$: ");

    updateSalary(found, newSalary);

    printf("\nUpdated record:\n");
    printf("  ID         : %d\n",      found->id);
    printf("  Name       : %s\n",      found->name);
    printf("  Department : %s\n",      found->department);
    printf("  Salary     : N$%.2f\n",  found->salary);
}

/* ============================================================
   MENU
   ============================================================ */
void recordsMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("   MFMS RECORDS - WEEK 11 (STRUCTURES)\n");
        printf("========================================\n\n");
        printf(" 1. Add employee        2. Display employees\n");
        printf(" 3. Add supplier        4. Display suppliers\n");
        printf(" 5. Add asset           6. Display assets\n");
        printf(" 7. Add budget          8. Display budgets\n");
        printf(" 9. Add project        10. Display projects\n");
        printf("11. Save employees (binary)\n");
        printf("12. Load employees (binary)\n");
        printf("13. Update employee salary\n");
        printf("14. Exit\n\n");

        choice = readInt("Enter your choice: ", 1, 13);

        switch (choice) {
            case  1: addEmployee();      break;
            case  2: displayEmployees(); break;
            case  3: addSupplier();      break;
            case  4: displaySuppliers(); break;
            case  5: addAsset();         break;
            case  6: displayAssets();    break;
            case  7: addBudget();        break;
            case  8: displayBudgets();   break;
            case  9: addProject();       break;
            case 10: displayProjects();  break;
            case 11: saveEmployees();    break;
            case 12: loadEmployees();    break;
            case 13: updateEmployeeSalary(); break;
            case 14: printf("\nThank you for using the system. Goodbye.\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 13);
}