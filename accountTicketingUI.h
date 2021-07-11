/*
    ==================================================
    Assignment #1 Milestone #4:
    ==================================================
    Name   : Tuan Nguyen
    ID     : 109062166
    Email  : tnguyen140@myseneca.ca
    Section: NFF
*/

#ifndef ACCOUNTTICKETINGUI_H_
#define ACCOUNTTICKETINGUI_H_

#include "account.h"

void displayAccountSummaryHeader(void);
void displayAccountDetailHeader(void);
void displayAccountSummaryRecord(const struct Account* account);
void displayAccountDetailRecord(const struct Account* account);
void applicationStartup(struct Account accounts[], int size);
int menuLogin(struct Account accounts[], int size);
void menuAgent(struct Account accounts[], int size, const struct Account* userAccount);
int findAccountIndexByAcctNum(int accountNumber, const struct Account accounts[], int size, int prompt);
void displayAllAccountSummaryRecords(const struct Account accounts[], int size);
void displayAllAccountDetailRecords(const struct Account accounts[], int size);
// Pause execution until user enters the enter key
void pauseExecution(void);

#endif