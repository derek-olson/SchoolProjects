//
//  main.cpp
//  Average
//
//  Created by Derek Olson on 8/20/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

//Dalton Bennett and Derek Olson

#include <iostream>

int main(int argc, const char * argv[]) {

    std::cout << "Enter 5 Assignment Scores: " << "\n";
    
    int score1; int score2; int score3; int score4; int score5;
    
    std::cin >> score1;
    std::cin >> score2;
    std::cin >> score3;
    std::cin >> score4;
    std::cin >> score5;
    
    float avg = (score1 + score2 + score3 + score4 + score5)/5;
    
    std::cout << "Your average score is: " << avg << "\n";
    
    return 0;
}
