#include "Board.h"

HashTable::HashTable(int size) : size(size) {

    table = new Node * [size];
    for (int i = 0; i < size; i++) {
        table[i] = new Node[size];
    }

    path = new Name * [size];
    for (int i = 0; i < size; i++) {
        path[i] = new Name[size];
    }
}

Node* HashTable::addCity(City* city) {

    int index = city->getHashCode();

    if (table[index]->city == nullptr) {
        table[index]->city = city;
        return table[index];
    }
    else {
        Node* current = table[index];

        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node(city);
        return current->next;
    }
}

void HashTable::Dijkstra(Board* board, City* startCity) {

    for (int i = 0; i < size; i++) {
        if (table[i]->city != nullptr) {
            table[i]->city->setVisited(false);
            table[i]->city->setDistance(INFINITY);

            Node* temp = table[i];
            while (temp->next != nullptr) {
                temp = temp->next;
                temp->city->setVisited(false);
                temp->city->setDistance(INFINITY);
            }
        }
    }

    Node* temp = table[startCity->getHashCode()];

    while (!temp->city->getCityName()->isEqual(startCity->getCityName())) {
        temp = temp->next;
    }

    temp->city->setDistance(0);
    startCity->setDistance(0);

    PQ* pq = new PQ(board->getNumberOfCities());
    pq->push(startCity->getCityName(), 0);

    while (pq->getSize() > 0) {

        Element el = pq->min();
        Name* name = el.name;
        pq->pop();

        Node* mainCity = findNodeFromName(name);
        mainCity->city->setVisited(true);

        Neighbour* neighbour = mainCity->neighbours;

        while (neighbour != nullptr) {

            Node* thisNeighboursNode = findNodeFromName(neighbour->city->getCityName());

            if (thisNeighboursNode->city->getVisited()) {
                neighbour = neighbour->next;
                continue;
            }

            int newDist = mainCity->city->getDistance() + neighbour->city->getTime();
            if (newDist < thisNeighboursNode->city->getDistance()) {
                thisNeighboursNode->city->setDistance(newDist);
                pq->push(neighbour->city->getCityName(), newDist);
            }

            neighbour = neighbour->next;
        }
    }
}

void HashTable::DijkstraPath(Board* board, City* startCity, Name* endName) {

    pathSize = 0;

    for (int i = 0; i < size; i++) {
        if (table[i]->city != nullptr) {
            table[i]->city->setVisited(false);
            table[i]->city->setDistance(INFINITY);
            table[i]->city->setPrevious(nullptr);

            Node* temp = table[i];
            while (temp->next != nullptr) {
                temp = temp->next;
                temp->city->setVisited(false);
                temp->city->setDistance(INFINITY);
                temp->city->setPrevious(nullptr);
            }
        }
    }

    Node* temp = table[startCity->getHashCode()];

    while (!temp->city->getCityName()->isEqual(startCity->getCityName())) {
        temp = temp->next;
    }

    temp->city->setDistance(0);
    startCity->setDistance(0);

    PQ* pq = new PQ(board->getNumberOfCities());
    pq->push(startCity->getCityName(), 0);

    while (pq->getSize() > 0) {

        Element el = pq->min();
        Name* name = el.name;
        pq->pop();

        Node* mainCity = findNodeFromName(name);
        mainCity->city->setVisited(true);

        Neighbour* neighbour = mainCity->neighbours;
        while (neighbour != nullptr) {

            Node* thisNeighboursNode = findNodeFromName(neighbour->city->getCityName());

            if (thisNeighboursNode->city->getVisited()) {
                neighbour = neighbour->next;
                continue;
            }

            int newDist = mainCity->city->getDistance() + neighbour->city->getTime();

            if (newDist < thisNeighboursNode->city->getDistance()) {
                thisNeighboursNode->city->setPrevious(name);
                thisNeighboursNode->city->setDistance(newDist);
                pq->push(neighbour->city->getCityName(), newDist);
            }
            neighbour = neighbour->next;
        }
    }

    if (findNodeFromName(endName)->city->getDistance() != INFINITY) {

        Name* current = findNodeFromName(endName)->city->getPrevious();
        while (current != nullptr) {

            Name* tempName = current;
            path[pathSize] = tempName;
            pathSize++;
            current = findNodeFromName(current)->city->getPrevious();
        }
    }
}
int HashTable::getPathSize() {
    return pathSize;
}

void HashTable::addNeighbour(Node* nodePointer, City* newNeighbour) {

    if (nodePointer->lastNeighbour == nullptr) {
        Neighbour* temp = new Neighbour(nullptr, nullptr, newNeighbour);
        nodePointer->neighbours = temp;
        nodePointer->lastNeighbour = temp;
    }
    else {
        Neighbour* tempPrev = nodePointer->lastNeighbour;
        Neighbour* temp = new Neighbour(nullptr, tempPrev, newNeighbour);

        nodePointer->lastNeighbour->next = temp;
        nodePointer->lastNeighbour = temp;
    }
}

bool HashTable::areCitiesEqual(City* city1, City* city2) {

    if (city1->getKey() == city2->getKey()) {
        if (city1->getCityName()->isEqual(city2->getCityName())) {
            return true;
        }
    }
    return false;
}

Node* HashTable::findNodeFromCity(City* city) {

    int index = city->getHashCode();

    if (areCitiesEqual(city, table[index]->city)) {
        return table[index];
    }
    else {
        Node* current = table[index];

        while (current->next != nullptr) {
            current = current->next;
            if (areCitiesEqual(city, current->city)) {
                return current;
            }
        }
        return current;
    }
}

Node* HashTable::findNodeFromName(Name* name) {

    name->setKeyAndHashCode(size);
    int index = name->getHashIndex();

    if (name->isEqual(table[index]->city->getCityName())) {
        return table[index];
    }
    else {

        Node* current = table[index];

        while (current->next != nullptr) {
            current = current->next;
            if (name->isEqual(current->city->getCityName())) {
                return current;
            }
        }

        return current;
    }
}

void HashTable::printAll() {
    Neighbour* temp;
    Node* temp2;

    for (int i = 0; i < size; i++) {
        cout << "INDEX " << i << "\n";

        if (table[i]->city == nullptr) {
            continue;
        }
        else {

            cout << "\nMAIN CITY: ";
            table[i]->city->printNameTime();

            if (table[i]->neighbours != nullptr) {

                temp = table[i]->neighbours;
                temp->city->printNameTime();

                while (temp->next != nullptr) {
                    temp = temp->next;
                    temp->city->printNameTime();
                }
            }

            temp2 = table[i];

            while (temp2->next != nullptr) {

                temp2 = temp2->next;
                cout << "\nMAIN CITY: ";
                temp2->city->printNameTime();

                if (temp2->neighbours != nullptr) {
                    temp = temp2->neighbours;
                    temp->city->printNameTime();
                    while (temp->next != nullptr) {
                        temp = temp->next;
                        temp->city->printNameTime();
                    }
                }
            }

        }

    }
}

HashTable::~HashTable() {}