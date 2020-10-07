//
//  main.cpp
//  vendingMachine
//
//  Created by Derek Olson on 8/19/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    
    float cost; float paid;
    
    std::cout << "Enter the cost \n";
    
    std::cin >> cost;
    
    std::cout << "Enter the amount paid \n";
    
    std::cin >> paid;
    
    float toReturn = paid - cost;
    
    // Quarters
    int quarters = toReturn/0.25;
    
    std::cout << "Quarters: " << quarters << "\n";
    
    float toReturn2 = toReturn - (0.25 * quarters);
    
    //Dimes
    int dimes = toReturn2/0.10;
    
    std::cout << "Dimes: " << dimes << "\n";
    
    float toReturn3 = toReturn2 - (0.10 * dimes);
    
    // Nickles
    int nickles = toReturn3/0.05;
    
    std::cout << "Nickles: " << nickles << "\n";
    
    float toReturn4 = toReturn3 - (0.05 * nickles);
    
    //Pennies
    int pennies = toReturn4/0.01;
    
    std::cout << "Pennies: " << pennies << "\n";
    
    return 0;
}






