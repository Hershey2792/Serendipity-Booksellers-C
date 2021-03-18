
//  Quentin Jefferies
// mainmenu.h
// Project 4
//  10/16/20.
//  Professor Kechiantz
#pragma once

#include <iostream>
#include <string.h>
#include <cstring>
#include <iomanip>




using namespace std;

const int BOOK_SIZE = 20;


//project functions
void cashier();
void invmenu();
void bookInfo(char[], char[], char[], char[], char[], int, double, double);
void reports();

//add invmenu stub functions
void lookUpBook();
void addBook();
void editBook();
void deleteBook();

//add reports stub functions
void repListing();
void repWholesale();
void repRetail();
void repQty();
void repCost();
void repAge();


 

