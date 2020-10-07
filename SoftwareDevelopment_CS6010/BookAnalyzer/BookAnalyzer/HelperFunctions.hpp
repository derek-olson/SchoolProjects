//
//  HelperFunctions.hpp
//  BookAnalyzer
//
//  Created by Derek Olson on 8/30/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef HelperFunctions_hpp
#define HelperFunctions_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>
#include <iomanip>
using namespace std;

struct CharStats{
    int totalChars;
    vector<int> wordChars;
};

struct WordStats{
    string title;
    string author;
    long totalWords;
    long totalChars;
    string minWord;
    string maxWord;
    vector<string> properNoun;
    vector<float> properNounPosition;
    vector<string> adjacentWords;
};

void ArgCheck(int argc);

vector<string> BookParser(string bookTitle);

string convertToString(int n);

string convertToBinaryString(int n);

void cipher(string encode, char c, int key, ofstream& outs);

WordStats GetTitle(string word, WordStats stats);

WordStats GetAuthor(string word, WordStats stats);

WordStats findShortestWord(string currentWord);

WordStats findLongesttWord(string currentWord);

bool FindPunctuation(string word);

bool FindCapitalLetters(char c);

float TextPosition(float index, float size);

WordStats FindProperNouns(string previousWord, string word, string nextWord, char c, int index, long size);

vector<string> FindAdjacentWords(string searchWord, string currentWord, string previousWord, string nextWord, int index, long size);

WordStats LoopThroughBookVector(vector<string> v, string searchWord, int key, string outFile);

#endif /* HelperFunctions_hpp */


