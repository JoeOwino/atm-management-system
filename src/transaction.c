#include "header.h"

void createTransaction(struct User u)
{
    struct Transaction t;
    struct Record r;
    int option;
    struct Date dt;

    t.id = getTransID("./data/transactions.txt");
    t.userId = u.id;

    while (1) 
    {
        system("clear");
        printf("\n\n\t\t======= Create  Transaction =======\n");
        printf("\n\t\t-->> Selcet Transction Type: ");
        printf("\n\t\t[1]- Deposit\n");
        printf("\n\t\t[2]- Withdraw\n");
        printf("\n\t\tEnter Chioce: ");

        if (!isValidMenuInput(1, 2, &option)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;
    }

    while (1)
    {
        system("clear");
        printf("\n\n\t\t======= Create  Transaction =======\n");
        if (option == 1) {
            printf("\n\t\t-->>Make Deposit\n");
            strcpy(t.type, "DEPOSIT");
        } else {
            printf("\n\t\t-->>Make a Withdrawal \n");
            strcpy(t.type, "WITHDRAWAL");
        }

        printf("\n\t\t-->> Please enter the Account Number: ");
        if (!isvalidIntegerInput(&t.accountNbr)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        if (!getAccount(t.accountNbr, &r, &u, u.id)) {
            printf("\n\tAccount not found!\n"); 
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;
    }

    while (1)
    {
        system("clear");
        printf("\n\n\t\t======= Create  Transaction =======\n");
        printf("\n\n\t\tTransaction: %s", t.type);
        printf("\n\n\t\tAccount: %d", t.accountNbr);

        printf("\n\t\t-->> Please enter the transaction date: ");
        if (!isValidDate(&dt)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        } 

        t.date.month = dt.month;
        t.date.day = dt.day;
        t.date.year = dt.year;

        break;
    }

    while (1)
    {
        system("clear");
        printf("\n\n\t\t======= Create  Transaction =======\n");
        printf("\n\n\t\tTransaction: %s", t.type);
        printf("\n\n\t\tAccount: %d", t.accountNbr);
        printf("\n\n\t\tDated: %d/%d/%d", t.date.month, t.date.day, t.date.year);

        printf("\n\t\t-->> Please enter the amount: ");
        if (!isvalidAmount(&t.amount, 50, 999999999)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        } 

        break;
    }

    writeTrans(t);
    printf("\n\n\t\t======= Transaction Created =======\n");

    printf("\n\n\t\tID: %d", t.id);
    printf("\n\n\t\tUser ID: %d", t.userId);
    printf("\n\n\t\tBy: %s", u.name);
    printf("\n\n\t\tDate: %d/%d/%d", t.date.month, t.date.day, t.date.year);
    printf("\n\n\t\tAccount: %d", t.accountNbr);
    printf("\n\n\t\tTransaction: %s", t.type);
    printf("\n\n\t\tDated: %d/%d/%d", t.date.month, t.date.day, t.date.year);
    printf("\n\n\t\tAmount: %lf\n", t.amount);
    
}

