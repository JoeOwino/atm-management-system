#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define RECORDS_FILE "./data/records.txt"
#define USERS_FILE "./data/users.txt"
#define TRANS_FILE "./data/history.txt"

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

struct Transaction
{
    int id;
    int userId;
    int accountNbr;
    struct Date date;
    char type[20];
    double amount;
};

// authentication functions
void loginMenu(struct User *u);
const char *getPassword(struct User *u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);

// menu functions
void mainMenu(struct User u);
void initMenu(struct User *u);
void printWelcomeMessage(char *name);

// registration functions
void registerUser(char name[50], char pass[50]);

// fileio IO functions
int getUserID();
FILE *openUserFile(struct User u);
FILE *openAccFile(struct User u, char *msg);
void writeUser(struct User u);
int getAccountFromFile(FILE *fp, char name[50], struct Record *r);
bool getAccountByID(FILE *fp, int id, struct Record *r, int accNbr);
void saveAccountToFile(FILE *fp, struct User u, struct Record r);
int saveUpdatedRecord(FILE *fp, struct User u, struct Record updated, char *action);
int getTransID();
void writeTrans(struct Transaction t);

// validation functions
bool isValidDate(struct Date *dt);
bool isValidPassword(char input[50]);
bool isValidPhoneNo(char *phone);
bool isValidName(char *input, struct User *u);
bool isvalidIntegerInput(int *result);
bool isValidPhoneNo(char *phone);
bool isValidMenuInput(int min, int max, int *result);
bool validateStringInput(char *input, size_t size);
bool isUniqueName(char name[50], struct User *u);
bool isContainsSpaces(char input[50]);
bool isUniqueAcc(int acc);
bool isvalidAmount(double *amount, double min, double max);

// Account Functions
void printAccount(struct Record r, struct User u);
void updateAccount(struct User u);
void removeAccount(struct User u);
void transferOwnership(struct User u);
void checkAccounts(struct User u);
double calculateInterest(int accNbr, char *accType, double amount);

// Transaction Functions
void createTransaction(struct User u);

#endif
