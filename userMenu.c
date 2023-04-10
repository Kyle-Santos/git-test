
/******************************************************
    Function to check if a string contains a substring
    @param string str - string that contains any character
    @param string substr - string keyword to be checked
    @return 1 if substring is found, 0 if not
    Pre-condition: 
******************************************************/
int contains_substring(string str, string substr) {
    int str_len = strlen(str);
    int substr_len = strlen(substr);
	int i, j;
    for (i = 0; i <= str_len - substr_len; i++) {
        for (j = 0; j < substr_len; j++) {
            if (str[i + j] != substr[j]) {
                break;
            }
        }
        if (j == substr_len) {
            return 1; // True, the substring is found
        }
    }
    return 0; // False, the substring is not found
}


/******************************************************
    Gets the input date from the user
    @param - int *m - address of the month variable
    @param - int *d - address of the day variable
    @param - int *y - address of the year variable
    @return N/A
    Pre-condition: 
******************************************************/
void getDate(int *m, int *d, int *y)
{
    do
    {
        printf("\nEnter the date of transaction (MM/DD/YYYY): ");
        scanf("%d/%d/%d", m, d, y);
        fflush(stdin);
    } while ((*m > 12 && *m <= 0) || (*d > 31 && *d <= 0) || *y < 1900);
}


/******************************************************
    Search seller ID in the array of users and returns the seller's index
    @param User acc[] - array of users
    @param const int nUsers - The number of user in the array
    @param string id - the product id of the product that is being looked for
    @param *prod_index - parameter for storing the index of the product  
    @return seller's index if found, 0 if not
    Pre-condition: 
******************************************************/
int searchSeller(User acc[], const int nUsers, string id, int *prod_index)
{
    int i, j;

    for (i = 0; i <  nUsers; i++)
        for (j = 0; j < acc[i].nProduct; j++)
        {    
            if (strcmp(acc[i].products[j].prodID, id) == 0)
            {
                *prod_index = j;
                return i;
            }
        }

    return 0;
}


/******************************************************
    Sorts an Item array by product ID. (from lowest to highest)
    @param Item p[] - array of items
    @param int size - size of the array
    @return N/A
    Pre-condition: 
******************************************************/
void SortByProdID(Item p[], int size)
{
    int i, j; // variables for looping
    string lowID;
    int pos;
    Item temp;

    if (size != 0)
    {
        for (i = 0; i < size - 1; i++)
        {
            strcpy(lowID, p[i].prodID);
            pos = i;
            for (j = i + 1; j < size; j++)
                if (strcmp(lowID, p[j].prodID) > 0)
                {    
                    pos = j;
                    strcmp(lowID, p[j].prodID);
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


/******************************************************
    Sorts an Item array by seller ID. (from lowest to highest)
    @param - Item p[] - array of items
    @param - int size - size of p array
    @return N/A
    Pre-condition:
******************************************************/
void SortCartBySellerID(Item p[], int size)
{
    int i, j; // variables for looping
    string lowID;
    int pos;
    Item temp;

    if (size != 0)
    {
        for (i = 0; i < size - 1; i++)
        {
            strcpy(lowID, p[i].sellerID);
            pos = i;
            for (j = i + 1; j < size; j++)
                if (strcmp(lowID, p[j].sellerID) > 0)
                {    
                    pos = j;
                    strcpy(lowID, p[j].sellerID);
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


/******************************************************
    Sorts User array by user ID. (from lowest to highest) returns the index of the user currently logged in.
    @param - User acc[] - array of users 
    @param - const int nUsers - number of users 
    @param - int logged
    @return index of the user currently logged in
    Pre-condition: 
******************************************************/
int SortUserByUserID(User acc[], const int nUsers, int logged)
{
    int i, j; // variables for looping
    string lowID;
    int pos;
    User temp;

    for (i = 0; i < nUsers - 1; i++)
    {
        strcpy(lowID, acc[i].userID);
        pos = i;
        for (j = i + 1; j < nUsers; j++)
            if (strcmp(lowID, acc[j].userID) > 0)
            {    
                pos = j;
                strcpy(lowID, acc[j].userID);
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


/******************************************************
    Search user ID in the array of users and returns the user's index
    @param - User acc[] - array of users
    @param - const int n - number of users in the array
    @param - string id - user id being looked for
    @return user's index
    Pre-condition: 
******************************************************/
int findUser(User acc[], const int n, string id)
{
    int i;

    for (i = 0; i < n; i++)
        if (strcmp(id, acc[i].userID) == 0)
            return i;

    return -1;
}


/******************************************************
    print items in a table
    @param - Item p[] - array of items
    @param - int n - number of items in the array
    @return N/A
    Pre-condition: 
******************************************************/
void showItemsInTable(Item p[], int n)
{
    int i;
    printf("\nSeller ID\t|\tProduct ID\t|\tItem Name\t|\tCategory\t|\tUnit Price\t|\tQuantity\n");
    printf("================================================================================================================================\n");
    for (i = 0; i < n; i++)
        printf("%9s\t\t%10s\t\t%-8s\t\t%-8s\t\t%10.2lf\t\t%8d\n\n", p[i].sellerID, p[i].prodID, p[i].item_name, p[i].category, p[i].price, p[i].quantity);
}


/******************************************************
    Asks the user whether he wants to continue viewing or exit
    @param - int *curr - is the current index in the array of something
    @param - int max - is the maximum where *curr can reach
    @return N/A
    Pre-condition: *curr shouldn't be >= max
******************************************************/
void continueNext(int *curr, int max)
{
    char t;

    do
    {
        if (*curr != max - 1)
        {
            printf("Type [N] to see next or [X] to exit viewing: ");
            scanf(" %c", &t);
            fflush(stdin);
        }
        else t = 'X';

        if (t == 'X') *curr = max;
    } while (t != 'X' && t != 'N');
}


/******************************************************
    prints the products by seller ID
    @param - User acc[] - array of items
    @param - const int nUsers - number of items in the array
    @return N/A
    Pre-condition: 
******************************************************/
void ViewProdBySellerID(User acc[], const int nUsers)
{
    int i;

    for (i = 0; i < nUsers; i++)
        if (acc[i].nProduct != 0)
        {
            printf("\nSeller ID: %s\n", acc[i].userID);
            showItemsInTable(acc[i].products, acc[i].nProduct);

            continueNext(&i, nUsers);
        }
}


/******************************************************
    All features of Sell Menu
    @param - User *acc - the user that is currently logged in 
    @param - int *numProduct - number of products that the seller is currently selling
    @return N/A
    Pre-condition: 
******************************************************/
void sellMenu(User *acc, int *numProduct)
{
    Item *thing = NULL;
    int i, temp;
    int choice = 0, prod = 0, found = 0;
    string selectProd;

    do
    {
        printf("\n--SELL MENU--\n");
        printf("\n[1] Add New Item\n");
        printf("[2] Edit Stock\n");
        printf("[3] Show My Products\n");
        printf("[4] Show My Low Stock Products\n");
        printf("[5] Exit Sell Menu\n\n");

        scanf("%d", &choice);
        fflush(stdin);

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
                    do
                    {
                        printf("\nEnter a unique Product ID (MAX 8): ");
                        scanf("%s", thing->prodID);
                    } while (isNumeric(thing->prodID) == 1 || isLenCorrect(thing->prodID, ANY_ID_LEN) == 1);

                    for (i = 0; i < acc->nProduct; i++)
                        if (strcmp(acc->products[i].prodID, thing->prodID) == 0)
                            i = *numProduct + 1;

                    if (i != *numProduct)
                        printf("\nProduct ID already exists. Please enter another.\n");

                } while (i != *numProduct);

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

                strcpy(thing->sellerID, acc->userID);

                rmNewLine(thing->item_name);
                rmNewLine(thing->category);
                rmNewLine(thing->description);

                *numProduct += 1; // updates the number of different products sold by one person

                break;
            
            // EDIT STOCK
            case 2:
                // SORT AND DSIPLAY A TABLE
                SortByProdID(acc->products, *numProduct);
                showItemsInTable(acc->products, acc->nProduct);

                // asks for product ID and checks if ID is valid
                printf("\nWhat product do you wish to edit (ENTER PRODUCT ID)? ");
                scanf("%s", selectProd);
                for (i = 0; i < *numProduct; i++)
                    if (strcmp(selectProd, acc->products[i].prodID) == 0)
                    {
                        found = 1;
                        prod = i;
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
                            acc->products[prod].quantity += temp;
                            break;
                        case 2: // CHANGE PRICE
                            printf("\nHow much should be the new price of the product? ");
                            scanf("%lf", &acc->products[prod].price);
                            break;
                        case 3: // CHANGE ITEM NAME
                            printf("\nWhat should be the new name of the product? ");
                            fgets(acc->products[prod].item_name, 22, stdin);
                            rmNewLine(acc->products[prod].item_name);
                            break;
                        case 4: // CHANGE CATEGORY
                            printf("\nWhat should be the new name of the product? ");
                            fgets(acc->products[prod].category, 17, stdin);
                            rmNewLine(acc->products[prod].category);
                            break;
                        case 5: // CHANGE DESCRIPTION
                            printf("\nWhat should be the new description of the product? ");
                            fgets(acc->products[prod].description, 32, stdin);
                            rmNewLine(acc->products[prod].description);
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
                SortByProdID(acc->products, *numProduct);
                showItemsInTable(acc->products, acc->nProduct);
                break;
            
            // SHOW MY LOW STOCK PRODUCTS
            case 4:
                for (i = 0; i < *numProduct; i++)
                {
                    thing = &acc->products[i]; // stores the address of the struct Item of the user in access
                    if (thing->quantity < 5)
                    {
                        printf("\nProduct ID: %s\nItem Name: %s\nCategory: %s\nDescription: %s\nUnit Price: %.2lf\nQuantity: %d\n\n", thing->prodID, thing->item_name, thing->category, thing->description, thing->price, thing->quantity);

                        continueNext(&i, *numProduct);
                    }
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


/******************************************************
    All features of Buy Menu
    @param - User acc[] - array of users
    @param - const int nUsers - number of users
    @param - int accInd - index of the user that is logged in 
    @param - Transaction out[] - array of transactions
    @param - int *nTrans - number of transactions 
    @return N/A
    Pre-condition: 
******************************************************/
int buyMenu(User acc[], const int nUsers, int accInd, Transaction out[], int *nTrans)
{
    int i, j, k, // counter
        choice = 0, 
        found = 0, 
        id_prod = 0,
        quantity = 0,
        available = 0,
        month, day, year;
    int *n; // int pointer for storing address of struct int elements. TO SHORTEN CALLING STRUCTS
    double total_amount = 0;
    string category, bin, id, search;
    Item *thing;
    FILE *bag = NULL, *trans;
    Item remove = {0}; // empty struct for removing elements of a struct array 
    
    sprintf(bin, "%s.bag", acc[accInd].userID);
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
        fflush(stdin);

        found = 0;

        switch (choice)
        {
            // VIEW ALL PRODUCTS
            case 1:
                accInd = SortUserByUserID(acc, nUsers, accInd);
                ViewProdBySellerID(acc, nUsers);
                break;

            // SHOW ALL PRODUCTS BY A SPECIFIC SELLER
            case 2:
                printf("\nEnter the seller ID of the seller: ");
                scanf("%s", id);
                getchar();

                found = findUser(acc, nUsers, id);

                if (found != -1)
                {
                    if (acc[found].nProduct != 0)
                        showItemsInTable(acc[found].products, acc[found].nProduct);
                    else
                        printf("\nSeller does not have any products being sold.\n");
                }
                else
                    printf("\nSeller ID does not exist.\n");
                    
                printf("\nYou will be redirected back to the Buy Menu...\n");
                sleep(1);  
                break;
            
            // SEARCH PRODUCTS BY CATEGORY
            case 3:
                printf("\nWhat category of products do you wanna see? ");
                scanf("%s", category);

                for (i = 0; i < nUsers; i++)
                {
                    for (j = 0; j < acc[i].nProduct; j++)
                        if (strcmp(category, acc[i].products[j].category) == 0)
                        {
                            found = 1;
                            thing = &acc[i].products[j]; // stores the address of the struct Item of the user in access
                            printf("\nProduct ID: %s\nItem Name: %s\nCategory: %s\nDescription: %s\nUnit Price: %.2lf\nQuantity: %d\n\n", thing->prodID, thing->item_name, thing->category, thing->description, thing->price, thing->quantity);
                            
                            continueNext(&j, acc[i].nProduct);
                        }
                }
                    
                if (!found)
                {
                    printf("\nCategory does not exist. You will be redirected back to the User Menu.\n");
                    sleep(1);
                }
                break;

            // SEARCH PRODUCTS BY NAME
            case 4:
                printf("\nEnter the keyword you want to search for: ");
			    scanf("%s", search);

			    for(i = 0; i < nUsers; i++)
                {
                    for (j = 0; j < acc[i].nProduct; j++) 
                    {
                        if (contains_substring(acc[i].products[j].item_name, search)) 
                        {
                            found = 1;
                            printf("\nProduct ID: %s\nItem Name: %s\nQuantity: %d\nPrice: %.2lf\n\n", acc[i].products[j].prodID, acc[i].products[j].item_name, acc[i].products[j].quantity,acc[i].products[j].price);
                            
                            continueNext(&i, acc[i].nProduct);
                        }
                    }
		        }
			    if (!found) 
                {
			        printf("\nKeyword does not match any products. You will be redirected back to the User Menu.\n");
			        sleep(1);
			    }

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
                    scanf("%s", id);
                    getchar();
                    
                    found = searchSeller(acc, nUsers, id, &id_prod);

                    // checks if the seller ID found is the same as the buyer.
                    // To avoid buying from self
                    if (found)
                    {
                        if (strcmp(acc[accInd].userID, acc[found].userID) == 0)
                        {
                            printf("\nError: You cannot buy products from yourself.\n");
                            found = 0;
                        }
                        for (i = 0; i < acc[accInd].inCart; i++)
                            if (strcmp(id, acc[accInd].cart[i].prodID) == 0)
                            {
                                printf("\nError: You can't add to cart item that is already in your cart.\n");
                                printf("\nYou will be redirected back to Buy Menu.\n");
                                i = acc[accInd].inCart + 1;
                            }
                        
                        if (i == acc[accInd].inCart)
                        {
                            printf("Enter the quantity you wanna buy: ");
                            scanf("%d", &quantity);
                            
                            if (quantity > acc[found].products[id_prod].quantity || quantity <= 0)
                                printf("\nError: Quantity entered is invalid. Item wasn't added.\n");
                            else
                            {
                                acc[accInd].cart[acc[accInd].inCart] = acc[found].products[id_prod];
                                acc[accInd].cart[acc[accInd].inCart].quantity = quantity;
                                acc[accInd].inCart++;
                                printf("\nItem successfully added.\n");
                                sleep(1);
                            }
                        }
                    }


                } while (!found);

                sleep(1);
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

                            printf("\nEnter the product ID of the item you wanna remove from your cart: ");
                            scanf("%s", id);

                            for (i = 0; i < acc[accInd].inCart; i++)
                            {
                                if (strcmp(id, acc[accInd].cart[i].prodID) == 0)
                                {   
                                    for (j = i + 1; j < acc[accInd].inCart; j++, i++)
                                        acc[accInd].cart[i] = acc[accInd].cart[j];

                                    acc[accInd].inCart -= 1;
                                    id_prod = 1;
                                }
                            }

                            if (id_prod != 1)
                                printf("Product ID does not exist.\n");
                            else
                                printf("Item has been successfully removed.\n");

                            sleep(1);
                            break;

                        // EDIT QUANITY
                        case 3:
                            id_prod = 0, quantity = 0;

                            printf("\nEnter the product ID of the item you wanna change the quantity from your cart: ");
                            scanf("%s", id);

                            for (i = 0; i < acc[accInd].inCart; i++)
                            {
                                if (strcmp(id, acc[accInd].cart[i].prodID) == 0)
                                {
                                    printf("Enter the new quantity: ");
                                    scanf("%d", &quantity);
                                    
                                    for (j = 0; j < nUsers; j++)
                                        if (strcmp(acc[accInd].cart[i].sellerID, acc[j].userID) == 0)
                                        {
                                            if (quantity > acc[accInd].products[j].quantity || quantity <= 0)
                                                id_prod = -1;
                                            else   
                                            {
                                                id_prod = 1; 
                                                acc[accInd].cart[i].quantity = quantity;
                                            }
                                        }
                                }
                            }

                            if (id_prod == -1)
                                printf("\nError: Quantity entered is invalid. Quantity wasn't changed\n");
                            else if (id_prod == 1)
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
                available = 0;
                choice = 0;

                // check if cart of any product quantity is more than the stocks of the seller
                for (i = 0; i < acc[accInd].inCart; i++)
                {
                    found = findUser(acc, nUsers, acc[accInd].cart[i].sellerID);

                    for (j = 0; j < acc[found].nProduct; j++)
                        if (strcmp(acc[found].products[j].prodID, acc[accInd].cart[i].prodID) == 0)
                        {
                            if (acc[found].products[j].quantity < acc[accInd].cart[i].quantity)
                            {
                                printf("\nThe quantity of the product was changed.\n");
                                printf("Please go to EDIT CART to modify your cart.\n"); 
                                printf("\nThe new quantity of %s is %d and its new price is %.2lf pesos.\n", acc[found].products[j].item_name, acc[found].products[j].quantity, acc[found].products[j].price);
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
                            // ALL
                            case 1:
                                strcpy(id, "");
                                total_amount = 0;

                                // sorts the cart items by seller ID
                                SortCartBySellerID(acc[accInd].cart, acc[accInd].inCart);

                                printf("\nQuantity |\tProduct ID\t|\tItem Name\t|\tUnit Price\t|\tTotal\n\n");

                                // loops through the cart
                                for (i = 0; i < acc[accInd].inCart; i++)
                                {   
                                    // if id is not equal to current seller ID in cart
                                    if (strcmp(id, acc[accInd].cart[i].sellerID) != 0)
                                    {
                                        n = &out[*nTrans].nItems;
                                        *n = 0;

                                        strcpy(id, acc[accInd].cart[i].sellerID);

                                        // since everything is sorted we can continue indexing until seller ID is not equal to ID
                                        for (j = i; j < acc[accInd].inCart; j++)
                                        {
                                            thing = &acc[accInd].cart[j];
                                            if (strcmp(thing->sellerID, id) == 0)
                                            {
                                                printf("%8d \t%10s\t\t%8s\t\t%10.2lf\t\t%3.2lf\n\n", thing->quantity, thing->prodID, thing->item_name, thing->price, thing->price * thing->quantity);
                                                total_amount += (thing->price * thing->quantity);
                                                out[*nTrans].checkout[*n] = *thing;
                                                *n += 1;

                                                strcpy(id, thing->sellerID);

                                                found = findUser(acc, nUsers, id);
                                                for (k = 0; k < acc[found].nProduct; k++)
                                                    if (strcmp(thing->prodID, acc[found].products[k].prodID) == 0)
                                                        acc[found].products[k].quantity -= thing->quantity;
                                            }
                                        }

                                        printf("\nTotal amount due: %.2lf\n", total_amount);
                                        printf("\nSeller ID: %s\tSeller Name: %s\n", acc[found].userID, acc[found].name);

                                        // add transaction
                                        out[*nTrans].date.month = month;
                                        out[*nTrans].date.day = day;
                                        out[*nTrans].date.year = year;
                                        
                                        out[*nTrans].amount = total_amount;
                                        strcpy(out[*nTrans].sellerID, acc[found].userID);
                                        strcpy(out[*nTrans].buyerID, acc[accInd].userID);

                                        // remove in cart
                                        for (i = 0; i < acc[accInd].inCart; i++)
                                            acc[accInd].cart[i] = remove;
                                        
                                        acc[accInd].inCart = 0;

                                        *nTrans += 1;
                                    }
                                }

                                //printf("\n\n%d/%d/%d %s %s %.2lf\n\n", out[0].date.month, out[0].date.day, out[0].date.year, out[0].buyerID, out[0].sellerID, out[0].amount);

                                sleep(1);
                                break;

                            // BY A SPECIFIC SELLER
                            case 2:
                                if (acc[accInd].inCart > 0)
                                {
                                    total_amount = 0;
                                    
                                    showItemsInTable(acc[accInd].cart, acc[accInd].inCart);
                                    printf("Input the seller ID of the seller: ");
                                    scanf("%s", id);

                                    printf("\nQuantity\t|\tProduct ID\t|\tItem Name\t|\tUnit Price\t|\tTotal\n\n");

                                    n = &out[*nTrans].nItems;
                                    *n = 0;

                                    for (i = 0; i < acc[accInd].inCart; i++)
                                    {
                                        thing = &acc[accInd].cart[i];
                                        if (strcmp(thing->sellerID, id) == 0)
                                        {
                                            printf("%8d\t\t%10s\t\t%8s\t\t%10.2lf\t\t%5.2lf\n\n", thing->quantity, thing->prodID, thing->item_name, thing->price, thing->price * thing->quantity);
                                            total_amount += (thing->price * thing->quantity);
                                            out[*nTrans].checkout[*n] = *thing;
                                            *n += 1;

                                            strcpy(id, thing->sellerID);

                                            found = findUser(acc, nUsers, id);
                                            for (j = 0; j < acc[found].nProduct; j++)
                                                if (strcmp(thing->prodID, acc[found].products[j].prodID) == 0)
                                                    acc[found].products[j].quantity -= thing->quantity;
                                        }
                                    }
                                    
                                    if (found)
                                    {
                                        printf("\nTotal amount due: %lf\n", total_amount);
                                        printf("\nSeller ID: %s\tSeller Name: %s\n", acc[found].userID, acc[found].name);

                                        // add transaction
                                        out[*nTrans].date.month = month;
                                        out[*nTrans].date.day = day;
                                        out[*nTrans].date.year = year;
                                        
                                        out[*nTrans].amount = total_amount;
                                        strcpy(out[*nTrans].sellerID, acc[found].userID);
                                        strcpy(out[*nTrans].buyerID, acc[accInd].userID);


                                        for (i = 0; i < out[*nTrans].nItems; i++)
                                        {
                                            for (j = 0; j < acc[accInd].inCart; j++)
                                            {
                                                if (strcmp(out[*nTrans].checkout[i].prodID, acc[accInd].cart[j].prodID) == 0)
                                                {    
                                                    for (k = j + 1; k < acc[accInd].inCart; k++, j++)
                                                        acc[accInd].cart[j] = acc[accInd].cart[k];

                                                    acc[accInd].inCart -= 1;
                                                }
                                            }
                                        }

                                        *nTrans += 1;
                                    }
                                }
                                else
                                    printf("\nTheres nothing to check out.\n");
                                
                                sleep(1);
                                break;
                            
                            // SPECIFIC ITEM
                            case 3:
                                if (acc[accInd].inCart > 0)
                                {
                                    total_amount = 0;
                                    
                                    showItemsInTable(acc[accInd].cart, acc[accInd].inCart);
                                    printf("Input the Product ID of the item: ");
                                    scanf("%s", id);

                                    printf("\nQuantity\t|\tProduct ID\t|\tItem Name\t|\tUnit Price\t|\tTotal\n\n");

                                    n = &out[*nTrans].nItems;
                                    *n = 0;

                                    for (i = 0; i < acc[accInd].inCart; i++)
                                    {
                                        thing = &acc[accInd].cart[i];
                                        if (strcmp(thing->prodID, id) == 0)
                                        {
                                            printf("%8d\t\t%10s\t\t%8s\t\t%10.2lf\t\t%5.2lf\n\n", thing->quantity, thing->prodID, thing->item_name, thing->price, thing->price * thing->quantity);
                                            total_amount += (thing->price * thing->quantity);
                                            out[*nTrans].checkout[*n] = *thing;
                                            *n += 1;
                                            i = acc[accInd].inCart + 1;
                                            strcpy(id, thing->sellerID);

                                            found = findUser(acc, nUsers, id);
                                            for (j = 0; j < acc[found].nProduct; j++)
                                                if (strcmp(thing->prodID, acc[found].products[j].prodID) == 0)
                                                    acc[found].products[j].quantity -= thing->quantity;
                                        }
                                    }

                                    if (i != acc[accInd].inCart)
                                    {
                                        //found = findUser(acc, nUsers, id);
                                        printf("\nTotal amount due: %lf\n", total_amount);
                                        printf("\nSeller ID: %s\tSeller Name: %s\n", acc[found].userID, acc[found].name);

                                        // add transaction
                                        out[*nTrans].date.month = month;
                                        out[*nTrans].date.day = day;
                                        out[*nTrans].date.year = year;
                                        
                                        out[*nTrans].amount = total_amount;
                                        strcpy(out[*nTrans].sellerID, acc[found].userID);
                                        strcpy(out[*nTrans].buyerID, acc[accInd].userID);

                                        for (i = 0; i < acc[accInd].inCart; i++)
                                        {
                                            if (strcmp(out[*nTrans].checkout[i].prodID, acc[accInd].cart[j].prodID) == 0)
                                            {
                                                for (j = i + 1; j < acc[accInd].inCart; i++, j++)
                                                    acc[accInd].cart[j] = acc[accInd].cart[k];
                                                    
                                                acc[accInd].inCart -= 1;
                                                i = acc[accInd].inCart + 1;
                                            }
                                        }

                                        *nTrans += 1;
                                    }
                                }
                                else
                                    printf("\nTheres nothing to check out.\n");
                                
                                sleep(1);
                                
                                break;

                            case 4:
                                printf("\nGoing back to the Buy Menu...\n");

                                trans = fopen("Transactions.dat", "wb");
                                fwrite(nTrans, sizeof(int), 1, trans);
                                fwrite(out, sizeof(Transaction), *nTrans, trans);
                                fclose(trans);

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

    return accInd;
}


/******************************************************
    All features of User Menu
    @param - User account[] - array of users
    @param - int nUsers - number of users 
    @param - Transaction checkout[] - array of transactions
    @param - int *nTrans - number of transactions
    @return N/A
    Pre-condition: 
******************************************************/
void userMenu(User account[], int nUsers, Transaction checkout[], int *nTrans)
{
    int i, on = 1; // ctr
    int choice = 0; // choice for seller menu
    string name, binName, ID, pass; 
    FILE *bin = NULL;

    // gets the ID and Password input 
    printf("\nEnter your user ID: ");
    scanf("%s", ID);   
    printf("Enter your password: ");
    scanf("%s", pass);

    for (i = 0; i < nUsers; i++)
    {
        // if the ID and Password match, logs in the existing user
        if (strcmp(ID, account[i].userID) == 0 && strcmp(pass, account[i].pw) == 0)
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
                    fflush(stdin);
                } while (choice > 3 || choice < 1);


                /****
                switch for the choices on USER MENU
                ****/
                switch(choice)
                {
                    case 1: // SELL MENU
                        sellMenu(&account[i], &account[i].nProduct);
                        break;
                    
                    case 2: // BUY MENU
                        // pass transactions
                        i = buyMenu(account, nUsers, i, checkout, nTrans);
                        break;
                    case 3: // exit user menu
                        if (account[i].inCart != 0)
                        {
                            printf("\nSaving user's unchecked out cart...\n");
                            sleep(1);
                            sprintf(binName, "%s.bag", account[i].userID);
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
