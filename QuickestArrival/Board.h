#pragma once
using namespace std;
#include <iostream>
#include "Name.h"
#include "City.h"
#include "HashTable.h"
#include "Queue.h"
#include "PQ.h"
#define QUEUESIZE 100
#define INFINITY 99999999

class Board {
private:
    int cols, rows;
    int vectorX[4] = { 1 , -1, 0, 0 };
    int vectorY[4] = { 0 , 0, 1, -1 };
    int numberOfCities = 0;
    int nextCityIndex = 0;
    int moveCount, nodesLeftInLayer, nodesInNextLayer;
public:
    char** board;
    bool** matrix;

    Board();
    void cleanMatrix(int x, int y);
    void printBoard();
    void printMatrix();
    void addCitiesToHashTable(HashTable* Structure);
    void addFlightsToHashTable(HashTable* Structure);
    void addAnswers(HashTable* Structure);
    void BFS(HashTable* Structure, Node* nodePtr, int startX, int startY);
    void checkNeighbours(int x, int y, Queue* queueX, Queue* queueY);
    bool isValidXY(int x, int y);
    int getNumberOfCities();
    Name* createName(int posX, int posY);
    ~Board();
};
