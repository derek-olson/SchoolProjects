//
//  Functions.cpp
//  TimingAndOptimizationLab
//
//  Created by Derek Olson on 9/13/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "Functions.hpp"
#include <vector>
#include <iostream>

std::vector<double> makeVector(int rows, int columns){
    std::vector<double> v;
    for (int i = 0; i < rows; i++){
        for (int i = 0; i < columns; i++){
            v.push_back(1);
        }
    }
    return v;
}


__attribute__((noinline)) double sum1(const std::vector<double>& vector, int numRows, int numCols){
    double sum = 0;
    for (int r = 0; r < numRows; r++){
        for (int c = 0; c < numCols; c++){
            sum += vector[((r * numCols) + c)];
        }
    }
    return sum;
}


__attribute__((noinline)) double sum2(const std::vector<double>& vector, int numRows, int numCols){
    double sum = 0;
    for (int c = 0; c < numCols; c++){
        for (int r = 0; r < numRows; r++){
            sum += vector[((r * numCols) + c)];
        }
    }
    return sum;
}


