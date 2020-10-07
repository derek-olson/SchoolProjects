//
//  main.cpp
//  VolumeConverter
//
//  Created by Derek Olson on 8/20/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//
// Dalton Bennett and Derek Olson


#include <iostream>

int main(int argc, const char * argv[]) {
    // get volume from user
    std::cout << "Enter volume in ounces: " << "\n";
    
    float ounces;
    
    std::cin >> ounces;
    
    float cups = ounces/8;
    float pints = ounces/16;
    float gallons = ounces/128;
    float liters = ounces * 0.0296;
    float cubicInches = ounces * 1.8;
    
    std::cout << "Ounces: " << ounces << "\n";
    std::cout << "Cups: " << cups << "\n";
    std::cout << "Pints: " << pints << "\n";
    std::cout << "Gallons: " << gallons << "\n";
    std::cout << "Liters: " << liters << "\n";
    std::cout << "Cubic Inches: " << cubicInches << "\n";
    
    
    return 0;
}
