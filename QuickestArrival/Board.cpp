#include "Board.h"


Board::Board() {
    cin >> cols >> rows;
    getchar();

    board = new char* [cols];
    for (int i = 0; i < cols; i++) {
        board[i] = new char[rows];
    }

    matrix = new bool* [cols];
    for (int i = 0; i < cols; i++) {
        matrix[i] = new bool[rows];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[j][i] = getchar();
            if (board[j][i] == '*') {
                numberOfCities++;
            }
        }
        getchar();
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[j][i] = false;
        }
    }
}

int Board::getNumberOfCities() {
    return numberOfCities;
}

bool Board::isValidXY(int x, int y) {
    if (x < 0 || y < 0 || x >= cols || y >= rows) {
        return false;
    }
    return true;
}

void Board::cleanMatrix(int x, int y) {

    matrix[x][y] = false;

    for (int i = 0; i < 4; i++) {
        if (isValidXY(x + vectorX[i], y + vectorY[i])) {
            if (matrix[x + vectorX[i]][y + vectorY[i]] == true) {
                cleanMatrix(x + vectorX[i], y + vectorY[i]);
            }
        }
    }
}

void Board::addAnswers(HashTable* Structure) {

    int k, type;
    char symbol;
    cin >> k;
    getchar();

    for (int i = 0; i < k; i++) {

        Name* name1 = new Name;
        symbol = getchar();
        while (symbol != 10 && symbol != 32) {
            name1->addLetter(symbol);
            symbol = getchar();
        }

        name1->setKeyAndHashCode(numberOfCities);

        Name* name2 = new Name;
        symbol = getchar();
        while (symbol != 10 && symbol != 32) {
            name2->addLetter(symbol);
            symbol = getchar();
        }

        name2->setKeyAndHashCode(numberOfCities);

        cin >> type;
        getchar();

        if (type == 0) {
            Structure->Dijkstra(this, new City(-1, -1, name1, numberOfCities, -1));
        }
        else {
            Structure->DijkstraPath(this, new City(-1, -1, name1, numberOfCities, -1), name2);
        }

        Node* temp = Structure->table[name2->getHashIndex()];

        if (name2->isEqual(temp->city->getCityName())) {
            cout << temp->city->getDistance();
        }
        else {
            while (temp->next != nullptr) {
                if (name2->isEqual(temp->city->getCityName())) {
                    cout << temp->city->getDistance();
                }
                temp = temp->next;
            }
            if (name2->isEqual(temp->city->getCityName())) {
                cout << temp->city->getDistance();
            }
        }

        if (type == 1) {
            for (int i = Structure->getPathSize() - 2; i >= 0; i--) {
                cout << " ";
                Structure->path[i]->print();
            }
        }
        cout << "\n";

        /*delete[] name1;
        delete[] name2;*/
    }
}


void Board::addFlightsToHashTable(HashTable* Structure) {
    int k, time;
    char symbol;
    cin >> k;
    getchar();

    for (int i = 0; i < k; i++) {

        Name* name1 = new Name;
        symbol = getchar();
        while (symbol != 10 && symbol != 32) {
            name1->addLetter(symbol);
            symbol = getchar();
        }

        name1->setKeyAndHashCode(numberOfCities);

        Name* name2 = new Name;
        symbol = getchar();
        while (symbol != 10 && symbol != 32) {
            name2->addLetter(symbol);
            symbol = getchar();
        }

        name2->setKeyAndHashCode(numberOfCities);

        cin >> time;
        getchar();

        Structure->addNeighbour(Structure->findNodeFromCity(new City(-1, -1, name1, numberOfCities)), new City(-1, -1, name2, numberOfCities, time));
    }
}

void Board::printBoard() {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << board[j][i];
        }
        cout << "\n";
    }
}

Name* Board::createName(int posX, int posY) {

    Name* newName = new Name;
    int startX, startY;

    for (int i = posX - 1; i < posX + 2; i++) {
        for (int j = posY - 1; j < posY + 2; j++) {
            if (isValidXY(i, j)) {
                if (board[i][j] != '#' && board[i][j] != '.' && board[i][j] != '*') {
                    startX = i;
                    startY = j;
                    while (isValidXY(startX - 1, startY)) {
                        if (board[startX - 1][startY] == '#' || board[startX - 1][startY] == '.' || board[startX - 1][startY] == '*') {
                            break;
                        }
                        startX--;
                    }

                    newName->addLetter(board[startX][startY]);

                    while (isValidXY(startX + 1, startY)) {
                        if (board[startX + 1][startY] == '#' || board[startX + 1][startY] == '.' || board[startX + 1][startY] == '*') {
                            break;
                        }
                        startX++;
                        newName->addLetter(board[startX][startY]);
                    }

                    newName->setKeyAndHashCode(numberOfCities);

                    return newName;
                }
            }
        }
    }
    newName->setKeyAndHashCode(numberOfCities);
    return newName;
}

void Board::addCitiesToHashTable(HashTable* Structure) {
    City* newCity;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[j][i] == '*') {

                newCity = new City(j, i, createName(j, i), numberOfCities);
                Node* nodePtr = Structure->addCity(newCity);
                BFS(Structure, nodePtr, j, i);
            }
        }
    }
}

void Board::BFS(HashTable* Structure, Node* nodePtr, int startX, int startY) {

    moveCount = 0;
    nodesLeftInLayer = 1;
    nodesInNextLayer = 0;

    int x, y;
    Queue* queueX = new Queue(QUEUESIZE);
    Queue* queueY = new Queue(QUEUESIZE);

    queueX->enqueue(startX);
    queueY->enqueue(startY);
    matrix[startX][startY] = true;

    while (!queueX->isEmpty()) {

        x = queueX->dequeue();
        y = queueY->dequeue();

        if (board[x][y] == '*' && (x != startX || y != startY)) {
            Structure->addNeighbour(nodePtr, new City(x, y, createName(x, y), numberOfCities, moveCount));
        }
        else {
            checkNeighbours(x, y, queueX, queueY);
        }

        nodesLeftInLayer--;
        if (nodesLeftInLayer == 0) {
            nodesLeftInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
            moveCount++;
        }
    }
    cleanMatrix(startX, startY);
    /*delete[] queueX;
    delete[] queueY;*/
}

void Board::checkNeighbours(int x, int y, Queue* queueX, Queue* queueY) {

    for (int i = 0; i < 4; i++) {
        int X = x + vectorX[i];
        int Y = y + vectorY[i];

        if (!isValidXY(X, Y)) {
            continue;
        }
        if (matrix[X][Y] == true || (board[X][Y] != '#' && board[X][Y] != '*')) {
            continue;
        }

        queueX->enqueue(X);
        queueY->enqueue(Y);
        matrix[X][Y] = true;
        nodesInNextLayer++;
    }
}

void Board::printMatrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[j][i];
        }
        cout << "\n";
    }
}

Board::~Board() {

    /*for (int i = 0; i < cols; i++) {
            delete[] board[i];
    }
    delete[] board;

    for (int i = 0; i < cols; i++) {
            delete[] matrix[i];
    }
    delete[] matrix;*/
}