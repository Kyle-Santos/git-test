/*
    Header file for Shopping-App.c
*/
#include <stdio.h>

#define MAX_USERS 100
#define MAX_TRANSACTIONS 1000
typedef char string[40];


typedef struct item
{
    int prodID;
    char item_name[22];
    char category[17];
    char description[32];
    int quantity;
    double price;
    unsigned int sellerID;
} Item;


typedef struct user
{
    unsigned int userID;
    char pw[12];
    char address[32];
    unsigned long long contact;
    char name[22];

    // products in the cart of user
    Item cart[10]; // could have different quantity per item
    int inCart; // keeps track of the number of different products in cart

    // products being sold by the user
    Item products[20];
    int nProduct; // keeps track of the number of products a seller sells 
} User;


typedef struct transaction
{
    int month, day, year;

    Item checkout[5]; // could have different quantity per item
    int nItems;
    
    int buyerID;
    int sellerID; // should have the same seller for all the items
    double amount;

} Transaction;

void printWelcome();

void menu();

void rmNewLine(char str[]);

void loadUsers(FILE *txt, User account[], int *nUsers);

void loadItems(FILE *txt, User account[], const int nUsers);

void registerUser(User account[], int *nUsers);


// USER MENU FUNCTIONS
int searchSeller(User acc[], const int nUsers, int *id);

void SortByProdID(Item p[], int size);

int SortUserBySellerID(User acc[], const int nUsers, int accInd);

void showItemsInTable(Item p[], int n);

void ViewProdBySellerID(User acc[], const int nUsers);

void sellMenu(User *acc, int *numProduct);

void buyMenu(User acc[], const int nUsers, int accInd);

void userMenu(User account[], int nUsers);


// ADMIN MENU FUNCTION/S
void adminMenu(User account[], int nUsers);