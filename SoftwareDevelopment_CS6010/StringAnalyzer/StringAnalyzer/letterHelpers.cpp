//
//  letterHelpers.cpp
//  StringAnalyzer
//
//  Created by Derek Olson on 8/26/19.
//  Copyright © 2019 Derek Olson. All rights reserved.

#include "letterHelpers.hpp"
#include <iostream>
#include <vector>
using namespace std;

bool isVowel(char input){
    // initialize a vector of vowels to test against
    std::vector<char> v = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
    for (int i = 0; i < v.size(); i++){
        if (input == v[i]){
            return true;
        }
    }
    return false;
}

bool isSpace(char input){
    if (input == ' '){
        return true;
    }
    return false;
}

bool isPunctuation(char input){
    // initialize a vector to test against
    std::vector<char> v = {'.', '!', '?', ','};
    for (int i = 0; i < v.size(); i++){
        if (input == v[i]){
            return true;
        }
    }
    return false;
}

bool isTermination(char input){
    // initialize a vector to test against
    std::vector<char> v = {'.', '!', '?'};
    for (int i = 0; i < v.size(); i++){
        if (input == v[i]){
            return true;
        }
    }
    return false;
}

bool isConsonant(char input){
    if(isVowel(input) || isSpace(input) || isPunctuation(input)){
        return false;
    }
    return true;
}
