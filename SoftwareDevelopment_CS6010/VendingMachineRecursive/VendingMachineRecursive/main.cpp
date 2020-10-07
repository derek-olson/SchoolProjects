//
//  main.cpp
//  VendingMachineRecursive
//
//  Created by Derek Olson on 8/20/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <list>
#include <array>
#include <iomanip>

// initiate an empty list
std::list <int> change;

// create an array of coin values. This could be moved to the function params.
int coins[4] = {25, 10, 5, 1};

//create a list of the coin amounts
int coinAounts[4] = {2, 2, 2, 2};

// this is a function of the value remaining and the coin value
void vendingMachine(float remaining, int coin)
{
    // use the if statement to allow the function to call itself
    // There are two main functions: keep track of the change and the remaining value
    // if/while the remaining value is greater than 0 do the following
    if (remaining > 0){
        
        // add coin to list
        change.push_back(coins[coin]);
        
        // subtract coin from the remaining value
        remaining = remaining - coins[coin];
        
        // count the number of a given coin in a list
        long coinNum = std::count(change.begin(), change.end(), coins[coin]);
        
        if (coinNum >=2){
            // run the function again
            coin += 1;
            vendingMachine(remaining, coin);
        }
        // run the function again
        vendingMachine(remaining, coin);
    }
    else if (remaining < 0){
        
        //add the coin value back to the remaining amount
        remaining = coins[coin] + remaining;
        
        // increment the coin index by 1 to move to the next largest coin value
        coin += 1;
        
        // run the function
        vendingMachine(remaining, coin);
    }
    else{
        
//        long cs = std::distance(std::begin(change), std::end(change));
//
//        float outList[cs];
//
//        for (int i = 0; i < cs; i++){
//            float toConver = change[i] / 100;
//
//        }
        
        // print out the final list. Maybe create a dictionary to tie the coin value to the scoin name.
        std::cout << "The change contains: \n";
        for (auto v : change){
            std::setprecision(4);
            float a = v/100.0;
            std::cout << a << "\n";}
        exit(2);
    }
}


int main(int argc, const char * argv[]) {
    // set the amount of change available in the machine.
    // This shouldn't be hard coded, but calculate from lines 18 and 21.
    float availChange = 82;
    
    // initialize variables for the cost and the amount paid
    float cost;
    float paid;
    
    // get info from the user
    std::cout << "Enter the cost of the item in dollar and cents\n";
    std::cin >> cost;
    cost = cost * 100;
    
    std::cout << "Enter the amount you paid for the item in dollars and cents\n";
    std::cin >> paid;
    paid = paid * 100;
    
    // handle errors in amount paid
    if (paid <= 0){
        std::cout << "Invalid amount paid";
        exit(1);
    }
    
    // handle if there is not enough change in the machine
    if (paid - cost > availChange){
        std::cout << "Not enough funds in the machine. Please retireve your payment. \n";
    }
    
    // make sure there are no problems with the amounts
    float remaining = cost - paid;
    while (remaining > 0){
        std::cout << "$" << remaining << " Remaining \n";
        std::cout << "Please insert $ \n";
        std::cin >> paid;
        remaining -= paid;
    }
    
    // call the function
    vendingMachine(paid - cost, 0);
        
    return 0;
}



