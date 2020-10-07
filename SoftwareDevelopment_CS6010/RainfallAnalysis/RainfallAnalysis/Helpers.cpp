//
//  Helpers.cpp
//  RainfallAnalysis
//
//  Created by Derek Olson on 8/29/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "Helpers.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

//"RainfallAnalysis.txt"

// initiate a vector of months
vector<string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

vector<int> years = {1996, 1997, 1998, 1999, 2000,2001,2002,2003,2004,2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2015, 2015};

//string city(string inFile){
//    string city;
//    ifstream file(inFile);
//    inFile >> city;
//}
// function to go line by line through a text file and return data points
vector<Data> ParseTextFile(string File){
    ifstream inFile(File);
    string line;
    Data temp_data;
    vector<Data> data;
    if (inFile.is_open()){
        inFile.ignore(80, '\n');
        while (getline(inFile, line)){
            string word;
            stringstream ss(line);
            for (int wordNum = 0; ss >> word; wordNum++){
                temp_data.month = word;
                ss >> word;
                temp_data.year = stoi(word);
                ss >> word;
                temp_data.precip = stod(word);
                data.push_back(temp_data);
            }
        }
    }
    inFile.close();
    return data;
}

// function to open file
void OpenFile(string inFile){
    ofstream file;
    file.open(inFile);
}

// function to return average precip
double AveragePrecip(vector<Data> data){
    double precip = 0.0;
    for (Data d : data){
        precip += d.precip;
    }
    double divisor = data.size();
    return precip /= divisor;
}

// function to write out monthly precip
vector<double> MonthlyPrecip(vector<Data> data){
    vector<double> avgMonthlyPrecips;
    for (int i = 0; i < months.size(); i++){
        double precip = 0.0; double divisor = 0.0;
        double avgMonthlyPrecip = 0;
        for (int j = 0; j < data.size(); j++){
            if (data[j].month == months[i]){
                precip += data[i].precip;
                divisor += 1.0;
            }

        }
        avgMonthlyPrecip = (precip/divisor);
        avgMonthlyPrecips.push_back(avgMonthlyPrecip);
    }
    return avgMonthlyPrecips;
}

// function to return a min index for ascending order
int  MinIndexAscending(const vector<double>& v, int start){
    int minIndex = start;
    for (int i = start + 1; i < v.size(); i++){
        if (v[i] < v[minIndex]){
            minIndex = i;
        }
    }
    return minIndex;
}

// sort function for ascending order
void SortAscending(vector<double>& v){
    for (int i = 0; i < v.size()-1; i++){
        int minIndex = MinIndexAscending(v,i);
        swap(v[i], v[minIndex]);
    }
}

// function to return a min index in descending order
int  MinIndexDescending(const vector<double>& v, int start){
    int minIndex = start;
    for (int i = start + 1; i < v.size(); i++){
        if (v[i] > v[minIndex]){
            minIndex = i;
        }
    }
    return minIndex;
}

// sort function for descending order
void SortDescending(vector<double>& v){
    for (int i = 0; i < v.size()-1; i++){
        int minIndex = MinIndexDescending(v,i);
        swap(v[i], v[minIndex]);
    }
}

// function to return a min index for a structure
int  MinIndexAscendingStructure(const vector<Data>& v, int start){
    int minIndex = start;
    for (int i = start + 1; i < v.size(); i++){
        if (v[i].precip > v[minIndex].precip){
            minIndex = i;
        }
    }
    return minIndex;
}

// sort function for a structure
void SortAscendingStructure(vector<Data>& v){
    for (int i = 0; i < v.size()-1; i++){
        int minIndex = MinIndexAscendingStructure(v,i);
        swap(v[i], v[minIndex]);
    }
}

// function to return a structure containing vectors of years, months and monthly precip totals
PrecipMonth wettestDryest(vector<Data> data){
    PrecipMonth monthlySums;
    vector<double> totals; vector<string> mnths; vector<int> yrs;
    for (int i = 0; i < years.size(); i++){
        for (int j = 0; j < months.size(); j++){
            double precip = 0;
            for (int k = 0; k < data.size(); k++){
                if (data[k].year == years[i] && data[k].month == months[j]){
                    precip += data[k].precip;
                    totals.push_back(precip);
                    mnths.push_back(months[j]);
                    yrs.push_back(years[i]);
                }
            }
        }
    }
    monthlySums.month = mnths;
    monthlySums.precip = totals;
    monthlySums.year = yrs;
    return monthlySums;
}

// function to get the wettest months
vector<double> WettestMonths(PrecipMonth data){
    vector<double> wettest;
    SortDescending(data.precip);
    for (int i = 0; i < 4; i++){
        wettest.push_back(data.precip[i]);
    }
    return wettest;
}

// function to get the dryest months
vector<double> DryestMonths(PrecipMonth data){
    vector<double> dryest;
    SortAscending(data.precip);
    for (int i = 0; i < 4; i++){
        dryest.push_back(data.precip[i]);
    }
    return dryest;
}

// function to get the median - assumes vector is sorted
long MedianIndex(vector<Data> data){
    long size = data.size();
    if (size % 2 == 0){
        return ((size/2)+((size/2)+1))/2;
    }
    return ceil(size/2);
}

// function to return info about the median month
Data MedianMonth(vector<Data> data){
    SortAscendingStructure(data);
    long medIndex = MedianIndex(data);
    return data[medIndex];
}

void WriteOutFile(ofstream& outFile, double average, vector<double> monthlies, vector<double> wettest, vector<double> dryest, Data median)
{
    
    outFile << "CS 6010 Rainfall Analysis \n" << "Derek Olson \n" << "Rainfall data for " << "City \n"; //fix!
    
    outFile << "The overall average rainfall amount is " << setprecision(3) << average << " inches. \n";
    
    for (int i = 0; i < months.size(); i++){
        outFile << "The average rainfall amount for " << months[i] << " is " << setprecision(3) << monthlies[i] << " inches \n";
    }
        
    outFile << "The rain amounts (in inches) of the four wettest months are: ";
    for (int i = 0; i < 4; i++){ outFile << wettest[i] << " ";}
    
    outFile << "\n";
    
    outFile << "The rain amounts (in inches) of the four driest months are: ";
    for (int i = 0; i < 4; i++){outFile << dryest[i] << " ";}
    
    outFile << "\n";
    
    outFile << "The median months is: \n" << median.month << " " << median.year << " " << median.precip << "\n";
}

