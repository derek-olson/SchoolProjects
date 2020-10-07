//
// Created by Derek Olson on 4/3/20.
//


#include <vector>
#include <thread>
#include <iostream>
#include "ConcurrentQueue.h"

void localEnqueue(ConcurrentQueue<int>& concurrentQueue, int& numInts){
    for(int i = 0; i < numInts; i++){
        concurrentQueue.enqueue(i);
    }
}

void localDequeue(ConcurrentQueue<int>& concurrentQueue, int& numInts) {

    for (int i = 0; i < numInts; i++) {
        int ret;
        concurrentQueue.dequeue(ret);
    }
}

bool testQueue(int numProducers, int numConsumers, int numInts){
    std::vector<std::thread> threads;
    threads.reserve(numProducers+numConsumers);
    ConcurrentQueue<int> concurrentQueue = ConcurrentQueue<int>();

    for(int i = 0; i < numProducers; i++){
        threads.emplace_back(&localEnqueue, std::ref(concurrentQueue), std::ref(numInts));
    }

    for(int i = 0; i < numConsumers; i++){
        wait;
        threads.emplace_back(std::thread(&localDequeue, std::ref(concurrentQueue), std::ref(numInts)));
    }

    for(auto &t : threads){
        t.join();
    }

    if(concurrentQueue.size() == numProducers - numConsumers){
        std::cout << concurrentQueue.size() << "\n";
        return 1;
    }else{
        std::cout << concurrentQueue.size() << "\n";
        return 0;
    }
}

int main(int argc, char* argv[]) {

    int producers = 3; //std::stoi(argv[1]);
    int consumers = 3; //std::stoi(argv[2]);
    int numInts = 100; //std::stoi(argv[3]);

    testQueue(producers, consumers, numInts);

    return 0;
}