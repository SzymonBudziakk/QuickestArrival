#pragma once

struct Element {
    Name* name;
    int distance;
};

class PQ {
private:
    Element* list;
    int size;

public:
    PQ(int size);
    void heapify(int n);
    void push(Name* newName, int newDistance);
    void pop();
    void build();
    void print();
    void swap(Element& a, Element& b);
    void heapifyUp(int n);
    Element min();
    bool test();
    int getSize();
    ~PQ();
};
