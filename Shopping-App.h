/*
    Header file for Shopping-App.c.c
*/

#define NUM_USERS 100
typedef char string[40];


typedef struct item
{
    int prodID;
    char item_name[22];
    char category[17];
    char description[32];
    int quantity;
    double price;
    int sellerID;
} Item;


typedef struct user
{
   unsigned int userID;
   char pw[12];
   char address[32];
   string contact;
   char name[22]; 
   Item products[20];
   int nProduct;
} User;


typedef struct transaction
{
    string month, day, year;
    Item product[5]; // could have different quantity per item
    int buyerID;
    int sellerID; // should have the same seller for all the items
    double amount;

} Transaction;


void menu();

void rmNewLine(char str[]);

void loadUsers(FILE *txt, User account[], int *nUsers);

void loadItems(FILE *txt, User account[], const int nUsers);

void registerUser(FILE *regUser, User account[], int *nUsers);

void SortByProdID(Item p[], int size);

void showItemsInTable(Item p[], int n);

void ViewProdBySellerID(User acc[], const int nUsers);

void sellMenu(User *acc, int *numProduct);

void buyMenu(User acc[], const int nUsers);

void userMenu(User account[], int nUsers);

void adminMenu(User account[], int nUsers);