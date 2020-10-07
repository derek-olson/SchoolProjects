//
//  main.cpp
//  TemplatesLab
//
//  Created by Derek Olson on 9/12/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "Functions.hpp"
#include <iostream>
#include <vector>

//Write a function templated named printEach that takes as a parameter any type that has a size() method, and operator[]. Print each element of the parameter on its own line.



int main(int argc, const char * argv[]) {

    Triple<int> x;
    x.first = 0;
    x.second = 1;
    x.third = 2;
    
    Triple<std::string> y;
    y.first = "Hello World!";
    y.second = "Why is this so hard?";
    y.third = "I need more coffee.";
    
    std::string s = "Apples";
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    
    
    printEach(s);
    printEach(v);
    
    return 0;
}
