#pragma once
#include "Board.h"

class City {
private:
    int x, y;
    int key, hashCode;
    Name* cityName;
    int time = -1;
    int distance;
    bool visited;
    Name* previous;

public:

    City(int x, int y, Name* cityName, int modulo);
    City(int x, int y, Name* cityName, int modulo, int time);

    int getKey();
    int getHashCode();
    void addNeighbour(City* city1, City* city2);
    Name* getCityName();
    void setDistance(int n);
    void setVisited(bool n);
    int getDistance();
    void setPrevious(Name* name);
    Name* getPrevious();
    bool getVisited();
    void setTime(int n);
    int getTime();
    void printNameTime();


    ~City();
};
