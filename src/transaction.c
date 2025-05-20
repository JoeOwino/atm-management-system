#include "header.h"

void createTransaction(struct User u)
{
    struct Transaction t;
    struct Record r;
    int option;

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

    
    
}

