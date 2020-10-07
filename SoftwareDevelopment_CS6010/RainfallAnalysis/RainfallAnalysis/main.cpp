//
//  main.cpp
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

int main(int argc, const char * argv[]) {
    
    // function to parse the text file
    vector<Data> data = ParseTextFile("Atlanta.txt");
    
    // function to get the average precip
    double average = AveragePrecip(data);
    
    vector<double> monthlies = MonthlyPrecip(data);
    
    PrecipMonth monthly_sums =  wettestDryest(data);
    
    vector<double> wetMonths = WettestMonths(monthly_sums);
    
    vector<double> dryMonths =  DryestMonths(monthly_sums);
    
    // function to return info about the median month
    Data medianMonth = MedianMonth(data);
    
    // function to write data to file
    ofstream outFile("rainfallAnalysis.txt");
    WriteOutFile(outFile, average, monthlies, wetMonths, dryMonths, medianMonth);

    return 0;
}


