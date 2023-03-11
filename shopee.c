/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying 
the concepts learned. I have constructed the functions and their respective algorithms and corresponding 
code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have 
not copied in part or whole or otherwise plagiarized the work of other students and/or persons.

Kyle Adrian L. Santos & Jan Kailu Eli A. Baradas, DLSU ID# <12209546> <>
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // library where sleep() is in; sleep was used to delay the display output

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
void registerUser();


void SortByProdID(Item p[], int size)
{
    int i, j;
    int lowID, pos;
    Item temp;

    if (size != 0)
    {
        for (i = 0; i < size - 1; i++)
        {
            lowID = p[i].prodID;
            pos = i;
            for (j = i + 1; j < size; j++)
                if (lowID > p[j].prodID)
                {    
                    pos = j;
                    lowID = p[j].prodID;
                }
            
            if (pos != i)
            {
                temp = p[i];
                p[i] = p[pos];
                p[pos] = temp;
            }
        }
    }
}

void showItemsInTable(Item p[], int n)
{
    int i;
    printf("\nProduct ID\t|\tItem Name\t|\tCategory\t|\tUnit Price\t|\tQuantity\n\n");
    for (i = 0; i < n; i++)
        printf("%10d\t\t%8s\t\t%8s\t\t%10.2lf\t\t%8d\n\n", p[i].prodID, p[i].item_name, p[i].category, p[i].price, p[i].quantity);
}

void ViewProdBySellerID(User acc[], const int nUsers)
{
    int i, j;
    int lowID, pos;
    User temp;
    Item *shorten;
    char t;

    if (nUsers != 0)
    {
        for (i = 0; i < nUsers - 1; i++)
        {
            lowID = acc[i].userID;
            pos = i;
            for (j = i + 1; j < nUsers; j++)
                if (lowID > acc[j].userID)
                {    
                    pos = j;
                    lowID = acc[j].userID;
                }
            
            if (pos != i)
            {
                temp = acc[i];
                acc[i] = acc[pos];
                acc[pos] = temp;
            }
        }
    }

    for (i = 0; i < nUsers; i++)
        if (acc[i].nProduct != 0)
        {
            printf("\nSeller ID: %d\n", acc[i].userID);
            showItemsInTable(acc[i].products, acc[i].nProduct);

            if (j != acc[i].nProduct - 1)
            {
                printf("Type [N] to see next or [X] to exit viewing: ");
                scanf("%c", &t);
                getchar();
            }

            if (t != 'N') i = nUsers;
        
        }
}


void sellMenu(User *acc, int *numProduct)
{
    FILE *txtItem = NULL; // FILE for appending
    Item *thing = NULL;
    int i, temp;
    char t; // serves as a variable for user input
    string buffer;
    int choice = 0, selectProd = 0, found = 0;

    do
    {
        printf("\n--SELL MENU--\n");
        printf("\n[1] Add New Item\n");
        printf("[2] Edit Stock\n");
        printf("[3] Show My Products\n");
        printf("[4] Show My Low Stock Products\n");
        printf("[5] Exit Sell Menu\n\n");

        scanf("%d", &choice);
        getchar();

        // switch for the choices on sell menu
        switch(choice)
        {
            // ADD NEW ITEM
            case 1:
                if (*numProduct == 20)
                {
                    printf("\nA seller cannot sell more than 20 products.\n");
                    break;
                }

                thing = &acc->products[*numProduct]; // stores the address of the struct Item of the user in access
                
                printf("\nEnter Product ID: ");
                scanf("%d", &thing->prodID);
                getchar();

                printf("What is the name of the product? ");
                fgets(thing->item_name, 22, stdin);

                printf("What is the product's category? ");
                fgets(thing->category, 17, stdin);

                printf("What is its description? ");
                fgets(thing->description, 32, stdin);

                printf("Quantity of the product: ");
                scanf("%d", &thing->quantity);

                printf("Price of the product: ");
                scanf("%lf", &thing->price);

                thing->sellerID = acc->userID;

                txtItem = fopen("Items.txt", "a");

                fprintf(txtItem, "\n%d %d\n%s%s%s%d %.2lf\n", thing->prodID, thing->sellerID, thing->item_name, thing->category, thing->description, thing->quantity, thing->price);

                rmNewLine(thing->item_name);
                rmNewLine(thing->category);
                rmNewLine(thing->description);

                *numProduct += 1; // updates the number of different products sold by one person

                fclose(txtItem);

                break;
            
            // EDIT STOCK
            case 2:
                // SORT AND DSIPLAY A TABLE
                SortByProdID(&acc->products[0], *numProduct);
                printf("\nProduct ID\t|\tItem Name\t|\tCategory\t|\tUnit Price\t|\tQuantity\n\n");       
                for (i = 0; i < *numProduct; i++)
                {
                    thing = &acc->products[i]; // stores the address of the struct Item of the user in access
                    printf("%10d\t\t%8s\t\t%8s\t\t%10.2lf\t\t%8d\n\n", thing->prodID, thing->item_name, thing->category, thing->price, thing->quantity);
                }

                // asks for product ID and checks if ID is valid
                printf("\nWhat product do you wish to edit (ENTER PRODUCT ID)? ");
                scanf("%d", &selectProd);
                for (i = 0; i < *numProduct; i++)
                    if (selectProd == acc->products[i].prodID)
                    {
                        found = 1;
                        selectProd = i;
                        i = *numProduct;
                    }

                // if not found breaks form the EDIT STOCK switch case
                if (!found) 
                {
                    printf("\nProduct ID is invalid. You will be redirected back to the SELL MENU.\n");
                    sleep(1);
                    break;
                }

                do
                {
                    printf("\n--EDIT STOCK--\n");
                    printf("\n[1] Replenish\n");
                    printf("[2] Change Price\n");
                    printf("[3] Change Item Name\n");
                    printf("[4] Change Category\n");
                    printf("[5] Change Description\n");
                    printf("[6] Finish Editing\n\n");

                    choice = 0;
                    scanf("%d", &choice);
                    getchar();

                    switch (choice)
                    {
                        case 1: // REPLENISH
                            printf("\nHow much stock will you add to the product? ");
                            scanf("%d", &temp);
                            acc->products[selectProd].quantity += temp;
                            break;
                        case 2: // CHANGE PRICE
                            printf("\nHow much should be the new price of the product? ");
                            scanf("%lf", &acc->products[selectProd].price);
                            break;
                        case 3: // CHANGE ITEM NAME
                            printf("\nWhat should be the new name of the product? ");
                            fgets(acc->products[selectProd].item_name, 22, stdin);
                            rmNewLine(acc->products[selectProd].item_name);
                            break;
                        case 4: // CHANGE CATEGORY
                            printf("\nWhat should be the new name of the product? ");
                            fgets(acc->products[selectProd].category, 17, stdin);
                            rmNewLine(acc->products[selectProd].category);
                            break;
                        case 5: // CHANGE DESCRIPTION
                            printf("\nWhat should be the new description of the product? ");
                            fgets(acc->products[selectProd].description, 32, stdin);
                            rmNewLine(acc->products[selectProd].description);
                            break;
                        case 6:
                            printf("\nExiting Edit Stock Menu\n");
                            break;
                        default:
                            printf("\nPlease enter a valid input.\n");
                    }

                } while (choice != 6);

                break;
            
            // SHOW MY PRODUCTS
            case 3:
                SortByProdID(&acc->products[0], *numProduct);
                printf("\nProduct ID\t|\tItem Name\t|\tCategory\t|\tUnit Price\t|\tQuantity\n\n");

                for (i = 0; i < *numProduct; i++)
                {
                    thing = &acc->products[i]; // stores the address of the struct Item of the user in access
                    printf("%10d\t\t%8s\t\t%8s\t\t%10.2lf\t\t%8d\n\n", thing->prodID, thing->item_name, thing->category, thing->price, thing->quantity);
                }
                break;
            
            // SHOW MY LOW STOCK PRODUCTS
            case 4:
                for (i = 0; i < *numProduct; i++)
                {
                    thing = &acc->products[i]; // stores the address of the struct Item of the user in access
                    if (thing->quantity < 5)
                    {
                        printf("\nProduct ID: %d\nItem Name: %s\nCategory: %s\nDescription: %s\nUnit Price: %.2lf\nQuantity: %d\n\n", thing->prodID, thing->item_name, thing->category, thing->description, thing->price, thing->quantity);
                        
                        if (i != *numProduct - 1)
                        {
                            printf("Type [N] to see next or [X] to exit viewing: ");
                            scanf("%c", &t);
                            getchar();
                        }
                    }

                    if (t != 'N') i = *numProduct;
                }
                break;

            // EXIT SELL MENU 
            case 5:
                printf("\nExiting Sell Menu...\n");
                sleep(1);
                break;

            // IF CHOICE ENTERED IS NOT PART OF THE CHOICES
            default:
                printf("\nEnter a valid input.\n");
        }
    } while (choice != 5);
}


void buyMenu(User acc[], const int nUsers)
{
    int i, choice = 0;
    int id = 0;

    do
    {
        printf("\n[1] View All Products\n");
        printf("[2] Show All Products by a Specific Seller\n");
        printf("[3] Search Products by Category\n");
        printf("[4] Search Products by Name\n");
        printf("[5] Add to Cart\n");
        printf("[6] Edit Cart\n");
        printf("[7] Check Out Menu\n");
        printf("[8] Exit Buy Menu\n\n");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            // VIEW ALL PRODUCTS
            case 1:
                ViewProdBySellerID(acc, nUsers);
                break;

            // SHOW ALL PRODUCTS BY A SPECIFIC SELLER
            case 2:
                printf("\nEnter the seller ID of the seller: ");
                scanf("%d", &id);
                getchar();

                for (i = 0; i < nUsers; i++)
                    if (acc[i].userID == id)
                    {
                        showItemsInTable(acc[i].products, acc[i].nProduct);
                        i = nUsers + 1;
                    }

                if (i == nUsers)
                {
                    printf("\nSeller ID does not exist. You will be redirected back to the User Menu.\n");
                    sleep(1);
                }
                    
                break;
            
            // SEARCH PRODUCTS BY CATEGORY
            case 3:

                break;
            
            default:
                printf("\nEnter a valid input.\n");
                break;
        }
    } while (choice > 8 || choice < 1);
}


void userMenu(User account[], int nUsers)
{
    int i, j, on = 1; // ctr
    int ID; 
    char pass[11];
    int choice = 0; // choice for seller menu
    string name;
  
    Item *access; // Item pointer to make the code shorter
    int *numProduct; // temp pointer variable for accessing the number of product a user has

    // gets the ID and Password input 
    printf("\nEnter your user ID: ");
    scanf("%d", &ID);   
    printf("Enter your password: ");
    scanf("%s", pass);

    for (i = 0; i < nUsers; i++)
    {
        // if the ID and Password match, logs in the existing user
        if (ID == account[i].userID && strcmp(pass, account[i].pw) == 0)
        {
            printf("\nHi %s! You are now logged in.\n", account[i].name);
            strcpy(name, account[i].name);
            
            while (on)
            {
                printf("\n--USER MENU--\n");
                do
                {
                    printf("\n[1] Sell Menu\n");
                    printf("[2] Buy menu\n");
                    printf("[3] Exit User Menu\n\n");

                    scanf("%d", &choice);
                    getchar();
                } while (choice > 3 || choice < 1);


                /****
                switch for the choices on USER MENU
                ****/
                switch(choice)
                {
                    case 1: // SELL MENU
                        numProduct = &account[i].nProduct;
                        sellMenu(&account[i], numProduct);
                        break;
                    
                    case 2: // buy menu
                        buyMenu(account, nUsers);
                        break;
                    case 3: // exit user menu
                        printf("\nSigning out user %s...\n\n", name);
                        on = 0;
                        string name;
                        i = nUsers + 1;
                        sleep(1);
                        break;

                }
            }
        }
    }

    if (nUsers == i)
        printf("\nUser ID or Password is incorrect. You will be redirected back to the menu.\n");

}


void adminMenu(User account[], int nUsers)
{
    int i;
    int choice = 0;

    do
    {
        printf("\n--ADMIN MENU--\n");
        printf("\n[1] Show All Users\n");
        printf("[2] Show All Sellers\n");
        printf("[3] Show Total Sales in Given Duration\n");
        printf("[4] Show Seller Sales\n");
        printf("[5] Show Shopaholics\n");
        printf("[6] Back to Main Menu\n\n");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            //SHOW ALL USERS
            case 1:
                printf("\n   User ID\t|\tPassword\t|\t      Name \t\t|\t\t  Address\t\t|\tContact No.\n\n");
                for (i = 0; i < nUsers; i++)
                    printf("%10d\t\t%8s\t\t%18s\t\t%26s\t\t%11s\n\n", account[i].userID, account[i].pw, account[i].name, account[i].address, account[i].contact);
                break;

            // BACK TO MAIN MENU
            case 6:
                printf("\nExiting back to Main Menu...\n");
                sleep(1);
                break;

            default:
                printf("\nEnter a valid input.\n");
        }

    } while (choice != 6);
}


int main()
{
    int choice;
    User account[NUM_USERS]; // declares an array of users with a max of 100 users
    int nUsers = 0; // this is to keep track of registered users

    FILE *regUser;
    FILE *usertxt = fopen("Users.txt", "r");
    FILE *itemtxt = fopen("Items.txt", "r");

    system("clear");
    
    if (usertxt == NULL || itemtxt == NULL)
        return 1;

    loadUsers(usertxt, account, &nUsers);
    loadItems(itemtxt, account, nUsers);
    fclose(usertxt);
    fclose(itemtxt);

    printf("\n _    _        _                                _____        _____  _                    _  _ \n");
    printf("| |  | |      | |                              |_   _|      /  ___|| |                  (_)| |\n");
    printf("| |  | |  ___ | |  ___  ___   _ __ ___    ___    | |  ___   \\ `--. | |__    __ _  _ __   _ | |\n");
    printf("| |/\\| | / _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\   | | / _ \\   `--. \\| '_ \\  / _` || '_ \\ | || |\n");
    printf("\\  /\\  /|  __/| || (__| (_) || | | | | ||  __/   | || (_) | /\\__/ /| | | || (_| || |_) || ||_|\n");
    printf(" \\/  \\/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|   \\_/ \\___/  \\____/ |_| |_| \\__,_|| .__/ |_|(_)\n");
    printf("                                                                                 | |          \n");
    printf("                                                                                 |_|          \n");

    do
    {
        choice = 0;
        menu();

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                regUser = fopen("Users.txt", "a");
                if (regUser == NULL)
                    return 1;

                registerUser(regUser, account, &nUsers);
                fclose(regUser);

                printf("\n--Have successfully registered the user--\n");
                sleep(1);
                break;
            case 2:
                userMenu(account, nUsers);
                break;
            case 3:
                adminMenu(account, nUsers);
                break;
            case 4:
                break;
            default:
                printf("\nEnter Valid Input.\n");
        }
    } while (choice != 4);
    
    printf("\nThank you for using Shapi!\n");
    return 0;
}



void menu()
{
    printf("\n--MAIN MENU--\n\n");
    printf("[1] Register a new user\n");
    printf("[2] User Menu\n");
    printf("[3] Admin Menu\n");
    printf("[4] Exit\n\n");
}


void rmNewLine(char str[])
{
    int i = 0;
    while (str[i] != 0)
    {
        if(str[i] == '\n')
            str[i] = 0;
        i++;
    }
}


void loadUsers(FILE *txt, User account[], int *nUsers)
{
    while (fscanf(txt, "%d", &(account[*nUsers].userID)) == 1)
    {
        fgetc(txt);

        fgets(account[*nUsers].pw, 12, txt);
        rmNewLine(account[*nUsers].pw);

        fgets(account[*nUsers].name, 22, txt);
        rmNewLine(account[*nUsers].name);

        fgets(account[*nUsers].address, 32, txt);
        rmNewLine(account[*nUsers].address);

        fgets(account[*nUsers].contact, 13, txt);
        rmNewLine(account[*nUsers].contact);

        // fscanf(txt, "%d", &(account[nUsers].contact));
        // scanf("%d", &(account[nUsers].contact));

        account[*nUsers].nProduct = 0;
        *nUsers += 1;
    }
}


void loadItems(FILE *txt, User account[], const int nUsers)
{
    int i;
    int *nP; // pointer to the number of user's product
    Item *prod;
    unsigned int pID, sID; // product id & seller id

    while (fscanf(txt, "%d", &pID) == 1)
    {
        fscanf(txt, "%d", &sID);

        for (i = 0; i < nUsers; i++)
        {
            if (sID == account[i].userID)
            {
                nP = &account[i].nProduct;
                prod = &account[i].products[*nP];
                
                prod->prodID = pID;
                prod->sellerID = sID;
                
                fgetc(txt);

                fgets(prod->item_name, 22, txt);
                rmNewLine(prod->item_name);

                fgets(prod->category, 17, txt);
                rmNewLine(prod->category);

                fgets(prod->description, 32, txt);
                rmNewLine(prod->description);

                fscanf(txt, "%d", &prod->quantity);

                fscanf(txt, "%lf", &prod->price);

                *nP += 1;
            }
        }
    } 
}


void registerUser(FILE *regUser, User account[], int *nUsers)
{
    int i;

    do
    {
        printf("\nEnter a unique user ID: ");
        scanf("%d", &(account[*nUsers].userID));

        for (i = 0; i < *nUsers; i++)
            if (account[i].userID == account[*nUsers].userID)
                break;

        if (i >= *nUsers)
            break;

        printf("User ID is taken. Please enter another.");

    } while (1);

    printf("\nYour user ID is now (%d)\n\n", account[*nUsers].userID);
    scanf("%*c");

    printf("Enter a unique password for your account (not exceeding 10 characters): ");
    fgets(account[*nUsers].pw, 12, stdin);

    printf("Enter your first and last name: ");
    fgets(account[*nUsers].name, 22, stdin);

    printf("Enter your address: ");
    fgets(account[*nUsers].address, 32, stdin);

    printf("Enter your 11-digit contact number: ");
    fgets(account[*nUsers].contact, 13, stdin);

    fprintf(regUser, "\n%d %s%s%s%s\n", account[*nUsers].userID, account[*nUsers].pw, account[*nUsers].name, account[*nUsers].address, account[*nUsers].contact);

    account[*nUsers].nProduct = 0;
    *nUsers += 1;
}