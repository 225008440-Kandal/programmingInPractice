/* ============================================================
   employees.h  -  Employee Management module
   PAP521S Project A - Municipal Financial Management System

   A header file declares WHAT this module offers to the rest
   of the program. It contains no function bodies - only the
   signatures other files are allowed to call.
   ============================================================ */

#ifndef EMPLOYEES_H          /* header guard: if EMPLOYEES_H is not defined... */
#define EMPLOYEES_H          /* ...define it now. This stops the compiler from */
                             /* reading this file twice and complaining about   */
                             /* duplicate declarations.                         */

/* Entry point. main.c calls this when the user picks
   option 1 on the main menu. */
void employeeMenu(void);

/* Getters used by reports.c.
   Reports has no data of its own - it reads ours through these.
   DO NOT change these names or return types: Student 5's code
   is written against them. */
int    getEmployeeCount(void);          /* how many employees are stored     */
double getEmployeeSalary(int i);        /* GROSS salary of employee number i */
const char* getEmployeeName(int i);     /* name of employee number i         */

#endif                       /* closes the #ifndef above */
