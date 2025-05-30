#include "header.h"

const char *RECORDS = "./data/records.txt";
const char *USERS = "./data/users.txt";

FILE *openUserFile(const char *filePath) {
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        printf("\t\tError! opening file: %s\n", filePath);
        exit(1);
    }
    return fp;
}

const char *getPassword(struct User *u)
{
    FILE *fp = openUserFile("./data/users.txt");
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

int getUserID(char *file)
{
    FILE *fp = openUserFile(file);

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

int getTransID(char *file)
{
    FILE *fp = openUserFile(file);
    struct Transaction t;
    
    int id = 0;
    
    while (fscanf(fp, "%d %d %d/%d/%d %d %s %lf", &t.id, &t.userId, &t.date.month, &t.date.day, &t.date.year, &t.accountNbr, t.type, &t.amount) != EOF)
    {
        if (t.id > id)
        {
            id = t.id;
        }

    }
    
    fclose(fp);
    
    return id + 1; // Increment the highest ID by 1
}

void writeUser(struct User u)
{
    FILE *fp;
    
    if ((fp = fopen("./data/users.txt", "a")) == NULL)
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



int saveUpdatedRecord(struct Record updated, struct User u, char *action)
{

    
    FILE *fp = fopen(RECORDS, "r");
    if (!fp) {
        perror("\t\tError opening file for reading");
        return 0;
    }
    
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
    if (remove(RECORDS) != 0) {
        perror("\t\tError removing original file");
        remove("./data/temp.txt");
        return 0;
    }
    
    if (rename("./data/temp.txt", RECORDS) != 0) {
        perror("\t\tError renaming temp file");
        return 0;
    }
    
    return 1;
}

void writeTrans(struct Transaction t) {
    FILE *fp;
    
    if ((fp = fopen("./data/transactions.txt", "a")) == NULL)
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
    if ((fp = fopen("./data/records.txt", "r")) == NULL) {
        printf("\t\tError! opening file");
        return false;
    }
    
    while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s\n",
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

