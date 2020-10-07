//
//  TestGenerator.cpp
//  CS6015 intro
//
//  Created by Derek Olson on 2/25/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#include "TestGenerator.hpp"
#include <stdlib.h>
#include <stdio.h>

FuzzGen::FuzzGen(){}

void FuzzGen::genRandStrings(){
    for(int j = 0; j < 1000; j++){
        std::string s;
        int rNum = rand()%(1000);
        for (size_t i = 0; i < rNum; ++i) {
            int randomChar = rand()%(26+26+10);
            if (randomChar < 26)
                s[i] = 'a' + randomChar;
            else if (randomChar < 26+26)
                s[i] = 'A' + randomChar - 26;
            else
                s[i] = '0' + randomChar - 26 - 26;
        }
        s[rNum] = 0;
        randStrings[j] = s;
    }
}

std::string FuzzGen::genRandBool(){
    int r = rand() % 2;
    
    if(r % 2 == 0){
        return "_true";
    }
    return "_false";
}

std::string FuzzGen::genRandNum(){
    return std::to_string(rand() % 1000);
}

std::string FuzzGen::genRandVar(){
    std::string s;
    int rNum = rand()%(20);
    for (size_t i = 0; i < rNum; ++i) {
        int randomChar = rand()%(26+26);
        if (randomChar < 26)
            s[i] = 'a' + randomChar;
        else if (randomChar < 26+26)
            s[i] = 'A' + randomChar - 26;
    }
    return s;
}

std::string FuzzGen::genRandChar(){
    std::string s;
    int randomChar = rand()%(26+26);
    if (randomChar < 26)
        s = 'a' + randomChar;
    else if (randomChar < 26+26)
        s = 'A' + randomChar - 26;
    return s;
}

std::string FuzzGen::genRandAdd(){
    int r = rand() % 4;
    switch (r % 2) {
        case 0:
            return "(" + genRandChar() + "+" + genRandNum() + ")";
            
        default:
            return "(" + genRandNum() + "+" + genRandNum() + ")";
    }
}

std::string FuzzGen::genRandMult(){
    int r = rand() % 4;
    switch (r % 2) {
        case 0:
            return "(" + genRandChar() + "*" + genRandNum() + ")";
            
        default:
            return "(" + genRandNum() + "*" + genRandNum() + ")";
    }
}

std::string FuzzGen::genRandCompExpr(){
    int r = rand() % 4;
    switch (r % 2) {
        case 0:
            return "(" + genRandNum() + "==" + genRandNum() + ")";
            
        default:
            return "(" + genRandChar() + "==" + genRandNum() + ")";
    }
}
std::string FuzzGen::genRandIfExpr(){
    int r = rand() % 15;
    switch (r % 5) {
        case 0:
            return "(_if " + genRandBool() + " _then " + genRandAdd() + " _else " + genRandAdd() + ")";
            
        case 1:
            return "(_if " + genRandBool() + " _then " + genRandAdd() + " _else " + genRandAdd() + ")";
            
        case 2:
            return "(if " + genRandBool() + " _then " + genRandAdd() + " _else " + genRandAdd() + ")";
            
        case 3:
            return "(_if " + genRandBool() + " then " + genRandAdd() + " _else " + genRandAdd() + ")";
            
        default:
            return "(_if " + genRandBool() + " _then " + genRandMult() + " _else " + genRandMult() + ")";
    }
}
std::string FuzzGen::genRandLetExpr(){
    int r = rand() % 15;
    switch (r % 5) {
        case 0:
            return "(_let " + genRandChar() + " = " + genRandNum() + " _in " + genRandAdd() + ")";
            
        case 1:
            return "(let " + genRandChar() + " = " + genRandNum() + " _in " + genRandAdd() + ")";
            
        case 2:
            return "(_let " + genRandNum() + " = " + genRandNum() + " _in " + genRandAdd() + ")";
            
        case 3:
            return "(_let " + genRandChar() + " = " + genRandNum() + " _in " + genRandMult() + ")";
            
        default:
            return "(_let " + genRandChar() + " = " + genRandChar() + " _in " + genRandMult() + ")";
    }
}

std::string FuzzGen::genRandFunExpr(){
    int r = rand() % 15;
    switch (r % 5) {
        case 0:
            return "(_fun (" + genRandChar() + ") "  + genRandAdd() + ")";
            
        case 1:
            return "(_fun (" + genRandNum() + ") "  + genRandAdd() + ")";
            
        case 2:
            return "(_fun (" + genRandChar() + ") "  + genRandMult() + ")";
            
        case 3:
            return "(_fun (" + genRandBool() + ") "  + genRandAdd() + ")";
            
        default:
            return "(_fun (" + genRandMult() + ") "  + genRandAdd() + ")";
    }
}

std::string FuzzGen::genRandCallExpr(){
    int r = rand() % 15;
    switch (r % 5) {
        case 0:
            return "(" + genRandChar() + "( "  + genRandNum() + "))";
            
        case 1:
            return "(" + genRandNum() + "( "  + genRandNum() + "))";
            
        case 2:
            return "(" + genRandChar() + "( "  + genRandChar() + "))";
            
        case 3:
            return "(" + genRandChar() + "( "  + genRandAdd() + "))";
            
        default:
            return "(" + genRandVar() + "( "  + genRandNum() + "))";
    }
}

std::string FuzzGen::genRandExpr(){
    return NULL;
}
