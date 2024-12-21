#include<iostream>
using namespace std;
class Book
{
protected:
    unsigned int bookId;
    string title;
    string author;
    bool isAvailable;

public:
    void addBook(int);
    void displayBooks();
    int getBookId();
};