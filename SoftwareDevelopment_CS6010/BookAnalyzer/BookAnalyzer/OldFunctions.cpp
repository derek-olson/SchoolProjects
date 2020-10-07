//
//  OldFunctions.cpp
//  BookAnalyzer
//
//  Created by Derek Olson on 9/5/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "OldFunctions.hpp"
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

int GetWordIndex(vector<string> v, string w){
    int index = 0;
    for (int i = 0; i < v.size(); i++){
        if (v[i] == w){
            index = i;
            return index;
        }
    }
    return index;
}

void Swap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}

int MinIndex(vector<int> v, int start){
    int minIndex = start;
    for (int i = start + 1; i < v.size(); i++){
        if (v[i] < v[minIndex]){
            minIndex = i;
        }
    }
    return minIndex;
}

void SortAscending(vector<int> v){
    for (int i = 0; i < v.size(); i++){
        int minIndex = MinIndex(v, i);
        Swap(v[i], v[minIndex]);
    }
}


void ReturnTitleAuthor(vector<string> v){
    vector<string> author; vector<string>title;
    int titleIndex = GetWordIndex(v, "Title:");
    int authIndex = GetWordIndex(v, "Author:");
    int releaseIndex = GetWordIndex(v, "Date:");
    if (titleIndex > 100 || authIndex > 150){
        cout << "Title & Author unknown \n";
    }
    for (int i = titleIndex + 1; i < authIndex; i++){
        title.push_back(v[i]);
    }
    for (int i = authIndex + 1; i < releaseIndex - 1; i++){
        author.push_back(v[i]);
    }
    cout << "Title: ";
    for (int i = 0; i < title.size(); i++){cout << title[i] << " ";}
    cout << "\n";
    
    cout << "Author: ";
    for (int i = 0; i < author.size(); i++){cout << author[i] << " ";}
    cout << "\n";
}

void TotalWords(vector<string> v){
    long totalWords = v.size();
    cout << "There are " << totalWords << " words in the book. \n";
}

// CHANGE THESE TO FOR LOOPS - CAN THESE BE INSERTED INTO A SINGLE LOOP FUNCTION
void ShortestWordSize(vector<int> v){
    SortAscending(v);
    cout << "The shortest word in the book is: " << v[0] << " characters \n";
}

void ShortestWord(vector<string> v){
    sort(v.begin(), v.end());
    cout << "The shortest word in the book is: " << v[0] << " characters \n";
}

void LongestWordSize(vector<int> v){
    SortAscending(v);
    cout << "The longest word in the boook is: " << v.back() << " characters \n";
}

void LongestWord(vector<string> v){
    sort(v.begin(), v.end());
    cout << "The longest word in the boook is: " << v.back() << " characters \n";
}


void SearchAndReport(string argv2, vector<string> v){
    vector<double> searchIndex;
    int searchCount = 0;
    vector<string> surroundingWords;
    for (int i = 0; i < v.size(); i++){
        if (v[i] == argv2){
            searchCount += 1;
            searchIndex.push_back(i);
            string word1 = v[i-1]; string word2 = v[i]; string word3 = v[i+1];
            surroundingWords.push_back(word1);
            surroundingWords.push_back(word2);
            surroundingWords.push_back(word3);
        }
    }
    if (searchCount > 0){
        cout << "The word " << argv2 << " appears " << searchCount << " times \n";
    }
    else{
        cout << argv2 << " is not in the book \n";
    }
    for (int i = 0; i < searchIndex.size(); i++){
        cout << "at " << setprecision(2) << searchIndex[i]/v.size() << "% ";
        for (int i = 0; i < 1; i++){
            cout << surroundingWords[i] << " " << surroundingWords[i+1] << " " << surroundingWords[i+2] << "\n";
        }
    }
}
