#include "header.h"

bool validateStringInput(char *input, size_t size)
{
    if (input == NULL || size == 0) {
        return false;
    }
    
    // Get input as a string
    if (fgets(input, size, stdin) == NULL) {
        printf("\n\n\t\tError reading input.\n");
        return false; // Error in input
    }
    
    // Remove newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
        len--; // Update length
    }
    
    // Check if input is empty
    if (len == 0) {
        printf("\n\n\t\tEmpty input. Please enter a value.\n");
        return false;
    }
    
    // Check if input was truncated (buffer was too small)
    if (len == size - 1 && input[len-1] != '\n') {
        // Input might have been truncated
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Clear remaining input
        printf("\n\n\t\tInput too long. Maximum %zu characters allowed.\n", size - 1);
        return false;
    }
    
    return true;
}

bool isContainsSpaces(char input[50])
{
    // Check for spaces or special characters
    
    for (int i = 0; i < strlen(input); i++) {
        if (isspace(input[i])) {
            return true;
        }
    }

    return false;
}

bool isUniqueName(char name[50], struct User *u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("\n\n\t\tError! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        
        if (strcmp(userChecker.name, name) == 0)
        {
            u -> id = userChecker.id;
            strcpy(u -> name, userChecker.name);
            strcpy(u -> password, userChecker.password);

            fclose(fp);
            return false;
        }
    }

    fclose(fp);

    return true;
}

bool isUniqueAcc(int acc) {
    FILE *fp;
    struct Record r;
    struct User u;
    
    if ((fp = fopen("./data/records.txt", "r")) == NULL) {
        printf("\n\n\t\tError! opening file");
        return false; 
    }
    
    // Option 1: Fix the format string to match your actual file format
    while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s\n", 
                 &r.id, &u.id, u.name, &r.accountNbr, 
                 &r.deposit.month, &r.deposit.day, &r.deposit.year, 
                 r.country, r.phone, &r.amount, r.accountType) == 11) {

        if (r.accountNbr == acc) {
            fclose(fp);
            return false; 
        } 
    }
    
    fclose(fp);
    return true;
}

bool isvalidIntegerInput(int *result) {

    char input[100]; // Buffer to store user input as string
    float temp; // For checking if input is a float
    char *endptr; // For strtof checking
    
    if (!validateStringInput(input, 100)) {
        printf("\n\n\t\tError reading input\n");
        return false; // Error in input
    }
    
    // Check if input is a valid integer
    temp = strtof(input, &endptr);
    
    // Check if conversion was successful and it's an integer (no decimal part)
    if (*endptr != '\0' || temp != (int)temp) {
        printf("\n\t\tInvalid input. Please enter a whole number.\n");
        return false; // Not an integer
    }
    
    // Convert to integer
    *result = (int)temp;
    
    return true;
}

bool isValidMenuInput(int min, int max, int *result) {

    if (!isvalidIntegerInput(result)) {
        return false; // Error in input
    }
    
    if (*result < min || *result > max) {
        printf("\n\n\t\tInvalid choice. Enter a numbber %d and %d.\n", min, max);
        return false; // Out of range
    }
    
    return true;
}

bool isValidDate(struct Date *dt)
{
    char input[100]; 
    
    if (!validateStringInput(input, 50)) {
        return false; // Error in input
    }
    
    // Use sscanf instead of scanf to parse the input string
    int items = sscanf(input, "%d/%d/%d", &dt->month, &dt->day, &dt->year);
    if (items != 3) {
        printf("\n\n\t\tInvalid date format. Please use MM/DD/YYYY format.\n");
        fflush(stdout); 
        return false;
    }
    
    // Check if the date is valid
    if (dt->month < 1 || dt->month > 12) {
        printf("\n\n\t\tInvalid month. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->day < 1 || dt->day > 31) {
        printf("\n\n\t\tInvalid day. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->year < 1900 || dt->year > 2100) {
        printf("\n\n\t\tInvalid year. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if ((dt->month == 4 || dt->month == 6 || dt->month == 9 || dt->month == 11) && dt->day > 30) {
        printf("\n\n\t\tInvalid day for the given month. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->month == 2) {
        if ((dt->year % 4 == 0 && dt->year % 100 != 0) || (dt->year % 400 == 0)) {
            if (dt->day > 29) {
                printf("\n\n\t\tInvalid day for February in a leap year. Please enter a valid date.\n");
                fflush(stdout); 
                return false;
            }
        } else {
            if (dt->day > 28) {
                printf("\n\n\t\tInvalid day for February. Please enter a valid date.\n");
                fflush(stdout); 
                return false;
            }
        }
    }
    
    // Check if the date is in the future
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if (dt->year > tm->tm_year + 1900 ||
        (dt->year == tm->tm_year + 1900 && dt->month > tm->tm_mon + 1) ||
        (dt->year == tm->tm_year + 1900 && dt->month == tm->tm_mon + 1 && dt->day > tm->tm_mday)) {
        printf("\n\n\t\tInvalid date. The date cannot be in the future.\n");
        fflush(stdout); // Ensure the message is displayed
        return false;
    }
    
    return true;
}

bool isValidName(char *input, struct User *u)
{


    if (!validateStringInput(input, 50)) {
        return false; // Error in input
    }

    if (isContainsSpaces(input)) {
        printf("\n\n\t\tInvalid name. Please enter a valid name without spaces.\n");
        fflush(stdout); 
        return false;
    }

    if (!isUniqueName(input, u)) {
        printf("\n\n\t\tName already taken. Please choose another name.\n");
        fflush(stdout); 
        return false;
    }

    return true;
}

bool isValidPassword(char *input)
{
    if (!validateStringInput(input, 50)) {
        return false; // Error in input
    }

    if (isContainsSpaces(input)) {
        printf("\n\n\t\tInvalid password. Please enter a valid password without spaces.\n");
        fflush(stdout); 
        return false;
    }

    if (strlen(input) < 8) {
        printf("\n\n\t\tPassword must be at least 8 characters long.\n");
        fflush(stdout); 
        return false;
    }

    return true;
}

bool isValidPhoneNo(char *phone) 
{    

    if (!validateStringInput(phone, 50)) {
        return false; // Error in input
    }

    // Check if the phone number is valid
    if (strlen(phone) < 8 || strlen(phone) > 15) {
        printf("\n\n\t\tInvalid phone number. Please enter a valid 8 to 15 digit phone number.\n");
        fflush(stdout); 
        return false;
    }
    
   // Verify that all characters are digits
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            printf("\n\n\t\tInvalid phone number. Please enter only digits (0-9).\n");
            fflush(stdout);
            return false;
        }
    }

    return true;
}

bool isvalidAmount(double *amount, double min, double max) {
    char input[100]; // Buffer to store user input as string
    double temp; // Changed from float to double for consistency
    char *endptr; // For strtod checking

    if (!validateStringInput(input, 100)) {
        printf("\n\n\t\tError reading input\n");
        return false; // Error in input
    }

    // Check if input is a valid double
    temp = strtod(input, &endptr); // Using strtod instead of strtof for double precision
    
    // Check if conversion was successful
    if (*endptr != '\0') { // This condition should be != '\0', not == '\0'
        printf("\n\n\t\tInvalid input. Please enter a valid number.\n");
        return false;
    }
    
    // Convert to double (no need to cast since strtod already returns double)
    *amount = temp;
    
    // Check if amount is within range
    if (*amount < min || *amount > max) {
        // Fixed format specifiers to %g for displaying double values
        printf("\n\n\t\tInvalid input. Please enter a number between %g and %g.\n", min, max);
        return false; // Out of range
    }
    
    return true;
}
