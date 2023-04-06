/*
    Header file for Shopping-App.c
*/
#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_TRANSACTIONS 1000
#define NAME_LEN 20
#define ANY_ID_LEN 8
#define PW_LEN 10
#define DESCRIPTION_LEN 30
typedef char string[40];


typedef struct item
{
    string prodID; // prodID should have a maximum of 8 in length
    string item_name; // item_name should have a maximum of 20 in length
    string category; // category should have a maximum of 15 in length
    string description; // description should have a maximum of 30 in length
    int quantity;
    double price;
    string sellerID; // User ID should have a maximum of 8 in length
} Item;


typedef struct user
{
    string userID; // User ID should have a maximum of 8 in length
    string pw; // pw should have a max of 10 in length
    string address; // address should have a maximum of 30 in length
    string contact; // should have a max of 20 in length
    string name; // name should have a maximum of 20 in length

    // products in the cart of user
    Item cart[10]; // could have different quantity per item
    int inCart; // keeps track of the number of different products in cart

    // products being sold by the user
    Item products[20];
    int nProduct; // keeps track of the number of products a seller sells 
} User;

typedef struct date 
{
    int month, 
        day, 
        year;
} Date;

typedef struct transaction
{
    Date date;

    Item checkout[5]; // could have different quantity per item
    int nItems;
    
    string buyerID;
    string sellerID; // should have the same seller for all the items
    double amount;

} Transaction;

void printWelcome();

void menu();

void rmNewLine(string str);

int isNumeric(string str);

void loadUsers(FILE *txt, User account[], int *nUsers);

void loadItems(FILE *txt, User account[], const int nUsers);

void registerUser(User account[], int *nUsers);


// USER MENU FUNCTIONS
int isLenCorrect(string str, int len);

int searchSeller(User acc[], const int nUsers, string id, int *prod_index);

void SortByProdID(Item p[], int size);

int SortUserBySellerID(User acc[], const int nUsers, int accInd);

void showItemsInTable(Item p[], int n);

void ViewProdBySellerID(User acc[], const int nUsers);

void sellMenu(User *acc, int *numProduct);

int buyMenu(User acc[], const int nUsers, int accInd, Transaction out[], int *nTrans);

void userMenu(User account[], int nUsers, Transaction checkout[], int *nTrans);


// ADMIN MENU FUNCTION/S
void adminMenu(User account[], int nUsers, Transaction receipt[], int nTrans);