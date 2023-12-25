#include "Board.h"

Name::Name() {
    str = new char[10];
    length = 0;
}

void Name::addLetter(char c) {
    if (length < 10) {
        str[length] = c;
        length++;
    }
    else {
        char* temp = new char[length + 1];
        memcpy(temp, str, length);
        delete[] str;
        str = temp;
        str[length] = c;
        length++;
    }
}

void Name::setKeyAndHashCode(int modulo) {
    key = 10007;

    for (int i = 0; i < length; i++) {
        key += str[i];
    }
    hashCode = key % modulo;
}

int Name::getKey() {
    return key;
}

int Name::getHashIndex() {
    return hashCode;
}

bool Name::isEqual(Name* newName) {
    if (length != newName->length) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (str[i] != newName->str[i]) {
            return false;
        }
    }
    return true;
}

int Name::getLength() {
    return length;
}

void Name::print() {
    for (int i = 0; i < length; i++) {
        cout << str[i];
    }
}

void Name::removeLetter() {

    if (length > 0) {
        length--;
    }
}

Name::~Name() {
    /*delete[] str;*/
}