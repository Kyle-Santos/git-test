#include "Shopping-App.h"

int searchSeller(User acc[], const int nUsers, int *id)
{
    int i, j;

    for (i = 0; i <  nUsers; i++)
        for (j = 0; j < acc[i].nProduct; j++)
        {    
            if (acc[i].products[j].prodID == *id)
            {
                *id = j;
                return i;
            }
        }

    return 0;
}

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

void SortCartBySellerID(Item p[], int size)
{
    int i, j;
    int lowID, pos;
    Item temp;

    if (size != 0)
    {
        for (i = 0; i < size - 1; i++)
        {
            lowID = p[i].sellerID;
            pos = i;
            for (j = i + 1; j < size; j++)
                if (lowID > p[j].sellerID)
                {    
                    pos = j;
                    lowID = p[j].sellerID;
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

int SortUserBySellerID(User acc[], const int nUsers, int logged)
{
    int i, j;
    int lowID, pos;
    User temp;

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
            if (logged == i)
                logged = pos;
            else if (logged == pos)
                logged = i;
            temp = acc[i];
            acc[i] = acc[pos];
            acc[pos] = temp;
        }
    }
    return logged;
}

int findUser(User acc[], const int n, int id)
{
    int i;

    for (i = 0; i < n; i++)
        if (id == acc[i].userID)
            return i;

    return -1;
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
    int i;
    char t;

    for (i = 0; i < nUsers; i++)
        if (acc[i].nProduct != 0)
        {
            printf("\nSeller ID: %d\n", acc[i].userID);
            showItemsInTable(acc[i].products, acc[i].nProduct);

            if (i != nUsers - 1)
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

                rmNewLine(thing->item_name);
                rmNewLine(thing->category);
                rmNewLine(thing->description);

                *numProduct += 1; // updates the number of different products sold by one person

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
                            scanf(" %c", &t);
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


void getDate(int *m, int *d, int *y)
{
    do
    {
        printf("\nEnter the current month in numeric: ");
        scanf("%d", m);
        printf("Enter the current day in numeric: ");
        scanf("%d", d);
        printf("Enter the current year in numeric: ");
        scanf("%d", y);

    } while ((*m > 12 && *m <= 0) || (*d > 31 && *d <= 0));
}


void buyMenu(User acc[], const int nUsers, int accInd)
{
    int i, j, k,// counter
        choice = 0, 
        found = 0, 
        id = 0,
        id_prod = 0,
        quantity = 0,
        available = 0,
        month, day, year;
    char t;
    double total_amount = 0;
    string category, bin;
    Item *thing;
    FILE *bag = NULL;
    Item remove;
    
    sprintf(bin, "%d.bag", acc[accInd].userID);
    bag = fopen(bin, "rb");

    if (bag != NULL)
    {
        fread(&acc[accInd].inCart, sizeof(int), 1, bag);
        fread(acc[accInd].cart, sizeof(Item), acc[accInd].inCart, bag);
    }
    fclose(bag);

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
                accInd = SortUserBySellerID(acc, nUsers, accInd);
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
                    printf("\nSeller ID does not exist. You will be redirected back to the Buy Menu.\n");
                    sleep(1);
                }
                    
                break;
            
            // SEARCH PRODUCTS BY CATEGORY
            case 3:
                printf("\nWhat category of products do you wanna see? ");
                scanf("%s", category);

                for (i = 0; i < nUsers; i++)
                {
                    if (acc[i].nProduct != 0)
                    {
                        for (j = 0; j < acc[i].nProduct; j++)
                            if (strcmp(category, acc[i].products[j].category) == 0)
                            {
                                found = 1;
                                thing = &acc[i].products[j]; // stores the address of the struct Item of the user in access
                                printf("\nProduct ID: %d\nItem Name: %s\nCategory: %s\nDescription: %s\nUnit Price: %.2lf\nQuantity: %d\n\n", thing->prodID, thing->item_name, thing->category, thing->description, thing->price, thing->quantity);
                                
                                if (j != acc[i].nProduct - 1)
                                {
                                    printf("Type [N] to see next or [X] to exit viewing: ");
                                    scanf(" %c", &t);
                                    getchar();
                                }

                                if (t != 'N') j = acc[i].nProduct;
                            }
                            
                    }
                }
                    
                if (!found)
                {
                    printf("\nCategory does not exist. You will be redirected back to the User Menu.\n");
                    sleep(1);
                }
                break;

            // SEARCH PRODUCTS BY NAME'
            case 4:

                break;

            // ADD TO CART
            case 5:
                if (acc[accInd].inCart == 10)
                {
                    printf("\nCart already has 10 items. Please check out or remove items.\n");
                    sleep(1);
                    break;
                }

                id_prod = 0;

                do 
                {
                    printf("\nEnter the product ID of the item you wanna add to your cart: ");
                    scanf("%d", &id_prod);
                    getchar();
                    
                    found = searchSeller(acc, nUsers, &id_prod);
                } while (!found);

                printf("Enter the quantity you wanna buy: ");
                scanf("%d", &quantity);
                
                if (quantity > acc[found].products[id_prod].quantity || quantity <= 0)
                    printf("\nError: Quantity entered is invalid. Item wasn't added.\n");
                else
                {
                    acc[accInd].cart[acc[accInd].inCart] = acc[found].products[id_prod];
                    acc[accInd].cart[acc[accInd].inCart].quantity = quantity;
                    acc[accInd].inCart++;
                }

                break;

            // EDIT CART
            case 6:
                choice = 0;

                do
                {
                    showItemsInTable(acc[accInd].cart, acc[accInd].inCart);
                    printf("\n%s\n", "===============================");
                    printf("%s\n", "         Edit Your Cart");
                    printf("%s\n", "===============================");
                    printf("\n[1] Remove All Items From Seller\n");
                    printf("[2] Remove Specific Item\n");
                    printf("[3] Edit Quantity\n");
                    printf("[4] Finish Edit Cart\n\n");
                    scanf("%d", &choice);
                    getchar();

                    switch(choice)
                    {
                        // REMOVE ALL ITEMS
                        case 1:
                            for (i = 0; i < acc[accInd].inCart; i++)
                                acc[accInd].cart[i] = remove;
                            
                            acc[accInd].inCart = 0;
                            printf("\nItems in cart is successfully removed.\n");
                            sleep(1);
                            break;

                        // REMOVE A SPEFICIC ITEM
                        case 2:
                            id_prod = 0;

                            do
                            {
                                printf("\nEnter the product ID of the item you wanna remove from your cart: ");
                                scanf("%d", &id_prod);
                                getchar();
                            } while (id_prod == 0);

                            for (i = 0; i < acc[accInd].inCart; i++)
                            {
                                if (id_prod == acc[accInd].cart[i].prodID)
                                {
                                    acc[accInd].cart[i] = remove;
                                    
                                    for (j = i + 1; j < acc[accInd].inCart; j++, i++)
                                        acc[accInd].cart[i] = acc[accInd].cart[j];

                                    acc[accInd].inCart -= 1;
                                    id_prod = 0;
                                }
                            }

                            if (id_prod != 0)
                                printf("Product ID does not exist.\n");
                            else
                                printf("Item has been successfully removed.\n");

                            sleep(1);
                            break;

                        // EDIT QUANITY
                        case 3:
                            id_prod = 0, quantity = 0;

                            do
                            {
                                printf("\nEnter the product ID of the item you wanna change the quantity from your cart: ");
                                scanf("%d", &id_prod);
                                getchar();
                            } while (id_prod == 0);

                            for (i = 0; i < acc[accInd].inCart; i++)
                            {
                                if (id_prod == acc[accInd].cart[i].prodID)
                                {
                                    printf("Enter the new quantity: ");
                                    scanf("%d", &quantity);
                                    
                                    for (j = 0; j < nUsers; j++)
                                        if (acc[accInd].cart[i].sellerID == acc[j].userID)
                                        {
                                            if (quantity > acc[accInd].products[j].quantity || quantity <= 0)
                                                id_prod = -1;
                                            else   
                                            {
                                                id_prod = 0; 
                                                acc[accInd].cart[i].quantity = quantity;
                                            }
                                        }
                                }
                            }

                            if (id_prod == -1)
                                printf("\nError: Quantity entered is invalid. Quantity wasn't changed\n");
                            else if (id_prod == 0)
                                printf("Quantity has been successfully modified.\n");
                            else
                                printf("\nError: Product ID does not exist.\n");

                            sleep(1);
                            break;

                        case 4:
                            printf("\nGoing back to the Buy Menu...\n");
                            sleep(1);
                            break;

                        default:
                            printf("\nError: Please enter a valid input.\n");
                            sleep(1);
                    
                    }

                } while (choice != 4);

                break;

            // CHECK OUT MENU
            case 7:
                choice = 0;

                // check if cart of any product quantity is more than the stocks of the seller
                for (i = 0; i < acc[accInd].inCart; i++)
                {
                    for (j = 0; j < nUsers; j++)
                        if (acc[accInd].cart[i].sellerID == acc[j].userID)
                            for (k = 0; k < acc[j].nProduct; k++)
                                if (acc[j].products[k].prodID == acc[accInd].cart[i].prodID)
                                {
                                    if (acc[j].products[k].quantity < acc[accInd].cart[i].quantity)
                                    {
                                        printf("\nThe quantity of the product was changed.\n");
                                        printf("Please go to EDIT CART to modify your cart.\n"); 
                                        printf("The new quantity is %d and its new price is %.2lf pesos.\n", acc[j].products[k].quantity, acc[j].products[k].price);
                                        available = 0;
                                    }
                                    else 
                                        available = 1;
                                }
                }

                if (available)
                {
                    getDate(&month, &day, &year);

                    do 
                    {
                        printf("\n%s\n", "===============================");
                        printf("%s\n", "        Check Out Menu");
                        printf("%s\n", "===============================");
                        printf("\n[1] All\n");
                        printf("[2] By a Specific Seller\n");
                        printf("[3] Specific Item\n");
                        printf("[4] Exit Check Out\n\n");
                        scanf("%d", &choice);
                        getchar();

                        switch (choice)
                        {
                            case 1:
                                total_amount = 0;
                                SortCartBySellerID(acc[accInd].cart, acc[accInd].inCart);

                                printf("\nQuantity |\tProduct ID\t|\tItem Name\t|\tUnit Price\t|\tTotal\n\n");

                                for (i = 0; i < acc[accInd].inCart; i++)
                                {   
                                    if (id != acc[accInd].cart[i].sellerID)
                                    {
                                        id = acc[accInd].cart[i].sellerID;

                                        for (j = 0; j < acc[accInd].inCart; j++)
                                        {
                                            thing = &acc[accInd].cart[j];
                                            if (thing->sellerID == id)
                                            {
                                                printf("%8d \t%10d\t\t%8s\t\t%10.2lf\t\t%3.2lf\n\n", thing->quantity, thing->prodID, thing->item_name, thing->price, thing->price * thing->quantity);
                                                total_amount += (thing->price * thing->quantity);
                                            }
                                        }

                                        // fix the bug where users are able to buy from themselves. fix the data type of numerics
                                        found = findUser(acc, nUsers,id);
                                        printf("\nTotal amount due: %lf\n", total_amount);
                                        printf("\nSeller ID: %d\tSeller Name: %s\n", acc[found].userID, acc[found].name);
                                    }
                                }
                                break;

                            case 2:
                                id = 0;
                                showItemsInTable(acc[accInd].cart, acc[accInd].inCart);
                                printf("Input the seller ID of the seller: ");
                                scanf("%d", &id);

                                printf("\nQuantity\t|\tProduct ID\t|\tItem Name\t|\tUnit Price\t|\tTotal\n\n");

                                for (i = 0; i < acc[accInd].inCart; i++)
                                {
                                    thing = &acc[accInd].cart[i];
                                    if (thing->sellerID == id)
                                        printf("%8d\t\t%10d\t\t%8s\t\t%10.2lf\t\t%5.2lf\n\n", thing->quantity, thing->prodID, thing->item_name, thing->price, thing->price * thing->quantity);
                                }
                                break;
                            
                            case 3:
                                break;

                            case 4:
                                printf("\nGoing back to the Buy Menu...\n");
                                sleep(1);
                                break;
                            
                            default:
                                printf("\nError: Please enter a valid input.\n");
                                sleep(1);
                        }
                    } while (choice != 4);
                }
                else
                    sleep(1);        

                break;

            // EXIT BUY MENU
            case 8:
                printf("\nExiting Buy Menu...\n");
                sleep(1);
                break;
            
            default:
                printf("\nEnter a valid input.\n");
        }
    } while (choice != 8);
}


void userMenu(User account[], int nUsers)
{
    int i, on = 1; // ctr
    int ID; 
    char pass[11];
    int choice = 0; // choice for seller menu
    string name, binName; 
    FILE *bin = NULL;
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
                printf("\n%s\n", "===============================");
                printf("           USER MENU");
                printf("\n%s\n", "===============================");

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
                        // pass transactions
                        buyMenu(account, nUsers, i);
                        break;
                    case 3: // exit user menu
                        if (account[i].inCart != 0)
                        {
                            printf("\nSaving user's unchecked out cart...\n");
                            sleep(1);
                            sprintf(binName, "%d.bag", account[i].userID);
                            bin = fopen(binName, "wb");
                            fwrite(&account[i].inCart, sizeof(int), 1, bin);
                            fwrite(account[i].cart, sizeof(Item), account[i].inCart, bin);
                            fclose(bin);
                        }

                        printf("\nSigning out user %s...\n\n", name);
                        on = 0;
                        i = nUsers + 1;
                        break;

                }
            }
        }
    }

    if (nUsers == i)
        printf("\nUser ID or Password is incorrect. You will be redirected back to the menu.\n");

}

