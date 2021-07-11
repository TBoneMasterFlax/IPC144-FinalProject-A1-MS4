/*
    ==================================================
    Assignment #1 Milestone #4:
    ==================================================
    Name   : Tuan Nguyen
    ID     : 109062166
    Email  : tnguyen140@myseneca.ca
    Section: NFF
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "commonHelpers.h"

#include <time.h>

#include <string.h>

#include <stdlib.h>

// -----------------------------------------
// Function Definitions

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}

// As demonstrated in the course notes: https://ict.senecacollege.ca//~ipc144/pages/content/formi.html#buf
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; // On purpose: do nothing 
    }
}

int getInteger(void)
{
    int intValue = 0;
    char newLine = 'n';
    do
    {
        scanf("%d%c", &intValue, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }
    } while (newLine != '\n');
    return intValue;
}

int getPositiveInteger(void)
{
    int intValue = 0;
    char newLine = 'n';
    do
    {
        scanf("%d%c", &intValue, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be a positive integer greater than zero: ");
        }
        else if (intValue <= 0)
        {
            printf("ERROR: Value must be a positive integer greater than zero: ");
        }
    } while (newLine != '\n' || intValue <= 0);
    return intValue;
}

double getDouble(void)
{
    double doubleValue = 0.0;
    char newLine = 'n';
    do
    {
        scanf("%lf%c", &doubleValue, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be a double floating-point number: ");
        }
    } while (newLine != '\n');
    return doubleValue;
}

double getPositiveDouble(void)
{
    double doubleValue = 0.0;
    char newLine = 'n';
    do
    {
        scanf("%lf%c", &doubleValue, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be a double floating-point number: ");
        }
        else if (doubleValue <= 0)
        {
            printf("ERROR: Value must be a positive double floating-point number: ");
        }
    } while (newLine != '\n' || doubleValue <= 0);
    return doubleValue;
}

int getIntFromRange(int lowerBound, int upperBound)
{
    int intValue = 0;
    char newLine;
    do
    {
        newLine = 'n';
        scanf("%d%c", &intValue, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }
        else if (intValue < lowerBound || intValue > upperBound)
        {
            printf("ERROR: Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (newLine != '\n' || intValue < lowerBound || intValue > upperBound);
    return intValue;
}

char getCharOption(char string[])
{
    char ch = 'c';
    char newLine = 'n';
    int i = 0;
    int flag = 1;
    int length = strlen(string);
    do
    {
        scanf("%c%c", &ch, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
        }
        else
        {
            for (i = 0; i < length; i++)
            {
                if (string[i] == ch)
                    flag = 0;
            }
        }
        if (flag == 1)
        {
            printf("ERROR: Character must be one of [%s]: ", string);
        }
    } while (flag);
    return ch;
}

void getCString(char* string, int lowerBound, int upperBound)
{
    char userString[151] = "\0";
    int flag = 1;
    int userLength;
    do
    {
        scanf("%[^\n]s", userString);
        clearStandardInputBuffer();
        userLength = strlen(userString);
        if (lowerBound == upperBound && userLength != lowerBound)
        {
            printf("ERROR: String length must be exactly %d chars: ", lowerBound);
        }
        else if (lowerBound != upperBound && userLength > upperBound)
        {
            printf("ERROR: String length must be no more than %d chars: ", upperBound);
        }
        else if (lowerBound != upperBound && userLength < lowerBound)
        {
            printf("ERROR: String length must be between %d and %d chars: ", lowerBound, upperBound);
        }
        else
        {
            strcpy(string, userString);
            flag = 0;
        }
    } while (flag);
}