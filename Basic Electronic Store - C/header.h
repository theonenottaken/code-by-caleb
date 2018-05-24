/**********************************************************
 * Name: Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-110-03
 * Targil 51
 **********************************************************/

#ifndef targ51_header_h
#define targ51_header_h

// The struct definition for Book.
typedef struct {
    char *author;
    int pages;
    int year;
} Book;

// The struct definition for Movie.
typedef struct {
    int rating;
    int year;
} Movie;

// The struct definition for Song.
struct Song {
    char *title;
    char *artist;
    int length;
    // The songs in each Album will be stored as a double-linked list.
    struct Song *prev;
    struct Song *next;
};

typedef struct Song Song;

// The struct definition for Album.
typedef struct {
    int year;
    // This is the "head" of the Song list.
    Song *songList;
} Album;

/*
 * This is the struct definition for Item. Every product in the store will be an instance of struct Item.
 * The Item struct will store all details that are not specific to a specific type of Item, such as name,
 * idNumber, etc. Then each Item also stores a pointer to a different struct that resembles the type of the
 * Item (Book, Movie, or Album). type1 points to a Book, type2 points to a Movie, and type3 points to an Album.
 * Thus, every product in the store will in essence be made up of two structs - one for Item and one for the
 * Item's type (either Book, Movie, or Album). In addition, the list of Items is stored as a double-linked
 * list, so each Item contains Item pointers to next and prev.
 */
struct Item {
    char *name;
    int idNumber;
    double price;
    // This quantity keeps track of how much of the Item is in the store.
    int quantity;
    // This quantity keeps track of how much of the Item is in a specific Customer's cart.
    int boughtQuantity;
    Book *type1;
    Movie *type2;
    Album *type3;
    struct Item *prev;
    struct Item *next;
};
typedef struct Item Item;

// The struct definition for Customer.
struct Customer {
    char *iD;
    // Each Customer will contain an Item pointer that points to a list of Items, which resembles the "shopping cart."
    Item *cart;
    // The bill will be calculated by adding up the prices of each item in the cart.
    double bill;
    // And of course, all of the Customers are stored in a double-linked list.
    struct Customer *prev;
    struct Customer *next;
};
typedef struct Customer Customer;

// The functions! See functions.c.
void Managing_Menu(Item **first, int* pSort, Customer** f);
void Customer_Menu(Item **first, Customer** f);
void Add_Items(Item **first, int* pSort);
void Insert (Item* item, Item** first, int* pSort);
void Update_Quant(Item **first);
void Print_Item(Item* i);
void Print_Catalog(Item *first);
void Print_Customer(Customer* cust);
void Sort(Item** pFirst, int (*sortType)(Item* current, Item* next));
int By_Price (Item* i, Item* j);
int By_Name (Item* i, Item* j);
void Print_All_Customers(Customer** first);
void Sort_Customers (Customer** first);
void Buy (Customer* buyer, Item** pFirst);
int Is_In_Cart (Customer* buyer, Item* item);
void Copy (Item* bought, Item* item);
void Print_Cart (Customer * cust);




#endif
