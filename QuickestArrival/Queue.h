#pragma once
#include "Board.h"


class Queue {

private:
    int front, rear, length;
    int* nums;

public:
    Queue(int size);
    void enqueue(int value);
    int dequeue();
    bool isEmpty();
    bool isFull();
    void resize();
    ~Queue();
};
