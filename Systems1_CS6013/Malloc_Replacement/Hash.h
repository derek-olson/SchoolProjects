//
// Created by Derek Olson on 3/3/20.
//

#ifndef MALLOC_REPLACEMENT_HASH_H
#define MALLOC_REPLACEMENT_HASH_H


#include <cstdlib>
#include <unordered_map>

class hashNode{
private:
    std::byte* p;
    int size;
    bool active;

public:
    hashNode(std::byte* p, int size);
    std::byte* getP() const;
    void setP(std::byte* p);
    int getSize() const;
    void setSize(int size);
    bool isActive() const;
    void setActive(bool active);

    void deactivate();
};

class Hash {
public:
    std::byte* memPtr; // pointer to memory
    size_t tableSize; //table size
    int tableCapacity; // table capacity
    int memSize; //memory size
    int memCapacity; //memory capacity
    hashNode* tablePtr; // pointer to array

    Hash(int tableCapacity);
    ~Hash();
    void* allocate(size_t bytesToAllocate);
    void deallocate(hashNode node);
    int hash(hashNode hn);
    void insert(int size);
    void remove(hashNode node);
    void grow();
};

#endif //MALLOC_REPLACEMENT_HASH_H
