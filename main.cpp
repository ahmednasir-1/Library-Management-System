#include <iostream>
#include <string>
#include "Book.h"
#include "User.h"
#include "Member.h"
#include "Student.h"
using namespace std;

void Book::displayBooks()
{
    cout << "Book Id: " << bookId << " - " << "Book Name: " << title << " - " << "Author: " << author << endl;
}
int Book::getBookId()
{
    return bookId;
}
void Book::addBook(int id)
{
    bookId = id;
    cout << "Enter details of " << bookId << ": " << endl;
    cout << "Enter the title of book: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter the author name: ";
    cin.ignore();
    getline(cin, author);
}

void User::setter()
{
    cout << "Enter your name: ";
    getline(cin, name);
}
void User::getter()
{
    cout << "Name: " << name;
}

void Member::addMem(int id)
{
    User::setter();
    memberId = id;
}
void Member::dispMem()
{
    User::getter();
    cout << "Member Id: " << memberID << endl;
}

void Librarian::dispBooks()
{
    for (int i = 0; i < bookCount; i++)
    {
        books[i].displayBooks();
    }
}
void Librarian::addMember()
{
    int memId;
    cout << "Enter how many members you want to add? ";
    cin >> memCount;
    if (memCount < MAX_MEMBERS)
    {

        for (int i = 0; i < memCount;)
        {
            cout << "Enter the member id: ";
            cin >> memId;
            if (searchBook(memId, i) == -1)
            {
                members[i].addMem(memId);
                i++;
            }
            else
            {
                cout << "member id already exists. " << endl;
            }
        }
    }
}
void Librarian::displayMember()
{
    for (int i = 0; i < memCount; i++){
        members[i].dispMem();
    }
}
void Librarian::searchMember(int id, int nn)
{
    int s;
    for (int i = 0; i < nn; i++)
    {
        if (id == getMemId())
        {
            s = i;
            break;
        }
    }
    return s;
}
void Librarian::addBook()
{
    int bookId;
    cout << "Enter how many books you want to add? ";
    cin >> bookCount;
    if (bookCount < MAXBOOKS)
    {

        for (int i = 0; i < bookCount;)
        {
            cout << "Enter the book id: ";
            cin >> bookId;
            if (searchBook(bookId, i) == -1)
            {
                books[i].addBook(bookId);
                i++;
            }
            else
            {
                cout << "book id already exists. " << endl;
            }
        }
    }
}
void Librarian::delBook()
{
    int bookId;
    cout << "Enter the book id to be deleted: ";
    cin >> bookId;
    int s = -1;
    s = searchBook(bookId, bookCount);
    if (s != -1)
    {
        for (int i = s; s < bookCount - 1; i++)
        {
            books[i] = books[i + 1];
        }
        bookCount--;
        cout << "Book deleted successfully." << endl;
    }
    else
    {
        cout << "Book with " << bookId << " not found." << endl;
    }
}
void Librarian::appBook()
{
    int bookId;
    do
    {
        cout << "Enter the book id: ";
        cin >> bookId;
        if (searchBook(bookId, bookCount) == -1)
        {
            books[bookCount].addBook(bookId);
            bookCount++;
            break;
        }
    } while (true);
}
int Librarian::searchBook(int &id, int &nn)
{
    int s = -1;
    for (int i = 0; i < nn; i++)
    {
        if (id == books[i].getBookId())
        {
            s = i;
            break;
        }
    }
    return s;
}
int main()
{
    Librarian l1;
    l1.addBook();
    l1.dispBooks();
}
