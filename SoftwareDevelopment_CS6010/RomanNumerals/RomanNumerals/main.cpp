//
//  main.cpp
//  RomanNumerals
//
//  Created by Derek Olson on 8/22/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <typeinfo>
using namespace std;

int main(int argc, const char * argv[]) {

    // get user input
    int toConvert;
    cout << "Enter integer to convert to roman numeral \n";
    cin >> toConvert;
    
    // do some checks for invalid inputs
    if (toConvert <= 0){
        cout << "invalid input \n";
        return(1);
    }
    int tester;
    if (typeid(toConvert) != typeid(tester)){
        cout << "Invalid input data type \n";
        return(1);
    }
    
    while (toConvert >= 1000){
        cout << 'M';
        toConvert -= 1000;
    }
    while (toConvert >= 900){
        cout << "CM";
        toConvert -= 900;
    }
    while (toConvert >= 500){
        cout << 'D';
        toConvert -= 500;
    }
    while (toConvert >= 400){
        cout << "CD";
        toConvert -= 400;
    }
    while (toConvert >= 100){
        cout << 'C';
        toConvert -= 100;
    }
    while (toConvert >= 100){
        cout << "XC";
        toConvert -= 100;
    }
    while (toConvert >= 50){
        cout << 'L';
        toConvert -= 50;
    }
    while (toConvert >= 40){
        cout << "XL";
        toConvert -= 40;
    }
    while (toConvert >= 10){
        cout << 'X';
        toConvert -= 10;
    }
    while (toConvert >= 5){
        cout << 'V';
        toConvert -= 5;
    }
    while (toConvert >= 1){
        cout << 'I';
        toConvert -= 1;
    }
    
    cout << "\n";

    return 0;
}

