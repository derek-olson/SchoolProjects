//
//  TestGenerator.hpp
//  CS6015 intro
//
//  Created by Derek Olson on 2/25/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef TestGenerator_hpp
#define TestGenerator_hpp
#include <iostream>
#include <sstream>
#include <stdio.h>

class FuzzGen{
public:
    std::string randStrings[1000];
    
public:
    //UPDATE CONSTRUCTOR
    FuzzGen();
    void genRandStrings();
    std::string genRandBool();
    std::string genRandNum();
    std::string genRandVar();
    std::string genRandChar();
    std::string genRandAdd();
    std::string genRandMult();
    std::string genRandFunExpr();
    std::string genRandBoolExpr();
    std::string genRandCompExpr();
    std::string genRandIfExpr();
    std::string genRandLetExpr();
    std::string genRandCallExpr();
    std::string genRandExpr();
    
};


#endif /* TestGenerator_hpp */
