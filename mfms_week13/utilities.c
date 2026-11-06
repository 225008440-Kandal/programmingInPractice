
 
#include <stdio.h>
#include <string.h>
#include "utilities.h"

static void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {

    }
}
 
int readInt(const char *prompt, int min, int max)
{
    int value;
 
    while (1) {                       
        printf("%s", prompt);         
 
        
        if (scanf("%d", &value) != 1) {
            clearInputBuffer();
            printf("  Invalid input. Please enter a number.\n");
            continue;                 
        }
 
        clearInputBuffer();          
 
        
        if (value >= min && value <= max) {
            return value;
        }
 
        printf("  Invalid input. Please enter a value between %d and %d.\n",
               min, max);
    }
}
 
double readMoney(const char *prompt)
{
    double value;
 
    while (1) {
        printf("%s", prompt);
 
       
        if (scanf("%lf", &value) != 1) {
            clearInputBuffer();
            printf("  Invalid input. Please enter a number.\n");
            continue;
        }
 
        clearInputBuffer();
 
        if (value < 0) {
            printf("  Invalid input. The amount cannot be negative.\n");
            continue;
        }
 
        return value;
    }
}
 
void readText(const char *prompt, char *out, int size)
{
    
    do {
        printf("%s", prompt);
        fgets(out, size, stdin);
 
       
        out[strcspn(out, "\n")] = '\0';
 
        if (strlen(out) == 0) {
            printf("  This cannot be empty. Please try again.\n");
        }
    } while (strlen(out) == 0);
}
 
void printHeading(const char *title)
{
    printf("\n==========================================\n");
    printf("  %s\n", title);
    printf("==========================================\n");
}
 