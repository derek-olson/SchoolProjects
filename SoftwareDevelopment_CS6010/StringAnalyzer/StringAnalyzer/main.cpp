//
//  main.cpp
//  StringAnalyzer
//
//  Created by Derek Olson on 8/25/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "letterHelpers.hpp"
#include "wordHelper.hpp"
using namespace std;


int main(int argc, const char * argv[]) {

    string input;
    cout << "Enter a string containing one or more sentences: \n";
    getline(cin, input);
    
    float words = numWords(input);
    cout << "The number of words is: " << words << "\n";
    
    int sentences = numSentences(input);
    cout << "The number of sentences is: " << sentences << "\n";
    
    float vowels = numVowels(input);
    cout << "The number of vowels is: " << vowels << "\n";
    
    float consonants = numConsonants(input);
    cout << "The number of consonants is: " << consonants << "\n";
    
    float readingLevel = (vowels + consonants) / words;
    cout << "The reading level is: " << setprecision(4) << readingLevel << "\n";
    
    cout << "The Wheel-of-Fortune cost metric is: " << averageVowelsPerWord(input) << "\n";
    
    return 0;
}


