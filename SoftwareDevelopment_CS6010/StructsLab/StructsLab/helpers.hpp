//
//  helpers.hpp
//  StructsLab
//
//  Created by Derek Olson on 8/27/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//
#pragma once
#ifndef helpers_hpp
#define helpers_hpp
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

struct Politician{
    string name;
    bool democrat;
    bool fed;
};

std::vector<string> Democrats(std::vector <Politician> politicians);

std::vector<Politician> FedRepublicans(std::vector<Politician> politicians);

string WhipVote(std::vector<Politician> politicians, bool bill_type);

#endif /* helpers_hpp */
