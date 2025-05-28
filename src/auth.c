#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{    
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\t\t=======================  ATM  ==========================\n");
    printf("\t\t                    Login to continue \n");
    printf("\t\t  Yuo can exit the system at any point by prssing ctr+c\n");
    printf("\t\t==========================================================\n\n");

    printf("\n\t\t\t\t\t Enter Username: ");
    scanf("%s", a);

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


