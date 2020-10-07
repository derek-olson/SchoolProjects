//
//  main.cpp
//  ForLoopPractice
//
//  Created by Derek Olson on 8/21/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {

//    for (int i = 1; i <= 10; i++){
//        std::cout << i << "\n";
//    }
//
//    int i = 1;
//    while (i < 11){
//        std::cout << i << "\n";
//        i = i + 1;
//    }
//
//    //The for loop was much simpler and didn't require variable declaration outside of the loop
//
//    int value1;
//    int value2;
//
//    std::cout << "Enter 2 integer values \n";
//    std::cout << "Enter value 1 \n";
//    std::cin >> value1;
//    std::cout << "Enter value 2 \n";
//    std::cin >> value2;
//
//    for (int i = value1; i <= value2; i++){
//        std::cout << i << "\n";
//    }
//
//    // program exits when values come in reverse order
//
//    //Print all the odd numbers between 1 and 20. Come up with two solutions: one that uses a loop and an if statement, and one that doesn't require an if statement.
//    //
//    for (int i = 1; i < 20; i++){
//        if (i % 2 != 0){
//            std::cout << i << "\n";
//        }
//    }
//
//    for (int i = 1; i < 20; i = i + 2){
//        std::cout << i << "\n";
//    }
//
//
//    int number;
//
//    std::cout << "Enter Number";
//    std::cin >> number;
//
//    while (number > -1){
//        //int counter = 1;
//        int prevNum;
//        int sum = number + prevNum;
//        prevNum = sum;
//        std::cout << "The sum is: " << sum << "\n";
//        std::cout << "Enter Number \n";
//        std::cin >> number;
//        if (number < 0){break;}
//    }
    
    //Print a multiplication table for the numbers 1 to 5. The output should be something like:
    
    for (int i = 1; i <= 5; i++){
        int num = 2;
        int prod = num * i;
        std::cout << prod << " ";
    }
    std::cout << "\n";
    
    for (int i = 1; i <= 5; i++){
        int num = 3;
        int prod = num * i;
        std::cout << prod << " ";
    }
    std::cout << "\n";
    
    for (int i = 1; i <= 5; i++){
        int num = 4;
        int prod = num * i;
        std::cout << prod << " ";
                
    }
    std::cout << "\n";
    
    for (int i = 1; i <= 5; i++){
        int num = 5;
        int prod = num * i;
        std::cout << prod << " ";
        
    }
    std::cout << "\n";
    
    return 0;
}



