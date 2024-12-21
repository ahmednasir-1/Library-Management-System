#include "User.h"
#include "Librarian.h"
class Member : virtual public User, Librarian
{
protected:
    int memberId;

public:
    void addMem(int);
    void dispMem();
    void getMemId(){
        return memberId;
    }
};