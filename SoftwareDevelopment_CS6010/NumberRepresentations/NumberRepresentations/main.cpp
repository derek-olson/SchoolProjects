//
//  main.cpp
//  NumberRepresentations
//
//  Created by Derek Olson on 9/4/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include "Functions.hpp"
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;

bool ApproxEquals(double a, double b, double c){
    return (abs(a-b)) < c;
}

void ReadCharByChar(string inFile){
    ifstream file(inFile);
    char c;
    while( file >> c){
        cout << c << endl;
    }
}


int main(int argc, const char * argv[]) {

    int x;
    cout << sizeof(x) << "\n";
    
    float y;
    cout << sizeof(y) << "\n";
    
    double z;
    cout << sizeof(z) << "\n";
    
    int8_t a;
    cout << sizeof(a) << "\n";
    
    int16_t b;
    cout << sizeof(b) << "\n";

    
    //uint8_t u8_min = 0;
    uint8_t u8_max = 0xFF;
    cout << ++u8_max << "\n";
    //uint16_t u16_min = 0;
    uint16_t u16_max = 0xFFFF;
    cout << ++u16_max << "\n";
    //uint64_t u64_min = 0;
    uint64_t u64_max = 0xFFFFFFFFFFFFFFFF;
    cout << ++u64_max << "\n";
    
    cout << +u8_max << "\n";
    
    int8_t s8_max = 0x7F;
    int8_t s8_min = ++s8_max; // 0x80
    cout << +s8_min << "\n";
    int16_t s16_min = 0x8000;
    int16_t s16_max = --s16_min; // 0x7FFF
    cout << s16_max << "\n";
    int64_t s64_min = 0x8000000000000000;
    int64_t s64_max = --s64_min; // 0x7FFFFFFFFFFFFFFF
    cout << s64_max << "\n";
    
    
    float n = 0.1 + 0.2;
    //assert(n == 0.3);
    cout << setprecision(18) << n << "\n";
    
    cout << ApproxEquals(n, 0.3, 0.001) << "\n";
    
    
    ReadCharByChar("UTF-8-demo.txt");
    
    // anyhting that is not in the ASCII table comes out with slashes before a number. 
    
    return 0;
}
