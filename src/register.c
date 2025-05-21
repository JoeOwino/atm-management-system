#include "header.h"

void registerUser(char name[50], char pass[50])
{

    struct termios oflags, nflags;
    while(1) {
        system("clear");
        printf("\n\n\t\t======= ATM =======\n");
        printf("\t\tMember Registration\n\n\n");

        printf("\t\tEnter Your name (no spaces or special charators):");
        // scanf("%s", name);

        // // Get input as a string
        if (!isValidName(name)) {
            printf("\t\tPress Enter to continue...");
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


    while(1) {
        system("clear");
        printf("\n\n\t\t======= ATM =======\n");
        printf("\t\tMember Registration\n\n\n");

        printf("\t\tEnter Your name (no spaces or special charators):%s", name);

        printf("\n\n\t\tEnter Your password (at least 8 charactors and no spaces):");

        // Get input as a string
        if (!isValidPassword(pass)) {
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

        break;
    } 

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    struct User u;
    u.id = getUserID("./data/users.txt");;
    strcpy(u.name, name);
    strcpy(u.password, pass);
    writeUser(u);

    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\t\tMember Registration\n\n\n");
    printf("\t\t\t\tRegiatered Successfully\n");
    printf("\t\tID: %d\n", u.id);
    printf("\t\tName: %s\n", name);
    printf("\t\tPassword: %s\n", pass);
    printf("\t\tPress Enter to continue...");
    getchar();
   
}
