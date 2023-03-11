/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying 
the concepts learned. I have constructed the functions and their respective algorithms and corresponding 
code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have 
not copied in part or whole or otherwise plagiarized the work of other students and/or persons.

Kyle Adrian L. Santos & Jan Kailu Eli A. Baradas, DLSU ID# <12209546> <12206717>
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // used solely for system("clear"), to clear the terminal when program is ran
#include <unistd.h> // library where sleep() is in; sleep was used to delay the display output

#include "userMenu.c"


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

    while (fscanf(txt, "%d %d", &pID, &sID) == 2)
    {

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
        getchar();

        for (i = 0; i < *nUsers; i++)
            if (account[i].userID == account[*nUsers].userID)
                i = *nUsers + 1;

        if (i != *nUsers)
            printf("User ID is taken. Please enter another.");

    } while (i != *nUsers);

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

    rmNewLine(account[*nUsers].pw);
    rmNewLine(account[*nUsers].name);
    rmNewLine(account[*nUsers].address);
    rmNewLine(account[*nUsers].contact);

    account[*nUsers].nProduct = 0;
    *nUsers += 1;
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