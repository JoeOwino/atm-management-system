#include "header.h"

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    struct Date dt;

    FILE *fp = fopen(RECORDS_FILE, "a+");
    if (fp == NULL) { 
        printf("\n\nError opening file.\n");
        return;
    }
    
    // Get the next available ID for the new record
    fseek(fp, 0, SEEK_END); 
    if (ftell(fp) == 0) {
        r.id = 1; // If file is empty, start with ID 1
    } else {
        fseek(fp, 0, SEEK_SET); // Reset file position to start
        while (getAccountFromFile(fp, userName, &cr)) {
            r.id = cr.id + 1; // Increment the last ID found
        }
    }
    r.userId = u.id; // Set the user ID for the new record

    while (1) {
        printWelcomeMessage(u.name);

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
        printWelcomeMessage(u.name);
        
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d\n", dt.month, dt.day, dt.year); 

        printf("\n\t\tEnter the account number: ");
        if (!isvalidIntegerInput(&r.accountNbr)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        if (!isUniqueAcc(r.accountNbr)) {
            printf("\n\t\tAccount number already exists. Please enter a unique account number.\n");
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        
        break;
    }
    
    while (1)
    {
        printWelcomeMessage(u.name);
        
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\n\t\tEnter the account number: %d\n", r.accountNbr);

        printf("\n\t\tEnter the country: ");
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
        printWelcomeMessage(u.name);
        
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\n\t\tEnter the account number: %d", r.accountNbr);
        printf("\n\t\tEnter the country: %s\n", r.country);

        printf("\n\t\tEnter the phone number: ");

        if (!isValidPhoneNo(r.phone)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;

    }

    while (1)
    {
        printWelcomeMessage(u.name);
        
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\n\t\tEnter the account number: %d", r.accountNbr);
        printf("\n\t\tEnter the country: %s", r.country);
        printf("\n\t\tEnter the phone number: %s\n", r.phone);

        printf("\n\t\tEnter amount to deposit: $");
        if (!isvalidAmount(&r.amount, 50, 1000000)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;

    }

    while (1)
    {
        printWelcomeMessage(u.name);
        
        printf("\t\t====== Create new account =====\n\n");
        printf("\t\tEnter the date of deposit (MM/DD/YYYY): %d/%d/%d", dt.month, dt.day, dt.year); 
        printf("\n\t\tEnter the account number: %d", r.accountNbr);
        printf("\n\t\tEnter the country: %s", r.country);
        printf("\n\t\tEnter the phone number: %s", r.phone);
        printf("\n\t\tAmount deposited: $%.2f\n", r.amount);

        printf("\n\t\tChoose the type of account:\n\t\t\t-> saving\n\t\t\t-> current\n\t\t\t-> fixed01(for 1 year)\n\t\t\t-> fixed02(for 2 years)\n\t\t\t-> fixed03(for 3 years)\n\n\t\t\tEnter your choice: ");

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
    

    saveAccountToFile(fp, u, r);
    fclose(fp);
}

void updateAccount(struct User u)
{
        struct Record r;
        int acc;
        int option;
        bool isUpdated = false;

        FILE *fp = openAccFile(u, "Update Accounts");
        if (fp == NULL) { 
            return;
        }

        while (1)
        {
            printWelcomeMessage(u.name);
            
            printf("\n\n\t\t======= Acount Update =======\n\n");
            printf("\n\t\t-->> Please enter the account number to update: ");

            if (!isvalidIntegerInput(&acc)) {
                printf("\t\tPress enter to continue...");
                getchar();
                continue;
            }
            
            if (!getAccountByID(fp, u.id, &r, acc)) {
                printf("\n\t\tAccount not found!\n");
                printf("\t\tPress enter to continue...");
                getchar();
                continue;
            } 

            isUpdated = true;
            break;
        }
        
        
        while (1)
        {
            printWelcomeMessage(u.name);
            
            printf("\n\n\t\t======= Acount Update =======\n\n");
            printf("\n\t\t-->> Please enter the account number to update: %d\n", acc);
            printf("\n\t\t- Select the account information you want to update: \n");
            printf("\n\t\t[1]- Phone Noumber (%s)\n", r.phone);
            printf("\n\t\t[2]- County (%s)\n", r.country);

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
                printWelcomeMessage(u.name);
                
                printf("\n\n\t\t======= Update Phone numebre for Account %d =======\n\n", acc);

                printf("\n\t\t-->> Please enter the new phone number: ");
                if (!isValidPhoneNo(r.phone)) {
                    printf("\t\tPress enter to continue...");
                    getchar();
                    continue;
                }

                break;
            }
        
            isUpdated = true;
            break;

        case 2:
            /* Country */
            while (1)
            {
                printWelcomeMessage(u.name);
                
                printf("\n\n\t\t======= Update Counry for Account %d =======\n\n", acc);

                printf("\n\t\t-->> Please enter the new country: ");

                if (!validateStringInput(r.country, sizeof(r.country))) {
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
            
            break;
        
        default:
            printf("\t\tInvalid operation!\n");
            break;
        }

    if (!isUpdated) {
        printf("\n\t\tNo changes made to the account.\n");
        printf("\t\tPress enter to continue...");
        getchar();
        return;
    }

    int isSaved = saveUpdatedRecord(fp, u, r, "update");
    if (isSaved == 0) {
        printf("\t\tfailed to update account\n");
        return;
    }

    printf("\n\t\tAccount updated successfully!\n");
}

void printAccount(struct Record r, struct User u)
{
    printf("\t\tAccount number: %d\n\t\tDeposit Date: %d/%d/%d \n\t\tcountry: %s \n\t\tPhone number: %s \n\t\tAmount deposited: $%.2f \n\t\tType Of Account: %s\n",
            r.accountNbr,
            r.deposit.day,
            r.deposit.month,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void removeAccount(struct User u)
{
    struct Record r;
    int acc;
    int option;

    FILE *fp = openAccFile(u, "Account Deletion");
    if (fp == NULL) { 
        return;
    }

    while (1)
    {
        printWelcomeMessage(u.name);
        printf("\n\n\t\t======= Account Deletion =======\n\n");
        printf("\n\t\t-->> Please enter the account number to delete: ");

        if (!isvalidIntegerInput(&acc)) {
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        }
        
        if (!getAccountByID(fp, u.id, &r, acc)) { 
            printf("\n\tAccount not found!\n");
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        } 

        break;
    }

    while (1) {
        printWelcomeMessage(u.name);
        printf("\n\n\t\t======= Acount Deletion =======\n\n");
        printf("\n\t\t-->> This action will is not reverseble\n");
        printf("\n\t\tAre you sure you want to delete account %d? \n", acc);
        printf("\n\t\t[1]- Cancel\n");
        printf("\n\t\t[2]- Confirm\n");
        printf("\n\t\tEnter choice: ");

        if (!isValidMenuInput(1, 2, &option)) {
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

        break;
    }

    if (option == 0) {
        printf("\n\t\tAccount deletion cancelled.\n");
        return;
    }

    saveUpdatedRecord(fp, u, r, "delete");
    printf("\n\t\tAccount deleted successfully!\n");
}   

void transferOwnership(struct User u)
{
    struct Record r;
    int acc;
    int option;

    FILE *fp = openAccFile(u, "Account Transfer");
    if (fp == NULL) { 
        return;
    }

    while (1)
    {
        printWelcomeMessage(u.name);
        printf("\n\n\t\t======= Account Transfer =======\n\n");
        printf("\n\t\t-->> Please enter the account number to transfer: ");

        if (!isvalidIntegerInput(&acc)) {
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        }
        
        if (!getAccountByID(fp, u.id, &r, acc)) {
            printf("\n\tAccount not found!\n");
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        } 

        break;
    }

    while (1)
    {
        printWelcomeMessage(u.name);
    
        printf("\n\n\t\t======= Acount Transfer =======\n\n");
        printf("\n\t\t-->> Please enter the account number to transfer: %d\n", acc);
        printf("\n\t\t-->> Please enter the new owner name: ");

        if (!validateStringInput(r.name, 50)) {
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        }

        if (isContainsSpaces(r.name)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        if (isUniqueName(r.name, &u)) {
            printf("Name Does not exist. Please choose another New Owner.\n");
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        }

        if (isContainsSpaces(r.name)) {
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }
        
        break;
    }

    while (1) {
        printWelcomeMessage(u.name);
        
        printf("\n\n\t\t======= Acount Transfer =======\n\n");
        printf("\n\t\t-->> This action will is not reverseble\n");
        printf("\n\t\tAre you sure you want to transfer ownership of account %d to %s? \n", acc, r.name);
        printf("\n\t\t[1]- Cancel\n");
        printf("\n\t\t[2]- Confirm\n");
        printf("\n\t\tEnter choice: ");

        if (!isValidMenuInput(1, 2, &option)) {
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

        break;
    }

    if (option == 0) {
        printf("\n\t\tAccount transfer cancelled.\n");
        return;
    }

    strcpy(r.name, u.name);
    r.userId = u.id;

    saveUpdatedRecord(fp, u, r, "transfer");
    printf("\n\t\tAccount transfered successfully!  to %d: %s\n", u.id, u.name);
}

void checkAccounts(struct User u)
{
    struct Record r;
    int acc;
    int option;

    FILE *fp = openAccFile(u, "Account Check");
    if (fp == NULL) { 
        return;
    }

    while (1)
    {
        printWelcomeMessage(u.name);        
        printf("\n\n\t\t======= Acount Check =======\n\n");
        printf("\n\t\t-->> Please enter the account number to check: ");

        if (!isvalidIntegerInput(&acc)) {
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        }
        
        if (!getAccountByID(fp, u.id, &r, acc)) {
            printf("\n\t\tAccount not found!\n");
            printf("\t\tPress enter to continue...");
            getchar();
            continue;
        } 

        break;
    }

    printWelcomeMessage(u.name);
    printf("\n\t\t====== Account Details =======\n\n");
    printAccount(r, u);

    double interest = calculateInterest(r.accountNbr, r.accountType, r.amount);
    if (interest == 0.0) {
        printf("\t\tYou will not get interests because the account is of type %s\n", r.accountType);
        return;
    }

    if (strcmp(r.accountType, "saving") == 0) {
        printf("\n\n\t\tYou will get %.2lf as interest on day %d of every month\n", interest, r.deposit.day);
    } else {
        printf("\n\n\t\tYou will get %.2lf as interest on %d/%d/%d\n", interest, r.deposit.month, r.deposit.day, r.deposit.year+1);
    }
}

double calculateInterest(int accNbr, char *accType, double amount)
{
    double interestRate = 0.0;

    if (strcmp(accType, "saving") == 0) {
        interestRate = 0.07 / 12; 
    } else if (strcmp(accType, "fixed01") == 0) {
        interestRate = 0.04;
    } else if (strcmp(accType, "fixed02") == 0) {
        interestRate = 0.05; 
    } else if (strcmp(accType, "fixed03") == 0) {
        interestRate = 0.08; 
    }

    return amount * interestRate;

}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *fp = openAccFile(u, "List of Accounts");
    if (fp == NULL) { 
        return;
    }

    printWelcomeMessage(u.name);        
    
    printf("\t\t====== List of Account =====\n\n");
    rewind(fp);  // Ensure we're reading from the start

    while (getAccountFromFile(fp, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printAccount(r, u);
            printf("\n\t\t=======================================\n\n");
        }
    }

    fclose(fp);
}

