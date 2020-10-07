//
//  Helpers.hpp
//  RainfallAnalysis
//
//  Created by Derek Olson on 8/29/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef Helpers_hpp
#define Helpers_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
using namespace std;

// create a structure to parse the text file and hold data points
struct Data{
    string month;
    int year;
    double precip;
};

// create a structure to hold corresponding vectors of precip and month
struct PrecipMonth{
    vector<double> precip;
    vector<string> month;
    vector<int> year;
};

// function to return a min index for ascending order
int  MinIndexAscending(const vector<double>& v, int start);

// sort function for ascending order
void SortAscending(vector<double>& v);

// function to return a min index in descending order
int  MinIndexDescending(const vector<double>& v, int start);

// sort function for descending order
void SortDescending(vector<double>& v);

int  MinIndexAscendingStructure(const vector<Data>& v, int start);

// sort function for a structure
void SortAscendingStructure(vector<Data>& v);

// function to open a file
void OpenFile(string inFile);

// function to parse the text file
vector<Data> ParseTextFile(string);

// function to get the average precip
double AveragePrecip(vector<Data> data);

vector<double> MonthlyPrecip(vector<Data> data);

PrecipMonth wettestDryest(vector<Data> data);

vector<double> WettestMonths(PrecipMonth data);

vector<double> DryestMonths(PrecipMonth data);

// function to get the median - assumes vector is sorted
long MedianIndex(vector<Data> data);

// function to return info about the median month
Data MedianMonth(vector<Data> data);


void WriteOutFile(ofstream& outFile, double average, vector<double> monthlies, vector<double> wettest, vector<double> dryest, Data median);

#endif /* Helpers_hpp */
