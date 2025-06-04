#include "header.h"

void registerUser(char name[50], char pass[50]) {
    struct User u;
    struct termios oflags, nflags;
    char pass2[50];

    // --- Input Name ---
    while (1) {
        printWelcomeMessage("guest");
        printf("\t\t============= Member Registration ================\n\n\n");
        printf("\t\tEnter Your name (no spaces or special characters): ");
        
        if (!isValidName(name, &u)) {
            printf("\t\tInvalid name. Press Enter to continue...");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    // Disable echo for password
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;
    tcsetattr(fileno(stdin), TCSANOW, &nflags);

    // --- Input Password ---
    while (1) {
        printWelcomeMessage("Guest");
        printf("\t\t============= Member Registration ================\n\n\n");
        printf("\t\tEnter Your name: %s\n", name);
        printf("\n\n\t\tEnter Your password (at least 8 characters and no spaces): ");

        if (!isValidPassword(pass)) {
            printf("\t\tInvalid password. Press Enter to continue...");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    // --- Confirm Password ---
    while (1) {
        printWelcomeMessage("Guest");
        printf("\t\t============= Member Registration ================\n\n\n");
        printf("\t\tEnter Your name: %s\n", name);
        printf("\n\n\t\tEnter Your password (at least 8 characters and no spaces): ");

        printf("\n\n\t\tConfirm Password): ");
        scanf("%s", pass2);

        if (strcmp(pass2, pass) != 0) {
            printf("\n\t\tThe passwords did not match\n");
            printf("\t\tPress Enter to continue...");
            getchar(); // flush newline
            continue;
        }
        break;
    }

    // Restore terminal settings
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }

    // --- Save user ---
    u.id = getUserID(USERS_FILE);
    strcpy(u.name, name);
    strcpy(u.password, pass);
    writeUser(u);   
    
    while (getchar() != '\n');
    
}
