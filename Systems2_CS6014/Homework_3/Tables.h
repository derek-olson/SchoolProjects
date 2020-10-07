//
// Created by Derek Olson on 2/24/20.
//

#ifndef HOMEWORK_3_TABLES_H
#define HOMEWORK_3_TABLES_H


#include <cstdint>

class Tables {
public:
    int arrays[8][256];
public:
    Tables();
    void shuffle_array(int arr[]);
    void swap (int *a, int *b);
    void copyArray(int arr1[], int arr2[]);
};


#endif //HOMEWORK_3_TABLES_H
