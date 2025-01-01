#include <iostream>
using namespace std;
class Authentication
{
protected:
    char username[30];
    char password[30];

public:
    // ctor
    Authentication(const char username[] = "", const char password[] = "") {}
    virtual void setCredentials();
    string getUserName();
    string getPassWord();
};
