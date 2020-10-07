//
//  main.cpp
//  Assembler
//
//  Created by Derek Olson on 9/6/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
using namespace std;

uint8_t outBinary = 0b00000000;
uint8_t IntToBinary(int x){
    if (x / 2 != 0){
        IntToBinary(x / 2);
    }
    uint8_t temp = x % 2;
    outBinary = outBinary << 1 | temp;
    cout << +outBinary << "\n";
    return outBinary;
}


int main(int argc, const char * argv[]) {
    uint8_t test = IntToBinary(8);
    cout << +test << "\n";
    
    struct instruction{
        string name;
        int opcode;
        uint8_t binary;
    };
    
    struct registers{
        string name;
        int value;
        uint8_t binary;
    };
    
    struct immediates{
        int value;
        uint8_t binary;
    };
    
    
    instruction instruct[8] = {
    "addi", 1, 0b0001,
    "blt", 2, 0b0010,
    "bne", 3, 0b0011,
    "j", 4, 0b0100,
    "mul", 5, 0b0101,
    "sub", 6, 0b0110,
    "read", 7, 0b0111,
    "print", 8, 0b1000
    };
    
    registers regist[4] = {
        "$0", 0, 0b00,
        "$1", 1, 0b01,
        "$2", 2, 0b10,
        "$3", 3, 0b11
    };
    
    immediates immed[11] = {
    0, 0b00000000,
    1, 0b00000001,
    2, 0b00000010,
    3, 0b00000011,
    4, 0b00000100,
    5, 0b00000101,
    6, 0b00000110,
    7, 0b00000111,
    8, 0b00001000,
    9, 0b00001001,
    -1, 0b11111111
    };
    
    string line;
    
    ifstream ins("Factorial.s");
    ofstream outStream("assembler.bin");
    
    struct OutBinary{
        uint8_t inst;
        uint8_t arg1;
        uint8_t arg2;
        uint8_t arg3;
    };
    //outStream.open("assebler.bin", std::ifstream::out | std::ofstream::app);
    while (getline(ins, line)){
        string name; string arg1; string arg2; string arg3;
        stringstream splitter(line);
        OutBinary outBinary;
        
        splitter >> name;
        cout << name;
        for (int i = 0; i < 8; i++){
            if (name == instruct[i].name){
                outBinary.inst = instruct[i].binary;
            }
        }
        
        splitter >> arg1;
        cout << arg1;
        if (arg1.front() == '$'){
            for (int i = 0; i < 4; i++){
                if (arg1 == regist[i].name){
                    outBinary.arg1 = regist[i].binary;
                }
            }
        }
        splitter >> arg2;
        cout << arg2;
        if (arg2.front() == '$'){
            for (int i = 0; i < 4; i++){
                if (arg2 == regist[i].name){
                    outBinary.arg2 = regist[i].binary;
                }
            }
        }else if (arg2.size() > 0 && arg2.front() != '$'){
            for (int i = 0; i < 3; i++){
                if (stoi(arg2) == immed[i].value){
                    outBinary.arg2 = immed[i].binary;
                }
            }
        }else if (arg2.size() < 1){
            outBinary.arg2 = 0b00;
        }
        
        splitter >> arg3;
        cout << arg3;
        
        if (arg3.front() == '$'){
            for (int i = 0; i < 4; i++){
                if (arg3 == regist[i].name){
                    outBinary.arg3 = regist[i].binary << 6;
                }
            }
        }else if (arg3.size() > 0 && arg3.front() != '$'){
            for (int i = 0; i < 11; i++){
                if (stoi(arg3) == immed[i].value){
                    outBinary.arg3 = immed[i].binary;
                }
            }
        }else if (arg3.size() < 1){
            outBinary.arg3 = 0b00000000;
        }
        cout << "\n";
        
        outStream.put(outBinary.inst << 4 | outBinary.arg1  << 2| outBinary.arg2);
        outStream.put(outBinary.arg3);
    }//outStream.close();
    
    return 0;
}
