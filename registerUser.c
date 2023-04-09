
/************************************************   
    Removes the new line from strings scanned from fgets
    @param - string str - string that will have its \n removed
    @return N/A
    Pre-condition: 
************************************************/
void 
rmNewLine(string str)
{
    int i = 0;
    while (str[i] != 0)
    {
        if(str[i] == '\n')
            str[i] = 0;
        i++;
    }
}


/************************************************   
    Checks if the string only has numeric characters
    @param - string str - string to be checked
    @return 0 if all characters are numeric, 1 if not
    Pre-condition: 
************************************************/
int 
isNumeric(string str)
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


/******************************************************
    returns 0 if string length is below or equal to max, 1 if not
    @param string str - string that contains any character
    @param len - The maxiumum length of the string to be checked
    @return 0 if string length is below or equal to max, 1 if not
    Pre-condition: 
******************************************************/
int isLenCorrect(string str, int len)
{
    if (strlen(str) > len)
        return 1;
        
    return 0;
}


/************************************************   
    Registers or adds a user into the array of users
    @param - User account[] - array of users
    @param - int *nUsers - number of users
    @return N/A
    Pre-condition:
************************************************/
void 
registerUser(User account[], int *nUsers)
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

    printf("\nYour user ID is now (%s)\n", account[*nUsers].userID);
    scanf("%*c");

    do
    {
        printf("\nEnter a unique password for your account (not exceeding 10 characters): ");
        fgets(account[*nUsers].pw, 12, stdin);

        if (isLenCorrect(account[*nUsers].pw, PW_LEN)) printf("\nEnter up to maximum length only (10).\n");
        fflush(stdin);
    }
    while (isLenCorrect(account[*nUsers].pw, PW_LEN));

    do
    {
        printf("\nEnter your first and last name: ");
        fgets(account[*nUsers].name, 22, stdin);
        if (isLenCorrect(account[*nUsers].name, NAME_LEN)) printf("\nEnter up to maximum length only (20).\n");
        fflush(stdin);
    } while (isLenCorrect(account[*nUsers].name, NAME_LEN));
    
    do
    {
        printf("\nEnter your address: ");
        fgets(account[*nUsers].address, 32, stdin);
        if (isLenCorrect(account[*nUsers].address, DESCRIPTION_LEN)) printf("\nEnter up to maximum length only (30).\n");
        fflush(stdin);
    } while (isLenCorrect(account[*nUsers].address, DESCRIPTION_LEN));
    
    do
    {
        printf("\nEnter your contact number: ");
        scanf("%s", account[*nUsers].contact); 
        if (isLenCorrect(account[*nUsers].contact, NAME_LEN)) printf("\nEnter up to maximum length only (20).\n");
        fflush(stdin);
    } while (isLenCorrect(account[*nUsers].contact, NAME_LEN) || isNumeric(account[*nUsers].contact));

    rmNewLine(account[*nUsers].pw);
    rmNewLine(account[*nUsers].name);
    rmNewLine(account[*nUsers].address);

    account[*nUsers].nProduct = 0;
    *nUsers += 1;
}
