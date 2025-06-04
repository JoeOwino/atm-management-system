#include "header.h"

void printWelcomeMessage(char *name)
{
    system("clear");
    printf("\n\n\t\t=======================  ATM  ==========================\n");
    printf("\t\t                    Welcome %s\n", name);
    printf("\t\t  Yuo can exit the system at any point by prssing ctr+c\n");
    printf("\t\t==========================================================\n\n");

}

int mainMenuLoop(struct User u)
{
    int option = 0;

    do {
        printWelcomeMessage(u.name);
        printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
        printf("\n\t\t[1]- Create a new account\n");
        printf("\n\t\t[2]- Update account information\n");
        printf("\n\t\t[3]- Check accounts\n");
        printf("\n\t\t[4]- Check list of owned account\n");
        printf("\n\t\t[5]- Make Transaction\n");
        printf("\n\t\t[6]- Remove existing account\n");
        printf("\n\t\t[7]- Transfer ownership\n");
        printf("\n\t\t[8]- Exit\n");
    
        printf("\n\t\tEnter choice: ");
        
        if (!isValidMenuInput(1, 8, &option)) {
            printf("\t\tPress Enter to continue...");
            getchar(); getchar(); 
        }

    } while (option < 1 || option > 8);

    return option;

}

void success(struct User u)
{
    int option;
    printf("\n\n\t\t✔ Success!\n");
invalid:
    printf("\t\tEnter any cahracter(s) to go to the main menu and 0 to exit!: ");
    scanf("%d", &option);
    while (getchar() != '\n');

    system("clear");

    if (option == 0)
    {
        exit(1);
    }
 

    mainMenu(u);
}

void mainMenu(struct User u)
{

    int option = mainMenuLoop(u);

    switch (option) {
    case 1:
        createNewAcc(u);
        break;

    case 2:
        updateAccount(u);
        break;

   case 3:
        checkAccounts(u);
        break;

    case 4:
        checkAllAccounts(u);
        break;

    case 5:
        createTransaction(u);
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        removeAccount(u);
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        transferOwnership(u);
        break;
    case 8:
        system("clear");
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
        system("clear");
        exit(1);
        break;
    }

    success(u);
}

void initMenu(struct User *u)
{
    int option;
    
    while(1) {
        system("clear");
        printf("\n\n\t\t=======================  ATM  ==========================\n");
        printf("\t\t             Login or register to continue \n");
        printf("\t\t  You can exit the system at any point by pressing ctrl+c\n");
        printf("\t\t==========================================================\n");

        printf("\n\t\t[1]- login\n");
        printf("\n\t\t[2]- register\n");
        printf("\n\t\t[3]- exit\n\n");
        printf("\t\tEnter choice: ");
        
        if (!isValidMenuInput(1, 3, &option)) {
            printf("\t\tPress Enter to continue...");
            getchar();
            continue;
        }

        break;
        
    }
    
    switch (option) {
        case 1:
            loginMenu(u);
            break; 
        case 2:
            registerUser(u->name, u->password);  
            break;
        case 3:
            printf("\n\t\tThank you for using our ATM service. Goodbye!\n");
            system("clear");
            exit(0);  // Exit with success code
            break;
            
        default:
            printf("\n\t\tInsert a valid operation!\n");
            system("clear");
            exit(1);
            // This should never execute due to the do-while validation
    }
}
