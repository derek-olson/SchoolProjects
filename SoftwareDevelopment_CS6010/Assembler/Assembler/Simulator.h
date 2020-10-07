#pragma once

/*
  Author: Daniel Kopta
  August 2017
  
  CS 6010 Fall 2017
  Simple MIPS-like simulator
  Header declarations

  Documentation for these functions is with their definitions
  in Simulator.cpp
*/

#include "Instruction.h"

std::string InstrToString(Instruction instr);
void ErrorExit(std::string message);
unsigned char ExtractOpcode(raw_instr_t bin);
unsigned char ExtractRegister(raw_instr_t bin, int reg);
int8_t ExtractImmediate(raw_instr_t bin);
void PackOperands(raw_instr_t bin, Instruction& instr);
Instruction PackInstruction(raw_instr_t bin);
std::vector<Instruction> ReadBinary(std::string filename, bool debug);
int ReadRegister(int registers[NUM_REGS], int which);
void WriteRegister(int registers[NUM_REGS], int which, int val);
std::string RegToString(int r);
std::string InstrToString(Instruction instr);
void PrintState(Instruction toExecute, int registers[NUM_REGS]);
void Execute(const std::vector<Instruction>& program, int& programCounter, int registers[NUM_REGS], bool debug);

