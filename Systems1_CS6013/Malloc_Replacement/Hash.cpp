//
// Created by Derek Olson on 3/3/20.
//

#include "Hash.h"
#include <sys/mman.h>
#include <cstdio>

//Hash table constructor
Hash::Hash(int tableCapacity){
    this->tablePtr = static_cast<hashNode *>(mmap(NULL, sizeof(hashNode) * tableCapacity,
                                                  PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0));
    this->tableSize = 0;
    this->tableCapacity = tableCapacity;

    this->memCapacity = 0;
    this->memSize = 0;
    this->memPtr = NULL;

    for(int i = 0; i < tableCapacity; i++){
        hashNode hn = hashNode(NULL, 0);
        hn.setActive(false);
        tablePtr[i] = hn;
    }
}

//hash table deconstructor
Hash::~Hash(){
    for(int i = 0; i < tableCapacity; i++){
        if(tablePtr[i].isActive()){
            deallocate(tablePtr[i]);
        }
    }

    munmap(tablePtr, tableCapacity);
}

//method to hash nodes
int Hash::hash(hashNode hn){
    int index = (this->tableSize + hn.getSize()) % this->tableCapacity;
    hashNode* nodes = static_cast<hashNode*>(tablePtr);
    while(nodes[index].isActive()){
        index = index+1 % tableCapacity;
    }
    return index;
}

void* Hash::allocate(size_t bytesToAllocate) {
    size_t roundedBytes = 0;
    size_t remainder = bytesToAllocate % 4096;
    if (remainder == 0) {
        roundedBytes = bytesToAllocate;
    }
    else {
        roundedBytes = bytesToAllocate + 4096 - remainder;
    }

    std::byte* mm = static_cast<std::byte*>(mmap(NULL, roundedBytes, PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANON|MAP_PRIVATE, -1, 0));

    this->memPtr = mm;
    this->memSize = 0;
    this->memCapacity = roundedBytes;
    return mm;
}

void Hash::deallocate(hashNode node){
    munmap(node.getP(), node.getSize());
}

void Hash::insert(int size) {
    if(this->tableSize == this->tableCapacity){
        grow();
    }
    if(this->memPtr == NULL || this->memSize + size >= this->memCapacity){
        allocate(size);
    }
    hashNode hn = hashNode(this->memPtr + this->memSize, size);
    this->memSize += size;

    this->tablePtr[this->hash(hn)] = hn;
    this->tableSize+=1;
}

void Hash::remove(hashNode node){
    int index = (this->tableSize + node.getSize()) % this->tableCapacity;
    int counter = 0;
    while(tablePtr[index].getP() != node.getP()){
        if(counter > tableCapacity){
            std::perror("table does not contain node");
        }
        index = index + 1 % tableCapacity;
        counter++;
    }
    tablePtr[index].setActive(false);
    tableSize--;

    deallocate(node);

}

void Hash::grow(){
    Hash temp = Hash(tableCapacity * 2);
    for(int i = 0; i < tableCapacity; i++){
        temp.tablePtr[temp.hash(this->tablePtr[i])] = this->tablePtr[i];
    }
    this->tablePtr = temp.tablePtr;
    temp.tablePtr = nullptr;
    this->tableCapacity = temp.tableCapacity;
    temp.tableCapacity = NULL;
}

hashNode::hashNode(std::byte* p, int size){
    this->p = p;
    this->size = size;
    this->active = true;
}

std::byte* hashNode::getP() const {
    return p;
}

void hashNode::setP(std::byte* p) {
    hashNode::p = p;
}

int hashNode::getSize() const {
    return size;
}

void hashNode::setSize(int size) {
    hashNode::size = size;
}

bool hashNode::isActive() const {
    return active;
}

void hashNode::setActive(bool active) {
    hashNode::active = active;
}


void hashNode::deactivate() {
    setActive(false);
    setP(NULL);
}