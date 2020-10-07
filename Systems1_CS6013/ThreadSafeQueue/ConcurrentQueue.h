//
// Created by Derek Olson on 3/30/20.
//

#pragma once

#include <mutex>

template <typename T>
class ConcurrentQueue{
private:
    struct Node{
        T data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int size_;
    std::mutex mutex = std::mutex();

public:
    ConcurrentQueue()
            :head(new Node{T{}, nullptr}), size_(0)
    {
        tail = head;
    }


    void enqueue(const T& x){
        Node* node = new Node();
        node->data = x;
        node->next = nullptr;

        mutex.lock();
        if (size() == 0) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        size_++;
        mutex.unlock();

    }

    bool dequeue(T& ret){

        mutex.lock();
        if (size() == 0) {
            //return false;
            mutex.unlock();
            return dequeue(ret);
        }
        Node *toDequeue = head;
        head = toDequeue->next;
        delete toDequeue;
        if (size() != 1) {
            ret = head->data;
        }
        size_--;
        mutex.unlock();
        return true;
    }

    ~ConcurrentQueue(){
        while(head){
            Node* temp = head->next;
            delete head;
            head = temp;
        }
    }

    int size() const{ return size_;}
};

