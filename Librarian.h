#include "User.h"
class Librarian : virtual public User
{
public:
    void addBook();
    void appBook();
    void updateBook();
    void delBook();
    void genRepBook();
    int searchBook(int &, int &);
    void dispBooks();
    void addMember();
    void delMember();
    void displayMember();
    void searchMember(int, int);
};