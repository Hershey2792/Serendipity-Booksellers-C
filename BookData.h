#ifndef BOOKDATA_H
#define BOOKDATA_H

const int ARRAY_SIZE = 51;

class BookData{
private:
    char isbn[ARRAY_SIZE];
    char title[ARRAY_SIZE];
    char author[ARRAY_SIZE];
    char pub[ARRAY_SIZE];
    char dateAdded[ARRAY_SIZE];
    int qtyOnHand;
    double wholesale;
    double retail;

public:
    BookData()//constructor set to nullptr
    {
        strcpy(title, "\0");
    }
    //mutator and accessors
    void setTitle(char* newTitle);
    char* getTitle();
    void setISBN(char* newISBN);
    char* getISBN();
    void setAuthor(char *newAuthor);
    char* getAuthor();
    void setPub(char* newPublisher);
    char* getPub();
    void setDateAdded(char* newDate);
    char* getDateAdded();
    void setQty(int newQuantity);
    int getQty();
    void setWholesale(double newWholesale);
    double getWholesale();
    void setRetail(double newRetail);
    double getRetail();

    //member functions
    int isEmpty(int index);
    void removeBook(int index);
    bool bookMatch(char titleEntered[ARRAY_SIZE], int index);


};




#endif




