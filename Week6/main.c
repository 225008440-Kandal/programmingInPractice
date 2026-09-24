#include <stdio.h>
#include <string.h>

#define NUM_SALARIES 5
#define NUM_BUDGETS 5
#define NUM_REGS 3

int main() {
    float salaries[NUM_SALARIES];
    float budgets[NUM_BUDGETS];
    char registrations[NUM_REGS][20];
    float total, average, highest, lowest, temp, searchSalary;
    char searchReg[20];
    int found;

    /* ---------- A. EMPLOYEE SALARIES ---------- */
    printf("=== A. EMPLOYEE SALARIES ===\n");
    for (int i = 0; i < NUM_SALARIES; i++) {
        printf("Enter salary %d: ", i + 1);
        scanf("%f", &salaries[i]);
    }

    total = 0;
    highest = salaries[0];
    lowest = salaries[0];
    for (int i = 0; i < NUM_SALARIES; i++) {
        total = total + salaries[i];
        if (salaries[i] > highest) {
            highest = salaries[i];
        }
        if (salaries[i] < lowest) {
            lowest = salaries[i];
        }
    }
    average = total / NUM_SALARIES;

    printf("\nAll salaries:\n");
    for (int i = 0; i < NUM_SALARIES; i++) {
        printf("%.2f\n", salaries[i]);
    }
    printf("Average: %.2f\n", average);
    printf("Highest: %.2f\n", highest);
    printf("Lowest : %.2f\n", lowest);

    printf("\nSearch for a salary: ");
    scanf("%f", &searchSalary);
    found = 0;
    for (int i = 0; i < NUM_SALARIES; i++) {
        if (salaries[i] == searchSalary) {
            printf("Found at position %d\n", i);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("Salary not found.\n");
    }

    /* ---------- B. DEPARTMENT BUDGETS ---------- */
    printf("\n=== B. DEPARTMENT BUDGETS ===\n");
    for (int i = 0; i < NUM_BUDGETS; i++) {
        printf("Enter budget %d: ", i + 1);
        scanf("%f", &budgets[i]);
    }

    total = 0;
    for (int i = 0; i < NUM_BUDGETS; i++) {
        total = total + budgets[i];
    }
    average = total / NUM_BUDGETS;

    printf("\nTotal budget  : %.2f\n", total);
    printf("Average budget: %.2f\n", average);

    /* bubble sort — ascending */
    for (int i = 0; i < NUM_BUDGETS - 1; i++) {
        for (int j = 0; j < NUM_BUDGETS - i - 1; j++) {
            if (budgets[j] > budgets[j + 1]) {
                temp = budgets[j];
                budgets[j] = budgets[j + 1];
                budgets[j + 1] = temp;
            }
        }
    }

    printf("\nSorted budgets (lowest to highest):\n");
    for (int i = 0; i < NUM_BUDGETS; i++) {
        printf("%.2f\n", budgets[i]);
    }

    /* ---------- C. VEHICLE REGISTRATIONS ---------- */
    printf("\n=== C. VEHICLE REGISTRATIONS ===\n");
    for (int i = 0; i < NUM_REGS; i++) {
        printf("Enter registration %d: ", i + 1);
        scanf("%19s", registrations[i]);
    }

    printf("\nAll registrations:\n");
    for (int i = 0; i < NUM_REGS; i++) {
        printf("%s\n", registrations[i]);
    }

    printf("\nSearch for a registration: ");
    scanf("%19s", searchReg);
    found = 0;
    for (int i = 0; i < NUM_REGS; i++) {
        if (strcmp(registrations[i], searchReg) == 0) {
            printf("Found at position %d\n", i);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("Registration not found.\n");
    }

    return 0;
}