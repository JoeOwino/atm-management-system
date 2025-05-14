#include "header.h"

bool validateStringInput(char *input) {
    // Get input as a string
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return false; // Error in input
    }
    
    // Remove newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    // Check if input is empty
    if (strlen(input) == 0) {
        printf("Empty input. Please enter a date.\n");
        return false;
    }

    return true;
}

bool isContainsSpaces(char input[50])
{
    // Check for spaces or special characters
    for (int i = 0; i < strlen(input); i++) {
        if (isspace(input[i]) || !isalnum(input[i])) {
            return false;
        }
    }

    return true;
}

bool isUnique_name(char name[50])
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

bool isvalidMenuInput(int min, int max, int *result) {
    char input[100]; // Buffer to store user input as string
    float temp; // For checking if input is a float
    char *endptr; // For strtof checking
    
    if (!validateStringInput(input)) {
        return false; // Error in input
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

bool isValidDate(struct Date *dt)
{
    char input[50]; 
    
    if (!validateStringInput(input)) {
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

    if (!validateStringInput(input)) {
        return false; // Error in input
    }

    if (isContainsSpaces(input)) {
        printf("Invalid name. Please enter a valid name without spaces.\n");
        fflush(stdout); 
        return false;
    }

    if (!isUnique_name(input)) {
        printf("Name already taken. Please choose another name.\n");
        fflush(stdout); 
        return false;
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

bool isValidLen(char input[50])
{
    // Remove newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
        len--;
    }
    
    // Check if input is empty
    if (len >= 8) {
        return true;
    }

    return false;
}
