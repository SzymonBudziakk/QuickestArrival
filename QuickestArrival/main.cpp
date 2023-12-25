#include "Board.h"

int main() {

    Board* map = new Board;
    HashTable* Structure = new HashTable(map->getNumberOfCities());
    map->addCitiesToHashTable(Structure);
    map->addFlightsToHashTable(Structure);
    map->addAnswers(Structure);

    /*Structure->printAll();*/

    return 0;
}