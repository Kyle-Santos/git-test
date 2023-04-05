/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying 
the concepts learned. I have constructed the functions and their respective algorithms and corresponding 
code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have 
not copied in part or whole or otherwise plagiarized the work of other students and/or persons.

Kyle Adrian L. Santos & Jan Kailu Eli A. Baradas, DLSU ID# <12209546> <12206717>
*********************************************************************************************************/

#include <stdio.h>

// libraries for aesthetics :))
#include <stdlib.h> // used solely for system("clear"), to clear the terminal when program is ran
#include <unistd.h> // library where sleep() is in; sleep was used to delay the display output

#include "userMenu.c"

int main()
{
    int i, j, choice;
    Item temp;
    User account[MAX_USERS]; // declares an array of users with a max of 100 users
    Transaction checkout[MAX_TRANSACTIONS];
    int nUsers = 0; // this is to keep track of registered users
    int total_transactions = 0;

    FILE *usertxt = fopen("Users.txt", "r");
    FILE *itemtxt = fopen("Items.txt", "r");
    FILE *transtxt = fopen("Transactions.dat", "rb");

    //system("clear");
     
    if (usertxt == NULL || itemtxt == NULL)
        return 1;

    loadUsers(usertxt, account, &nUsers);
    loadItems(itemtxt, account, nUsers);
    fclose(usertxt);
    fclose(itemtxt);

    printWelcome();

    do
    {
        choice = 0;
        menu();

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                if (nUsers < MAX_USERS)
                {
                    registerUser(account, &nUsers);
                    printf("\n---Have successfully registered the user---\n");
                }
                else
                    printf("\n---Users registered have reached the maximum allowed---\n");
                sleep(1);
                break;
            case 2:
                userMenu(account, nUsers);
                break;
            case 3:
                adminMenu(account, nUsers);
                break;
            case 4:
                printf("\nSaving All Information...\n");
                sleep(1);

                usertxt = fopen("Users.txt", "w");
                itemtxt = fopen("Items.txt", "w");
                
                for (i = 0; i < nUsers; i++)
                    fprintf(usertxt, "%s %s\n%s\n%s\n%s\n\n", account[i].userID, account[i].pw, account[i].name, account[i].address, account[i].contact);

                for (i = 0; i < nUsers; i++)
                {
                    for (j = 0; j < account[i].nProduct; j++)
                    {
                        temp = account[i].products[j];
                        fprintf(itemtxt, "%s %s\n%s\n%s\n%s\n%d %.2lf\n\n", temp.prodID, temp.sellerID, temp.item_name, temp.category, temp.description, temp.quantity, temp.price);
                        fflush(itemtxt);
                    }
                }
                
                fclose(usertxt);
                fclose(itemtxt);
                printf("\nData has been saved.\n");
                sleep(1);
                break;
            default:
                printf("\nEnter Valid Input.\n");
        }
    } while (choice != 4);
    
    printf("\nThank you for using the app!\n");
    sleep(1);
    return 0;
}


void printWelcome()
{
    printf("\n _    _        _                                _____        _____  _                    _  _ \n");
    printf("| |  | |      | |                              |_   _|      /  ___|| |                  (_)| |\n");
    printf("| |  | |  ___ | |  ___  ___   _ __ ___    ___    | |  ___   \\ `--. | |__    __ _  _ __   _ | |\n");
    printf("| |/\\| | / _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\   | | / _ \\   `--. \\| '_ \\  / _` || '_ \\ | || |\n");
    printf("\\  /\\  /|  __/| || (__| (_) || | | | | ||  __/   | || (_) | /\\__/ /| | | || (_| || |_) || ||_|\n");
    printf(" \\/  \\/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|   \\_/ \\___/  \\____/ |_| |_| \\__,_|| .__/ |_|(_)\n");
    printf("                                                                                 | |          \n");
    printf("                                                                                 |_|          \n");
}


void menu()
{
    sleep(1);
    printf("\n%s\n", "===============================");
    printf("%s\n", "           MAIN MENU");
    printf("%s\n\n", "===============================");
    printf("[1] Register a new user\n");
    printf("[2] User Menu\n");
    printf("[3] Admin Menu\n");
    printf("[4] Exit\n\n");
}


void rmNewLine(string str)
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
    while (fscanf(txt, "%s", account[*nUsers].userID) == 1)
    {
        fgetc(txt);

        fgets(account[*nUsers].pw, 12, txt);
        rmNewLine(account[*nUsers].pw);

        fgets(account[*nUsers].name, 22, txt);
        rmNewLine(account[*nUsers].name);

        fgets(account[*nUsers].address, 32, txt);
        rmNewLine(account[*nUsers].address);

        fscanf(txt, "%s", account[*nUsers].contact);

        account[*nUsers].nProduct = 0;
        account[*nUsers].inCart = 0;
        *nUsers += 1;
    }
}


void loadItems(FILE *txt, User account[], const int nUsers)
{
    int i;
    int *nP; // pointer to the number of user's product
    Item *prod;
    string pID, sID; // product id & seller id

    while (fscanf(txt, "%s %s", pID, sID) == 2)
    {
        for (i = 0; i < nUsers; i++)
        {
            if (strcmp(sID, account[i].userID) == 0)
            {
                nP = &account[i].nProduct;
                prod = &account[i].products[*nP];
                
                strcpy(prod->prodID, pID);
                strcpy(prod->sellerID, sID);
                
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


int isNumeric(string str)
{
    int i = 0;

    // if empty return 0
    if (str[i] == '0')
        return 1;

    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 1;
        i++;
    }

    return 0;
}


void registerUser(User account[], int *nUsers)
{
    int i;

    do
    {
        do 
        {
            printf("\nEnter a unique user ID: ");
            scanf("%s", account[*nUsers].userID);
        } while (isNumeric(account[*nUsers].userID) == 1 || isLenCorrect(account[*nUsers].userID, ANY_ID_LEN) == 1);

        for (i = 0; i < *nUsers; i++)
            if (strcmp(account[i].userID, account[*nUsers].userID) == 0)
                i = *nUsers + 1;

        if (i != *nUsers)
            printf("User ID is taken. Please enter another.");

    } while (i != *nUsers);

    printf("\nYour user ID is now (%s)\n\n", account[*nUsers].userID);
    scanf("%*c");

    printf("Enter a unique password for your account (not exceeding 10 characters): ");
    fgets(account[*nUsers].pw, 12, stdin);

    printf("Enter your first and last name: ");
    fgets(account[*nUsers].name, 22, stdin);

    printf("Enter your address: ");
    fgets(account[*nUsers].address, 32, stdin);

    printf("Enter your 11-digit contact number: ");
    scanf("%s", account[*nUsers].contact);

    rmNewLine(account[*nUsers].pw);
    rmNewLine(account[*nUsers].name);
    rmNewLine(account[*nUsers].address);

    account[*nUsers].nProduct = 0;
    *nUsers += 1;
}


void adminMenu(User account[], int nUsers)
{
    int i;
    int choice = 0;

    do
    {
        printf("\n%s\n", "===============================");
        printf("         --ADMIN MENU--");
        printf("\n%s\n", "===============================");
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
            // SHOW ALL USERS
            case 1:
                system("clear");
                printf("\n   User ID\t|\tPassword\t|\t      Name \t\t|\t\t  Address\t\t|\tContact No.\n\n");
                for (i = 0; i < nUsers; i++)
                    printf("%10s\t\t%8s\t\t%18s\t\t%26s\t\t%11s\n\n", account[i].userID, account[i].pw, account[i].name, account[i].address, account[i].contact);
                break;

            // SHOW ALL SELLERS
            case 2:
                printf("\n   User ID\t|\tPassword\t|\t      Name \t\t|\t\t  Address\t\t|\tContact No.\n\n");
                for (i = 0; i < nUsers; i++)
                {
                    if (account[i].nProduct != 0)
                        printf("%10s\t\t%8s\t\t%18s\t\t%26s\t\t%11s\n\n", account[i].userID, account[i].pw, account[i].name, account[i].address, account[i].contact);
                }
                break;

            // BACK TO MAIN MENU
            case 6:
                printf("\nExiting back to Main Menu...\n");
                break;

            default:
                printf("\nEnter a valid input.\n");
        }

    } while (choice != 6);
}