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
        printWelcomeMessage(u);
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
        printWelcomeMessage(u);
        
        printf("\n\n\t\t======= Create  Transaction =======\n");
        if (option == 1) {
            printf("\n\t\t-->>Make Deposit\n");
            strcpy(t.type, "DEPOSIT");
        } else {
            printf("\n\t\t-->>Make a Withdrawal\n");
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

        if (strcmp(r.accountType, "fixed01") || strcmp(r.accountType, "fixed02") || strcmp(r.accountType, "fixed03")) {
            printf("\n\t\tThis account is not eligible for transactions!\n");
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        }

        break;
    }


    while (1)
    {
        printWelcomeMessage(u);
        
        printf("\n\n\t\t======= Create  Transaction =======\n");
        printf("\n\n\t\tTransaction: %s", t.type);
        printf("\n\n\t\tAccount: %d\n", t.accountNbr);

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
        printWelcomeMessage(u);
        
        printf("\n\n\t\t======= Create  Transaction =======\n");
        printf("\n\n\t\tTransaction: %s", t.type);
        printf("\n\n\t\tAccount: %d", t.accountNbr);
        printf("\n\n\t\tDated: %d/%d/%d\n", t.date.month, t.date.day, t.date.year);

        printf("\n\t\t-->> Please enter the amount: ");
        if (!isvalidAmount(&t.amount, 50, 999999999)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        } 

        if (strcmp(t.type, "WITHDRAWAL") == 0 && t.amount > r.amount) {
            printf("\n\t\tInsufficient funds for withdrawal!\n");
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        }

        break;
    }

    if (strcmp(t.type, "WITHDRAWAL") == 0) {
        r.amount -= t.amount; // Deduct amount for withdrawal
    } else {
        r.amount += t.amount; // Add amount for deposit
    }

    writeTrans(t);
    saveUpdatedRecord(r, u, "update");
    printf("\n\n\t\t======= Transaction Created =======\n");
}

