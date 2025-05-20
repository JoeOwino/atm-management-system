#include "header.h"

bool getAccount(int acc, struct Record *r, struct User *u)
{
    FILE *fp;
    if ((fp = fopen("./data/records.txt", "r")) == NULL) {
        printf("Error! opening file");
        return false;
    }
    
    while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s\n",
           &r->id, &u->id, u->name, &r->accountNbr,
           &r->deposit.month, &r->deposit.day, &r->deposit.year,
           r->country, r->phone, &r->amount, r->accountType) == 11) {
        if (r->accountNbr == acc) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

void updateAccount(struct User u)
{
        struct Record r;
        int acc;
        int option;

        while (1)
        {
            system("clear");
            printf("\n\n\t\t======= Acount Update =======\n\n");
            printf("\n\t\t-->> Please enter the account number to update: \n");

            if (!isvalidIntegerInput(&acc)) {
                printf("\t\tPress enter to continue...");
                getchar();
                continue;
            }
            
            if (!getAccount(acc, &r, &u)) {
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
            printf("\n\n\t\t======= Acount Update =======\n\n");
            printf("\n\t\t-->> Please enter the account number to update: %d\n", acc);
            printf("\n\t\t- Select the account information you want to update: \n");
            printf("\n\t\t[1]- Phone Noumber: \n");
            printf("\n\t\t[2]- County\n");

            printf("\n\t\tEnter choice: ");

            if (!isValidMenuInput(1, 2, &option)) {
                printf("\t\tPress Enter to continue...");
                getchar();
                continue;
            }

            break;
        }

        switch (option)
        {
        case 1:
            /* Phone Number */
            while (1)
            {
                system("clear");
                printf("\n\n\t\t======= Update Phone numebre for Account %d =======\n\n", acc);

                printf("\n\t\t-->> Please enter the new phone number: ");
                if (!isValidPhoneNo(r.phone)) {
                    printf("\t\tPress enter to continue...");
                    getchar();
                    continue;
                }

                break;
            }
        
            break;

        case 2:
            /* Country */

            break;
        
        default:
            printf("Invalid operation!\n");
            break;
        }

        
}

void printAccount(struct Record r, struct User u)
{
    system("clear");
    printf("\n=== Account Details ===\n");
    printf("Record ID: %d\n", r.id);
    printf("User ID: %d\n", u.id);
    printf("Name: %s\n", u.name);
    printf("Account Number: %d\n", r.accountNbr);
    printf("Date: %d/%d/%d\n", r.deposit.month, r.deposit.day, r.deposit.year);
    printf("Country: %s\n", r.country);
    printf("Phone: %s\n", r.phone);
    printf("Balance: %.2lf\n", r.amount);
    printf("Account Type: %s\n", r.accountType);
    printf("======================\n");
}
