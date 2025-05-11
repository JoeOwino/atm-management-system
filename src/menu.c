#include "header.h"

bool validateIntegerInput(int min, int max, int *result) {
    char input[100]; // Buffer to store user input as string
    float temp; // For checking if input is a float
    char *endptr; // For strtof checking
    
    // Get input as a string
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return false; // Error in input
    }
    
    // Remove newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    // Check if input is empty
    if (strlen(input) == 0) {
        return false;
    }
    
    // Check if input is a valid integer
    temp = strtof(input, &endptr);
    
    // Check if conversion was successful and it's an integer (no decimal part)
    if (*endptr != '\0' || temp != (int)temp) {
        return false; // Not an integer
    }
    
    // Convert to integer
    int value = (int)temp;
    
    // Check range
    if (value < min || value > max) {
        return false; // Out of range
    }
    
    // All checks passed, store result and return success
    *result = value;
    return true;
}

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
    int option;
    
    do {
        system("clear");  // Note: system("cls") for Windows
        printf("\n\n\t\t======= ATM =======\n");
        printf("\n\t\t-->> Feel free to login / register :\n");
        printf("\n\t\t[1]- login\n");
        printf("\n\t\t[2]- register\n");
        printf("\n\t\t[3]- exit\n\n");
        printf("\t\tEnter choice: ");
        
        // Use our validation function
        if (!validateIntegerInput(1, 3, &option)) {
            printf("\n\t\tInvalid input. Please enter a whole number (1, 2, or 3).\n");
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }
        
    } while (option < 1 || option > 3);
    
    switch (option) {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0) {
                printf("\n\n\t\tPassword Match!\n");
                printf("\t\tLogin successful.\n");
            } else {
                printf("\n\t\tWrong password or username!\n");
                exit(1);
            }
            break;
            
        case 2:
            registerUser(u->name, u->password);  // This would be the function to implement
            if (strcmp(u->password, getPassword(*u)) == 0) {
                printf("\n\n\t\tPassword Match!\n");
                printf("\t\tLogin successful.\n");
            } else {
                printf("\n\t\tWrong password or username!\n");
                exit(1);
            }
            break;
            
        case 3:
            printf("\n\t\tThank you for using our ATM service. Goodbye!\n");
            exit(0);  // Exit with success code
            break;
            
        default:
            printf("\n\t\tInsert a valid operation!\n");
            // This should never execute due to the do-while validation
    }
}

