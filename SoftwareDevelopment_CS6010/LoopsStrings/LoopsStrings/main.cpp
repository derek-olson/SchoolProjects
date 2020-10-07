//
//  main.cpp
//  Loops and strings
//
//  Created by Derek Olson on 8/22/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//
// With Amy Vang & Bentley Sayer

#include <iostream>
#include <string>

int main(int argc, const char * argv[]) {

    // initialize string var
    std::string userDate;
    
    // get user input
    std::cout << "Enter a date with format mm/dd/yyyy \n";
    std::cin >> userDate;
    

    //handle potential issues with formatting - do this better
    long strLength = userDate.size();
    
    if (strLength > 10 || strLength < 10){
        std::cout << "Date is in the incorrect format. Please enter date again with format mm/dd/yyyy \n";
        std::cin >> userDate;
    }
    
    char fwdSlsh = '/';
    if (userDate[2] != fwdSlsh){
        std::cout << "Date is in the incorrect format. Please enter date again with format mm/dd/yyyy \n";
        exit(1);
    }
    
    //handle the month
    std::string month = userDate.substr(0,2);
    
    int monthCheck = std::stoi(month);
    
    if (monthCheck > 12 || monthCheck < 1){
        std::cout << "Invalid Date \n";
        exit(1);
    }
    
    std::string outMonth;
    
    if (month == "01"){outMonth = "January";}
    else if (month == "02"){outMonth = "February";}
    else if (month == "03"){outMonth = "March";}
    else if (month == "04"){outMonth = "April";}
    else if (month == "05"){outMonth = "May";}
    else if (month == "06"){outMonth = "June";}
    else if (month == "07"){outMonth = "July";}
    else if (month == "08"){outMonth = "August";}
    else if (month == "09"){outMonth = "September";}
    else if (month == "10"){outMonth = "October";}
    else if (month == "11"){outMonth = "November";}
    else if (month == "12"){outMonth = "December";}
    
    //handle day
    std::string outDay = userDate.substr(3,2);
    if (outDay[0] == '0'){outDay = outDay[1];}
    
    int dayCheck = std::stoi(outDay);
    
    if (outMonth == "February" && dayCheck > 28){
        std::cout << "Invalid Date \n";
        exit(1);
    }
    else if ((outMonth == "September" || outMonth == "April" || outMonth == "June" || outMonth == "November") && dayCheck > 30)
    {
        std::cout << "Invalid Date \n";
        exit(1);
    }
    else if ((outMonth == "January" || outMonth == "March" || outMonth == "May" || outMonth == "July" || outMonth == "August") && dayCheck > 31)
    {
        std::cout << "Invalid Date \n";
        exit(1);
    }
    //handle year
    std::string outYear = userDate.substr(6,4);
    
    int yearCheck = std::stoi(outYear);
    
    //return formatted date
    std::string date = outMonth + " " + outDay + ", " + outYear;
    std::cout << date << "\n";

    
    if (dayCheck * monthCheck == yearCheck % 100){
        std::cout << "This is a magic date! \n";
    }
    else {std::cout << "This is not a magic date \n";}
    
    return 0;
}
