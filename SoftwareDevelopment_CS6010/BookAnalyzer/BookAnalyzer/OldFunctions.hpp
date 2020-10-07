//
//  OldFunctions.hpp
//  BookAnalyzer
//
//  Created by Derek Olson on 9/5/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef OldFunctions_hpp
#define OldFunctions_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "OldFunctions.hpp"
using namespace std;

int GetWordIndex(vector<string> v, string w);

void Swap(int& x, int& y);

int MinIndex(vector<int> v, int start);

void SortAscending(vector<int> v);

void ReturnTitleAuthor(vector<string> v);

void TotalWords(vector<string> v);

void ShortestWordSize(vector<int> v);

void ShortestWord(vector<string> v);

void LongestWordSize(vector<int> v);

void LongestWord(vector<string> v);

void SearchAndReport(string argv2, vector<string> v);

#endif /* OldFunctions_hpp */
