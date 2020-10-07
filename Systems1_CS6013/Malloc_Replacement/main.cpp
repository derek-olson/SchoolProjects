#include <iostream>
#include "Hash.h"
#include <chrono>

int main() {
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //TESTING
    ///////////////////////////////////////////////////////////////////////////////////////////////
    Hash ht = Hash(5);
    //After initialization the hash table size is 0 and the capacity is 5.
    std::cout << "Table Size: " << ht.tableSize << std::endl;
    std::cout << "Table Capacity: " << ht.tableCapacity << std::endl;
    std::cout << "Table Memory Location: " << ht.tablePtr << std::endl;

    //insert 1 node into the table
    ht.insert(3);
    //After inserting 1 node into the hash table the table size is 1 and the capacity
    //is still 5.
    std::cout << "Table Size: " << ht.tableSize << std::endl;
    std::cout << "Table Capacity: " << ht.tableCapacity << std::endl;
    std::cout << "Table Memory Location: " << ht.tablePtr << std::endl;
    std::cout << "Allocated Node Location: " << ht.tablePtr[3].getP() << std::endl;
    std::cout << "Memory Location: " << ht.memPtr << std::endl;

    //insert 5 more nodes
    ht.insert(4);
    ht.insert(2);
    ht.insert(5);
    ht.insert(8);
    ht.insert(6);
    //After inserting 6 nodes into the hash table the table size is 6 and the capacity has doubled from
    //5 to 10. The table memory location has also changed.
    std::cout << "Table Size: " << ht.tableSize << std::endl;
    std::cout << "Table Capacity: " << ht.tableCapacity << std::endl;
    std::cout << "Table Memory Location: " << ht.tablePtr << std::endl;
    std::cout << "Allocated Node Location: " << ht.tablePtr[3].getP() << std::endl;
    std::cout << "Memory Location: " << ht.memPtr << std::endl;

    ht.remove(ht.tablePtr[5]);
    std::cout << "Allocated Node Location After Removal: " << ht.tablePtr[5].getP() << std::endl;

    ht.deallocate(ht.tablePtr[0]);
    std::cout << "Allocated Node Location After Deallocation: " << ht.tablePtr[0].getP() << std::endl;
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //BENCHMARK TESTING FOR INSERT VS ALLOCATE VS MALLOC
    ///////////////////////////////////////////////////////////////////////////////////////////////
    int allocateTime = 0;
    Hash table = Hash(3);
    for(int i = 0; i < 100; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        table.allocate(3);
        table.allocate(4);
        table.allocate(2);
        table.allocate(5);
        table.allocate(8);
        table.allocate(6);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        allocateTime += duration.count();
    }
    std::cout << "Allocation Time: " << allocateTime/100 << std::endl;

    int insertTime = 0;
    Hash insertTable = Hash(3);
    for(int i = 0; i < 100; i++) {
        auto start3 = std::chrono::high_resolution_clock::now();
        insertTable.insert(3);
        insertTable.insert(4);
        insertTable.insert(2);
        insertTable.insert(5);
        insertTable.insert(8);
        insertTable.insert(6);
        auto stop3 = std::chrono::high_resolution_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3- start3);
        insertTime += duration3.count();
    }
    std::cout << "Insert Time: " << insertTime/100 << std::endl;

    int mallocTime = 0;
    for(int i = 0; i < 100; i++) {
        auto start2 = std::chrono::high_resolution_clock::now();
        malloc(3);
        malloc(4);
        malloc(2);
        malloc(5);
        malloc(8);
        malloc(6);
        auto stop2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
        mallocTime += duration2.count();
    }
    std::cout << "Malloc Time: " << mallocTime/100.0 << std::endl;

    return 0;

}
