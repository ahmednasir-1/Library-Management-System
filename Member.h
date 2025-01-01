#pragma once
#include"Library.h"

class Member : public Library
{
protected:
    unsigned int memberId;
    char regNo[25];

public:
    // ctor
    Member(const char n[] = " ", unsigned int mId = 0, const char rNo[] = " ") : Library(n), memberId(mId) {}
    void setter();
    void getter();
    unsigned int getMemberId();
};
