#pragma once
using namespace std;
#include <cstring>
#include <iostream>

class Name {
private:
    char* str;
    int length, key, hashCode;

public:

    Name();

    void addLetter(char c);
    void removeLetter();
    bool isEqual(Name* newName);
    void print();
    void setKeyAndHashCode(int modulo);

    int getKey();
    int getHashIndex();
    int getLength();


    ~Name();
};
