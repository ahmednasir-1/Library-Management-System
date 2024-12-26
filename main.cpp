#include <iostream>
#include <string>
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
    friend void readUsers(Authentication *pp[], int &userCount);
    friend void saveUsers(Authentication *pp[], int userCount);
    void setPassword();
    string getUserName()
    {
        return username;
    }
    string getPassWord()
    {
        return password;
    }
    void saveToFile();
    void readFromFile(string s1[3]);
};
void Authentication::saveToFile()
{
    ofstream outfile;
    outfile.open("userDetails.txt", ios::out);
    if (!outfile)
    {
        cout << "Error. File can't be opened. " << endl;
    }

    outfile << username << endl
            << password << endl;
    outfile.close();
}
void Authentication::readFromFile(string s1[2])
{
    ifstream infile;
    infile.open("userDetails.txt", ios::in);
    if (!infile)
    {
        cout << "Error. File can't be opened. " << endl;
    }
    // // string arr[2];
    // while (infile.good())
    // {
    //     for (int i = 0; i < 2; i++)
    //     {
    //         getline(infile, s1[i]);
    //         // cout << endl;
    //     }
    // }
    for (int i = 0; i < 2; i++)
    {
        if (!getline(infile, s1[i]))
        {
            cout << "Error: Unable to read line " << i + 1 << "." << endl;
            infile.close();
            return;
        }
    }
    infile.close();
}
void Authentication::setPassword()
{
    cout << "Enter your username: ";
    cin.ignore();
    cin.getline(username, 30);
    cout << "Enter your password: ";
    cin.getline(password, 30);
    // saveToFile();
}

class Book
{
protected:
    unsigned int bookId;
    string title;
    string author;
    bool isAvailable;
    int noOfCopies;

public:
    void addBook(int);
    void displayBooks();
    int getBookId();
};
class User
{
protected:
    // int userId;
    string name;

public:
    void viewBooks();
    void setter();
    void getter();
};
class Member : virtual public User
{
protected:
    int memberId;

public:
    void addMem(int);
    void dispMem();
    int getMemId()
    {
        return memberId;
    }
};
class Student : virtual public User
{
public:
    // void viewBooks();
};
class Librarian : virtual public User, virtual public Book
{
protected:
    Book books[MAXBOOKS];
    Member members[MAX_MEMBERS];
    int bookCount;
    int memCount;

public:
    void setterBook();
    void getterBook();
    void addBook();
    void appBook();
    // void updateBook();
    void delBook();
    // void genRepBook();
    int searchBook(int &, int &);
    void dispBooks();
    void addMember();
    // void delMember();
    void displayMember();
    int searchMember(int, int);
    int getBookCount()
    {
        return bookCount;
    }
};
void Librarian::setterBook()
{
}
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
    cin.ignore();
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
    cout << "Member Id: " << memberId << endl;
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
    for (int i = 0; i < memCount; i++)
    {
        members[i].dispMem();
    }
}
int Librarian::searchMember(int id, int nn)
{
    int s;
    for (int i = 0; i < nn; i++)
    {
        if (id == members[i].getMemId())
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
void saveUsers(Authentication *pp[], int userCount)
{
    ofstream outfile;
    outfile.open("userdetails.DAT", ios::out | ios::binary);
    if (!outfile)
    {
        cout << "Error while opening the file. " << endl;
    }
    outfile.write(reinterpret_cast<char *>(&userCount), sizeof(int));
    for (int i = 0; i < userCount; i++)
    {
        outfile.write(reinterpret_cast<char *>(pp[i]), sizeof(Authentication));
    }
    outfile.close();
}
void readUsers(Authentication *pp[], int &userCount)
{
    ifstream infile;
    infile.open("userdetails.DAT", ios::in | ios::binary);
    if (!infile)
    {
        cout << "Error while opening the file. " << endl;
    }
    infile.read(reinterpret_cast<char *>(&userCount), sizeof(int));
    for (int i = 0; i < userCount; i++)
    {
        pp[i] = new Authentication;
        infile.read(reinterpret_cast<char *>(pp[i]), sizeof(Authentication));
    }
    infile.close();
}
int main()
{
    Librarian library;
    Authentication *aptr[3];
    int userCount = 0;
    int ch;
    do
    {
        cout << "----- Library Management System -------- " << endl
             << "1. Create Account" << endl
             << "2. Login" << endl
             << "3. Search a Book" << endl
             << "4. Display Books" << endl
             << "5. Save Users Data" << endl
             << "6. Read Users Data" << endl
             << "7. Exit" << endl
             << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            if (userCount < 3)
            {
                aptr[userCount] = new Authentication;
                aptr[userCount]->setPassword();
                userCount++;
            }
            else
            {
                cout << "Can't add more admins. " << endl;
            }
        }
        break;
        case 2:
        {
            string id, pass;
            cout << "Enter your user id: ";
            cin.ignore();
            getline(cin, id);
            // string s1[2];
            // Authentication::readFromFile(string s1[2]);
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
                            cout << "---- LMS ------" << endl
                                 << "1. Add a Book" << endl
                                 << "2. Search a Book" << endl
                                 << "3. Append a Book" << endl
                                 << "4. Delete a Book" << endl
                                 << "5. Display Books" << endl
                                 << "6. Add a Member" << endl
                                 << "7. Search a Member" << endl
                                 << "8. Delete a Member" << endl
                                 << "9. Display Members" << endl
                                 << "10. Exit" << endl
                                 << "Enter your choice: ";
                            cin >> ch;
                        }
                        else
                        {
                            cout << "Password not match. " << endl;
                        }
                        j++;
                    }
                    exit(1);
                }
                else
                {
                    cout << "User name not found. " << endl;
                    break;
                }
            }
        }
        break;
        case 3:
        {
            int id;
            cout << "Enter the book id: ";
            cin >> id;
            // library.searchBook(id, getBookCount());
        }
        break;
        case 4:
        {
            library.dispBooks();
        }
        break;
        case 5:
        {
            saveUsers(aptr, userCount);
        }
        break;
        case 6:
        {
            readUsers(aptr, userCount);
        }
        break;
        case 7:
            break;
        }
    } while (ch != 7);
}
