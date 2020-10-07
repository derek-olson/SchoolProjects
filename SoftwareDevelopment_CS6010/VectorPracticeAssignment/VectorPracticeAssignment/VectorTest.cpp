//
//  main.cpp
//  VectorPracticeAssignment
//
//  Created by Derek Olson on 8/26/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//


/*
CS 6010 Fall 2019
Vector util library tests
Compile this file together with your VectorUtil library with the following command:
clang++ -std=c++11 VectorTest.cpp VectorUtil.cpp
Most of the provided tests will fail until you have provided correct
implementations for the VectorUtil library functions.
You will need to provide more thorough tests.
*/

#include <iostream>
#include <string>

// Include the VectorUtil library
#include "VectorUtil.hpp"

/*
 * Helper function for failing a test.
 * Prints a message and exits the program.
 */
void ErrorExit(std::string message)
{
    std::cerr << "Failed test: " << message << std::endl;
    exit(1);
}


int main()
{
    
    // Set up some input vectors for testing purposes.
    
    // We can use list initialization syntax:
    vector<int> v1 = {3, 1, 0, -1, 5};
    
    // Or we can repeatedly push_back items
    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    
    // When testing, be sure to check boundary conditions, such as an empty vector
    vector<int> empty;

    // v1 doesn't contain 4, so this should return false
    if(Contains(v1, 4))
        ErrorExit("Contains test 1");

    // v1 does contain -1, so this should return true
    if(!Contains(v1, -1))
        ErrorExit("Contains test 2");

    /*
     * The vector 'empty' doesn't contain anything, so this should return false
     * The specific value we're looking for here (99) is not important in this test.
     * This test is designed to find any general errors caused by the array being empty.
     * That type of error is unlikely to depend on the value we are looking for.
     */
    
    if(Contains(empty, 99))
        ErrorExit("Contains empty");

    // TODO: Add your own tests that thoroughly exercise your VectorUtil library.
    
    // check to see if vector is empty
    if(empty.size() < 1){
        ErrorExit("Empty vector");
    }
    
    // check to see if vector is larger than expected
    int vectorSize = 10;
    if(empty.size() > vectorSize){
        ErrorExit("Empty vector");
    }
    
    // check to see if vector has negative values
    for (int i : empty){
        if (i < 0){
            ErrorExit("vector contains negative values");
        }
    }
    
    // Check to see if the max value exceeds a threshold
    int maxThreshold = 1000;
    if (FindMax(empty) > maxThreshold){
        ErrorExit("Max value exceeds limit");
    }
    
    // Check to see if the min value exceeds a threshold
    int minThreshold = 100;
    if (FindMin(empty) < minThreshold){
        ErrorExit("Min value is below limit");
    }
    
    // check the average value and a specific value
    int toContain = -1;
    if (Average(empty) < 50 || Contains(empty, toContain)){
        ErrorExit("Does not meet average threshold or contains negative values");
    }
    
    // check to see if the input vector is sorted
    if (!IsSorted(empty)){
        ErrorExit("Vector is not sorted");
    }
    
    // Since any failed test exits the program, if we made it this far, we passed all tests.
    std::cout << "All tests passed!" << std::endl;
    
}
