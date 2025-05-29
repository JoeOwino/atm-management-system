#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char name[50], char pass[50])
{    
    struct termios oflags, nflags;
    struct User u;



    while (1)
    {
        system("clear");
        printf("\n\n\t\t=======================  ATM  ==========================\n");
        printf("\t\t                    Login to continue \n");
        printf("\t\t  Yuo can exit the system at any point by prssing ctr+c\n");
        printf("\t\t==========================================================\n");

        printf("\n\t\tEnter Username: ");

        if (!validateStringInput(name, 50)) {
            printf("\t\tError reading input\n");
            printf("\t\tPress enter to continue....");
            fflush(stdout); 
            getchar(); 
            continue; 
        }

        if (isContainsSpaces(name)) {
            printf("\t\tInvalid name. Please enter a valid name without spaces.\n");
            printf("\t\tPress enter to continue....");
            fflush(stdout); 
            getchar(); 
            continue; 
        }

        strcpy(u.name, name);

        if (isUniqueName(name, &u)) {
            printf("\t\tUser whith name %s not found.\n", name);
            printf("\t\tPress enter to continue....");
            fflush(stdout); 
            getchar(); 
            continue; 
        }        

        break;
    }
    
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
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login: ");
    scanf("%s", pass);


    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
}


