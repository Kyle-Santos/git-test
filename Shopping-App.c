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

#include "Shopping-App.h"
#include "loadFiles.c"
#include "registerUser.c"
#include "userMenu.c"
#include "adminMenu.c"


int main()
{
    int i, j, choice;
    Item temp;
    User account[MAX_USERS]; // declares an array of users with a max of 100 users
    Transaction checkout[MAX_TRANSACTIONS]; // declares an array of transactions with a max of 1000
    int nUsers = 0; // this is to keep track of registered users
    int total_transactions = 0; // this is to keep track of number of transactions
    string username, pass;

    FILE *usertxt = fopen("Users.txt", "r");
    FILE *itemtxt = fopen("Items.txt", "r");
    FILE *transtxt = fopen("Transactions.dat", "rb");

    system("clear");
     
    if (usertxt == NULL || itemtxt == NULL)
        return 1;

    loadUsers(usertxt, account, &nUsers);
    loadItems(itemtxt, account, nUsers);
    fclose(usertxt);
    fclose(itemtxt);

    if (transtxt == NULL)
        return 1;

    // reads the Transactions.dat and stores the data in checkout array
    fread(&total_transactions, sizeof(int), 1, transtxt);
    fread(checkout, sizeof(Transaction), total_transactions, transtxt);
    fclose(transtxt);

    printWelcome();

    do
    {
        choice = 0;
        menu();

        scanf("%d", &choice);
        fflush(stdin);

        switch(choice)
        {
            // REGISTER USER
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

            // USER MENU
            case 2:
                userMenu(account, nUsers, checkout, &total_transactions);
                break;

            // ADMIN MENU
            case 3:
                printf("\nEnter username: ");
                scanf("%s", username);
                printf("\nEnter password: ");
                scanf("%s", pass);

                if (strcmp(username, "admin") == 0 && strcmp(pass, "admin") == 0)
                {
                    printf("\nYou are now logged in.\n");
                    sleep(1);
                    adminMenu(account, nUsers, checkout, total_transactions);
                }
                else
                    printf("\nIncorrect Admin Account\n");
                break;

            // EXIT
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


/************************************************   
    Prints a welcoming message
    @return N/A
    Pre-condition: 
************************************************/
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


/************************************************  
    Prints the main menu choices
    @return N/A
    Pre-condition: 
************************************************/
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


