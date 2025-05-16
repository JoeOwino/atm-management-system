#include "header.h"

const char *RECORDS = "./data/records.txt";

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
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

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
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

        if (!getAccountFromFile(pf, userName, &cr)) {
            printf("failed to get the Account from the file");
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        if (!isUniqueAcc(r.accountNbr)) {
            printf("Account number already taken. Please enter a unique account number.\n");
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
            printf("Invalid country name. Please try again.\n");
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        if (isContainsSpaces(r.country)) {
            printf("Invalid country name. Please enter a valid country name without spaces.\n");
            printf("\t\tPress enter to continue...");
            getchar(); 
            continue;
        }

        break;

    }
    

    printf("\nEnter the phone number: ");
    scanf("%d", &r.phone);
    while (getchar() != '\n'); // Clear input buffer
    
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    while (getchar() != '\n'); // Clear input buffer
    
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice: ");
    scanf("%49s", r.accountType); // Added limit to prevent buffer overflow
    while (getchar() != '\n'); // Clear input buffer
    
    saveAccountToFile(pf, u, r);
    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}
