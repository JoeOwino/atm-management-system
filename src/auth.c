#include "header.h"

void loginMenu(struct User *u)
{
    struct termios oflags, nflags;
    char pass[50];
    char name[50];
    char userPass [50];
    FILE *fp = openUserFile(*u);
    if (fp == NULL) {
        printf("\t\tFailed to open users file");
        return;
    }

    while (1)
    {
        system("clear");
        printf("\n\n\t\t=======================  ATM  ==========================\n");
        printf("\t\t                    Login to continue \n");
        printf("\t\t  You can exit the system at any point by pressing ctrl+c\n");
        printf("\t\t==========================================================\n");

        printf("\n\t\tEnter Username: ");

        if (!validateStringInput(name, 50)) {
            printf("\n\t\tError reading input\n");
            printf("\t\tPress enter to continue....");
             while (getchar() != '\n');
; 
            continue;
        }

        if (isContainsSpaces(name)) {
            printf("\n\t\tInvalid name. Please enter a valid name without spaces.\n");
            printf("\t\tPress enter to continue....");
             while (getchar() != '\n');
; 
            continue;
        }

        strcpy(u->name, name);

        if (isUniqueName(name, u)) {
            printf("\n\t\tUser with name %s not found.\n", name);
            printf("\t\tPress enter to continue....");
             while (getchar() != '\n');
; 
            continue;
        }

        break;
    }

    // disable echo
    if (tcgetattr(fileno(stdin), &oflags) != 0) {
        perror("tcgetattr");
        exit(1);
    }
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }

    while (1)
    {
        system("clear");
        printf("\n\n\t\t=======================  ATM  ==========================\n");
        printf("\t\t                   Login to continue \n");
        printf("\t\t  You can exit the system at any point by pressing ctrl+c\n");
        printf("\t\t==========================================================\n");

        printf("\n\t\tEnter Username: %s", name);
        printf("\n\n\t\tEnter the password to login: ");

        if (!fgets(pass, 50, stdin)) {
            printf("\n\n\t\tError reading password\n");
            continue;
        }

        // Remove trailing newline from fgets
        pass[strcspn(pass, "\n")] = 0;
        strcpy(userPass, getPassword(u));
        

        if (strcmp(pass, userPass) != 0) {
            printf("\n\n\t\tWrong password!\n");
            printf("\t\tPress enter to continue....");
             while (getchar() != '\n');
;
            continue;
        }

        break;
    }

    // restore terminal settings
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }
}
