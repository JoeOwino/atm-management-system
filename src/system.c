#include "header.h"

const char *RECORDS = "./data/records.txt";

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
            r.id,
	        u.id,
	        u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}


void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    struct Date dt;
    
    if (pf == NULL) { 
        printf("Error opening file.\n");
        return;
    }
    
    // Get the next available ID for the new record
    fseek(pf, 0, SEEK_END); 
    if (ftell(pf) == 0) {
        r.id = 1; // If file is empty, start with ID 1
    } else {
        fseek(pf, 0, SEEK_SET); // Reset file position to start
        while (getAccountFromFile(pf, userName, &cr)) {
            r.id = cr.id + 1; // Increment the last ID found
        }
    }
    r.userId = u.id; // Set the user ID for the new record


    while (1) {
        system("clear");
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): "); 
        
        if (!isValidDate(&dt)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }
        
        // Store the date in the record
        r.deposit.day = dt.day;
        r.deposit.month = dt.month;
        r.deposit.year = dt.year;
        
        break;
    }

    while (1)
    {
        system("clear");
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 

        printf("\nEnter the account number: ");
        if (!isvalidIntegerInput(&r.accountNbr)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        if (!isUniqueAcc(r.accountNbr)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        
        break;
    }
    
    // Reset file position to end for appending
    // fseek(pf, 0, SEEK_END);
    
    while (1)
    {
        system("clear");
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\nEnter the account number: %d", r.accountNbr);

        printf("\nEnter the country: ");
        if (!validateStringInput(r.country, 50)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        if (isContainsSpaces(r.country)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;

    }

    while (1)
    {
        system("clear");
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\nEnter the account number: %d", r.accountNbr);
        printf("\nEnter the country: %s", r.country);

        printf("\nEnter the phone number: ");

        if (!isValidPhoneNo(r.phone)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;

    }

    while (1)
    {
        system("clear");
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\nEnter the account number: %d", r.accountNbr);
        printf("\nEnter the country: %s", r.country);
        printf("\nEnter the phone number: %s", r.phone);

        printf("\nEnter amount to deposit: ");
        if (!isvalidAmount(&r.amount, 50, 1000000)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;

    }

    while (1)
    {
        system("clear");
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\nEnter the account number: %d", r.accountNbr);
        printf("\nEnter the country: %s", r.country);
        printf("\nEnter the phone number: %s", r.phone);
        printf("\nAmount deposited: $%.2f", r.amount);

        printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice: ");

        if (!validateStringInput(r.accountType, 20)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

   if (strcmp(r.accountType, "current") != 0 && strcmp(r.accountType, "saving") != 0 && strcmp(r.accountType, "fixed01") != 0 && strcmp(r.accountType, "fixed02") != 0 && strcmp(r.accountType, "fixed03") != 0) {
        
        printf("\n\t\tInvalid account type. Please select from the available options.");
        printf("\n\t\tPress enter to continue...");
        getchar();
        continue;
    }

        break;
    }
    

    saveAccountToFile(pf, u, r);
    fclose(pf);
}
