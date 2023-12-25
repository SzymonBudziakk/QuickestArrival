#include "Board.h"

Queue::Queue(int size) {
    front = -1;
    rear = -1;
    length = size;
    nums = new int[size];
}

void Queue::enqueue(int value) {
    if (isFull()) {
        resize();
    }
    else if (isEmpty()) {
        front++;
    }
    rear = (rear + 1) % length;
    nums[rear] = value;
}

int Queue::dequeue() {
    if (isEmpty()) {
        return -1;
    }
    int temp = nums[front];
    if (front == rear) {
        front = -1;
        rear = -1;
    }
    else {
        front = (front + 1) % length;
    }
    return temp;
}

bool Queue::isEmpty() {
    return front == -1;
}

bool Queue::isFull() {
    return (rear + 1) % length == front;
}

void Queue::resize() {
    int* tempArr = new int[length * 2];
    int i = 0;
    int j = front;

    do {
        tempArr[i++] = nums[j];
        j = (j + 1) % length;
    } while (j != front);

    front = 0;
    rear = length - 1;
    nums = tempArr;
    length *= 2;
}

Queue::~Queue() {
    delete[] nums;
}