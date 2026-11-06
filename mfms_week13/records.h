/* records.h - the five MFMS record types */
#ifndef RECORDS_H
#define RECORDS_H

#define MAX_RECORDS 100

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int    id;
    char   name[30];
    char   department[20];
    double salary;
} Employee;

typedef struct {
    int  id;
    char name[40];
    char email[40];
    char phone[15];
    char town[20];
} Supplier;

typedef struct {
    int    id;
    char   description[40];
    double value;
    Date   acquired;          /* nested structure */
} Asset;

typedef struct {
    char   department[20];
    double allocated;
    double spent;
} Budget;

typedef struct {
    int    id;
    char   title[40];
    double budget;
    Date   startDate;         /* nested structures */
    Date   endDate;
} Project;

void recordsMenu(void);

#endif