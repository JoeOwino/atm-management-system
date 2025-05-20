#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>


struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    char phone[50];
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);

// menu functions
void mainMenu(struct User u);
void initMenu(struct User *u);

// registration functions
void registerUser(char name[50], char pass[50]);

// fileio functions
int getID(char *file);
void writeUser(struct User u);
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r);


// validation functions
bool isValidDate(struct Date *dt);
bool isValidPassword(char input[50]);
bool isValidName(char *input);
bool isvalidIntegerInput(int *result);
bool isValidPhoneNo(char *phone);
bool isValidMenuInput(int min, int max, int *result);
bool isUniqueName(char name[50]);
bool validateStringInput(char *input, size_t size);
bool isContainsSpaces(char input[50]);
bool isUniqueAcc(int acc);
bool isvalidAmount(double *amount, double min, double max);

// Account Functions
bool getAccount(int acc, struct Record *r, struct User *u);
void printAccount(struct Record r, struct User u);
