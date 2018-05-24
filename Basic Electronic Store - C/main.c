
/**********************************************************
 * Name: Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-110-03
 * Targil 51
 **********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    int input;
    /* 
     * sortMethod will tell the Sort and Insert functions how the list of items is supposed to be
     * sorted at the moment. 1 = by ID number. 2 = by name. 3 = by price. pSortMethod allows us to change 
     * the value of sortMethod in functions.
     */
    int sortMethod = 1;
    int* pSortMethod = &sortMethod;
    // The "head" of the list of items. At first, the list is empty so firstItem equals NULL.
    Item *firstItem = NULL;
    // The head of the list of customers. It's also empty at the moment.
    Customer *firstCustomer = NULL;
    // These temp pointers will be used to free all of the memory at the end of the program.
    Item *iTemp = NULL;
    Song* songTemp = NULL;
    Customer *cTemp = NULL;
    
    for ( ; ; ){
        scanf("%d", &input);
        switch (input){
            case 1:
                /*
                 * Enter managing menu. Pass firstItem and firstCustomer by address so that we'll be able to
                 * change their values in the function (when we want to change the first element of either list).
                 */
                Managing_Menu(&firstItem, pSortMethod, &firstCustomer);
                break;
            case 2:
                // Enter customer menu. Again, pass firstItem and firstCustomer by address.
                Customer_Menu(&firstItem, &firstCustomer);
                break;
            case 3:
                // End program. Free the allocated memory! First, loop through list of items in store.
                while (firstItem != NULL) {
                    // Store the first item in the temp pointer.
                    iTemp = firstItem;
                    // Move to the next item in the list.
                    firstItem = firstItem->next;
                    /* 
                     * Each Item holds another struct for either Book. Movie, or Album.
                     * Find the nested struct and free it.
                     */
                    if (iTemp->type1 != NULL) {
                        // First, free the string that holds the author name.
                        free (iTemp->type1->author);
                        // Then free the Book.
                        free (iTemp->type1);
                    }
                    else if (iTemp->type2 != NULL)
                        // Free the Movie.
                        free (iTemp->type2);
                    // If it's an Album...
                    else if (iTemp->type3 != NULL) {
                        // Loop through the list of Songs
                        while (iTemp->type3->songList != NULL) {
                            songTemp = iTemp->type3->songList;
                            iTemp->type3->songList = iTemp->type3->songList->next;
                            // Free the title of the song.
                            free (songTemp->title);
                            // Free the artist.
                            free (songTemp->artist);
                            // Free the Song.
                            free (songTemp);
                        }
                        // Free the Album.
                        free (iTemp->type3);
                    }
                    // Free the name of the Item.
                    free (iTemp->name);
                    // Then free the Item.
                    free (iTemp);
                }
                // Now, loop through the list of customers.
                while (firstCustomer != NULL) {
                    // Store this customer in the temp pointer.
                    cTemp = firstCustomer;
                    // And move on to the next customer.
                    firstCustomer = firstCustomer->next;
                    // Each customer contains a "cart" - a list of items that he has bought. So loop through that too.
                    while (cTemp->cart != NULL) {
                        // Store in temp pointer.
                        iTemp = cTemp->cart;
                        /*
                         * Move to next Item. There is no need to free the nested struct (Book, Movie, or Album) of each
                         * Item in the cart, because a new struct was not created for the type of the bought Item. The type
                         * pointer in the bought Item simply points to the same type struct (Book, Movie, or Album) that is 
                         * stored in the identical Item in the store. So the Book, Movie, or Album struct would have already 
                         * been freed when we freed the list of Items in the store.
                         */
                        cTemp->cart = cTemp->cart->next;
                        // Free the name of the Item.
                        free (iTemp->name);
                        // Free the Item in the cart.
                        free (iTemp);
                    }
                    // Free the Customer.
                    free (cTemp);
                }
                return 0;
            default:
                break;
        }
    }
    return 0;
}
