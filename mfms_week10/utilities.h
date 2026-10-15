#ifndef UTILS_H
#define UTILS_H
 

int readInt(const char *prompt, int min, int max);
 

double readMoney(const char *prompt);
 

void readText(const char *prompt, char *out, int size);
 

void printHeading(const char *title);
 
#endif