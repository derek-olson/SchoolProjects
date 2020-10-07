//
//  main.cpp
//  PointerPracticeLab
//
//  Created by Derek Olson on 9/9/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <array>

double* IncreaseArraySize(int size, double* a){
    double* newArray = new double [size*2];
    for (int i = 0; i < size; i++){
        newArray[i] = a[i];
    }
    a = newArray;
    delete [] newArray;
    return a;
}

double* CopyArray(int size, double* a){
    double* newArray = new double [size];
    for (int i = 0; i < size; i++){
        newArray[i] = a[i];
    }
    return newArray;
}

int main(int argc, const char * argv[]) {

//    Write a function that takes an array of doubles as a parameter (well, as 2 parameters, a pointer to a double, and the size of the array) and returns a copy of the array (it should return a pointer to the start of the copied array).
    
    double* test = new double [8];

    double* newArray = CopyArray(2, test);
    
    delete[] test;
    
    double* testArray = IncreaseArraySize(2, test);
    
    return 0;
}
