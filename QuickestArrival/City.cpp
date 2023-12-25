#include "Board.h"


City::City(int x, int y, Name* cityName, int modulo) : x(x), y(y), cityName(cityName) {

    cityName->setKeyAndHashCode(modulo);
    key = cityName->getKey();
    hashCode = cityName->getHashIndex();
    distance = INFINITY;
    visited = false;
    previous = nullptr;
}
City::City(int x, int y, Name* cityName, int modulo, int time) : x(x), y(y), cityName(cityName), time(time) {

    cityName->setKeyAndHashCode(modulo);
    key = cityName->getKey();
    hashCode = cityName->getHashIndex();
    distance = INFINITY;
    visited = false;
    previous = nullptr;
}

void City::setPrevious(Name* name) {
    previous = name;
}

int City::getDistance() {
    return distance;
}

int City::getKey() {
    return key;
}

void City::setDistance(int n) {
    distance = n;
}

Name* City::getPrevious() {
    return previous;
}

void City::setVisited(bool n) {
    visited = n;
}

bool City::getVisited() {
    return visited;
}

int City::getHashCode() {
    return hashCode;
}

Name* City::getCityName() {
    return cityName;
}

void City::setTime(int n) {
    time = n;
}

int City::getTime() {
    return time;
}

void City::printNameTime() {
    cityName->print();
    cout << " " << time << " " << distance << "\n";
}

City::~City() {}