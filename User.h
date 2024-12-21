#include <iostream>
#include "Book.h"
#include "Member.h"
using namespace std;
#define MAXBOOKS 100
#define MAX_MEMBERS 50
class User
{
protected:
    // int userId;
    string name;
    Book books[MAXBOOKS];
    Member members[MAX_MEMBERS];
    int bookCount;
    int memCount;

public:
    void viewBooks();
    void setter();
    void getter();
};