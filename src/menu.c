#include "header.h"

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // student TODO : add your **Update account information** function
        // here
        break;
    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        // here
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        // here
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{

    int r = 0;
    int option;
    char input[100]; // Buffer to store user input as string
    float temp; // For checking if input is a float
    char *endptr; // For strtof checking
    
    do {
        system("clear");  // Note: system("cls") for Windows
        printf("\n\n\t\t======= ATM =======\n");
        printf("\n\t\t-->> Feel free to login / register :\n");
        printf("\n\t\t[1]- login\n");
        printf("\n\t\t[2]- register\n");
        printf("\n\t\t[3]- exit\n\n");
        printf("\t\tEnter choice: ");
        
        // Get input as a string
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue; // Error in input
        }
        
        // Remove newline if present
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        // Check if input is a valid integer
        temp = strtof(input, &endptr);
        
        // Check if conversion was successful and it's an integer (no decimal part)
        if (*endptr != '\0' || temp != (int)temp) {
            printf("\n\t\tInvalid input. Please enter a whole number (1, 2, or 3).\n");
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }
        
        // Convert to integer
        option = (int)temp;
        
    } while (option < 1 || option > 3);
       
    switch (option)
    {
    case 1:
        loginMenu(u->name, u->password);
        if (strcmp(u->password, getPassword(*u)) == 0)
        {
            printf("\n\nPassword Match!");
        }
        else
        {
            printf("\nWrong password!! or User Name\n");
            exit(1);
        }
        r = 1;
        break;
    case 2:
        // student TODO : add your **Registration** function
        // here
        r = 1;
        break;
    case 3:
        exit(1);
        break;
    default:
        printf("Insert a valid operation!\n");
    }
    
};

