#include <iostream>
#include <string>
#include <typeinfo>
#include <fstream>
#define MAXBOOKS 100
#define MAX_MEMBERS 50
using namespace std;

class Authentication
{
protected:
    char username[30];
    char password[30];

public:
    virtual void setCredentials();
    string getUserName()
    {
        return username;
    }
    string getPassWord()
    {
        return password;
    }
};

void Authentication::setCredentials()
{
    cout << "Enter your username: ";
    cin.ignore();
    cin.getline(username, 30);
    cout << "Enter your password: ";
    cin.getline(password, 30);
    // saveToFile();
}
class Library
{
protected:
    char name[30];

public:
    virtual void setter();
    virtual void getter();
};
class Member : public Library
{
protected:
    int memberId;
    int regNo;

public:
    void setter();
    void getter();
    int getMemberId();
};
class Book : public Library
{
protected:
    unsigned int bookId;
    char title[30];
    char author[30];
    // bool isAvailable;
    // int noOfCopies;

public:
    void setter();
    void getter();
    void searchBook(Library *lib[], int tCount);
    unsigned int getBookId()
    {
        return bookId;
    }
};
void Book::setter()
{
    cout << "Enter book id: ";
    cin >> bookId;
    cout << "Enter the title of book: ";
    cin.ignore();
    cin.getline(title, 30);
    cout << "Enter the author name: ";
    cin.getline(author, 30);
}
void Book::getter()
{
    cout << "Book Id: " << bookId << " - " << "Book Name: " << title << " - " << "Author: " << author << endl;
}
void Library::setter()
{
    cout << "Enter your name: ";
    cin.ignore();
    cin.getline(name, 30);
}
void Library::getter()
{
    cout << "Name: " << name << endl;
}

void Member::setter()
{
    Library::setter();
    cout << "Enter your member id: ";
    cin >> memberId;
}
void Member::getter()
{
    Library::getter();
    cout << "Member Id: " << memberId << endl;
}
int Member::getMemberId()
{
    return memberId;
}
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
}
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
    // cout << "Total Count: " << totalCount << ", Book Count: " << userCount << endl;
    for (int i = 0; i < userCount; i++)
    {
        pp[i] = new Authentication;
        infile.read(reinterpret_cast<char *>(pp[i]), sizeof(Authentication));
    }
    infile.close();
}
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
            lib[i]->getter();
        }
    }
    outfile.close();
}
void readBooks(Library *lib[], int &bCount)
{
    ifstream infile;
    infile.open("bookdetails.DAT", ios::in | ios::binary);
    if (!infile)
    {
        cout << "Error while opening the file. " << endl;
    }
    infile.read(reinterpret_cast<char *>(&bCount), sizeof(int));
    // cout << " (rB) Book Count: " << bCount << endl;
    for (int j = 0; j < bCount; j++)
    {
        lib[j] = new Book;
        infile.read(reinterpret_cast<char *>(lib[j]), sizeof(Book));
        // lib[j]->getter();
    }
    infile.close();
}
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
            // cout << "hello" << endl;
        }
        // cout << "nice " << endl;
    }
    outfile.close();
}
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
        // cout << "hi!" << endl;
    }
    infile.close();
}
int main()
{
    Library *lptr[100];
    Authentication *aptr[3];
    int userCount = 0;
    int totalCount = 0;
    int bookCount = 0;
    int memberCount = 0;
    int chh;
    do
    {
        cout << "----- Library Management System -------- " << endl
             << "1. Create Account (Only for Librarian)" << endl
             << "2. Login as Librarian" << endl
             << "4. Search a book" << endl
             << "5. Display all Books" << endl
             << "6. Save Users Data" << endl
             << "7. Read Users Data" << endl
             << "8. Exit" << endl
             << "Enter your choice: ";
        cin >> chh;
        switch (chh)
        {
        case 1:
        {
            if (userCount < 3)
            {
                aptr[userCount] = new Authentication;
                aptr[userCount]->setCredentials();
                userCount++;
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
            cout << "Enter your user id: ";
            cin.ignore();
            getline(cin, id);
            for (int i = 0; i < userCount; i++)
            {
                if (aptr[i]->getUserName() == id)
                {
                    int j = 0;
                    while (j < 3)
                    {
                        cout << "Enter your password: ";
                        cin.ignore();
                        getline(cin, pass);
                        if (aptr[i]->getPassWord() == pass)
                        {
                            cout << "You sucessfully login. " << endl;
                            int ch;
                            do
                            {
                                char choice;
                                cout << "---- LMS ------" << endl
                                     << "1. Add a Book" << endl
                                     << "2. Search a Book" << endl
                                     << "3. Update Book Details" << endl
                                     << "4. Delete a Book" << endl
                                     << "5. Display Books" << endl
                                     << "6. Add a Member" << endl
                                     << "7. Search a Member" << endl
                                     << "8. Delete a Member" << endl
                                     << "9. Display Members" << endl
                                     << "10. Go back" << endl
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
                                }
                                case 2:
                                {
                                    unsigned int idToSearch;
                                    cout << "Enter the Book ID to search: ";
                                    cin >> idToSearch;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[i]);
                                            if (book->getBookId() == idToSearch)
                                            {
                                                cout << "Book Found!" << endl;
                                                book->getter();
                                                // return;
                                            }
                                        }
                                    }
                                    // cout << "Book with ID " << idToSearch << " not found." << endl;
                                    break;
                                }
                                case 3:
                                {
                                    unsigned int idToUpdate;
                                    cout << "Enter the Book ID to update: ";
                                    cin >> idToUpdate;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[i]);
                                            if (book->getBookId() == idToUpdate)
                                            {
                                                cout << "Current Book Details:" << endl;
                                                book->getter();
                                                cout << "Enter new details for the book:" << endl;
                                                book->setter();
                                                cout << "Book updated successfully!" << endl;
                                            }
                                        }
                                    }
                                    // cout << "Book with ID " << idToUpdate << " not found." << endl;
                                    break;
                                }
                                case 4:
                                {
                                    unsigned int idToDelete;
                                    cout << "Enter the Book ID to delete: ";
                                    cin >> idToDelete;

                                    for (int i = 0; i < totalCount; i++)
                                    {
                                        if (typeid(*lptr[i]) == typeid(Book))
                                        {
                                            Book *book = static_cast<Book *>(lptr[i]);
                                            if (book->getBookId() == idToDelete)
                                            {
                                                delete lptr[i]; // Free memory
                                                for (int j = i; j < totalCount - 1; j++)
                                                {
                                                    lptr[j] = lptr[j + 1]; // Shift elements
                                                }
                                                lptr[totalCount - 1] = nullptr; // Clear last pointer
                                                totalCount--;
                                                bookCount--;
                                                cout << "Book deleted successfully!" << endl;
                                                // return;
                                            }
                                        }
                                    }
                                    // cout << "Book with ID " << idToDelete << " not found." << endl;
                                    break;
                                }
                                case 5:
                                {
                                    for (int n = 0; n < totalCount; n++)
                                    {
                                        if (typeid(*lptr[n]) == typeid(Book))
                                        {
                                            lptr[n]->getter();
                                            cout << "****" << endl;
                                        }
                                    }
                                    break;
                                }
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
                                }
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
                                                // return;
                                            }
                                        }
                                    }
                                    break;
                                }
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
                                                delete lptr[i]; // Free memory
                                                for (int j = i; j < totalCount - 1; j++)
                                                {
                                                    lptr[j] = lptr[j + 1]; // Shift elements
                                                }
                                                lptr[totalCount - 1] = nullptr; // Clear last pointer
                                                totalCount--;
                                                memberCount--;
                                                cout << "member deleted successfully!" << endl;
                                                // return;
                                            }
                                        }
                                    }
                                    break;
                                }
                                case 9:
                                {
                                    for (int m = 0; m < totalCount; m++)
                                    {
                                        if (typeid(*lptr[m]) == typeid(Member))
                                        {
                                            lptr[m]->getter();
                                            cout << "****" << endl;
                                        }
                                    }
                                    break;
                                }
                                case 10:
                                    break;
                                }
                            } while (ch != 10);
                            break;
                        }
                        else
                        {
                            cout << "Password not match. " << endl;
                        }
                        j++;
                    }
                    // exit(1);
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
            string id, pass;
            cout << "Enter your member id: ";
            cin.ignore();
            getline(cin, id);
            for (int i = 0; i < userCount; i++)
            {
                if (aptr[i]->getUserName() == id)
                {
                    cout << "Enter your password: ";
                    cin.ignore();
                    getline(cin, pass);
                    if (aptr[i]->getPassWord() == pass)
                    {
                        cout << "You sucessfully login. " << endl;
                    }
                }
            }
            break;
        }
        case 5:
        {
            for (int i = 0; i < totalCount; i++)
            {
                if (typeid(*lptr[i]) == typeid(Book))
                {
                    lptr[i]->getter();
                    cout << "******" << endl;
                }
            }
            break;
        }
        case 6:
        {
            saveUsers(aptr, userCount, totalCount);
            saveBooks(lptr, totalCount, bookCount);
            saveMembers(lptr, memberCount, totalCount);
            // cout << "Total Count: " << totalCount << ", Book Count: " << bookCount << endl;
            cout << "Data saved sucessfully. " << endl;
            break;
        }
        case 7:
        {
            readUsers(aptr, userCount, totalCount);
            readBooks(lptr, bookCount);
            readMembers(lptr, memberCount);
            // cout << "Total Count: " << totalCount << ", Book Count: " << bookCount << endl;
            cout << "Data read sucessfully. " << endl;
            break;
        }
        case 8:
        {
            for (int i = 0; i < totalCount; i++)
            {
                delete lptr[i];
            }
            break;
        }
        }
    } while (chh != 8);
}
