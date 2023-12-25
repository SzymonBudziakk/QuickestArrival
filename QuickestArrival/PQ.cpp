#include "Board.h"


PQ::PQ(int startSize) {

    list = new Element[startSize];
    size = 0;
}

void PQ::push(Name* newName, int newDistance) {

    list[size].distance = newDistance;
    list[size].name = newName;
    size++;

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(i);
    }
}

void PQ::pop() {
    for (int i = 0; i < size - 1; i++) {
        list[i].distance = list[i + 1].distance;
        list[i].name = list[i + 1].name;
    }
    size--;
}

int PQ::getSize() {
    return size;
}

void PQ::build() {

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(i);
    }
}

void PQ::swap(Element& a, Element& b) {
    Element temp = a;
    a = b;
    b = temp;
}

void PQ::heapify(int n) {
    int largest = n;
    int l = 2 * n + 1;
    int r = 2 * n + 2;

    if (l < size && list[l].distance < list[largest].distance)
        largest = l;

    if (r < size && list[r].distance < list[largest].distance)
        largest = r;

    if (largest != n) {
        swap(list[n], list[largest]);
        heapify(largest);
    }
}

void PQ::heapifyUp(int n) {
    int parent = (n - 1) / 2;
    if (list[n].distance < list[parent].distance) {
        swap(list[n], list[parent]);
        heapifyUp(parent);
    }
}

void PQ::print() {

    for (int i = 0; i < size; i++) {
        list[i].name->print();
        cout << " " << list[i].distance << "\n";
    }
}

Element PQ::min() {
    return list[0];
}

bool PQ::test() {
    int minim = list[0].distance;
    for (int i = 1; i < size; i++) {
        if (minim > list[i].distance) {
            return false;
        }
    }
    return true;
}

PQ::~PQ() {
    delete[] list;
}