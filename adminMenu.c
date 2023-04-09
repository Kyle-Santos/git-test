

/************************************************   
    Sorts the Transaction array in increasing order by Seller ID
    @param - Transaction t[] - array of transactions
    @param -  int n - number of transactions
    @return N/A
    Pre-condition: 
************************************************/
void 
sortTransactionsBySellerID(Transaction t[], int n)
{
    int i, j; // variables for looping
    string lowID;
    int pos;
    Transaction temp;

    for (i = 0; i < n - 1; i++)
    {
        strcmp(lowID, t[i].sellerID);
        pos = i;
        for (j = i + 1; j < n; j++)
            if (strcmp(lowID, t[j].sellerID) > 0)
            {    
                pos = j;
                strcmp(lowID, t[j].sellerID);
            }
        
        if (pos != i)
        {
            temp = t[i];
            t[i] = t[pos];
            t[pos] = temp;
        }
    }
}


/************************************************   
    Sorts the Transaction array in increasing order by Buyer ID
    @param - Transaction t[] - array of transactions
    @param -  int n - number of transactions
    @return N/A
    Pre-condition: 
************************************************/
void 
sortTransactionsByBuyerID(Transaction t[], int n)
{
    int i, j; // variables for looping
    string lowID;
    int pos;
    Transaction temp;

    for (i = 0; i < n - 1; i++)
    {
        strcmp(lowID, t[i].buyerID);
        pos = i;
        for (j = i + 1; j < n; j++)
            if (strcmp(lowID, t[j].buyerID) > 0)
            {    
                pos = j;
                strcmp(lowID, t[j].buyerID);
            }
        
        if (pos != i)
        {
            temp = t[i];
            t[i] = t[pos];
            t[pos] = temp;
        }
    }
}


/*********************************************** 
    Admin Features are all displayed and run here. 
    @param - User account[] - array of users
    @param - int nUsers - number of users
    @param - Transaction receipt[] - array of transactions
    @param - int nTrans - number of transactions
    @return N/A
    Pre-condition: 
************************************************/
void 
adminMenu(User account[], int nUsers, Transaction receipt[], int nTrans)
{
    int i, j,
        choice = 0,
        flag = 0,
        found = 0;
    double total_amount;
    string id;
    Date start, end;

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

            // SHOW TOTAL SALES IN GIVEN DURATION
            case 3:
                total_amount = 0;
                flag = 0;
                printf("\n(Start Date)");
                getDate(&start.month, &start.day, &start.year);

                do
                {
                    printf("\n(End Date)");
                    getDate(&end.month, &end.day, &end.year);

                    if (end.year > start.year)
                        flag = 1;
                    else if (end.year == start.year)
                    {
                        if (end.month > start.month)
                            flag = 1;
                        else if (end.month == start.month)
                            if (end.day >= start.day)
                                flag = 1;
                    }
                } while (flag == 0);

                for (i = 0; i < nTrans; i++)
                {
                    if (receipt[i].date.year > start.year && receipt[i].date.year < end.year)
                        total_amount += receipt[i].amount;
                    else if (receipt[i].date.year == start.year || receipt[i].date.year == end.year)
                    {
                        if (receipt[i].date.month > start.month && receipt[i].date.month < end.month)
                            total_amount += receipt[i].amount;
                        else if (receipt[i].date.month == start.month || receipt[i].date.month == end.month)
                            if (receipt[i].date.day >= start.day && receipt[i].date.day <= end.day)
                                total_amount += receipt[i].amount;
                    }
                }

                printf("\nThe total amount of all the transactions "); 
                printf("from %d/%d/%d to %d/%d/%d is %.2lf\n", start.month, start.day, start.year, end.month, end.day, end.year, total_amount);

                sleep(1);
                break;
            
            // SHOW SELLERS SALES
            case 4:
                total_amount = 0;
                flag = 0;
                printf("\n(Start Date)");
                getDate(&start.month, &start.day, &start.year);

                do
                {
                    printf("\n(End Date)");
                    getDate(&end.month, &end.day, &end.year);

                    if (end.year > start.year)
                        flag = 1;
                    else if (end.year == start.year)
                    {
                        if (end.month > start.month)
                            flag = 1;
                        else if (end.month == start.month)
                            if (end.day >= start.day)
                                flag = 1;
                    }
                } while (flag == 0);

                sortTransactionsBySellerID(receipt, nTrans);
                printf("\nSeller ID\t|\tSeller Name\t|\tTotal Sales\n"); 

                for (i = 0; i < nTrans; i++)
                {
                    if (strcmp(id, receipt[i].sellerID) != 0)
                    {
                        strcpy(id, receipt[i].sellerID);

                        for (j = i; j < nTrans; j++)
                        {
                            if (strcmp(id, receipt[j].sellerID) == 0)
                            {
                                if (receipt[j].date.year > start.year && receipt[j].date.year < end.year)
                                    total_amount += receipt[j].amount;
                                else if (receipt[j].date.year == start.year || receipt[j].date.year == end.year)
                                {
                                    if (receipt[j].date.month > start.month && receipt[j].date.month < end.month)
                                        total_amount += receipt[j].amount;
                                    else if (receipt[j].date.month == start.month || receipt[j].date.month == end.month)
                                        if (receipt[j].date.day >= start.day && receipt[j].date.day <= end.day)
                                            total_amount += receipt[j].amount;
                                }
                            }
                        }

                        found = findUser(account, nUsers, id);
                        printf("%9s\t\t%8s\t\t%11.2lf\n", account[found].userID, account[found].name, total_amount);
                    }
                }

                sleep(1);
                break;

            // SHOW SHOPAHOLICS
            case 5:
                total_amount = 0;
                flag = 0;
                printf("\n(Start Date)");
                getDate(&start.month, &start.day, &start.year);

                do
                {
                    printf("\n(End Date)");
                    getDate(&end.month, &end.day, &end.year);

                    if (end.year > start.year)
                        flag = 1;
                    else if (end.year == start.year)
                    {
                        if (end.month > start.month)
                            flag = 1;
                        else if (end.month == start.month)
                            if (end.day >= start.day)
                                flag = 1;
                    }
                } while (flag == 0);

                sortTransactionsByBuyerID(receipt, nTrans);
                printf("\nBuyer ID\t|\tBuyer Name\t|\tTotal Spending\n"); 

                for (i = 0; i < nTrans; i++)
                {
                    if (strcmp(id, receipt[i].buyerID) != 0)
                    {
                        strcpy(id, receipt[i].buyerID);

                        for (j = i; j < nTrans; j++)
                        {
                            if (strcmp(id, receipt[j].buyerID) == 0)
                            {
                                if (receipt[j].date.year > start.year && receipt[j].date.year < end.year)
                                    total_amount += receipt[j].amount;
                                else if (receipt[j].date.year == start.year || receipt[j].date.year == end.year)
                                {
                                    if (receipt[j].date.month > start.month && receipt[j].date.month < end.month)
                                        total_amount += receipt[j].amount;
                                    else if (receipt[j].date.month == start.month || receipt[j].date.month == end.month)
                                        if (receipt[j].date.day >= start.day && receipt[j].date.day <= end.day)
                                            total_amount += receipt[j].amount;
                                }
                            }
                        }

                        found = findUser(account, nUsers, id);
                        printf("%8s\t\t%10s\t\t%14.2lf\n", account[found].userID, account[found].name, total_amount);
                    }
                }

                sleep(1);
                // edit quantity when checking out. need to check if quantity hits 0 so need to remove.
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
