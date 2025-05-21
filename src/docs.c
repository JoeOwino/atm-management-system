#include "header.h"

int getUserID(char *file)
{
    FILE *fp;
    struct User userChecker;
    
    if ((fp = fopen(file, "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }
    
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
    FILE *fp;
    struct Transaction t;
    
    if ((fp = fopen(file, "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }
    
    int id = 0;
    
    while (fscanf(fp, "%d %d/%d/%d %d, %s %lf", &t.id, &t.date.month, &t.date.day, &t.date.year, &t.accountNbr, t.type, &t.amount) != EOF)
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
        printf("Error! opening file\n");
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


#define RECORDS_FILE "./data/records.txt"

// Updates the record for a given account in the file
int saveUpdatedRecord(struct Record updated, struct User u) 
{
    FILE *fp = fopen(RECORDS_FILE, "r");
    if (!fp) {
        perror("Error opening file for reading");
        return 0;
    }

    FILE *temp = fopen("./data/temp.txt", "w");
    if (!temp) {
        perror("Error opening temporary file for writing");
        fclose(fp);
        return 0;
    }

    struct Record r;
    int found = 0;

   while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s\n", 
                 &r.id, &u.id, u.name, &r.accountNbr, 
                 &r.deposit.month, &r.deposit.day, &r.deposit.year, 
                 r.country, r.phone, &r.amount, r.accountType) == 11) {

        if (r.id == updated.id) {
            r = updated;
            found = 1;
        }

        fprintf(temp, "%d %d %s %d %d/%d/%d %s %s %lf %s\n", 
                 r.id, u.id, u.name, r.accountNbr, 
                 r.deposit.month, r.deposit.day, r.deposit.year, 
                 r.country, r.phone, r.amount, r.accountType);
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        printf("Record not found.\n");
        remove("data/temp.txt");
        return 0;
    }

    // Replace original file with updated temp file
    remove(RECORDS_FILE);
    rename("data/temp.txt", RECORDS_FILE);

    return 1;
}

void writeTrans(struct Transaction t) {
    FILE *fp;
    
    if ((fp = fopen("./data/transactions.txt", "a")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }
    
    fprintf(fp, "%d %d/%d/%d %d, %s %lf", t.id, t.date.month, t.date.day, t.date.year, t.accountNbr, t.type, t.amount);
    
    fclose(fp);
}

