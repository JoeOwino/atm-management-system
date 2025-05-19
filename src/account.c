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
