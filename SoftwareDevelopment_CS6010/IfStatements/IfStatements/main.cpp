//
//  main.cpp
//  IfStatements
//
//  Created by Derek Olson on 8/21/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

// PART 1

#include <iostream>

int main(int argc, const char * argv[]) {
    
    // get user age
    int userAge;
    std::cout << "What is your age? \n";
    std::cin >> userAge;
    
    if (userAge >= 18){
        std::cout << "User is old enough to vote \n";
    }
    else if (userAge < 18){
        std::cout << "User is NOT old enough to vote \n";
    }
    
    if (userAge > 80){
        std::cout << "They're part of the greatest generation \n";
    }
    else if (userAge > 60 && userAge <= 80){
        std::cout << "Baby Boomer \n";
    }
    else if (userAge > 40 && userAge <= 60){
        std::cout << "Generation X \n";
    }
    else if (userAge > 20 && userAge <= 40){
        std::cout << "Millenial \n";
    }
    else if (userAge < 20){
        std::cout << "iKid \n";
    }
    
    
// PART 2
    
    // initiate boolean vars
    bool isWeekday = false;
    bool isHoliday= false;
    bool hasYoungChildren = false;
    bool sleepIn = false;
    
    // initiate char vars for user input
    char weekday;
    char holiday;
    char youngChildren;
    
    // Get user input
    std::cout << "Respond with 'y' or 'n' for the following questions \n";
    
    std::cout << "Is it a weekday? \n";
    std::cin >> weekday;
    
    std::cout << "Is it a holiday? \n";
    std::cin >> holiday;
    
    std::cout << "Do you have young children? \n";
    std::cin >> youngChildren;
    
    // set bool values based on user input
    if (weekday == 'y' || weekday == 'Y'){isWeekday = true;}
    if (weekday == 'n' || weekday == 'N'){isWeekday = false;}
    if (holiday == 'y' || holiday == 'Y'){isHoliday = true;}
    if (holiday == 'n' || holiday =='N'){isHoliday = false;}
    if (youngChildren == 'y' || youngChildren == 'Y'){hasYoungChildren = true;}
    if (youngChildren == 'n' || youngChildren == 'N'){hasYoungChildren = false;}
    
    // logic to determine if user will sleep in
    if (hasYoungChildren){
        sleepIn = false;
    }
    else if (isHoliday){
        sleepIn = true;
    }
    else if (isWeekday){
        sleepIn = false;
    }

    // print whether user gets to sleep in
    if (sleepIn == true){
        std::cout << "You get to sleep in \n";
    }
    else if (sleepIn == false){
        std::cout << "You don't get to sleep in \n";
    }
    
    return 0;
}
