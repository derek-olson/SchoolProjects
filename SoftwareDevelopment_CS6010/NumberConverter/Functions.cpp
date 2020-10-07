//
//  Functions.cpp
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
using namespace std;

int ConvertStringToBase10(string numString){
    stringstream s(numString);
    int x;
    s >> x;
    return x;
}

int ConvertStringToBase2(string numString){
    int biNumVal = 0;
    int power = 0;
    for (long i = numString.size()-1; i < numString.size(); i--){
        int val = numString[i] - '0';
        biNumVal += val * (pow(2, power));
        power += 1;
    }
    return biNumVal;
}

int ConvertStringToBase16(string numString){
    int hexNumVal = 0;
    for (int i = 0; i < numString.size(); i++){
        int val = tolower(numString[i]) - 'a' + 10;
        hexNumVal += val*pow(16,numString.size()-i-1);
        
    }
    return hexNumVal;
}

int ConvertStringToInt(string numString, int base){
    int x = 0;
    if (base == 10){
       x = ConvertStringToBase10(numString);
    }
    if (base == 2){
        x = ConvertStringToBase2(numString);
    }
    if (base == 16){
        x = ConvertStringToBase16(numString);
        }
    return x;
}


string convertToString(int n){
    string outString;
    stringstream ss;
    ss << n;
    outString = ss.str();
    return outString;
}

//one that converts an int to its decimal representation as a string
string convertDecimalToString(int n){
    string decString = convertToString(n);
    return decString;
}

//one that converts an int to its binary string representation
string binaryString;
string convertToBinaryString(int n){
    if (n / 2 != 0){
        convertToBinaryString(n / 2);
    }
    string tempString = convertToString(n % 2);
    binaryString = binaryString + tempString;
    return binaryString;
}

//one that converts an int to its hexidecimal string representation.
string hexString = "";
string convertToHexidecimalString(int n){
    if (n / 16 != 0){
        convertToHexidecimalString(n / 16);
    }
    string tempString = convertToString(n % 16);
    if (tempString == "15"){
        tempString = "F";
    }else if(tempString == "14"){
        tempString = "E";
    }else if(tempString == "13"){
        tempString = "D";
    }else if(tempString == "12"){
        tempString = "C";
    }else if(tempString == "11"){
        tempString = "B";
    }else if(tempString == "10"){
        tempString = "A";
    }
    hexString += tempString;
    return hexString;
}
