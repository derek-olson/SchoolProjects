//
// Created by Derek Olson on 3/30/20.
//

#include "SerialQueueTests.h"


#include <iostream>
#include "SerialQueue.hpp"
void testEnque(){
    SerialQueue<int>* serialQueue = new SerialQueue<int>();
    serialQueue->enqueue(10);
    std::cout << serialQueue->size() << "\n";
    assert(serialQueue->size() == 1);
}

void testDequeue(){
    SerialQueue<int>* serialQueue = new SerialQueue<int>();
    serialQueue->enqueue(10);
    serialQueue->enqueue(20);
    serialQueue->enqueue(30);
    std::cout << serialQueue->size() << "\n";
    int ret;
    serialQueue->dequeue(ret);
    std::cout << ret << "\n";
    assert(serialQueue->dequeue(ret));
    assert(ret == 30);
}
int main() {
    //dynamic tests
    testEnque();
    testDequeue();

    //static tests
    SerialQueue<int> serialQueue = SerialQueue<int>();
    serialQueue.enqueue(100);
    std::cout << serialQueue.size() << "\n";
    int ret;
    serialQueue.dequeue(ret);


    return 0;
}