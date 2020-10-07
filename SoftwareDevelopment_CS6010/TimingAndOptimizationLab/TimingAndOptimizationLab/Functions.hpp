//
//  Functions.hpp
//  TimingAndOptimizationLab
//
//  Created by Derek Olson on 9/13/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp
#include <vector>
#include <iostream>
#include <stdio.h>

std::vector<double> makeVector(int rows, int columns);

double sum1(const std::vector<double>& vector, int numRows, int numCols);

double sum2(const std::vector<double>& vector, int numRows, int numCols);

#endif /* Functions_hpp */
