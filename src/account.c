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
