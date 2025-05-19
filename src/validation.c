#include "header.h"

bool validateStringInput(char *input, size_t size)
{
    if (input == NULL || size == 0) {
        return false;
    }
    
    // Get input as a string
    if (fgets(input, size, stdin) == NULL) {
        printf("Error reading input.\n");
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
        printf("Empty input. Please enter a value.\n");
        return false;
    }
    
    // Check if input was truncated (buffer was too small)
    if (len == size - 1 && input[len-1] != '\n') {
        // Input might have been truncated
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Clear remaining input
        printf("Input too long. Maximum %zu characters allowed.\n", size - 1);
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

bool isUniqueName(char name[50])
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

bool isUniqueAcc(int acc) {
    FILE *fp;
    struct Record r;
    struct User u;
    
    if ((fp = fopen("./data/records.txt", "r")) == NULL) {
        printf("Error! opening file");
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
        printf("Error reading input\n");
        return false; // Error in input
    }
    
    // Check if input is a valid integer
    temp = strtof(input, &endptr);
    
    // Check if conversion was successful and it's an integer (no decimal part)
    if (*endptr != '\0' || temp != (int)temp) {
        printf("Invalid input. Please enter a whole number.\n");
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
        printf("Invalid input. Please enter a whole number between %d and %d.\n", min, max);
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
        printf("Invalid date format. Please use MM/DD/YYYY format.\n");
        fflush(stdout); 
        return false;
    }
    
    // Check if the date is valid
    if (dt->month < 1 || dt->month > 12) {
        printf("Invalid month. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->day < 1 || dt->day > 31) {
        printf("Invalid day. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->year < 1900 || dt->year > 2100) {
        printf("Invalid year. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if ((dt->month == 4 || dt->month == 6 || dt->month == 9 || dt->month == 11) && dt->day > 30) {
        printf("Invalid day for the given month. Please enter a valid date.\n");
        fflush(stdout); 
        return false;
    }
    
    if (dt->month == 2) {
        if ((dt->year % 4 == 0 && dt->year % 100 != 0) || (dt->year % 400 == 0)) {
            if (dt->day > 29) {
                printf("Invalid day for February in a leap year. Please enter a valid date.\n");
                fflush(stdout); 
                return false;
            }
        } else {
            if (dt->day > 28) {
                printf("Invalid day for February. Please enter a valid date.\n");
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
        printf("Invalid date. The date cannot be in the future.\n");
        fflush(stdout); // Ensure the message is displayed
        return false;
    }
    
    return true;
}

bool isValidName(char *input)
{

    if (!validateStringInput(input, 50)) {
        return false; // Error in input
    }

    if (isContainsSpaces(input)) {
        printf("Invalid name. Please enter a valid name without spaces.\n");
        fflush(stdout); 
        return false;
    }

    if (!isUniqueName(input)) {
        printf("Name already taken. Please choose another name.\n");
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
        printf("Invalid password. Please enter a valid password without spaces.\n");
        fflush(stdout); 
        return false;
    }

    if (strlen(input) < 8) {
        printf("Password must be at least 8 characters long.\n");
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
    if (strlen(phone) != 10 ) {
        printf("Invalid phone number. Please enter a valid 10-digit phone number.\n");
        fflush(stdout); 
        return false;
    }
    
   // Verify that all characters are digits
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            printf("Invalid phone number. Please enter only digits (0-9).\n");
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
        printf("Error reading input\n");
        return false; // Error in input
    }

    // Check if input is a valid double
    temp = strtod(input, &endptr); // Using strtod instead of strtof for double precision
    
    // Check if conversion was successful
    if (*endptr != '\0') { // This condition should be != '\0', not == '\0'
        printf("Invalid input. Please enter a valid number.\n");
        return false;
    }
    
    // Convert to double (no need to cast since strtod already returns double)
    *amount = temp;
    
    // Check if amount is within range
    if (*amount < min || *amount > max) {
        // Fixed format specifiers to %g for displaying double values
        printf("Invalid input. Please enter a number between %g and %g.\n", min, max);
        return false; // Out of range
    }
    
    return true;
}
