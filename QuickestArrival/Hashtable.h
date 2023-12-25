#pragma once
#include "Board.h"

class Board;

struct Neighbour {
    Neighbour* next;
    Neighbour* prev;
    City* city;

    Neighbour() : next(nullptr), prev(nullptr), city(nullptr) {}
    Neighbour(Neighbour* next, Neighbour* prev, City* city) : next(next), prev(prev), city(city) {}
};

struct Node {
    Node* next;
    City* city;
    Neighbour* neighbours;
    Neighbour* lastNeighbour;

    Node() : next(nullptr), city(nullptr), neighbours(nullptr), lastNeighbour(nullptr) {}
    Node(City* city) : next(nullptr), city(city), neighbours(nullptr), lastNeighbour(nullptr) {}
};

class HashTable {
private:

    int pathSize;
    int size;

public:
    Node** table;
    Name** path;

    HashTable(int size);

    void Dijkstra(Board* board, City* startCity);
    void DijkstraPath(Board* board, City* startCity, Name* endName);
    void printAll();
    void addNeighbour(Node* nodePointer, City* newNeighbour);
    Node* addCity(City* city);
    Node* findNodeFromCity(City* city);
    Node* findNodeFromName(Name* name);
    bool areCitiesEqual(City* city1, City* city2);
    int getPathSize();
    ~HashTable();
};