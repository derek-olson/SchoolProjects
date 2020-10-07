//
// Created by Derek Olson on 2/24/20.
//
#include <iostream>
#include "Tables.h"
#include "iterator"

Tables::Tables()
{
    for(int i = 0; i < 256; i++){
        arrays[0][i] = i;
    }
    for(int i = 0; i < 7; i++){
        shuffle_array(arrays[i]);
        copyArray(arrays[i], arrays[i+1]);
    }
    shuffle_array(arrays[7]);
}

void Tables::shuffle_array(int arr[])
{
    for (int i = 255; i > 0; i--)
    {
        //rand (time(NULL));

        // Pick a random index from 0 to i
        int j = rand() % (i + 1);

        // Swap arr[i] with the element
        // at random index
        swap(&arr[i], &arr[j]);
    }
}

void Tables::swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Tables::copyArray(int arr1[], int arr2[])
{
    for(int i = 0; i < 256; i++){
        arr2[i] = arr1[i];
    }
}