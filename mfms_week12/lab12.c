/* ============================================================
   lab12.c  -  PAP521S Week 12 - Pointers
   Parts A, B and C of the lab, as a standalone program.
   ============================================================ */

#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 5

typedef struct {
    int    id;
    char   name[30];
    double salary;
} Employee;


/* ---------- Part A: what a pointer holds ---------- */
static void warmUp(void)
{
    int  age = 25;
    int *p   = &age;     /* p stores the ADDRESS of age */

    printf("--- Part A: a pointer and the variable it points to ---\n");
    printf("  value of age        : %d\n",  age);
    printf("  address of age (&age): %p\n", (void *)&age);
    printf("  value stored in p   : %p\n",  (void *)p);
    printf("  value at *p         : %d\n",  *p);

    *p = 30;             /* change age THROUGH the pointer */

    printf("  after *p = 30, age is now: %d\n\n", age);
}


/* ---------- Part B: swapping ---------- */

/* The wrong version: plain doubles, so it only swaps copies. */
static void swapWrong(double a, double b)
{
    double temp = a;
    a = b;
    b = temp;
}

/* The right version: addresses, so it reaches the originals. */
static void swapSalaries(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}


/* ---------- Part C: arrays passed to functions ---------- */

/* const says this function only reads - it will not change the array. */
static void displaySalaries(const double salaries[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("    Employee %d: N$%.2f\n", i + 1, salaries[i]);
    }
}

static double findHighest(const double salaries[], int n)
{
    double highest = salaries[0];
    int i;

    for (i = 1; i < n; i++) {
        if (salaries[i] > highest) {
            highest = salaries[i];
        }
    }

    return highest;
}

static double calculateAverage(const double salaries[], int n)
{
    double total = 0;
    int i;

    if (n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        total = total + salaries[i];
    }

    return total / n;
}

/* No const here: this one DOES change the array. */
static void giveRaise(double salaries[], int n, double percent)
{
    int i;

    for (i = 0; i < n; i++) {
        salaries[i] = salaries[i] + (salaries[i] * percent / 100.0);
    }
}


/* ---------- Part D: pointers to structures ---------- */
static void updateSalary(Employee *e, double newSalary)
{
    e->salary = newSalary;      /* -> because e is a POINTER */
}

static Employee *findEmployee(Employee list[], int n, int id)
{
    int i;

    for (i = 0; i < n; i++) {
        if (list[i].id == id) {
            return &list[i];    /* the ADDRESS of the match */
        }
    }

    return NULL;                /* nothing found */
}


int main(void)
{
    double salaries[3] = { 15000.00, 18500.50, 21000.75 };
    double a = 15000.00, b = 21000.75;

    Employee staff[MAX_EMPLOYEES] = {
        {1001, "Maria", 18500.50},
        {1002, "Simon", 17200.00},
        {1003, "Anna",  21000.75}
    };
    int count = 3;
    Employee *found;

    warmUp();

    printf("--- Part B: swapping two salaries ---\n");
    printf("  before      : a = %.2f   b = %.2f\n", a, b);

    swapWrong(a, b);
    printf("  swapWrong   : a = %.2f   b = %.2f   (nothing changed)\n", a, b);

    swapSalaries(&a, &b);
    printf("  swapSalaries: a = %.2f   b = %.2f   (swapped)\n\n", a, b);

    printf("--- Part C: arrays in functions ---\n");
    printf("  the array as given:\n");
    displaySalaries(salaries, 3);
    printf("  highest : N$%.2f\n", findHighest(salaries, 3));
    printf("  average : N$%.2f\n", calculateAverage(salaries, 3));

    giveRaise(salaries, 3, 10.0);
    printf("  after a 10%% raise - the ORIGINAL array changed:\n");
    displaySalaries(salaries, 3);
    printf("\n");

    printf("--- Part D: finding and updating a record ---\n");

    found = findEmployee(staff, count, 1002);
    if (found != NULL) {
        printf("  found %s earning N$%.2f\n", found->name, found->salary);
        updateSalary(found, 19000.00);
        printf("  %s now earns N$%.2f\n", found->name, found->salary);
    } else {
        printf("  Employee not found.\n");
    }

    found = findEmployee(staff, count, 9999);
    if (found == NULL) {
        printf("  ID 9999: employee not found (findEmployee returned NULL)\n");
    }

    return 0;
}