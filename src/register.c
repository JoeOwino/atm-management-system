#include "header.h"

const bool isUnique_name(char name[50])
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        printf("%d %s %s\n", userChecker.id, userChecker.name, userChecker.password);
        
        if (strcmp(userChecker.name, name) == 0)
        {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);

    return true;
}


void registerUser(char name[50], char pass[50])
{

    struct termios oflags, nflags;

    do 
    {
        system("clear");

        printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t Enter Your name (no spaces or special charators):");

        scanf("%s", name);

        if (!isUnique_name(name)) {
            printf("\n\t\tName already taken. Please choose another name.\n");
            printf("\t\tPress Enter to continue...");
            continue;
        }

    } while (isUnique_name(name));
    
    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter a password of your choice (No spaces):");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    printf("\n\t\t\t\tRegiatered Successfully\nName: %s\nPassword: %s", name, pass);

}
