#include "Shopping-App.h"


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

                do
                {
                    printf("\nEnter a unique Product ID: ");
                    scanf("%d", &thing->prodID);
                    getchar();

                    for (i = 0; i < acc->nProduct; i++)
                        if (acc->products[i].prodID == thing->prodID)
                            i = *numProduct + 1;

                    if (i != *numProduct)
                        printf("\nProduct ID already exists. Please enter another.\n");

                } while (i != *numProduct);

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
                showItemsInTable(acc->products, acc->nProduct);

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
                showItemsInTable(acc->products, acc->nProduct);
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
                        if (acc[i].nProduct != 0)
                            showItemsInTable(acc[i].products, acc[i].nProduct);
                        else
                            printf("\nSeller does not have any products being sold.\n");
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
    int i, on = 1; // ctr
    int ID; 
    char pass[11];
    int choice = 0; // choice for seller menu
    string name;
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

