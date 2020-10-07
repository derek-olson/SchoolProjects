//
//  main.cpp
//  RoadTripCalculator
//
//  Created by Derek Olson on 8/20/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <iomanip>

int main(int argc, const char * argv[]) {
    
    int distance; int mpg; float cost;
    
    std::cout << "Enter the distance: ";
    
    std::cin >> distance;
    
    std::cout << "distnce is " << distance << " \n";
    
    std::cout << "Enter the miles per gallon: ";
    
    std::cin >> mpg;
    
    std::cout << "mpg is " << mpg << " \n";
    
    std::cout << "Enter the cost per gallon: ";
    
    std::cin >> cost;
    
    std::cout << "cost per gallon is " << cost << " \n";
    
    //distance * dollars per gallon / miles per gallon
    
    std::cout << "The cost of your trip is: $" << std::setprecision(4) << distance * cost / mpg << " \n"; //good job
    
    return 0;
}
