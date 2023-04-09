
/************************************************   
    Loads the users in Users.txt to the User account[] array
    @param - FILE *txt - file pointer that points to Users.txt
    @param - User account[] - array of users
    @param - int *nUsers - number of users
    @return N/A
    Pre-condition: 
************************************************/
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


/************************************************ 
    Loads the items in Items.txt to their respective seller 
    @param - FILE *txt - file pointer that points to Items.txt
    @param - User account[] - array of users
    @param - const int nUsers - number of users
    @return N/A
    Pre-condition: 
************************************************/
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
