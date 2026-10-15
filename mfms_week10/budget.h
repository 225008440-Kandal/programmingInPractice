#ifndef BUDGET_H
#define BUDGET_H
void budgetMenu(void);
int getDepartmentCount(void);
double getAllocated(int i);
double getExpenditure(int i);
const char* getDepartmentName(int i);
/* File handling - Week 10 */
void saveBudgets(void);
void loadBudgets(void);
#endif
 