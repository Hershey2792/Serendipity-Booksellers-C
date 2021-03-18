/* Project 9
 mainmenu.cpp
 Created by Quentin Jefferies on 11/15/20.
 Copyright © 2020 Quentin . All rights reserved.
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include "BookData.h"
#include "mainmenu.h"

BookData book[BOOK_SIZE];

using namespace std;

fstream inputFile;
char filename[] = "inventory.txt";

//function for StructuredData

char isbn[ARRAY_SIZE];
char title[ARRAY_SIZE];
char author[ARRAY_SIZE];
char pub[ARRAY_SIZE];
char dateAdded[ARRAY_SIZE];
int qtyOnHand;
double wholesale;
double retail;


using namespace std;

int main()
{

    //open an empty file
    inputFile.open(filename, ios::in | ios::binary);

    /*if inventory file fails to open, then it means its not there
    so create it*/
    if (inputFile.fail())
    {
        inputFile.open(filename, ios::out | ios::binary);
        inputFile.close();
        inputFile.clear();
        //prompt user file is created so add books to the inventory
        cout << "File created! Please add books to the inventor" << endl;
        cout << "Press ENTER to continue";
        cin.get();
    }
    else
    {
        //if open we will read from the file
        int index = 0;

        while (!inputFile.eof() && index < BOOK_SIZE)
        {
            //seek through the file and read contents of the file
            inputFile.seekg(index * sizeof(book), ios::beg);
            inputFile.read(reinterpret_cast<char *>(&book), sizeof(book));
            book[index]; //h
            index++;
        }
        inputFile.close();
        inputFile.clear();
    }

    cout << "Serendipity Booksellers" << endl;
    cout << "     Main Menu       " << endl
         << endl;
    cout << "1.  Cashier Module" << endl
         << "2.  Inventory Database Module" << endl
         << "3.  Report Module" << endl
         << "4.  Exit" << endl
         << endl;

    int choice;
    cout << "Enter Your Choice: ";

    //Loop through to make sure 1 - 4 is entered
    while (cin >> choice)
    {
        //if choice is greater than 4 prompt the user and re-enter choice
        if (choice > 4)
        {
            cout << "Please enter a number in the range 1 - 4. " << endl;
            cout << "Enter your choice: ";
        }
        else
        {

            //add switch statements for each menu choice
            switch (choice)
            {
            case 1:
                cashier();
                break;
            case 2:
                invmenu();
                break;
            case 3:
                reports();
                break;
            case 4:
                inputFile.open(filename, ios::out | ios::binary); //Save the data in the file by writing to it open binary file for output
                for (int index = 0; index < BOOK_SIZE; index++)   //write data to the file at the byte size of index throughout the loop
                {
                    inputFile.seekp(index * sizeof(book), ios::beg);                //find byte position of index at starting at the beginning
                    inputFile.write(reinterpret_cast<char *>(&book), sizeof(book)); //write book struct to the file
                }
                exit(0);
                break;
            }
        }
        cout << "Serendipity Booksellers" << endl;
        cout << "     Main Menu       " << endl
             << endl;
        cout << "1.  Cashier Module" << endl
             << "2.  Inventory Database Module" << endl
             << "3.  Report Module" << endl
             << "4.  Exit" << endl
             << endl;
        cout << "Enter your choice: ";
    }
    return 0;
}


void swapBook(BookData book[ARRAY_SIZE], int column, int row) 
{
    for (row = 0; row < BOOK_SIZE; row++)
    {
        for (column = row + 1; column < BOOK_SIZE; column++) //loop through book size array with column
        {
            if (book[row].getQty() < book[column].getQty()) //if quantity is smallest
            {
                int temp = book[column].getQty(); //list in descending order
                book[column].setQty(book[row].getQty());
                book[row].setQty(temp);

                double temp1 = book[column].getWholesale(); //list in descending order
                book[column].setWholesale(book[row].getWholesale());
                book[row].setWholesale(temp1);

                char temp2[ARRAY_SIZE]; //https://www.geeksforgeeks.org/program-to-sort-an-array-of-strings-using-selection-sort/
                strcpy(temp2, book[row].getTitle());
                strcpy(book[row].getTitle(), book[column].getTitle());
                strcpy(book[column].getTitle(), temp2);

                char temp3[ARRAY_SIZE];
                strcpy(temp3, book[row].getISBN()); //swap isbn descending order
                strcpy(book[row].getISBN(), book[column].getISBN());
                strcpy(book[column].getISBN(), temp3);

                strcpy(temp3, book[row].getPub()); //swap isbn descending order
                strcpy(book[row].getPub(), book[column].getPub());
                strcpy(book[column].getPub(), temp3);

                strcpy(temp3, book[row].getDateAdded()); //swap isbn descending order
                strcpy(book[row].getDateAdded(), book[column].getDateAdded());
                strcpy(book[column].getDateAdded(), temp3);

                strcpy(temp3, book[row].getAuthor()); //swap isbn descending order
                strcpy(book[row].getAuthor(), book[column].getAuthor());
                strcpy(book[column].getAuthor(), temp3);

                double temps = book[column].getRetail(); //list in descending order
                book[column].setRetail(book[row].getRetail());
                book[row].setRetail(temps);
            }
        }
    }
}

void strUpper(char *string)
{
    int i = 0;
    while (string[i] != 0)
    {
        string[i] = toupper(string[i]);
        i++;
    }
}

char *BookData::getISBN()
{
    return isbn;
}
void BookData::setISBN(char *newIsbn)
{
    strUpper(newIsbn);
    strcpy(isbn, newIsbn);
}
char *BookData::getTitle()
{
    return title;
}

void BookData::setTitle(char *newTitle)
{
    strUpper(newTitle);
    strcpy(title, newTitle);
}
char *BookData::getAuthor()
{
    return author;
}
void BookData::setAuthor(char *newAuthor)
{
    strUpper(newAuthor);
    strcpy(author, newAuthor);
}
char *BookData::getPub()
{
    return pub;
}
void BookData::setPub(char *newPublisher)
{
    strUpper(newPublisher);
    strcpy(pub, newPublisher);
}
char *BookData::getDateAdded()
{
    return dateAdded;
}
void BookData::setDateAdded(char *newDate)
{
    strUpper(newDate);
    strcpy(dateAdded, newDate);
}
int BookData::getQty()
{
    return qtyOnHand;
}
void BookData::setQty(int newQuantity)
{
    qtyOnHand = newQuantity;
}
double BookData::getWholesale()
{
    return wholesale;
}
void BookData::setWholesale(double newWholesale)
{
    wholesale = newWholesale;
}
double BookData::getRetail()
{
    return retail;
}
void BookData::setRetail(double newRetail)
{
    retail = newRetail;
}

int BookData::isEmpty(int index)
{
    if (strcmp(book[index].getTitle(), "") == 0)
        return 1;

    else
        return 0;
}

void removeBook(int index)
{
    book[index].setTitle(0);
    book[index].setISBN(0);
    book[index].setAuthor(0);
    book[index].setPub(0);
    book[index].setDateAdded(0);
    book[index].setQty(0);
    book[index].setWholesale(0);
    book[index].setRetail(0);
}

//reports function
void reports()
{
    cout << "    Serendipity Booksellers" << endl;
    cout << "    Inventory Database" << endl
         << endl;
    cout << "1.  Inventory Listing" << endl
         << "2.  Inventory Wholesale Value" << endl
         << "3.  Inventory Retail Value" << endl
         << "4.  Listing by Quantity" << endl
         << "5.  Listing by Cost" << endl
         << "6.  Listing by Age" << endl
         << "7.  Return to Main Menu" << endl
         << endl;

    cout << "Enter your choice: ";
    int choice;

    //loop through choices and check of correct input
    while (cin >> choice)
    {
        if (choice > 7)
        {
            cout << "Please enter a number in the range 1 - 7. " << endl;
        }
        else
        {
            //add switch statements for each menu choice
            switch (choice)
            {
            case 1:
                repListing();
                break;
            case 2:
                repWholesale();
                break;
            case 3:
                repRetail();
                break;
            case 4:
                repQty();
                break;
            case 5:
                repCost();
                break;
            case 6:
                repAge();
                break;
            case 7:
                return;
                break;
            }
        }
        cout << "    Serendipity Booksellers" << endl;
        cout << "    Inventory Database" << endl
             << endl;
        cout << "1.  Inventory Listing" << endl
             << "2.  Inventory Wholesale Value" << endl
             << "3.  Inventory Retail Value" << endl
             << "4.  Listing by Quantity" << endl
             << "5.  Listing by Cost" << endl
             << "6.  Listing by Age" << endl
             << "7.  Return to Main Menu" << endl
             << endl;

        cout << "Enter your choice: ";
    }
}

//Start of invmenu function
void invmenu()
{
    //display menu
    cout << "Serendipity Booksellers" << endl;
    cout << "Inventory Database" << endl
         << endl;
    cout << "1.  Look Up a Book" << endl
         << "2.  Add a Book" << endl
         << "3.  Edit a Book's Record" << endl
         << "4.  Delete a Book" << endl
         << "5.  Return to the Main Menu" << endl
         << endl;

    int choice;
    cout << "Enter your choice (select 5 for main menu): ";

    //loop through choices and check of correct input
    while (cin >> choice)
    {
        if (choice > 5)
        {

            cout << "Please enter a number in the range 1 - 5. " << endl;
        }
        else
        {
            //add switch statements for each menu choice
            switch (choice)
            {
            case 1:
                lookUpBook();
                break;
            case 2:
                addBook();
                break;
            case 3:
                editBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                return;
                break;
            }
        }
        //display menu
        cout << "Serendipity Booksellers" << endl;
        cout << "Inventory Database" << endl
             << endl;
        cout << "1.  Look Up a Book" << endl
             << "2.  Add a Book" << endl
             << "3.  Edit a Book's Record" << endl
             << "4.  Delete a Book" << endl
             << "5.  Return to the Main Menu" << endl
             << endl;

        cout << "Enter your choice (select 5 for main menu): ";
    }
}

//Start of Book Info function
void bookInfo(char isbn[ARRAY_SIZE], char title[ARRAY_SIZE], char author[ARRAY_SIZE], char publisher[ARRAY_SIZE], char dateAdded[ARRAY_SIZE], int qtyOnHand, double wholesale, double retail)
{

    cout << "       Serendipity Booksellers" << endl;
    cout << "           Book Information" << endl
         << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Date Added: " << dateAdded << endl;
    cout << "Quantity-On-Hand: " << qtyOnHand << endl;
    cout << "Wholesale Cost: " << wholesale << endl;
    cout << "Retail Price: " << retail << endl;
}

//Start of cashier
void cashier()
{
    //Decalare arrays for the order
    char isbnNum[BOOK_SIZE];
    char dateOrdered[BOOK_SIZE];
    int qtyOrdered[BOOK_SIZE];
    int quantityCounter;
    int index;
    double salesTax = 0;
    double total = 0;
    double runningTotal = 0;
    double subtotal[BOOK_SIZE];

    int userEntry = 0;

    while (true)
    {
        cout << "Serendipity Bookseller" << endl;
        cout << "   Cashier Module" << endl
             << endl;

        //Prompt User to enter proper information for date
        string date;
        cout << "Enter the Date of the transaction: ";
        cin >> date;
        cin.ignore();
        //Enter a book title you would like to look up
        cout << "Enter the isbn number of the book you want to look up: ";
        cin.getline(isbnNum, ARRAY_SIZE);

        cout << "Enter the quantity of books for your order: ";
        cin >> qtyOrdered[userEntry];

        //Loop through book information and search for an isbn match
        for (index = 0; index < BOOK_SIZE; index++)
        {
            if (strcmp(book[index].getISBN(), isbnNum) == 0) //check if entered ISBN matches one stored
            {
                cout << "Serendipity Bookseller" << endl;
                cout << "   Cashier Module" << endl
                     << endl;
                cout << "Book Title: " << book[index].getTitle() << endl;
                cout << fixed << showpoint << setprecision(2) << "Retail Price: $" << book[index].getRetail() << endl; //http://www.cplusplus.com/reference/iomanip/setprecision/
                quantityCounter = book[index].getQty() - qtyOrdered[userEntry];

                if (quantityCounter >= 0)
                {
                    cout << "The new quantity on hand is: " << quantityCounter << endl
                         << endl
                         << endl;
                }
                else
                    cout << "no more quanitty on hand" << endl;
                
            }
            else
                cout << "The book is not in the inventory" << endl;
                break;
            
        }

        //Another transaction to be processed
        char choice;
        bool run = true;

        cout << "Is another transaction to be processed? (Y/N): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            run;
        }
        else if (choice == 'n' || choice == 'N')
        {
            for (index = 0; index < BOOK_SIZE; index++)
            {
                subtotal[index] = book[index].getQty() * book[index].getRetail();
                salesTax += (subtotal[index]) * 0.06;
                runningTotal += subtotal[index];
                total = salesTax + runningTotal;
            }
            cout << "Serendipity Bookseller" << endl;
            cout << "   Cashier Module" << endl
                 << endl;
            cout << "Transaction Date: " << date << endl
                 << endl;
            cout << "_________________________________" << endl
                 << endl;

            cout << "Subtotal: " << runningTotal << endl;
            cout << "Sales tax: " << salesTax << endl;
            cout << "Grand total: " << total << endl
                 << endl
                 << endl;

            return;
        }
    }
}

void repListing()
{
    string date;
    cout << "Enter the date of your transaction: ";
    cin >> date;

    cout << "Serendipity Bookseller" << endl;
    cout << "   Inventory Report" << endl
         << endl;
    cout << date << endl;
    cout << "_________________________________" << endl
         << endl;

    char nullposition[] = {'\0'};
    for (int index = 0; index < BOOK_SIZE; index++) //http://www.cplusplus.com/reference/iomanip/setprecision/
    {
        if (strcmp(book[index].getTitle(), nullposition) != 0) //print book information of books stored
        {
            cout << "Book title: " << book[index].getTitle() << endl;
            cout << "Author: " << book[index].getAuthor() << endl;
            cout << "Publisher: " << book[index].getPub() << endl;
            cout << "Date Added: " << book[index].getDateAdded() << endl;
            cout << "Quantity: " << book[index].getQty() << endl;
            cout << "_________________________________" << endl
                 << endl;
            cout << fixed << showpoint << setprecision(2) << "Wholesale: $" << book[index].getWholesale() << endl; //format dollar format
            cout << "Price: $" << book[index].getRetail() << endl
                 << endl
                 << endl;
        }
        else if (index > BOOK_SIZE - 1)
        {
            cout << "no more books available to be stored" << endl;
            break;
        }
    }

    string choice;
    cout << "Select Enter to continue";
    cin.ignore();
    cin.get();
}
void repWholesale()
{
    //Display Header for transaction from inventory
    string date;
    cout << "Enter the date of your transaction: ";
    cin >> date;

    cout << "Serendipity Bookseller" << endl;
    cout << "   Wholesale Report" << endl
         << endl;
    cout << date << endl;
    cout << "_________________________________" << endl
         << endl;

    //retail value
    int totalWholesale = 0;
    int subTotal = 0;
    const int *BOOK_SIZEptr = &BOOK_SIZE; //https://www.learncpp.com/cpp-tutorial/610-pointers-and-const/

    //List inventory data
    for (int index = 0; index < *BOOK_SIZEptr; index++) //http://www.cplusplus.com/reference/iomanip/setprecision/
    {
        if (strlen(book[index].getTitle()) != 0)
        {
            cout << "Book title: " << book[index].getTitle() << endl;
            cout << "isbn: " << book[index].getISBN() << endl;
            cout << "Quantity: " << book[index].getQty() << endl;
            cout << "Wholesale Cost: " << book[index].getWholesale() << endl;
            cout << "_________________________________" << endl
                 << endl;
            subTotal = book[index].getQty() * book[index].getWholesale();
            totalWholesale += subTotal;

            cout << fixed << showpoint << setprecision(2) << "Total Wholesale Price: $" << totalWholesale << endl
                 << endl;
        }
    }
    //cout << fixed << showpoint << setprecision(2) << "Total Wholesale Price: $" << totalWholesale << endl
    //<< endl;

    string choice;
    cout << "Select Enter to continue\n";
    cin.ignore();
    cin.get();
}
void repRetail()
{
    //Display Header for transaction from inventory
    string date;
    cout << "Enter the date of your transaction: ";
    cin >> date;

    cout << "Serendipity Bookseller" << endl;
    cout << "   Retail Report" << endl
         << endl;
    cout << date << endl;
    cout << "_________________________________" << endl
         << endl;

    //retail value
    int totalRetail = 0;
    int subTotal = 0;
    const int *BOOK_SIZEptr = &BOOK_SIZE; //https://www.learncpp.com/cpp-tutorial/610-pointers-and-const/

    //List inventory data if string is not empty
    for (int index = 0; index < *BOOK_SIZEptr; index++) //http://www.cplusplus.com/reference/iomanip/setprecision/
    {
        if (strlen(book[index].getISBN()) != 0)
        {
            cout << "Book title: " << book[index].getTitle() << endl;
            cout << "isbn: " << book[index].getISBN() << endl;
            cout << "Quantity: " << book[index].getQty() << endl;
            cout << fixed << showpoint << setprecision(2);
            cout << "Retail price: " << book[index].getRetail() << endl;

            cout << "_________________________________" << endl
                 << endl;
            subTotal = book[index].getQty() * book[index].getRetail(); //calculate retail price
            totalRetail += subTotal;                                   //sum retail price of each book

            cout << "Subtotal: $" << subTotal <<endl << endl; //list total retail price
        }
        else if (index > BOOK_SIZE - 1)
        {
            cout << "no more books available to be stored" << endl;
            break;
        }
    }

    cout << fixed << showpoint << setprecision(2) << "Total Retail Price: $" << totalRetail << endl //list total retail price
         << endl;

    string choice;
    cout << "Select Enter to continue";
    cin.ignore();
    cin.get();
}

void repQty()
{
    //pointers to sort array

    //Display Header for transaction from inventory
    string date;
    cout << "Enter the date of your transaction: ";
    cin >> date;

    cout << endl;
    cout << "Serendipity Bookseller" << endl; //Quantity report header
    cout << "   Quantity Report" << endl
         << endl;
    cout << date << endl;
    cout << "_________________________________" << endl
         << endl;

    int index;

    const int *BOOK_SIZEptr = &BOOK_SIZE; //pointer to book size

 for (int row = 0; row < *BOOK_SIZEptr; row++)
    {
        for (int column = row + 1; column < *BOOK_SIZEptr; column++) //loop through book size array with column
        {
          
            swapBook(&book[index], column, row);
        }
    }

    
    for (index = 0; index < *BOOK_SIZEptr; index++) // loop through array and if title has been entered, list the
                                                    //list the titles in descending order
    {

        if (strlen(book[index].getTitle()) != '\0')
        {
            cout << "Book title: " << book[index].getTitle() << endl;
            cout << "ISBN: " << book[index].getISBN() << endl;
            cout << "Quantity: " << book[index].getQty() << endl;
            cout << "_________________________________" << endl
                 << endl;
            cout << endl;
        }
    }

    string choice;
    cout << "Select Enter to continue";
    cin.ignore(); // clear cin and add whitespace character
    cin.get();
}

void repCost()
{
    //Display Header for transaction from inventory
    string date;
    cout << "Enter the date of your transaction: ";
    cin >> date;

    cout << "Serendipity Bookseller" << endl;
    cout << "   Cost Report" << endl
         << endl;
    cout << date << endl;
    cout << "_________________________________" << endl
         << endl;

    int index;
    //int *qtyOnHandPtr;
    int wholesaleSum = 0;
    //double wholesaleBookptr = wholesale[BOOK_SIZE];
    const int *BOOK_SIZEptr = &BOOK_SIZE; //pointer to book size

    //sort the quantity in descending order loop through array https://www.includehelp.com/cpp-programs/sort-an-array-in-descending-order.aspx
    for (int row = 0; row < *BOOK_SIZEptr; row++)
    {
        for (int column = row + 1; column < *BOOK_SIZEptr; column++) //loop through column and adjacent row
        {
            if (book[row].getWholesale() < book[column].getWholesale()) //if column is larger than row
            {

              //swap entire book 
                swapBook(&book[index], column, row);
                
            }
        }
    }

    for (index = 0; index < *BOOK_SIZEptr; index++) // loop through array and if title has been entered, list the                                              //list the titles in descending order
    {
        if (book[index].getTitle() != '\0')
        {
            cout << "Book title: " << book[index].getTitle() << endl;
            cout << "ISBN: " << book[index].getISBN() << endl;
            cout << "Quantity: " << book[index].getQty() << endl;
            wholesaleSum += book[index].getWholesale();
            cout << "Wholesale Price: $" << book[index].getWholesale() << endl;
            cout << "_________________________________" << endl;
            cout << endl;
        }
    }

    cout << fixed << showpoint << setprecision(2) << "Total Wholesale Price: $" << wholesaleSum << endl
         << endl; //http://www.cplusplus.com/reference/iomanip/setprecision/

    string choice;
    cout << "Select Enter to continue";
    cin.ignore(); //clear cin and add whitespace character for continue
    cin.get();
}

void repAge()
{
    string date;
    cout << "Enter the date of your transaction: ";
    cin >> date;

    cout << "Serendipity Bookseller" << endl;
    cout << "   Age Report" << endl
         << endl;
    cout << date << endl;
    cout << "_________________________________" << endl
        << endl;

    int index;
    //string datePtr[BOOK_SIZE] = &dateAdded[BOOK_SIZE];
    //double wholesaleBookptr = wholesale[BOOK_SIZE];
    const int *BOOK_SIZEptr = &BOOK_SIZE; //pointer to book size

    for (index = 0; index < *BOOK_SIZEptr; index++)
    {
        //sort the quantity in descending order loop through array https://www.includehelp.com/cpp-programs/sort-an-array-in-descending-order.aspx
        for (int row = 0; row < *BOOK_SIZEptr; row++)
        {
            for (int column = row + 1; column < *BOOK_SIZEptr; column++) //loop through column and adjacent row
            {
                if (book[row].getDateAdded() < book[column].getDateAdded())
                {
                    swapBook(&book[index], column, row);
                }
            }
        }
    }

    for (int index = 0; index < *BOOK_SIZEptr; index++)
    {
        if (strlen(book[index].getTitle()) != '\0')
        {
            cout << "Book title: " << book[index].getTitle() << endl;
            cout << "ISBN: " << book[index].getISBN() << endl;
            cout << "Quantity: " << book[index].getQty() << endl;
            cout << "Date Added: " << book[index].getDateAdded() << endl;
            cout << "_________________________________" << endl
                << endl;
            cout << endl;
        }
    }

    string choice;
    cout << "Select Enter to continue";
    cin.ignore();
    cin.get();
}

//Stub functions for each switch statement
void lookUpBook()
{

    /*initialize index, bool for if we found book
     and a string for the title entered by the user  */
    int index = 0;
    bool bookFound = false;
    char yesOrNo;

    char titleEntered[ARRAY_SIZE];

    cin.ignore();

    cout << "Enter the title of the book: ";
    cin.getline(titleEntered, ARRAY_SIZE);
    strUpper(titleEntered); //convert to uppercase

    cout << endl;

    while (bookFound)
    {
        if (strstr(book[index].getTitle(), titleEntered))
            bookFound = true;

        else
            index++;
    }

    bookFound = false;

    /*while index is less than 20 determine
     whether we found the book or not..if not increment index*/
    while (!bookFound && !inputFile.eof())
    {
        cout << "The book title you entered is: " << titleEntered << endl;
        cout << "Similar title: " << book[index].getTitle() << endl;
        cout << "Similar isbn: " << book[index].getISBN() << endl;
        cout << "Similar publisher: " << book[index].getPub() << endl
             << endl;

        cout << "Is this the correct book?: ";
        cin >> yesOrNo;

        if (yesOrNo == 'Y' || yesOrNo == 'y')
        {
            bookInfo(book[index].getISBN(), book[index].getTitle(), book[index].getAuthor(), book[index].getPub(),
                     book[index].getDateAdded(), book[index].getQty(), book[index].getWholesale(), book[index].getRetail());
            cout << "\n"
                 << endl;
            bookFound = true;
        }
        else
        {
            cout << "title not found" << endl;
            cout << "Are you sure you would like to quit: ";
            cin >> yesOrNo;

            if (yesOrNo == 'y' || yesOrNo == 'Y')
                bookFound = true; //best way to stop a while loop without using break/continue
        }
    }
}

void addBook()
{
    char isbn[ARRAY_SIZE];
    char title[ARRAY_SIZE];
    char author[ARRAY_SIZE];
    char publisher[ARRAY_SIZE];
    char date[ARRAY_SIZE];
    int qtyOnHand;
    double wholesale;
    double retail;

    /*loop through and if book is empty string change bool to true
     if its not empty then bool is false and terminate with message*/
    int index;
    for (index = 0; index < BOOK_SIZE; index++)
    {
        if (book[index].isEmpty(index)) //if title is open for me to add book
        {
            cin.ignore();
            cout << "Enter the following items: " << endl;
            cout << "ISBN: ";
            cin.getline(isbn, ARRAY_SIZE);
            book[index].setISBN(isbn);
            inputFile << isbn;

            cout << "Book title: ";
            cin.getline(title, ARRAY_SIZE);
            book[index].setTitle(title);
            inputFile << title;

            cout << "Author's name: ";
            cin.getline(author, ARRAY_SIZE);
            book[index].setAuthor(author);
            inputFile << isbn;

            cout << "Publisher: ";
            cin.getline(publisher, ARRAY_SIZE);
            book[index].setPub(publisher);
            inputFile << publisher;

            cout << "The date the book was added to the inventory (XX-XX-XXXX): ";
            cin.getline(date, ARRAY_SIZE);
            book[index].setDateAdded(date);
            inputFile << date;

            cout << "The quantity of the book being added: ";
            cin >> qtyOnHand;
            book[index].setQty(qtyOnHand);
            inputFile << qtyOnHand;

            cout << "The wholesale cost of the book: ";
            cin >> wholesale;
            book[index].setWholesale(wholesale);
            inputFile << wholesale;

            cout << "The retail price of the book: ";
            cin >> retail;
            book[index].setRetail(retail);
            inputFile << retail;
            break;
        }
        else if (index > BOOK_SIZE)
        {
            cout << "No more books may be added to the inventory";
            break;
        }
    }
    cout << endl;
}
/*Get title from user..if it matches then set bool to true and
loop through the found books, locate the right book, and edit the fields  */
void editBook()
{
    //struct variables
    char isbn[ARRAY_SIZE];
    char title[ARRAY_SIZE];
    char titleEntered[ARRAY_SIZE];
    char author[ARRAY_SIZE];
    char pub[ARRAY_SIZE];
    char dateAdded[ARRAY_SIZE];
    int qtyOnHand;
    double wholesale;
    double retail;

    char choice;
    int index = 0;
    bool foundBook = false;
    string changedFields;
    cin.ignore();

    //get title from the user
    cout << "Enter the book title: ";
    cin.getline(titleEntered, ARRAY_SIZE);
    strUpper(titleEntered);

    cout << endl;
    while (!foundBook)
    {
        if (strstr(book[index].getTitle(), titleEntered))
            foundBook = true;

        else
            index++;
    }

    foundBook = false;

    while (!foundBook)
    {
        strstr(book[index].getTitle(), titleEntered);

        foundBook = true;
        cout << endl;
        cout << "The book title you entered is: " << titleEntered << endl;
        cout << "Similar title: " << book[index].getTitle() << endl;
        cout << "Is this the correct book? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N')
            cout << "title not found" << endl;

        else if (choice == 'y' || choice == 'Y')
        {
            bookInfo(book[index].getISBN(), book[index].getTitle(), book[index].getAuthor(), book[index].getPub(),
                     book[index].getDateAdded(), book[index].getQty(), book[index].getWholesale(), book[index].getRetail());
            foundBook = true;

            cin.ignore();
            cout << "Which of the fields would you like to change? ";
            getline(cin, changedFields);

            if (changedFields == "ISBN" || changedFields == "isbn")
            {
                cout << "The current ISBN is: ";
                cout << book[index].getISBN() << endl;
                cout << "Enter a new ISBN: ";
                cin.getline(isbn, ARRAY_SIZE);
                book[index].setISBN(isbn);
                inputFile << isbn;
                cout << "The new isbn is: " << book[index].getISBN() << endl
                     << endl;
            }
            else if (changedFields == "title")
            {
                cout << "The current title is: ";
                cout << book[index].getTitle() << endl;
                cout << "Enter a new book title: ";
                cin.getline(titleEntered, ARRAY_SIZE);
                book[index].setTitle(titleEntered);
                inputFile << title;
                cout << "The new title is: " << book[index].getTitle() << endl
                     << endl;
            }
            else if (changedFields == "author" || changedFields == "Author")
            {
                cout << "The current author's name is: ";
                cout << book[index].getAuthor() << endl;
                cout << "Enter a new author name: ";
                cin.getline(author, ARRAY_SIZE);
                book[index].setAuthor(author);
                inputFile << author;
                cout << "The new author is: " << book[index].getAuthor() << endl
                     << endl;
            }
            else if (changedFields == "publisher" || changedFields == "Publisher")
            {
                cout << "The current publisher's name is: ";
                cout << book[index].getPub() << endl;
                cout << "Enter a new publisher: ";
                cin.getline(pub, ARRAY_SIZE);
                book[index].setPub(pub);
                inputFile << pub;
                cout << "The new publisher is: " << book[index].getPub() << endl
                     << endl;
            }
            else if (changedFields == "date added" || changedFields == "Date Added")
            {
                cout << "The current date added is: ";
                cout << book[index].getDateAdded() << endl;
                cout << "Enter a new date: ";
                cin.getline(dateAdded, ARRAY_SIZE);
                book[index].setDateAdded(dateAdded);
                inputFile << dateAdded;
                cout << "The new date is: " << book[index].getDateAdded() << endl
                     << endl;
            }
            else if (changedFields == "quantity on hand" || changedFields == "qty" ||
                     changedFields == "Quantity-On-Hand")
            {
                cout << "The current Quantity-On-Hand is: ";
                cout << book[index].getQty() << endl;
                cout << "Enter a new qty";
                cin >> qtyOnHand;
                book[index].setQty(qtyOnHand);
                inputFile << qtyOnHand;
                cout << "The new quantity is: " << book[index].getQty() << endl
                     << endl;
            }
            else if (changedFields == "wholesale" || changedFields == "Wholesale" ||
                     changedFields == "wholesale cost")
            {
                cout << "The current wholesale price is: ";
                cout << book[index].getWholesale() << endl;
                cout << "Enter a new wholesale price";
                cin >> wholesale;
                book[index].setWholesale(wholesale);
                inputFile << wholesale;
                cout << "The new wholesale price is: " << book[index].getWholesale() << endl
                     << endl;
            }

            else if (changedFields == "retail price" || changedFields == "Retail Price")
            {
                cout << "The current retail cost is: ";
                cout << book[index].getRetail() << endl;
                cout << "Enter a new qty: ";
                cin >> retail;
                book[index].setRetail(retail);
                inputFile << retail;
                cout << "The new retail is: " << book[index].getRetail() << endl
                     << endl;
            }
        }
    }
}

void deleteBook()
{

    int index = 0;
    char titleEntered[ARRAY_SIZE];
    bool foundBook = false;
    char answer;

    cin.ignore();
    cout << "Enter the book title you want to delete: ";
    cin.getline(titleEntered, ARRAY_SIZE);

    while (foundBook)
    {
        if (strstr(book[index].getTitle(), titleEntered))
        {
            foundBook = true;
        }
        index++;
    }

    for (index = 0; index < BOOK_SIZE; index++)

    {
        cout << endl;
        char choice;
        if (!foundBook)
        {
            cout << "The book title you entered is: " << titleEntered << endl;
            cout << "Similar title: " << book[index].getTitle() << endl;
            cout << "Is this the correct book?(y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                bookInfo(book[index].getISBN(), book[index].getTitle(), book[index].getAuthor(), book[index].getPub(),
                         book[index].getDateAdded(), book[index].getQty(), book[index].getWholesale(), book[index].getRetail());

                cout << "Are you sure this is the book you would like to delete? (Y/N) ";
                cin >> answer;
                if (answer == 'y' || answer == 'Y')
                {

                    removeBook(index);
                    cout << "You have successfully deleted this book!\n\n";
                    break;
                }

                else if (answer == 'n' || answer == 'N')
                {
                    cout << "Book not found" << endl;
                    break;
                }
            }
        }
    }
}

