//
//  HelperFunctions.cpp
//  BookAnalyzer
//
//  Created by Derek Olson on 8/30/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "HelperFunctions.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>
#include <iomanip>
#include <sstream>
#include <string.h>
using namespace std;

// check arguments
void ArgCheck(int argc){
    if (argc != 3)
    {
        cout << "Invalid inputs \n";
        exit(1);
    }
}

// start collecting all the stats
WordStats stats;

// return the book as a vector. Get and print out the title and author
vector<string> BookParser(string bookTitle){
    vector<string> words;
    string word;
    string line;
    ifstream inBook(bookTitle);
    if (inBook.fail()){
        cout << "Book is unavailable";
        }
    while (inBook >> word){
        words.push_back(word);
    }
//    while (getline(inBook, line)){
//        if (line.substr(0,4) == "Title" ){
//            cout << line << "\n";
//            stats.title = line.substr(1);
//        }
//        if (line.substr(0,5) == "Author" ){
//            cout << line << "\n";
//            stats.author = line.substr(1);
//        }
//    }
    return words;
}

// convert a number to a string
string convertToString(int n){
    string outString;
    stringstream ss;
    ss << n;
    outString = ss.str();
    return outString;
}

// return a binary string representation
string binaryString;
string convertToBinaryString(int n){
    if (n / 2 != 0){
        convertToBinaryString(n / 2);
    }
    string tempString = convertToString(n % 2);
    binaryString = binaryString + tempString;
    return binaryString;
}

// modify characters based on secret key
void cipher(string encode, char c, int key, ofstream& outs){
    string outName = stats.title;
    if (encode == "-encode"){
        if (outs.is_open()){
            if (c > 47 && c < 58){
                string s(1,c);
                int n = stoi(s);
                string binaryString = convertToBinaryString(n);
                outs << binaryString;
            }
            else if (c > 97 && c < 123){
                c = (((c - 98) + key) % 26) + 98;
                outs << c;
            }
            else if (c > 64 && c < 91){
                c = (((c - 65) + key) % 26) + 65;
                outs << c;
            }
            else{
                outs << c;
            }
        }
    }
}

// function to find the shortest word
WordStats findShortestWord(string currentWord){
    if (currentWord.size() < stats.minWord.size()){
        stats.minWord = currentWord;
    }
    return stats;
}

// function to find the longest word
WordStats findLongesttWord(string currentWord){
    if (currentWord.size() > stats.maxWord.size()){
        stats.maxWord = currentWord;
    }
    return stats;
}

// test for punctuation
bool FindPunctuation(string word){
    return (word.back() != '!' || word.back() != '.' || word.back() != '?');
}

// test for capital letters
bool FindCapitalLetters(char c){
    return c > 64 && c < 91;
}

// return the relative position
float TextPosition(float index, float size){
    return (index/size)*100;
}

// return words adjacent to search word
WordStats FindAdjacentWords(string searchWord, string currentWord, string previousWord, string nextWord, int index, long size, WordStats stats){
    if (currentWord == searchWord){
        float tp = TextPosition(index, size);
        stats.adjacentWords.push_back(previousWord);
        stats.adjacentWords.push_back(searchWord);
        stats.adjacentWords.push_back(nextWord);
        cout << "At " << tp << " %: " << previousWord << " " << currentWord << " " << nextWord << "\n";
    }
    return stats;
}

// return proper noun stats
WordStats FindProperNouns(string previousWord, string word, string nextWord, char c, int index, long size, WordStats stats){
    if (FindPunctuation(previousWord) && FindCapitalLetters(c)){
        float tp = TextPosition(index, size);
        stats.properNounPosition.push_back(tp) ;
        stats.properNoun.push_back(word);
        cout << "At " << tp << " %: " << previousWord << " " << word << " " << nextWord << "\n";
    }
    return stats;
}


void printProperNounIndex(vector<float> f){
    for (int i = 0; i < f.size(); i++){
        cout << "At " << f[i] << ": ";
    }
}

void printProperNouns(vector<string> v){
    for (int i = 0; i < v.size(); i = i + 3){
        cout << v[i] << " " << v[i+1] << " " << v[i + 2] << "\n";
    }
}

// loop through the vector once and get all the stats
WordStats LoopThroughBookVector(vector<string> v, string searchWord, int key, string outFile){
    stats.totalChars = 0;
    stats.totalWords = v.size();
    stats.minWord = "alphabet";
    ofstream outs(outFile);
    for (int i = 1200; i < v.size(); i++){
        string test = v[i];
        findShortestWord(v[i]);
        findLongesttWord(v[i]);
        FindProperNouns(v[i-1], v[i], v[i+1], v[i][0], i, stats.totalWords, stats);
        FindAdjacentWords(searchWord, v[i], v[i-1], v[i+1], i, stats.totalWords, stats);
        for (int j = 0; j < v[i].size(); j++){
            cipher(searchWord, v[i][j], key, outs);
            stats.totalChars++;
        }
    }
    return stats;
}


