//
//  Functions.hpp
//  NumberConverter
//
//  Created by Derek Olson on 9/3/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp
#include <iostream>
#include <math.h>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
using namespace std;

int ConvertStringToBase10(string numString);

int ConvertStringToBase2(string numString);

int ConvertStringToBase16(string numString);

int ConvertStringToInt(string numString, int base);

string convertToString(int n);

string convertDecimalToString(int n);

string convertToBinaryString(int n);

string convertToHexidecimalString(int n);

#endif /* Functions_hpp */
