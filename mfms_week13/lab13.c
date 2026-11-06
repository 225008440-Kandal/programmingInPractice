/* ============================================================
   lab13.c  -  PAP521S Week 13 - Dynamic Memory Allocation
   An employee list with no fixed upper limit.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int    id;
    char   name[30];
    double salary;
} Employee;

int main(void)
{
    int capacity = 2;              /* slots available */
    int count    = 0;              /* slots used      */
    int i;
    Employee *employees = NULL;
    Employee *bigger;
    Employee e;

    /* TODO 1: ask the heap for room for 'capacity' employees.
       malloc returns NULL when the request fails, so we check. */
    employees = malloc(capacity * sizeof(Employee));
    if (employees == NULL) {
        printf("Out of memory!\n");
        return 1;
    }

    printf("Employee ID (0 to stop): ");
    scanf("%d", &e.id);

    while (e.id != 0) {
        printf("Name (one word): ");
        scanf("%29s", e.name);
        printf("Salary: ");
        scanf("%lf", &e.salary);

        /* TODO 2: the array is full, so double its capacity.
           The result goes into a TEMPORARY pointer first: if
           realloc fails it returns NULL, and assigning that
           straight into 'employees' would lose the old block. */
        if (count == capacity) {
            capacity = capacity * 2;

            bigger = realloc(employees, capacity * sizeof(Employee));

            if (bigger == NULL) {
                printf("Out of memory!\n");
                free(employees);
                return 1;
            }

            employees = bigger;    /* only now is it safe */
            printf("  (grown to %d slots)\n", capacity);
        }

        /* TODO 3: store the record and move the counter on. */
        employees[count] = e;
        count++;

        printf("Employee ID (0 to stop): ");
        scanf("%d", &e.id);
    }

    /* TODO 4: show every employee, then the two numbers. */
    printf("\n");
    for (i = 0; i < count; i++) {
        printf("%-6d %-12s N$%.2f\n",
               employees[i].id, employees[i].name, employees[i].salary);
    }
    printf("Employees: %d | Capacity: %d\n", count, capacity);

    /* TODO 5: give the memory back, then forget the address. */
    free(employees);
    employees = NULL;

    return 0;
}