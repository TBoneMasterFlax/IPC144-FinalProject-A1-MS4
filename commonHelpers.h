/*
    ==================================================
    Assignment #1 Milestone #4:
    ==================================================
    Name   : Tuan Nguyen
    ID     : 109062166
    Email  : tnguyen140@myseneca.ca
    Section: NFF
*/

#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_

// -----------------------------------------
// Function Prototypes
int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
double getDouble(void);
double getPositiveDouble(void);
int getIntFromRange(int lowerBound, int upperBound);
char getCharOption(char string[]);
void getCString(char* string, int lowerBound, int upperBound);

#endif