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

bool isEmpty(char input[50])
{
    // Remove newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
        len--;
    }
    
    // Check if input is empty
    if (len == 0) {
        return true;
    }

    return false;
}

bool isValidName(char input[50])
{

    // Check for spaces or special characters
    for (int i = 0; i < strlen(input); i++) {
        if (isspace(input[i]) || !isalnum(input[i])) {
            return false;
        }
    }

    return true;
}

bool isValidPassword(char input[50])
{
    // Check for spaces
    for (int i = 0; i < strlen(input); i++) {
        if (isspace(input[i])) {
            return false;
        }
    }

    return true;
}

void registerUser(char name[50], char pass[50])
{

    struct termios oflags, nflags;
    do {
        system("clear");
        printf("\n\n\t\t======= ATM =======\n");
        printf("\t\tMember Registration\n\n\n");

        printf("\t\tEnter Your name (no spaces or special charators):");
        // scanf("%s", name);

        // // Get input as a string
        if (fgets(name, 50, stdin) == NULL) {
            printf("\n\t\tError reading input. Please try again.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

        if (isEmpty(name)) {
            printf("\n\t\tName cannot be empty. Please try again.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
        }

        if (!isValidName(name)) {
            printf("\n\t\tName contains spaces or special characters. Please use only letters and numbers.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
        }

        if (!isUnique_name(name)) {
            printf("\n\t\tName already taken. Please choose another name.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
        }

    } while (!isUnique_name(name) || isEmpty(name) || !isValidName(name));
    
    
    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;


    do {
        system("clear");
        printf("\n\n\t\t======= ATM =======\n");
        printf("\t\tMember Registration\n\n\n");

        printf("\t\tEnter Your name (no spaces or special charators):%s", name);
        printf("\n\n\t\tEnter Your password (no spaces):");

        // Get input as a string
        if (fgets(pass, 50, stdin) == NULL) {
            printf("\n\t\tError reading input. Please try again.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

        if (isEmpty(pass)) {
            printf("\n\t\tPassword cannot be empty. Please try again.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
        }

        if (!isValidPassword(pass)) {
            printf("\n\t\tPassword contains spaces. Please use only letters and numbers.\n");
            printf("\t\tPress Enter to continue...");
            getchar();
        }

    } while (!isValidPassword(pass) || isEmpty(pass));

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }




    printf("\n\t\t\t\tRegiatered Successfully\nName: %s\nPassword: %s\n", name, pass);

    printf("END\n");
}
