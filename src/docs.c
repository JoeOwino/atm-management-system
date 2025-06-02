#include "header.h"

FILE *openFile(const char *filePath) {
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        printf("\t\tError! opening file: %s\n", filePath);
        exit(1);
    }
    return fp;
}

FILE *openUserFile(struct User u) {
    FILE *fp = fopen(USERS_FILE, "a+");

    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END); 
    if (ftell(fp) == 0) {
        system("clear");
        printf("\n\n\t\t=======================  ATM  ==========================\n");
        printf("\t\t                    Login to continue \n");
        printf("\t\t  You can exit the system at any point by pressing ctrl+c\n");
        printf("\t\t==========================================================\n");

        printf("\n\t\tNo user created yet.\n");
        printf("\t\tEnter 1 to register or any other character(s) to go to go back: ");
    
        char choice[10];
        fgets(choice, sizeof(choice), stdin);
    
        if (choice[0] == '1') {
            registerUser(u.name, u.password);
        } else {
            initMenu(&u);
        }
    }
    
    return fp;
}

FILE *openAccFile(struct User u, char *msg) {
    FILE *fp = fopen(RECORDS_FILE, "a+");

    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END); 
    if (ftell(fp) == 0) {
        printWelcomeMessage(u);
        
        printf("\n\t\t======= %s =======\n\n", msg);
        printf("\n\t\tNo Accounts record created yet.\n");
        printf("\t\tEnter 1 to create account or any other character(s) to go to main menu: ");
    
        char choice[10];
        fgets(choice, sizeof(choice), stdin);
    
        if (choice[0] == '1') {
            createNewAcc(u);
        } else {
         mainMenu(u);
        }
    }
    
    return fp;
}

void saveAccountToFile(FILE *fp, struct User u, struct Record r)
{
    fprintf(fp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n", 
        r.id, u.id, u.name, r.accountNbr, r.deposit.month, 
        r.deposit.day, r.deposit.year,r.country, r.phone, 
        r.amount,r.accountType);
}

int saveUpdatedRecord(FILE *fp, struct User u, struct Record updated, char *action)
{       
    FILE *temp = fopen("./data/temp.txt", "w");
    if (!temp) {
        perror("\t\tError opening temporary file for writing");
        fclose(fp);
        return 0;
    }
    
    struct Record r;
    struct User temp_user; // Create separate user variable for reading
    int found = 0;
    
    while (fscanf(fp, "%d %d %49s %d %d/%d/%d %49s %19s %lf %19s\n",
                  &r.id, &temp_user.id, temp_user.name, &r.accountNbr,
                  &r.deposit.month, &r.deposit.day, &r.deposit.year,
                  r.country, r.phone, &r.amount, r.accountType) == 11) {
        
        if (r.id == updated.id) {
            // Record found - update it
            r = updated;
            found = 1;
            
            if (strcmp(action, "delete") == 0) {
                continue; // Skip writing this record (delete operation)
            }
            
            // For updated records, use the passed user info
            fprintf(temp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n",
                    r.id, u.id, u.name, r.accountNbr,
                    r.deposit.month, r.deposit.day, r.deposit.year,
                    r.country, r.phone, r.amount, r.accountType);
        } else {
            // For non-matching records, keep original user info
            fprintf(temp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n",
                    r.id, temp_user.id, temp_user.name, r.accountNbr,
                    r.deposit.month, r.deposit.day, r.deposit.year,
                    r.country, r.phone, r.amount, r.accountType);
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if (!found) {
        printf("\t\tRecord not found.\n");
        remove("./data/temp.txt");
        return 0;
    }
    
    // Replace original file with updated temp file
    if (remove(RECORDS_FILE) != 0) {
        perror("\t\tError removing original file");
        remove("./data/temp.txt");
        return 0;
    }
    
    if (rename("./data/temp.txt", RECORDS_FILE) != 0) {
        perror("\t\tError renaming temp file");
        return 0;
    }
    
    return 1;
}

void writeTrans(struct Transaction t) {
    FILE *fp;
    
    if ((fp = fopen(TRANS_FILE, "a")) == NULL)
    {
        printf("\t\tError! opening file\n");
        exit(1);
    }
    
    fprintf(fp, "%d %d %d/%d/%d %d %s %lf\n", t.id, t.userId, t.date.month, t.date.day, t.date.year, t.accountNbr, t.type, t.amount);
    
    fclose(fp);
}

bool getAccount(int acc, struct Record *r, struct User *u, int userID)
{
    struct User tempUser = *u; 
    
    FILE *fp;
    if ((fp = fopen(RECORDS_FILE, "r")) == NULL) {
        printf("\t\tError! opening file");
        return false;
    }
    
    while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n",
           &r->id, &u->id, u->name, &r->accountNbr,
           &r->deposit.month, &r->deposit.day, &r->deposit.year,
           r->country, r->phone, &r->amount, r->accountType) == 11) {
            
        if (r->accountNbr == acc && userID == u->id) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);

    *u = tempUser; 
    return false;
}

const char *getPassword(struct User *u)
{
    FILE *fp = openFile(USERS_FILE);
    struct User userChecker;


    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        // printf("%d %s %s\n", userChecker.id, userChecker.name, userChecker.password);
        
        if (strcmp(userChecker.name, u->name) == 0)
        {
            u -> id = userChecker.id;
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);

    return "no user found";
}

int getUserID()
{
    FILE *fp = openFile(USERS_FILE);

    struct User userChecker;
    
    int id = 0;
    
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (userChecker.id > id)
        {
            id = userChecker.id;
        }
    }
    
    fclose(fp);
    
    return id + 1; // Increment the highest ID by 1
}

void writeUser(struct User u)
{
    FILE *fp;
    
    if ((fp = fopen(USERS_FILE, "a")) == NULL)
    {
        printf("\t\tError! opening file\n");
        exit(1);
    }
    
    fprintf(fp, "%d %s %s\n", u.id, u.name, u.password);
    
    fclose(fp);
}

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

