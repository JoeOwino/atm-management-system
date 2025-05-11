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
        
        if (strcmp(userChecker.name, name) == 0)
        {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);

    return true;
}


void registerUser(char name[100], char pass[50])
{

    struct termios oflags, nflags;
    size_t len;

    do 
    {
        system("clear");
        printf("\n\n\t\t======= ATM =======\n");
        printf("\t\tMember Registration\n\n\n");

        printf("\t\tEnter Your name (no spaces or special charators):");
        // scanf("%s", name);

        // // Get input as a string
        if (fgets(name, 100, stdin) == NULL) {
            printf("\n\t\tError reading input. Please try again.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

       // Remove newline if present
        len = strlen(name);
        if (len > 0 && name[len-1] == '\n') {
            name[len-1] = '\0';
            len--;
        }
        
        // Check if input is empty
        if (len == 0) {
            printf("\n\t\tName cannot be empty. Please try again.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

        if (!isUnique_name(name)) {
            printf("\n\t\tName already taken. Please choose another name.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
            //continue;
        }

    } while (!isUnique_name(name) || len == 0);
    
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
    printf("\n\n\n\n\n\t\tEnter a password of your choice (No spaces):");
    scanf("%s", pass);

    printf("\n\t\t\t\tRegiatered Successfully\nName: %s\nPassword: %s\n", name, pass);

    printf("END\n");
}
