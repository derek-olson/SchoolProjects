//
//  main.cpp
//  BookAnalyzer
//
//  Created by Derek Olson on 8/30/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "HelperFunctions.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>
#include <iomanip>
using namespace std;

int main(int argc, const char * argv[]) {
    
    // check to make sure the valid number of parameters are included
    //ArgCheck(argc);
    
    // parse the text file and return a vector of strings
    vector<string> words = BookParser("Huck_Finn.txt"); //argv[1]
    
    WordStats test = LoopThroughBookVector(words, "-encoded", 3, "_encoded.txt");
    
    cout << "The longest word is: " << test.maxWord << "\n";
    cout << "The shortest word is: " << test.minWord << "\n";
    cout << "There are " << test.totalWords << " total words" << "\n";
    cout << "There are " << test.totalChars << " total characters" << "\n";

    
    return 0;
}

