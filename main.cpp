// Library Managment System
// Programming Tier: Tier - 2
// Programming Approach: Object - Oriented Programming
// Programmer: Ahmed Nasir
// Date: 1-Jan-2025
// **************************
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <iomanip>

// user-defined header files
#include "Authentication.h"
#include "Member.h"
#include "Book.h"

#define MAX 100
#define MAX_ADMIN 3
#define isValidNum(min, max, val) ((val >= min) && (val <= max))
using namespace std;
// Report Struct Declaration
// To generate reports of returning and borrowing books
struct Report
{
    int memberID;
    int bookID;
};

// Member Function definitions of class Authentication

string Authentication::getUserName()
{
    return username;
} // end of string Authentication::getUserName() function

string Authentication::getPassWord()
{
    return password;
} // end of string Authentication::getPassWord() function

void Authentication::setCredentials()
{
    cout << "Enter your username: ";
    cin.ignore();
    cin.getline(username, 30);
    cout << "Enter your password: ";
    cin.getline(password, 30);
} // end of void Authentication::setCredentials() function

// Member Function definitions of class Book

unsigned int Book::getBookId()
{
    return bookId;
} // end of unsigned int Book::getBookId() function

void Book::setIsBookAvailable(bool bb)
{
    isAvailable = bb;
} // end of void Book::setIsBookAvailable(bool bb) function

bool Book::getIsBookAvailable()
{
    return isAvailable;
} // end of bool Book::getIsBookAvailable() function

void Book::setter()
{
    do
    {
        cout << "Enter the book Id: ";
        cin >> bookId;
        if (isValidNum(10, 99, bookId))
            break;
        else
            cout << "Invalid Number. Please add two digit number." << endl;
    } while (true);
    cout << "Enter the title of book: ";
    cin.ignore();
    cin.getline(title, 30);
    cout << "Enter the author name: ";
    cin.getline(author, 30);
    cout << "Is the book available ? [1 - YES, 0 - NO]: ";
    cin >> isAvailable;
} // end of void Book::setter() function

void Book::getter()
{
    cout << left << setw(13) << bookId << setw(30) << title << setw(30) << author << setw(9) << isAvailable << endl;
} // end of void Book::getter() function

// Member Function Definitions of Class Library

void Library::setter()
{
    cout << "Enter your name: ";
    cin.ignore();
    cin.getline(name, 30);
} // end of void Library::setter() function

void Library::getter()
{
    cout << left << setw(20) << name;
} // end of void Library::getter() function

// Member function definitions of Member Class

void Member::setter()
{
    Library::setter();
    do
    {
        cout << "Enter the member id: ";
        cin >> memberId;
        if (isValidNum(10, 99, memberId))
            break;
        else
            cout << "Invalid Number. Please add two digit number." << endl;
    } while (true);
    cout << "Enter the registration number: ";
    cin.ignore();
    cin.getline(regNo, 25);
} // end of void Member::setter() function

void Member::getter()
{
    Library::getter();
    cout << left << setw(13) << memberId << setw(25) << regNo << endl;
} // end of void Member::getter() function

unsigned int Member::getMemberId()
{
    return memberId;
} // end of unsigned int Member::getMemberId() function

void saveUsers(Authentication *pp[], int userCount, int totalCount)
{
    ofstream outfile;
    outfile.open("userdetails.DAT", ios::out | ios::binary);
    if (!outfile)
    {
        cout << "Error while opening the file. " << endl;
    }
    outfile.write(reinterpret_cast<char *>(&userCount), sizeof(int));
    outfile.write(reinterpret_cast<char *>(&totalCount), sizeof(int));
    for (int i = 0; i < userCount; i++)
    {
        outfile.write(reinterpret_cast<char *>(pp[i]), sizeof(Authentication));
    }
    outfile.close();
} // end of void saveUsers(Authentication *pp[], int userCount, int totalCount) function

void saveReports(Report repp[], int rCount)
{
    ofstream outfile;
    outfile.open("reportdetails.DAT", ios::out | ios::binary);
    if (!outfile)
    {
        cout << "Error while opening the file. " << endl;
    }
    outfile.write(reinterpret_cast<char *>(&rCount), sizeof(int));
    for (int i = 0; i < rCount; i++)
    {
        outfile.write(reinterpret_cast<char *>(&repp[i]), sizeof(Report));
    }
    outfile.close();
} // end of void saveReports(Report repp[], int rCount) function

void readReports(Report repp[], int &rCount)
{
    ifstream infile;
    infile.open("reportdetails.DAT", ios::in | ios::binary);
    if (!infile)
    {
        cout << "Error while opening the file. " << endl;
    }
    infile.read(reinterpret_cast<char *>(&rCount), sizeof(int));
    for (int i = 0; i < rCount; i++)
    {
        infile.read(reinterpret_cast<char *>(&repp[i]), sizeof(Report));
    }
    infile.close();
} // end of void readReports(Report repp[], int &rCount) function

void readUsers(Authentication *pp[], int &userCount, int &totalCount)
{
    ifstream infile;
    infile.open("userdetails.DAT", ios::in | ios::binary);
    if (!infile)
    {
        cout << "Error while opening the file. " << endl;
    }
    infile.read(reinterpret_cast<char *>(&userCount), sizeof(int));
    infile.read(reinterpret_cast<char *>(&totalCount), sizeof(int));
    for (int i = 0; i < userCount; i++)
    {
        pp[i] = new Authentication;
        infile.read(reinterpret_cast<char *>(pp[i]), sizeof(Authentication));
    }
    infile.close();
} // end of void readUsers(Authentication *pp[], int &userCount, int &totalCount) function

void saveBooks(Library *lib[], int tCount, int bCount)
{
    ofstream outfile;
    outfile.open("bookdetails.DAT", ios::out | ios::binary);
    if (!outfile)
    {
        cout << "Error while opening the file. " << endl;
    }
    outfile.write(reinterpret_cast<char *>(&bCount), sizeof(int));
    for (int i = 0; i < tCount; i++)
    {
        if (typeid(*lib[i]) == typeid(Book))
        {
            outfile.write(reinterpret_cast<char *>(lib[i]), sizeof(Book));
        }
    }
    outfile.close();
} // end of void saveBooks(Library *lib[], int tCount, int bCount) function

void readBooks(Library *lib[], int &bCount)
{
    ifstream infile;
    infile.open("bookdetails.DAT", ios::in | ios::binary);
    if (!infile)
    {
        cout << "Error while opening the file. " << endl;
    }
    infile.read(reinterpret_cast<char *>(&bCount), sizeof(int));
    for (int j = 0; j < bCount; j++)
    {
        lib[j] = new Book;
        infile.read(reinterpret_cast<char *>(lib[j]), sizeof(Book));
    }
    infile.close();
} // end of void readBooks(Library *lib[], int &bCount) function

void saveMembers(Library *lib[], int mCount, int tCount)
{
    ofstream outfile;
    outfile.open("memberdetails.DAT", ios::out | ios::binary);
    if (!outfile)
    {
        cout << "Error while opening the file. " << endl;
    }
    outfile.write(reinterpret_cast<char *>(&mCount), sizeof(int));
    for (int k = 0; k < tCount; k++)
    {
        if (typeid(*lib[k]) == typeid(Member))
        {
            outfile.write(reinterpret_cast<char *>(lib[k]), sizeof(Member));
        }
    }
    outfile.close();
} // end of void saveMembers(Library *lib[], int mCount, int tCount) function

void readMembers(Library *lib[], int &mCount)
{
    ifstream infile;
    infile.open("memberdetails.DAT", ios::in | ios::binary);
    if (!infile)
    {
        cout << "Error while opening the file. " << endl;
    }
    infile.read(reinterpret_cast<char *>(&mCount), sizeof(int));
    for (int i = 0; i < mCount; i++)
    {
        lib[i] = new Member;
        infile.read(reinterpret_cast<char *>(lib[i]), sizeof(Member));
    }
    infile.close();
} // end of void readMembers(Library *lib[], int &mCount) function

// Main Function
int main()
{
    Library *lptr[MAX];
    Authentication *aptr[MAX_ADMIN];
    int userCount = 0;
    Report rep[10];
    int repCount = 0;
    int totalCount = 0;
    int bookCount = 0;
    int memberCount = 0;
    int chh;
    do
    {
        cout << "----- Library Management System -------- " << endl
             << "1. Create Account (Only for Librarian)" << endl
             << "2. Login as Librarian" << endl
             << "3. Save Users Data" << endl
             << "4. Read Users Data" << endl
             << "5. Exit" << endl
             << "Enter your choice: ";
        cin >> chh;
        switch (chh)
        {
        case 1:
        {
            if (userCount < MAX_ADMIN)
            {
                aptr[userCount] = new Authentication;
                aptr[userCount]->setCredentials();
                userCount++;
                cout << "User added. " << endl;
            }
            else
            {
                cout << "Can't add more admins. " << endl;
            }
            break;
        }
        case 2:
        {
            string id, pass;
            int attempt = 0;
            bool flagAttempt = true;
            int ch;
            cout << "Enter the username: ";
            cin.ignore();
            getline(cin, id);
            for (int i = 0; i < userCount; i++)
            {
                if (aptr[i]->getUserName() == id)
                {
                    while (attempt < 3)
                    {
                        cout << "Enter the password: ";
                        cin.ignore();
                        getline(cin, pass);
                        if (aptr[i]->getPassWord() == pass)
                        {
                            cout << "You sucessfully login. " << endl;
                            flagAttempt = false;
                            do
                            {
                                char choice;
                                cout << "------------ LMS - Librarian Menu ---------------" << endl;
                                cout << "------- Book Menu ------" << endl
                                     << "1. Add a Book" << endl
                                     << "2. Search a Book" << endl
                                     << "3. Update Book Details" << endl
                                     << "4. Delete a Book" << endl
                                     << "5. Display Books" << endl
                                     << "------- Member Menu ------" << endl
                                     << "6. Add a Member" << endl
                                     << "7. Search a Member" << endl
                                     << "8. Delete a Member" << endl
                                     << "9. Display Members" << endl
                                     << "------- Borrow and Return Menu ------" << endl
                                     << "10. Borrow a book to member" << endl
                                     << "11. Return a Book from member" << endl
                                     << "12. Generate Reports" << endl
                                     << "13. Logout" << endl
                                     << "Enter your choice: ";
                                cin >> ch;
                                switch (ch)
                                {
                                case 1:
                                {
                                    do
                                    {
                                        lptr[totalCount] = new Book;
                                        lptr[totalCount]->setter();
                                        totalCount++;
                                        bookCount++;
                                        cout << "Book added successfully. " << endl;
                                        cout << "Do you want to add another book? [Y/N]: ";
                                        cin >> choice;
                                        if (!(choice == 'y' || choice == 'Y'))
                                            break;
                                    } while (true);
                                    break;
                                } // end of Case 1

                                case 2:
                                {
                                    unsigned int idToSearch;
                                    bool flag = true;
                                    cout << "Enter the Book ID to search: ";
                                    cin >> idToSearch;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[i]);
                                            if (book->getBookId() == idToSearch)
                                            {
                                                flag = false;
                                                cout << "Book Found!" << endl;
                                                book->getter();
                                                break;
                                            }
                                        }
                                    }
                                    if (flag)
                                        cout << "Book with ID " << idToSearch << " not found." << endl;
                                    break;
                                } // end of Case 2

                                case 3:
                                {
                                    unsigned int idToUpdate;
                                    bool flag = true;
                                    cout << "Enter the Book ID to update: ";
                                    cin >> idToUpdate;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[i]);
                                            if (book->getBookId() == idToUpdate)
                                            {
                                                flag = false;
                                                cout << "Current Book Details:" << endl;
                                                book->getter();
                                                cout << "Enter new details for the book:" << endl;
                                                book->setter();
                                                cout << "Book updated successfully!" << endl;
                                            }
                                        }
                                    }
                                    if (flag)
                                        cout << "Book with ID " << idToUpdate << " not found." << endl;
                                    break;
                                } // end of Case 3

                                case 4:
                                {
                                    unsigned int idToDelete;
                                    bool flag = true;
                                    cout << "Enter the Book ID to delete: ";
                                    cin >> idToDelete;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[i]);
                                            if (book->getBookId() == idToDelete)
                                            {
                                                delete lptr[i];
                                                for (int j = i; j < totalCount - 1; j++)
                                                {
                                                    lptr[j] = lptr[j + 1];
                                                }
                                                lptr[totalCount - 1] = nullptr;
                                                totalCount--;
                                                bookCount--;
                                                cout << "Book deleted successfully!" << endl;
                                                break;
                                            }
                                        }
                                    }
                                    if (flag)
                                        cout << "Book with ID " << idToDelete << " not found." << endl;
                                    break;
                                } // end of Case 4

                                case 5:
                                {
                                    cout << "*********************************************************************************" << endl;
                                    cout << left << setw(13) << "Book Id" << setw(30) << "Book Name" << setw(30) << "Author" << setw(9) << "Available " << endl;
                                    cout << "*********************************************************************************" << endl;
                                    for (int n = 0; n < totalCount; n++)
                                    {
                                        if (typeid(*lptr[n]) == typeid(Book))
                                        {
                                            lptr[n]->getter();
                                        }
                                    }

                                    cout << "*********************************************************************************" << endl;
                                    break;
                                } // end of Case 5

                                case 6:
                                {
                                    do
                                    {
                                        lptr[totalCount] = new Member;
                                        lptr[totalCount]->setter();
                                        userCount++;
                                        totalCount++;
                                        memberCount++;
                                        cout << "Member added successfully. " << endl;
                                        cout << "Do you want to add another member? [Y/N]: ";
                                        cin >> choice;
                                        if (!(choice == 'y' || choice == 'Y'))
                                            break;
                                    } while (true);
                                    break;
                                } // end of Case 6

                                case 7:
                                {
                                    unsigned int idToSearch;
                                    cout << "Enter the member ID to search: ";
                                    cin >> idToSearch;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Member))
                                        {
                                            Member *member = static_cast<Member *>(lptr[i]);
                                            if (member->getMemberId() == idToSearch)
                                            {
                                                cout << "Member Found!" << endl;
                                                member->getter();
                                                break;
                                            }
                                        }
                                    }
                                    break;
                                } // end of Case 7

                                case 8:
                                {
                                    unsigned int idToDelete;
                                    cout << "Enter the Book ID to delete: ";
                                    cin >> idToDelete;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Member))
                                        {
                                            Member *member = static_cast<Member *>(lptr[i]);
                                            if (member->getMemberId() == idToDelete)
                                            {
                                                delete lptr[i];
                                                for (int j = i; j < totalCount - 1; j++)
                                                {
                                                    lptr[j] = lptr[j + 1];
                                                }
                                                lptr[totalCount - 1] = nullptr;
                                                totalCount--;
                                                memberCount--;
                                                cout << "Member deleted successfully!" << endl;
                                                // return;
                                            }
                                        }
                                    }
                                    break;
                                } // end of Case 8

                                case 9:
                                {
                                    cout << "*********************************************************" << endl;
                                    cout << left << setw(20) << "Name" << setw(13) << "Member ID" << setw(25) << "Reg No" << endl;
                                    cout << "*********************************************************" << endl;
                                    for (int m = 0; m < totalCount; m++)
                                    {
                                        if (typeid(*lptr[m]) == typeid(Member))
                                        {
                                            lptr[m]->getter();
                                        }
                                    }
                                    cout << "*********************************************************" << endl;
                                    break;
                                } // end of Case 9

                                case 10:
                                {
                                    int memId, bookId;
                                    cout << "Enter the member id to which you give a book: ";
                                    cin >> memId;
                                    cout << "Enter the book id: ";
                                    cin >> bookId;

                                    bool bookFound = false, memberFound = false;
                                    for (int j = 0; j < totalCount; j++)
                                    {
                                        if (typeid(*lptr[j]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[j]);
                                            if (book->getBookId() == bookId)
                                            {
                                                bookFound = true;
                                                if (book->getIsBookAvailable())
                                                {
                                                    book->setIsBookAvailable(false);
                                                    rep[repCount].bookID = bookId;
                                                    rep[repCount].memberID = memId;
                                                    repCount++;
                                                    cout << "Book given successfully." << endl;
                                                }
                                                else
                                                {
                                                    cout << "Book is already borrowed." << endl;
                                                }
                                                break;
                                            }
                                        }
                                    }

                                    if (!bookFound)
                                        cout << "Book not found!" << endl;

                                    break;
                                } // end of Case 10

                                case 11:
                                {
                                    int memId, bookId;
                                    cout << "Enter the member id who is returning a book: ";
                                    cin >> memId;
                                    cout << "Enter the book id: ";
                                    cin >> bookId;

                                    bool bookFound = false, memberFound = false;
                                    for (int j = 0; j < totalCount; j++)
                                    {
                                        if (typeid(*lptr[j]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[j]);
                                            if (book->getBookId() == bookId)
                                            {
                                                bookFound = true;
                                                if (!book->getIsBookAvailable())
                                                {
                                                    book->setIsBookAvailable(true);
                                                    cout << "Book returned successfully." << endl;

                                                    // Remove from report
                                                    for (int k = 0; k < repCount; k++)
                                                    {
                                                        if (rep[k].bookID == bookId && rep[k].memberID == memId)
                                                        {
                                                            for (int m = k; m < repCount - 1; m++)
                                                            {
                                                                rep[m] = rep[m + 1];
                                                            }
                                                            repCount--; // Decrement report count
                                                            break;
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    cout << "Book was not borrowed." << endl;
                                                }
                                                break;
                                            }
                                        }
                                    }

                                    if (!bookFound)
                                        cout << "Book not found!" << endl;

                                    break;
                                } // end of Case 11

                                case 12:
                                {
                                    cout << "***********************" << endl;
                                    cout << left << setw(12) << "Mem Id" << setw(12) << "Book Id" << endl;
                                    cout << "***********************" << endl;
                                    for (int j = 0; j < repCount; j++)
                                    {
                                        cout << left << setw(12) << rep[j].bookID << setw(12) << rep[j].memberID << endl;
                                    }
                                    cout << "***********************" << endl;
                                    break;
                                } // end of Case 12

                                case 13:
                                    break;
                                } // end of Case 13
                                // end of Nested Switch
                            } while (ch != 13);
                            break;
                        }
                        else
                        {
                            cout << "Password not match. " << endl;
                        }
                        attempt++;
                    }
                    if (flagAttempt)
                        exit(1);
                    break;
                }
                else
                {
                    cout << "Username not found. " << endl;
                    break;
                }
            }
            break;
        }
        case 3:
        {
            saveUsers(aptr, userCount, totalCount);
            saveBooks(lptr, totalCount, bookCount);
            saveMembers(lptr, memberCount, totalCount);
            saveReports(rep, repCount);
            cout << "Data saved sucessfully. " << endl;
            break;
        }
            // end of Case 3

        case 4:
        {
            readUsers(aptr, userCount, totalCount);
            readBooks(lptr, bookCount);
            readMembers(lptr, memberCount);
            readReports(rep, repCount);
            cout << "Data read sucessfully. " << endl;
            break;
        } // end of Case 4

        case 5:
        {
            for (int i = 0; i < totalCount; i++)
            {
                delete lptr[i];
            }
            break;
        } // end of Case 5

        } // end of Switch
    } while (chh != 5);

    system("pause");
    return 0;
} // end of main function
