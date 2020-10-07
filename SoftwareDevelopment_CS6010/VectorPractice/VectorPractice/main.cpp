//
//  main.cpp
//  VectorPractice
//
//  Created by Derek Olson on 8/26/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

// fuinction to return the sum of the integers in a vector
int intSum(std::vector<int> input){
    int sumInts = 0;
    for(int i : input){
        sumInts += i;
    }
    return sumInts;
}

// function to return the characters of a string in a vector
std::vector<char> stringToVec(string input){
    std::vector<char> charVec;
    for (char c : input){
        charVec.push_back(c);
    }
    return charVec;
}

//function to return the integers in a vector in reverse order
std::vector<int> reversal(std::vector<int> input){
    std::vector<int> intVec;
    for (int i : input){
        intVec.push_back(i);
    }
    std::reverse(intVec.begin(), intVec.end());
    return intVec;
}

int main(int argc, const char * argv[]) {
    
    std::vector<int> ints = {0 , 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int test = intSum(ints);
    cout << test << "\n";
    
    string stringTest = "Hello there!";
    std::vector<char> test2 = stringToVec(stringTest);
    for(char c : test2){
        cout << c << "\n";
    }
        
    std::vector<int> testVec = {1,2,3};
    std::vector<int> test3 = reversal(testVec);
    for(char c : test3){
        cout << c << "\n";
    }
    for(int c : test3){
        cout << c << "\n";
    }
    return 0;
}
