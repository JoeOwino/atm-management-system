#include "header.h"

const char *RECORDS = "./data/records.txt";

bool isValidDate(struct Date *dt)
{
    char input[50]; 
    
    // Get input as a string
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return false; // Error in input
    }
    
    // Remove newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    // Check if input is empty
    if (strlen(input) == 0) {
        printf("Empty input. Please enter a date.\n");
        return false;
    }
    
    // Use sscanf instead of scanf to parse the input string
    int items = sscanf(input, "%d/%d/%d", &dt->month, &dt->day, &dt->year);
    if (items != 3) {
        printf("Invalid date format. Please use MM/DD/YYYY format.\n");
        fflush(stdout); 
        return false;
    }
    
    // Check if the date is valid
    if (dt->month < 1 || dt->month > 12) {
        printf("Invalid month. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->day < 1 || dt->day > 31) {
        printf("Invalid day. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->year < 1900 || dt->year > 2100) {
        printf("Invalid year. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if ((dt->month == 4 || dt->month == 6 || dt->month == 9 || dt->month == 11) && dt->day > 30) {
        printf("Invalid day for the given month. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->month == 2) {
        if ((dt->year % 4 == 0 && dt->year % 100 != 0) || (dt->year % 400 == 0)) {
            if (dt->day > 29) {
                printf("Invalid day for February in a leap year. Please enter a valid date.\n");
                fflush(stdout); 
                return false;
            }
        } else {
            if (dt->day > 28) {
                printf("Invalid day for February. Please enter a valid date.\n");
                fflush(stdout); 
                return false;
            }
        }
    }
    
    // Check if the date is in the future
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if (dt->year > tm->tm_year + 1900 ||
        (dt->year == tm->tm_year + 1900 && dt->month > tm->tm_mon + 1) ||
        (dt->year == tm->tm_year + 1900 && dt->month == tm->tm_mon + 1 && dt->day > tm->tm_mday)) {
        printf("Invalid date. The date cannot be in the future.\n");
        fflush(stdout); // Ensure the message is displayed
        return false;
    }
    
    return true;
}

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

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
            printf("\t\tPress any key to try again...");
            getchar(); 
            continue;
        }
        
        // Store the date in the record
        r.deposit.day = dt.day;
        r.deposit.month = dt.month;
        r.deposit.year = dt.year;
        
        break;
    }
    
    printf("\nEnter the account number: ");
    scanf("%d", &r.accountNbr);
    while (getchar() != '\n'); // Clear input buffer
    
    // Reset file position to beginning for reading
    rewind(pf);
    
    // Check if account exists
    bool accountExists = false;
    while (getAccountFromFile(pf, userName, &cr)) {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr) {
            printf("✖ This Account already exists for this user\n\n");
            accountExists = true;
            break;
        }
    }
    
    if (accountExists) {
        fclose(pf);
        success(u);
        return;
    }
    
    // Reset file position to end for appending
    fseek(pf, 0, SEEK_END);
    
    printf("\nEnter the country: ");
    scanf("%49s", r.country); // Added limit to prevent buffer overflow
    while (getchar() != '\n'); // Clear input buffer
    
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
