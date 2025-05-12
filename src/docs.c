#include "header.h"

int getID(char *file)
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
