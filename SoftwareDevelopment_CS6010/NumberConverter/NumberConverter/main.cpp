//
//  main.cpp
//  NumberConverter
//
//  Created by Derek Olson on 9/3/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "Functions.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <ctype.h>
#include <sstream>

int main(int argc, const char * argv[]) {

    // base 10 tests
    int a = ConvertStringToInt("-10", 10);
    cout << a;
    cout << "\n";
    int b = ConvertStringToInt("-1000", 10);
    cout << b;
    cout << "\n";
    int c = ConvertStringToInt("255", 10);
    cout << c;
    cout << "\n";
    int d = ConvertStringToInt("3000", 10);
    cout << d;
    cout << "\n";
    
    // base 2 tests
    int e = ConvertStringToInt("101", 2);
    cout << e;
    cout << "\n";
    int f = ConvertStringToInt("10010", 2);
    cout << f;
    cout << "\n";
    int g = ConvertStringToInt("1001111", 2);
    cout << g;
    cout << "\n";
    int h = ConvertStringToInt("11111111", 2);
    cout << h;
    cout << "\n";
    
    // base 16 tests
    int i = ConvertStringToInt("FF", 16);
    cout << i;
    cout << "\n";
    int j = ConvertStringToInt("ff", 16);
    cout << j;
    cout << "\n";
    int k = ConvertStringToInt("FFE", 16);
    cout << k;
    cout << "\n";
    int l = ConvertStringToInt("c", 16);
    cout << l;
    cout << "\n";
    
    // convert decimal to string tests
    string decimalToString1 = convertToString(256);
    cout << decimalToString1;
    cout << "\n";
    string decimalToString2 = convertToString(-99);
    cout << decimalToString2;
    cout << "\n";
    string decimalToString3 = convertToString(1000001);
    cout << decimalToString3;
    cout << "\n";
    
    //convert binary to string tests
    string binaryToString1 = convertToBinaryString(256);
    cout << binaryToString1;
    cout << "\n";
    string binaryToString2 = convertToBinaryString(1054);
    cout << binaryToString2;
    cout << "\n";
    string binaryToString3 = convertToBinaryString(6);
    cout << binaryToString3;
    cout << "\n";
    
    // convert hexadecimal to string tests
    string printHexString1 = convertToHexidecimalString(256);
    cout << printHexString1;
    cout << "\n";
    string printHexString2 = convertToHexidecimalString(255);
    cout << printHexString2;
    cout << "\n";
    string printHexString3 = convertToHexidecimalString(14);
    cout << printHexString3;
    cout << "\n";
    
    
    // additional tests
    bool x = ConvertStringToInt(convertToHexidecimalString(255), 16) == 255;
    cout << x;
    cout << "\n";
    
    bool y = ConvertStringToInt(convertToBinaryString(255), 2) == 255;
    cout << y;
    cout << "\n";
    
    bool z = ConvertStringToInt(convertToString(255), 2) == 11111111;
    cout << z;
    cout << "\n";
    return 0;
}
