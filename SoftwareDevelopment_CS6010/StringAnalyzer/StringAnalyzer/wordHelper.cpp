//
//  wordHelper.cpp
//  StringAnalyzer
//
//  Created by Derek Olson on 8/26/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include "wordHelper.hpp"
#include "letterHelpers.hpp"
using namespace std;

float numWords(string input){
    float wordCount = 0.0;
    for (int i = 0; i < input.size(); i++){
        if (isSpace(input[i])){
            wordCount = wordCount + 1.0;
            if (isSpace(input[i-1]) == isSpace(input[i])){
                wordCount = wordCount - 1.0;
            }
        }
    }
    if (input[0] == ' '){
        wordCount = wordCount - 1.0;
    }
    if (input[input.size()-1] == ' ' ){
        wordCount = wordCount - 1.0;
    }
    return wordCount + 1.0;
}

int numSentences(string input){
    int sentenceCount = 0;
    for (int i = 0; i < input.size(); i++){
        if (isTermination(input[i])){
            sentenceCount = sentenceCount + 1;
        }
    }
    return sentenceCount;
}

float numVowels(string input){
    float vowelCount = 0.0;
    for (int i = 0; i < input.size(); i++){
        if (isVowel(input[i])){
            vowelCount = vowelCount + 1.0;
        }
    }
    return vowelCount;
}
float numConsonants(string input){
    float consonantCount = 0.0;
    for (int i = 0; i < input.size(); i++){
        if (isConsonant(input[i])){
            consonantCount = consonantCount + 1.0;
        }
    }
    return consonantCount;
}

float averageVowelsPerWord(string input){
    return numVowels(input)/numWords(input);
}
