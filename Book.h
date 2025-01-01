#include "Library.h"
class Book : public Library
{
protected:
    unsigned int bookId;
    char title[30];
    char author[30];
    bool isAvailable;

public:
    // ctor
    Book(const char n[] = " ", unsigned int bId = 0, const char t[] = " ", const char a[] = " ", bool isA = false) : Library(n), bookId(bId), isAvailable(isA) {}
    void setter();
    void getter();
    unsigned int getBookId();
    bool getIsBookAvailable();
    void setIsBookAvailable(bool);
};
