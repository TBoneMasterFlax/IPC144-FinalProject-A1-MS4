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
#include "account.h"
#include "accountTicketingUI.h"
#include <string.h>
#include <stdlib.h>

void displayAccountSummaryHeader(void)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* account)
{
    char accountType[] = "CUSTOMER";
    if (account->account_type == 'A')
    {
        strcpy(accountType, "AGENT");
    }
    printf("%05d %-9s %5d\n", account->account_number, accountType, account->demographic.birth_year);
}

void displayAccountDetailRecord(const struct Account* account)
{
    char accountType[] = "CUSTOMER";
    if (account->account_type == 'A')
    {
        strcpy(accountType, "AGENT");
    }
    char hiddenPassword[9];
    strcpy(hiddenPassword, account->user_login.password);
    int passwordLength = strlen(hiddenPassword);
    int i;
    for (i = 0; i < passwordLength; i++)
    {
        if (i % 2 != 0)
        {
            hiddenPassword[i] = '*';
        }
    }
    printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", account->account_number, accountType, account->demographic.birth_year, account->demographic.income, account->demographic.country, account->user_login.display_name, account->user_login.login_name, hiddenPassword);
}

void applicationStartup(struct Account accounts[], int size)
{
    int userIndex = -1;
    int flag = 1;
    do
    {
        userIndex = menuLogin(accounts, size);
        if (userIndex < 0)
        {
            flag = 0;
        }
    } while (flag);
}

int menuLogin(struct Account accounts[], int size)
{
    int userIndex;
    int selection, flag = 1;
    int accountNumber, i = 0;
    char exit;
    do
    {
        userIndex = -1;
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 1);
        switch (selection)
        {
        case 0:
            printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
            exit = getCharOption("yYnN");
            putchar('\n');
            if (exit == 'y' || exit == 'Y')
            {
                printf("==============================================\n");
                printf("Account Ticketing System - Terminated\n");
                printf("==============================================\n");
                flag = 0;
            }
            break;
        case 1:
            printf("\nEnter your account#: ");
            accountNumber = getPositiveInteger();
            for (i = 0; i < size; i++)
            {
                if (accountNumber == accounts[i].account_number)
                {
                    userIndex = i;
                    break;
                }
            }
            if (userIndex < 0)
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            else
            {
                if (accounts[userIndex].account_type == 'A')
                {
                    putchar('\n');
                    menuAgent(accounts, size, &accounts[userIndex]);
                }
                else
                {
                    printf("\nCUSTOMER: home menu currently unavailable...\n\n");
                    pauseExecution();
                }
                flag = 0;
            }
            break;
        default:
            break;
        }
    } while (flag);
    return userIndex;
}

void menuAgent(struct Account accounts[], int size, const struct Account* userAccount)
{
    int selection, flag = 1;
    int accountNumber, i = 0;
    int firstEmptyIndex, arrayIndex;
    char removeAccount;
    do
    {
        firstEmptyIndex = -1;
        for (i = 0; i < size; i++)
        {
            if (accounts[i].account_number <= 0)
            {
                firstEmptyIndex = i;
                break;
            }
        }
        arrayIndex = -1;
        printf("AGENT: %s (%d)\n", userAccount->user_login.display_name, userAccount->account_number);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: summary view\n");
        printf("5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 5);
        switch (selection)
        {
        case 0:
            printf("\n### LOGGED OUT ###\n\n");
            flag = 0;
            break;
        case 1:
            if (firstEmptyIndex < 0)
            {
                printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
                pauseExecution();
            }
            else
            {
                getAccount(&accounts[firstEmptyIndex]);
                getUserLogin(&accounts[firstEmptyIndex].user_login);
                getDemographic(&accounts[firstEmptyIndex].demographic);
                printf("*** New account added! ***\n\n");
                pauseExecution();
            }
            break;
        case 2:
            printf("\nEnter the account#: ");
            accountNumber = getPositiveInteger();
            for (i = 0; i < size; i++)
            {
                if (accountNumber == accounts[i].account_number)
                {
                    arrayIndex = i;
                    break;
                }
            }
            if (arrayIndex < 0)
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            else
            {
                updateAccount(&accounts[arrayIndex]);
            }
            putchar('\n');
            break;
        case 3:
            printf("\nEnter the account#: ");
            accountNumber = getPositiveInteger();
            for (i = 0; i < size; i++)
            {
                if (accountNumber == accounts[i].account_number)
                {
                    arrayIndex = i;
                    break;
                }
            }
            if (arrayIndex < 0)
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            else
            {
                if (accounts[arrayIndex].account_number == userAccount->account_number)
                {
                    printf("\nERROR: You can't remove your own account!\n\n");
                    pauseExecution();
                }
                else
                {
                    displayAccountDetailHeader();
                    displayAccountDetailRecord(&accounts[arrayIndex]);
                    printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
                    removeAccount = getCharOption("YN");
                    if (removeAccount == 'Y')
                    {
                        accounts[arrayIndex].account_number = 0;
                        printf("\n*** Account Removed! ***\n\n");
                        pauseExecution();
                    }
                    else
                    {
                        printf("\n*** No changes made! ***\n\n");
                        pauseExecution();
                    }
                }
            }
            break;
        case 4:
            putchar('\n');
            displayAllAccountSummaryRecords(accounts, size);
            putchar('\n');
            pauseExecution();
            break;
        case 5:
            putchar('\n');
            displayAllAccountDetailRecords(accounts, size);
            putchar('\n');
            pauseExecution();
            break;
        default:
            break;
        }
    } while (flag);
}

int findAccountIndexByAcctNum(int accountNumber, const struct Account accounts[], int size, int prompt)
{
    return 0;
}

void displayAllAccountSummaryRecords(const struct Account accounts[], int size)
{
    int i = 0;
    displayAccountSummaryHeader();
    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number > 0)
        {
            displayAccountSummaryRecord(&accounts[i]);
        }
    }
}

void displayAllAccountDetailRecords(const struct Account accounts[], int size)
{
    int i = 0;
    displayAccountDetailHeader();
    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number > 0)
        {
            displayAccountDetailRecord(&accounts[i]);
        }
    }
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
}