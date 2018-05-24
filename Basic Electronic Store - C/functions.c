/**********************************************************
 * Name: Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-110-03
 * Targil 51
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*************************************************************************************
 * Function name: Managing_Menu                                                      *
 * The Input: A pointer to pointer to the first Item in the store, a pointer         *
 *            to "sortMethod", which tells us how the Items in the store are         *
 *            supposed to be sorted (by number, name, or price), and a pointer       *
 *            to pointer to the first Customer in the Customer list.                 *
 * The Output: The function is void so it doesn't return anything.                   *
 * The Function Operation: The function acts as the "managing menu" for the user.    *
 *                         It inputs a number which resembles the option that the    *
 *                         user has chosen, and then uses a switch-case to implement *
 *                         the user's choice. Each case in the switch-case contains  *
 *                         another function that executes the user's choice.         *
 *************************************************************************************/
void Managing_Menu(Item** pFirst, int* pSort, Customer** pFirstCust) {
    /*
     * sortType will be used in case 6, which sorts the list of Items. It will tell us whether
     * to sort the list by name or by price.
     */
    int input, sortType;
    // iDNum will be used to find the item to be printed in case 3.
    int iDNum;
    // found will tell us whether or not the item in case 3 exists in the store.
    int found = 0;
    // This will be used in case 5, when the manager wants to print the details of a specific customer.
    char customerID[10];
    // counter will loop through the list of Items.
    Item* counter;
    // customerCount will do the same for the list of Customers.
    Customer *customerCount;
    
    for ( ; ; ){
        scanf("%d", &input);
        switch (input){
            case 1:
                // If user inputs 1, that means he wants to add items to the store.
                Add_Items(pFirst, pSort);
                break;
            case 2:
                // Update the quantity of an item.
                Update_Quant(pFirst);
                break;
            case 3:
                // Scan the ID number of the requested item.
                scanf("%d", &iDNum);
                counter = *pFirst;
                // Loop through the list of Items in the store...
                while (counter != NULL) {
                    // ...until you find the item with that ID number.
                    if (counter->idNumber == iDNum){
                        // Print the details of the item.
                        Print_Item (counter);
                        // The item exists in the store!
                        found = 1;
                        // Stop searching. You already found the item.
                        break;
                    }
                    // If you didn't find it yet, move to the next item in the list.
                    counter = counter->next;
                }
                // If the requested item does not exist in the store...
                if (found == 0)
                    // Tell the user it cannot be found. What a shame.
                    printf("Product %d: cannot be found\n", iDNum);
                // Reset found to 0 for the next time the user might want to print the details of a specific item.
                found = 0;
                break;
            case 4:
                // If user inputs 4, print details of all items in the store.
                Print_Catalog (*pFirst);
                break;
            case 5:
                // Scan the ID number of the customer you want to find.
                scanf("%s", customerID);
                customerCount = *pFirstCust;
                // Loop through list of customers...
                while (customerCount != NULL) {
                    // Until you find the customer with that ID number.
                    if (strcmp (customerCount->iD, customerID) == 0){
                        // Print details of that customer.
                        Print_Customer (customerCount);
                        // Stop searching.
                        break;
                    }
                    // If you didn't find the customer yet, move on to the next one in the list.
                    customerCount = customerCount->next;
                }
                // If you didn't find any customer with that ID number, do nothing.
                
                
                // ...this is doing nothing...
                
                
                break;
            case 6:
                // Case 6! Time to sort. Scan 1 or 2 and store it in sortType.
                scanf("%d", &sortType);
                // If user inputted 1...
                if (sortType == 1) {
                    // Sort alphabetically by name. (The function Sort receives a pointer to another function).
                    Sort (pFirst, By_Name);
                    // Change the value of sortMethod so now we know the list is sorted by name.
                    *pSort = 2;
                }
                // If user inputted 2...
                else if (sortType == 2) {
                    // Sort by price.
                    Sort (pFirst, By_Price);
                    // Change the value of sortMethod so that now we know the list is sorted by price.
                    *pSort = 3;
                }
                break;
            case 7:
                // Print details of all customers in the customer list.
                Print_All_Customers(pFirstCust);
                break;
            case 8:
                // Exit the managing menu.
                return;
            default:
                break;
        } // End of switch-case
    } // End of infinite for loop.
}

/***************************************************************************************************
 * Function name: Customer_Menu                                                                    *
 * The Input: A pointer to pointer to the first Item in the list of Items in the store, and        *
 *            a pointer to pointer to the first Customer in the list of Customers.                 *
 * The Output: The function is void. It doesn't return anything.                                   *
 * The Function Operation: The function acts as the "customer menu" for the user. First, the       *
 *                         customer "logs in" with his ID number, so the function inputs a string  *
 *                         of 9 digits. Then it tries to find an existing customer with that ID    *
 *                         number. If it can't find one, it creates a new Customer with that ID    *
 *                         number. Then the function inputs the customer's choice in the menu      *
 *                         and uses a switch case to execute the different choices. Each case      *
 *                         contains a different function that will execute the choice for that     *
 *                         case.                                                                   *
 ***************************************************************************************************/
void Customer_Menu(Item** pFirstItem, Customer** pFirstCust) {
    char customerID[10];
    int input;
    // This variable will tell us later whether a customer with that ID already existed or a new Customer was created.
    int exists = 1;
    // A counter pointer to loop through the list of Customers.
    Customer* counter = *pFirstCust;
    // A pointer for the new Customer, if one needs to be created.
    Customer* newCust = NULL;
    // This pointer will be necessary when we want to insert the new Customer in the Customer list.
    Customer* previous = NULL;
    // Scan a string of nine digits. This the customer ID number.
    scanf("%s", customerID);
    
    // Loop through the list of Customers...
    while (counter != NULL) {
        // Until you find a customer with that ID number.
        if (strcmp(counter->iD, customerID) == 0)
            // Stop searching.
            break;
        // If you didn't find the customer yet, move on to the next customer in the list.
        counter = counter->next;
    }
    // If counter reached the end of the list without the loop ever breaking, then no customer exists with that ID.
    if (counter == NULL) {
        exists = 0;
        // Make a new customer!
        newCust = malloc(sizeof(Customer));
        // Test to be sure that there was enough memory to allocate.
        if (newCust != NULL) {
            // Make a string for the new Customer's ID, and copy the inputted string to it.
            newCust->iD = (char *) malloc(strlen(customerID) + 1);
            strcpy(newCust->iD, customerID);
            // The new customer hasn't bought anything yet, so his bill is 0.
            newCust->bill = 0;
            // Now, it's time to insert the new Customer at the end of the Customer list.
            counter = *pFirstCust;
            // Loop through the customer list until you get to the end.
            while (counter != NULL){
                previous = counter;
                counter = counter->next;
            }
            // If there were no customers previously in the list, then this new Customer is the first Customer.
            if (counter == NULL) {
                // *pFirstCust equals NULL, so next will point to NULL.
                newCust->next = *pFirstCust;
                // And because it's the first Customer in the list, prev also points to NULL.
                newCust->prev = NULL;
                // firstCustomer (from the main function) now points to this new Customer.
                *pFirstCust = newCust;
            }
            // If there were already customers in the list...
            else {
                // Insert newCust at the end of the list, after "previous."
                previous->next = newCust;
                newCust->prev = previous;
                newCust->next = NULL;
            }
        } // End of "if (newCust!= NULL)"
    } // End of "if (counter == NULL)"
    for ( ; ; ){
        // Now, the user chooses what he wants to do in the Customer Menu. Input choice.
        scanf("%d", &input);
        switch (input){
            case 1:
                // Print details of all items in the store. This is the same function as in case 4 in the managing menu.
                Print_Catalog(*pFirstItem);
                break;
            case 2:
                /*
                 * Now, the customer wants to buy items from the store.
                 * If the customer currently logged in already existed in the customer list, then the counter
                 * pointer points to the customer logged in (the customer with the same ID number as the inputted
                 * string). So pass "counter" to the function Buy.
                 */
                if (exists == 1)
                    Buy(counter, pFirstItem);
                // If the customer did not already exist in the customer list, then pass "newCust" to function Buy.
                else if (exists == 0)
                    Buy(newCust, pFirstItem);
                break;
            case 3:
                /*
                 * Print details of all items that the customer has already bought.
                 * Same thing as in case 2: If this customer already existed, then pass "counter"
                 * to the function. If it's a new customer, then pass "newCust."
                 */
                if (exists == 1)
                    Print_Cart (counter);
                else if (exists == 0)
                    Print_Cart (newCust);
                break;
            case 4:
                // Exit the Customer menu.
                return;
            default:
                break;
        } // End of switch-case
    } // End of infinite loop.
}

/************************************************************************************************************
 * Function Name: Add_Items                                                                                 *
 * The Input: A pointer to pointer to the first Item in the store, and a pointer to sortMethod, which       *
 *            tells us how the list of Items is sorted at the moment (by number, by name, or by price.)     *
 * The Output: The function is void, but it creates a new Item and inserts it into the list of Items in the *
 *             store.                                                                                       *
 * The Function Operation: The function inputs what type of Item the user wants to add (Book, Movie, or     *
 *                         Album) and then uses a switch case to execute each input, with the help of       *
 *                         the function Insert after it has created the new Item. Case 1 adds a new book.   *
 *                         Case 2 adds a new movie. Case 3 adds a new album.                                *
 ************************************************************************************************************/
void Add_Items(Item **pFirst, int* pSort) {
    /*
     * input will tell us what type of Item to add. songInput will tell us whether or not to add another song
     * in case 3 (adding an Album). bufferName is a buffer for the name of the new Item, bufferAuthor is a buffer
     * for the author (if it's a book) or the artist (if it's a song). *newItem will point to the new Item that
     * we create. *newSong will point to each new song to be added into the album. *songCounter and *previous
     * will be used to add the new song into the album. int songs will be used to calculate the price of the
     * album.
     */
    int input, songInput;
    char bufferName[100];
    char bufferAuthor[100];
    int bookPages, year, rating;
    Item *newItem;
    Song *newSong;
    Song *songCounter;
    Song *previous = NULL;
    int songs;
    
    for ( ; ; ){
        scanf("%d", &input);
        switch (input){
            // Add a book...
            case 1:
                // Create new Item.
                newItem = malloc(sizeof(Item));
                // Test that there was enough memory.
                if (newItem != NULL){
                    // Create new Book and link it to the new Item. It is the Item's type.
                    newItem->type1 = malloc(sizeof(Book));
                    // Test for successful memory allocation
                    if (newItem->type1 != NULL) {
                        // Scan ID number and save it as a member of newItem.
                        scanf("%d", &newItem->idNumber);
                        // Scan the name of the item into bufferName.
                        scanf("%s", bufferName);
                        // Create properly sized string, and copy from bufferName.
                        newItem->name = (char *) malloc(strlen(bufferName) + 1);
                        strcpy(newItem->name, bufferName);
                        // Do the same thing for the author of the book.
                        scanf("%s", bufferAuthor);
                        newItem->type1->author = (char *) malloc(strlen(bufferAuthor) + 1);
                        strcpy(newItem->type1->author, bufferAuthor);
                        // Scan the number of pages in the book.
                        scanf("%d", &bookPages);
                        // If it's out of range...
                        if (bookPages < 1 || bookPages > 1000){
                            printf("Warning: Range error, setting value to maximum\n");
                            // Set value to maximum.
                            newItem->type1->pages = 1000;
                        }
                        else {
                            // Otherwise, set value to what was inputted.
                            newItem->type1->pages = bookPages;
                        }
                        // Scan the year it was published.
                        scanf("%d", &year);
                        // If it's out of range...
                        if (year < 1900 || year > 2014){
                            printf("Warning: Range error, setting value to maximum\n");
                            // Set value to maximum.
                            newItem->type1->year = 2014;
                        }
                        else
                            // Otherwise, set value to what was inputted.
                            newItem->type1->year = year;
                        // Input the price.
                        scanf("%lf", &newItem->price);
                        // Input the quantity.
                        scanf("%d", &newItem->quantity);
                        // Insert the new Item into the list of Items, based on how the list is currently sorted.
                        Insert (newItem, pFirst, pSort);
                    } // End of if (newItem->type1 != NULL)
                } // End of if (newItem != NULL)
                break;
            // Add a movie...
            case 2:
                // Create new Item.
                newItem = malloc(sizeof(Item));
                // Test for successful memory allocation.
                if (newItem != NULL) {
                    // Create new Movie and link it to the new Item. It is the Item's type.
                    newItem->type2 = malloc(sizeof(Movie));
                    // Test for successful memory allocation.
                    if (newItem->type2 != NULL) {
                        // Input ID number.
                        scanf("%d", &newItem->idNumber);
                        // Scan the name of the item into bufferName.
                        scanf("%s", bufferName);
                        // Create a properly sized string for newItem->name, and copy from bufferName.
                        newItem->name = (char *) malloc(strlen(bufferName) + 1);
                        strcpy (newItem->name, bufferName);
                        // Input the year of release.
                        scanf("%d", &year);
                        // If it's out of range...
                        if (year < 1900 || year > 2014) {
                            printf("Warning: Range error, setting value to maximum\n");
                            // Set value to maximum.
                            newItem->type2->year = 2014;
                        }
                        else
                            // Otherwise, set value to what was inputted.
                            newItem->type2->year = year;
                        // Input rating.
                        scanf("%d", &rating);
                        // Range check.
                        if (rating < 1 || rating > 5){
                            printf("Warning: Range error, setting value to maximum\n");
                            newItem->type2->rating = 5;
                        }
                        else
                            newItem->type2->rating = rating;
                        // Input price.
                        scanf("%lf", &newItem->price);
                        // Input quantity.
                        scanf("%d", &newItem->quantity);
                        // Insert the new Item into the list of Items, based on how the list is currently sorted.
                        Insert (newItem, pFirst, pSort);
                        
                    } // End of if (newItem->type2 != NULL)
                } // End of if (newItem != NULL)
                break;
            // Add an album...
            case 3:
                // Set songInput equal to 1 so that we can enter the while loop while (songInput != 2).
                songInput = 1;
                songs = 0;
                // Create new Item.
                newItem = malloc(sizeof(Item));
                // Test for successful memory allocation.
                if (newItem != NULL) {
                    // Create new Album and link it to newItem. It is the Item's type.
                    newItem->type3 = malloc(sizeof(Album));
                    // Test for successful memory allocation.
                    if (newItem->type3 != NULL) {
                        // Input ID number.
                        scanf("%d", &newItem->idNumber);
                        // Scan the name of the Item into bufferName.
                        scanf("%s", bufferName);
                        // Create properly sized string for newItem->name, and copy from bufferName.
                        newItem->name = (char *) malloc(strlen(bufferName) + 1);
                        strcpy(newItem->name, bufferName);
                        // Input the year of release.
                        scanf("%d", &year);
                        // Range check.
                        if (year < 1900 || year > 2014){
                            printf("Warning: Range error, setting value to maximum\n");
                            newItem->type3->year = 2014;
                        }
                        else
                            newItem->type3->year = year;
                        // Input the quantity.
                        scanf("%d", &newItem->quantity);
                        // Add songs. As long as the user does not enter 2...
                        while (songInput != 2) {
                            scanf("%d", &songInput);
                            // If he inputs 1, add another song.
                            if (songInput == 1) {
                                // Create new Song.
                                newSong = malloc(sizeof(Song));
                                // Test for successful memory allocation.
                                if (newSong != NULL) {
                                    // Scan string to bufferName.
                                    scanf("%s", bufferName);
                                    // Create properly sized string for newSong->title, and copy from bufferName.
                                    newSong->title = (char *) malloc(strlen(bufferName) + 1);
                                    strcpy(newSong->title, bufferName);
                                    // Do the same thing for the artist with bufferAuthor.
                                    scanf("%s", bufferAuthor);
                                    newSong->artist = (char *) malloc(strlen(bufferAuthor));
                                    strcpy(newSong->artist, bufferAuthor);
                                    // Input length of the song.
                                    scanf("%d", &newSong->length);
                                    
                                    /*
                                     * Now, insert the Song into the song list.
                                     * If the list is empty, this is the first song (songList).
                                     */
                                    if (newItem->type3->songList == NULL){
                                        newItem->type3->songList = newSong;
                                        newItem->type3->songList->next = NULL;
                                        newItem->type3->songList->prev = NULL;
                                    }
                                    // Otherwise, insert at the end of the list.
                                    else {
                                        // Counter pointer starts at the beginning of the list.
                                        songCounter = newItem->type3->songList;
                                        newSong->next = NULL;
                                        // Loop through the list of songs until you get to the end.
                                        while (songCounter != NULL) {
                                            previous = songCounter;
                                            songCounter = songCounter->next;
                                        }
                                        // Insert song at the end.
                                        previous->next = newSong;
                                        newSong->prev = previous;
                                        newSong->next = NULL;
                                    }
                                    // Increment "songs" to keep track of the number of songs in the album.
                                    songs++;
                                } // End of if (newSong != NULL)
                            } // End of if (songInput == 1)
                        } // End of while
                        // After you've finished adding songs, calculate the price of the album.
                        newItem->price = 5 * songs;
                        // Insert the new Item into the list of Items, based on how the list is currently sorted.
                        Insert (newItem, pFirst, pSort);
                    } // End of if (newItem->type3 != NULL)
                } // End of if (newItem != NULL)
                break;
            case 4:
                // Stop adding items. Go back to Managing Menu.
                return;
            default:
                break;
        } // End of switch-case
    } // End of infinte for loop
}

/*****************************************************************************************************************
 * Function Name: Insert                                                                                         *
 * The Input: A pointer to the Item that needs to be inserted into the list, a pointer to pointer to the first   *
 *            Item in the list, and a pointer to sortMethod, which tells us how the list is currently sorted     *
 *            (by number, by name, or by price).                                                                 *
 * The Output: The function is void, but it inserts the Item that it received as a parameter into the list of    *
 *             Items in the store, based on how the list is currently sorted.                                    *
 * The Function Operation: The function loops through the list of Items, but before each pass through the loop,  *
 *                         it checks to see if it has reached the point in the list where the new Item needs to  *
 *                         be inserted. It does this with three if-statements, one for each sorting method (by   *
 *                         number, by name, or by price). Once it has found where the item needs to be inserted, *
 *                         it inserts the Item at that spot in the list.                                         *
 *****************************************************************************************************************/
void Insert (Item* item, Item** first, int* pSort){
    /*
     * current will count through each Item in the list. previous will keep track of the Item before current.
     * newItem points to the Item to be inserted.
     */
    Item *current = *first;
    Item *newItem = item;
    Item *previous = NULL;
    newItem->next = NULL;
    // If the list is currently sorted by ID number...
    if (*pSort == 1){
        /*
         * As long as you haven't reached the end of the list and the new Item's ID number is greater
         * than the ID number of the current Item in the list...
         */
        while (current != NULL && newItem->idNumber > current->idNumber){
            // ...keep moving through the list.
            previous = current;
            current = current->next;
        }
    }
    // If the list is currently sorted alphabetically by name...
    else if (*pSort == 2) {
        /*
         * As long as you haven't reached the end of the list and the name of the new Item comes after the
         * name of the current Item alphabetically...
         */
        while (current != NULL && strcmp(newItem->name, current->name) > 0){
            // ...keep moving through the list.
            previous = current;
            current = current->next;
        }
    }
    // If the list is currently sorted in descending order by price...
    else if (*pSort == 3) {
        /*
         * As long as you haven't reached the end of the list and the price of the new Item is lower
         * than the price of the current Item in the list...
         */
        while (current != NULL && newItem->price < current->price){
            // ... keep moving through the list.
            previous = current;
            current = current->next;
        }
    }
    // If current still points to the first Item in the list...
    if (current == *first) {
        // Then insert the Item at the beginning of the list.
        newItem->next = *first;
        newItem->prev = NULL;
        // firstItem now points to newItem.
        *first = newItem;
    }
    // Otherwise...
    else {
        // Insert the new Item in between previous and current.
        previous->next = newItem;
        // (If it's at the end of the list, then current will equal NULL.)
        newItem->next = current;
        newItem->prev = previous;
    }
}

/****************************************************************************************************************
 * Function Name: Print_Catalog                                                                                 *
 * The Input: A pointer to the first Item in the list of Items in the store.                                    *
 * The Output: The function is void, but it prints details of all of the items in the store.                    *
 * The Function Operation: Loop through the Items in the list. For each Item in the list, print its details by  *
 * calling the function Print_Item.                                                                             *
 ****************************************************************************************************************/
void Print_Catalog (Item* first) {
    Item *counter = first;
    while (counter != NULL) {
        Print_Item (counter);
        printf("\n");
        counter = counter->next;
    }
}

/*************************************************************************************************************
 * Function Name: Update_Quant                                                                               *
 * The Input: A pointer to pointer to the first Item in the list of Items in the store.                      *
 * The Output: The function is void, but it adds a quantity (inputted by the user) to the quantity of an     *
 *             existing Item in the store.                                                                   *
 * The Function Operation: The function inputs the ID number of the requested item and the quantity to add.  *
 *                         It then loops through the list of Items until it finds the correct Item, and then *
 *                         adds the inputted quantity to the existing quantity of the Item. If it does not   *
 *                         find an Item with the inputted ID number, then it prints that the item could not  *
 *                         be found.                                                                         *
 *************************************************************************************************************/
void Update_Quant (Item** first) {
    int iDNum, quant;
    // This variable will tell us whether or not the requested Item was found.
    int found = 0;
    // A counter pointer to count through the list of Items.
    Item* counter = *first;
    // Input the ID number of the Item.
    scanf("%d", &iDNum);
    // Input the quantity to add.
    scanf("%d", &quant);
    // Loop through the list of Items...
    while (counter != NULL) {
        // ...until you find the Item with the inputted ID number.
        if (counter->idNumber == iDNum) {
            // Add the inputted quantity to its quantity.
            counter->quantity += quant;
            // The item was found!
            found = 1;
            // Stop searching.
            break;
        }
        // If you haven't found it yet, move on to the next Item in the list.
        counter = counter->next;
    } // End of while
    // If the Item was not found...
    if (found == 0)
        // ...tell that to the user.
        printf("Product %d: cannot be found\n", iDNum);
}

/**********************************************************************************************************
 * Function Name: Print_Item                                                                              *
 * The Input: A pointer to the Item whose details need to be printed.                                     *
 * The Output: The function is void, but it prints the details of the Item that was passed as a parameter.*
 * The function Operation: The function uses three if-statements to test for the type of the Item. If the *
 *                         Item is a Book, then it prints the details of the book in the format specified *
 *                         by the assignment instructions. If the Item is a Movie, then it prints the     *
 *                         details in the Movie format, etc. When the Item is an Album, the function uses *
 *                         a Song pointer to count through all of the Songs in the Album and print each   *
 *                         one.                                                                           *
 **********************************************************************************************************/
void Print_Item (Item* item) {
    // A counter pointer to count through the Songs in the Album (if the Item is an Album).
    Song *songCounter;
    // If the Item is a Book...
    if (item->type1 != NULL) {
        // Print the details in the appropriate format.
        printf("[#%d Type: Book]\n", item->idNumber);
        printf("Name: %s\n", item->name);
        printf("Price: %.2lf\n", item->price);
        printf("Quantity: %d\n", item->quantity);
        printf("Year: %d\n", item->type1->year);
        printf("Author: %s\n", item->type1->author);
        printf("Pages: %d\n", item->type1->pages);
    }
    // If the Item is a Movie...
    else if (item->type2 != NULL) {
        // Print the details in the appropriate format.
        printf("[#%d Type: Movie]\n", item->idNumber);
        printf("Name: %s\n", item->name);
        printf("Price: %.2lf\n", item->price);
        printf("Quantity: %d\n", item->quantity);
        printf("Year: %d\n", item->type2->year);
        printf("Rating: %d\n", item->type2->rating);
    }
    // If the Item is an Album...
    else if (item->type3 != NULL) {
        // Print the details in the appropriate format.
        printf("[#%d Type: Album]\n", item->idNumber);
        printf("Name: %s\n", item->name);
        printf("Price: %.2lf\n", item->price);
        printf("Quantity: %d\n", item->quantity);
        printf("Year: %d\n", item->type3->year);
        printf("Track List:\n");
        // The counter pointer starts at the first Song in the list...
        songCounter = item->type3->songList;
        // And loops through the list...
        while (songCounter != NULL) {
            // Print details of each Song.
            printf("%s - %s (%dmin)\n", songCounter->artist, songCounter->title, songCounter->length);
            // Move on to the next song.
            songCounter = songCounter->next;
        }
    }
}

/*************************************************************************************************************
 * Function Name: Print_Customer                                                                             *
 * The Input: A pointer to the Customer whose details we want to print.                                      *
 * The Output: The function is void, but it prints the ID number and bill of the customer that was passed as *
 *             a parameter.                                                                                  *
 * The Function Operation: Very simple. It just uses the printf function and prints the ID and bill of the   *
 *                         customer that was passed as a parameter.                                          *
 *************************************************************************************************************/
void Print_Customer (Customer* cust) {
    // This is pretty self-explanatory, right?
    printf("[id: %s Bill: %.2lf]\n", cust->iD, cust->bill);
}

/***********************************************************************************************************
 * Function Name: Print_All_Customers                                                                      *
 * The Input: A pointer to pointer of the first Customer in the list of Customers.                         *
 * The Output: The function is void, but it prints the ID number and bill of each Customer in the Customer *
 *             list.                                                                                       *
 * The Function Operation: The function uses a counter pointer to count through the list, and for each     *
 *                         Customer in the list it calls the Print_Customer function to print its ID       *
 *                         number and bill.                                                                *
 ***********************************************************************************************************/
void Print_All_Customers (Customer** firstCust) {
    // First, sort the customers by the total price they owe, in ascending order.
    Sort_Customers (firstCust);
    Customer* counter = *firstCust;
    // Then loop through the list of customers...
    while (counter != NULL) {
        // ...and print each one.
        Print_Customer(counter);
        counter = counter->next;
    }
}

/***********************************************************************************************************
 * Function Name: Sort_Customers                                                                           *
 * The Input: A pointer to pointer to the first Customer in the customer list.                             *
 * The Output: The function doesn't return anything, but it sorts the list of customers in ascending order *
 *             by the total price that each customer owes.                                                 *
 * The Function Operation: The function uses a bubble sort on the list of Customers to sort the list in    *
 *                         ascending order by bill.                                                        *
 ***********************************************************************************************************/
void Sort_Customers (Customer** firstCust) {
    // "current" is the inner counter.
    Customer* current = *firstCust;
    // "counter" is the outer counter. It starts at the second element in the list in order to iterate n - 1 times.
    Customer* counter = current->next;
    // "previous" keeps track of the element before "current."
    Customer* previous = NULL;
    // "next" keeps track of the element after "current."
    Customer* next = current->next;
    
    // The outer loop. This will cause the inner loop to iterate fully n - 1 times.
    while (counter != NULL) {
        // The inner loop.
        while (current->next != NULL) {
            // If the bill of the current customer is greater than that of the next customer in the list...
            if (current->bill > next->bill) {
                // Swap the two customers. First, check to see if "current" is the first customer in the list.
                if (current == *firstCust) {
                    /*
                     * "current" becomes the second customer in the list.
                     * "next" becomes the first customer in the list.
                     */
                    current->next = next->next;
                    next->prev = previous;
                    next->next = current;
                    current->prev = next;
                    // firstCustomer now points to "next."
                    *firstCust = next;
                }
                // If "current" is not first in the list...
                else {
                    // The customer after "previous" is now "next."
                    previous->next = next;
                    // The customer after "current" is now the one that was after "next."
                    current->next = next->next;
                    next->next->prev = current;
                    // The customer before "next" is now "previous."
                    next->prev = previous;
                    // The customer after "next" is now "current."
                    next->next = current;
                    // The customer before "current" is now "next."
                    current->prev = next;
                
                }
            } // End of if (current->bill > next->bill)
            // Move each counter to the next element in the list.
            previous = current;
            current = next;
            next = next->next;
        } // End of inner while.
        // After going through the entire list, reset the counters to the beginning.
        previous = NULL;
        current = *firstCust;
        next = current->next;
        // "counter" moves to next element of the list, only for the sake of counting n - 1 iterations.
        counter = counter->next;
    } // End of outer while. The inner while has now been implemented n - 1 times.
}

/*************************************************************************************************************
 * Function Name: Buy                                                                                        *
 * The Input: A pointer to the Customer that is doing the buying, and a pointer to pointer to the first Item *
 *            in the list of Items in the store.                                                             *
 * The Output: The function doesn't return anything. It does, however, allow the customer to "buy" an item   *
 *             from the store. The function creates a new Item identical to the one being bought from the    *
 *             store and inserts it into the Customer's shopping cart.                                       *
 * The Function Operation: The function inputs the ID number of the Item that the customer wants to buy and  *
 *                         loops through the list of Items to find it. If it finds it, it first checks that  *
 *                         there's enough of the Item in stock for the customer to buy the amount that he    *
 *                         wants to buy. Then the function checks if the Item being bought already exists in *
 *                         the Customer's cart. If it does, it just adds the quantity being bought now to    *
 *                         the bought quantity of the Item in the cart. If it does not already exist in the  *
 *                         Customer's cart, then the function creates a new Item struct with all the same    *
 *                         details as the Item being bought from the store. Then the function inserts this   *
 *                         new Item into the Customer's shopping cart and updates the Customer's bill.       *
 *                         Finally, if the Item in the store runs out of stock after this transaction, the   *
 *                         function removes the Item from the store completely.                              *
 *************************************************************************************************************/
void Buy (Customer* buyer, Item** pFirst) {
    int itemNum, quant;
    // This variable will tell us whether or not the requested Item was found in the store.
    int found = 0;
    /*
     * The "sort" variable and its pointer "pSort" are necessary for later when we insert the bought Item into
     * the customer's shopping cart. To do this, we will call the Insert function, but this function needs to
     * know how the list is sorted. The Items in a customer's shopping cart are always listed by ID number, so 
     * "sort" equals 1, and now the Insert function will insert the Item into the shopping cart while keeping
     * the cart sorted by ID number.
     */
    int sort = 1;
    int* pSort = &sort;
    // These Item pointers will be used if we have to remove the bought Item from the store.
    Item* counter = *pFirst;
    Item* previous = NULL;
    Item* next = *pFirst;
    next = next->next;
    // bought points to the newly bought Item. boughtCounter will be used to loop through the shopping cart.
    Item* bought;
    Item* boughtCounter;
    // Input the ID number and quantity to buy.
    scanf("%d", &itemNum);
    scanf("%d", &quant);
    // Loop through the list of Items in the store...
    while (counter != NULL) {
        // ...until you find the Item with that ID number.
        if (counter->idNumber == itemNum) {
            // The Item has been found!
            found = 1;
            // If there is not enough of the Item in stock...
            if (quant > counter->quantity) {
                printf("Does not have enough items in stock\n");
                // The transaction doesn't occur. Go back to the Customer Menu.
                return;
            }
            // Otherwise...
            else {
                // Decrease the quantity in the store by how much is being bought.
                counter->quantity -= quant;
                // If this Item is already in the Customer's cart...
                if (Is_In_Cart(buyer, counter) == 1){
                    // Counter pointer starts at the beginning of the list
                    boughtCounter = buyer->cart;
                    // And loops through the cart...
                    while (boughtCounter != NULL) {
                        // ...until it finds the Item being bought.
                        if (boughtCounter->idNumber == counter->idNumber) {
                            // Add the quantity currrently being bought to the bought quantity of this Item.
                            boughtCounter->boughtQuantity += quant;
                            // Update the bill.
                            buyer->bill += quant * counter->price;
                            // Stop searching. You found the item.
                            break;
                        }
                        // If you haven't found it yet, move on to the next Item in the cart.
                        boughtCounter = boughtCounter->next;
                    }
                }
                // If the item is NOT already in the customer's cart...
                else {
                    // Make a new Item. bought points to it.
                    bought = malloc(sizeof(Item));
                    // Test for successful memory allocation.
                    if (bought != NULL) {
                        // Copy the details from the Item in the store to the bought Item.
                        Copy (bought, counter);
                        // Save the value of how much the customer is buying of the item.
                        bought->boughtQuantity = quant;
                        // Insert the Item into the customer's shopping cart, while keeping it sorted by ID number.
                        Insert (bought, &buyer->cart, pSort);
                        // Update the customer's bill.
                        buyer->bill += quant * counter->price;
                    }
                }
                // After a successful transaction, thank the customer. It's good business practice.
                printf("Thank you!\n");
                // Now that the Item has been bought, if there is no more of it in the store...
                if (counter->quantity == 0) {
                    /*
                     * We now have to delete the Item from the store.
                     */
                    
                    // If it's the first Item in the list of Items in the store...
                    if (counter == *pFirst) {
                        // "next" is now the first Item. And delete (what was previously) the first Item.
                        next->prev = NULL;
                        *pFirst = next;
                        free (counter);
                    }
                    // If it's the LAST item...
                    else if (counter->next == NULL) {
                        // "previous" is now the last Item. And delete (what was previously) the last Item.
                        previous->next = NULL;
                        free (counter);
                    }
                    // If it's not the first and not the last...
                    else {
                        // Link previous and next together, and delete counter.
                        previous->next = next;
                        next->prev = previous;
                        free (counter);
                    }
                } // End of if (counter->quantity == 0)
            } // End of else
            // After we've found the Item the customer wants to buy, stop looping through the store.
            break;
        } // End of if (counter->idNumber == itemNum)
        // Move each pointer counter to the next Item in the list.
        previous = counter;
        counter = counter->next;
        /*
         * If counter is already at the end of the list, then next equals NULL and trying to assign
         * next->next to anything is a bad idea. So first make sure next is not equal to NULL before
         * moving it to the next item in the list.
         */
        if (next != NULL)
            next = next->next;
    } // End of while
    // If, after all that, we didn't find the Item in the store...
    if (found == 0)
        printf("Product %d: cannot be found\n", itemNum);
    
}

/*******************************************************************************************
 * Function name: Is_In_Cart                                                               *
 * The Input: A pointer to the Customer that is doing the buying, and a pointer to an      *
 *            Item. The function checks if this Item is in this Customer's cart.           *
 * The Output: The function returns 1 if the item is in the customer's cart. If it is      *
 *             not, the function returns 0.                                                *
 * The function operation: The function uses a counter pointer to loop through the         *
 *                         customer's cart. If it finds an item that has the same ID       *
 *                         number as the item that was passed as a parameter, it returns   *
 *                         1. If it gets through the entire cart without finding such an   *
 *                         item, it returns 0.                                             *
 *******************************************************************************************/
int Is_In_Cart (Customer* buyer, Item* item) {
    // Counter pointer starts at first Item in the customer's cart.
    Item* counter = buyer->cart;
    // Loop through the cart...
    while (counter != NULL) {
        // ...until you find an item with the same ID number as "item."
        if (counter->idNumber == item->idNumber) {
            // Return 1. The item is in the cart!
            return 1;
        }
        // If you haven't found it yet, move on to next item in the cart.
        counter = counter->next;
    }
    // If until now you haven't returned 1, return 0. The item is not in the cart.
    return 0;
}

/****************************************************************************************************
 * Function name: Copy                                                                              *
 * The Input: A pointer to the newly created bought Item that is about to be inserted into the      *
 *            buyer's cart, and a pointer to the Item in the store that was just bought.            *
 * The Output: The function is void. It copies all the details from the Item in the store and saves *
 *             them to the newly created bought Item.                                               *
 * The Function Operation: For idNumber and price, the function just assigns the appropriate values *
 *                         to the appropriate variables. For name, create a new properly sized      *
 *                         string and copy from the other Item's name. Everything else is done      *
 *                         by simply directing the bought Item's type pointer to the same struct    *
 *                         object (Book, Movie, or Album) that the Item in the store's type         *
 *                         pointer points to. Brilliant! There is no need to copy over the quantity *
 *                         of the Item because the bought Item will not be stored in the store.     *
 *                         Once it's in the cart, only boughtQuantity matters.                      *
 ****************************************************************************************************/
void Copy (Item* bought, Item* item) {
    // Copy the ID number.
    bought->idNumber = item->idNumber;
    // Copy the price.
    bought->price = item->price;
    // Make a properly sized string for the name.
    bought->name = (char *) malloc(strlen(item->name) + 1);
    // And copy the name.
    strcpy(bought->name, item->name);
    // If the Item is a Book...
    if (item->type1 != NULL) {
        // type1 of the bought Item points to the same Book.
        bought->type1 = item->type1;
    }
    // If it's a Movie...
    else if (item->type2 != NULL) {
        // type2 of the bought Item points to the same Movie.
        bought->type2 = item->type2;
    }
    // If it's an Album...
    else if (item->type3 != NULL) {
        // type3 of the bought Item points to the same Album.
        bought->type3 = item->type3;
    }
}

/*************************************************************************************************
 * Function Name: Print_Cart                                                                     *
 * The Input: A pointer to the Customer whose cart we want to print.                             *
 * The Output: The function is void. It prints the ID Number and bought quantity of each item in *
 *             the customer's cart, along with the total price that the customer owes.           *
 * The Function Operation: The function uses a pointer counter to loop through the items in the  *
 *                         customer's cart. For each item in the cart, it prints the ID number   *
 *                         of the item and its bought quantity. After it finishes looping through*
 *                         the cart, it prints the customer's bill.                              *
 *************************************************************************************************/
void Print_Cart (Customer* cust) {
    // Counter pointer. Starts at first item in the cart.
    Item* counter = cust->cart;
    // Loop through the items in the cart...
    while (counter != NULL) {
        // For each item, print idNumber and boughtQuantity.
        printf("[#%d Quantity: %d]\n", counter->idNumber, counter->boughtQuantity);
        // Move to next Item.
        counter = counter->next;
    }
    // Print the customer's total price (bill).
    printf("Total price: %.2lf\n", cust->bill);
}

/*****************************************************************************************************
 * Function Name: Sort                                                                               *
 * The Input: A pointer to pointer to the first Item in the list of Items in the store, and a        *
 *            function pointer that points to either the function By_Price (sort the list by price)  *
 *            or to the function By_Name (sort the list by name).                                    *
 * The Output: The function sorts the list of Items in the store according to the sort method given  *
 *             by the function pointer (either alphabetically by name or descending by price).       *
 * The Function Operation: The function performs a bubble sort. It loops through the list n - 1      *
 *                         times (if there are n elements in the list) while keeping track of the    *
 *                         previous and next items in each iteration. For each item in the list,     *
 *                         the function checks if it is "greater" than the next item in the list.    *
 *                         If it is, the function swaps the two Items.                               *
 *****************************************************************************************************/
void Sort (Item** pFirst, int (*sortType) (Item* current, Item* next)) {
    // "current" starts at the beginning. It is the counter of the inner loop.
    Item* current = *pFirst;
    // "counter" starts at the second Item in the list, so it will loop n - 1 times. It's the outer loop counter.
    Item* counter = current->next;
    // "previous" starts at NULL. "next" starts at the second element.
    Item* previous = NULL;
    Item* next = current->next;
    
    // The outer loop. It will iterate n - 1 times.
    while (counter != NULL) {
        // The inner loop. Loop through the entire list...
        while (current->next != NULL) {
            /*
             * If the method by which we are sorting requires that we swap the current Item
             * with the next Item, swap the two Items. See functions By_Price and By_Name.
             */
            if ((*sortType) (current, next) == 1){
                /*
                 * Time to swap!
                 */
                
                // If the current Item is the first Item in the list...
                if (current == *pFirst) {
                    /*
                     * Move the current Item to the second spot in the list.
                     * Move "next" to the first spot in the list. Change the
                     * value of *pFirst so that now firstItem points to "next".
                     */
                    current->next = next->next;
                    next->prev = previous;
                    next->next = current;
                    current->prev = next;
                    *pFirst = next;
                }
                // If current is NOT first in the list...
                else {
                    /*
                     * The Item after "previous" is now "next."
                     * The Item after "next" is now "current."
                     */
                    previous->next = next;
                    current->next = next->next;
                    next->prev = previous;
                    next->next = current;
                    current->prev = next;
                }
            } // End of if.
            // Move to the next Item in the list.
            previous = current;
            current = next;
            next = next->next;
        } // End of inner while.
        // Reset all of the inner pointers to the beginning of the list.
        current = *pFirst;
        previous = NULL;
        next = current->next;
        // Move "counter" (the outer loop) to the next Item in the list.
        counter = counter->next;
    } // End of outer while. The inner while was executed n - 1 times.
}

// Pointed-to function for sorting by price in descending order
int By_Price (Item* i, Item* j) {
    // If the price of "current" is lower than the price of "next"...
    if (i->price < j->price)
        // Return 1. Tells the Sort function to swap these two Items.
        return 1;
    // Otherwise...
    else
        // Don't swap.
        return 0;
}

// Pointed-to function for sorting alphabetically by name
int By_Name (Item* i, Item* j) {
    // If "current" comes after "next" alphabetically
    if (strcmp(i->name, j->name) > 0)
        // Tell the Sort function to swap these two Items.
        return 1;
    // Otherwise...
    else
        // Don't swap.
        return 0;
}



