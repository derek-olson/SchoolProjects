#pragma once

#include <string>

const int NUM_REGS = 4;


/*
 * A sequence of values in ascending order, starting at 0, representing opcodes.
 */
enum Opcode{
  INVALID_OP = 0,
  addi,
  blt,
  bne,
  j,
  mul,
  sub,
  read,
  print,
  END
};

/*
 * The string names of each instruction. These must appear in the same order as their Opcodes.
 */
const std::string opNames[] = {"INVALID",
			       "addi",
			       "blt",
			       "bne",
			       "j",
			       "mul",
			       "sub",
			       "read",
			       "print",
			       "END"};

/*
 * A simple two-byte data type. This will represent the raw binary machine code
 * for one instruction.
 */
struct raw_instr_t
{
  unsigned char bytes[2];
};

/*
 * A struct to track an instruction in a more useful way for the simulator.
 * The fields in this struct correspond to what the machine code bits encode.
 */
struct Instruction
{
  unsigned char opCode;
  unsigned char regOperands[3];
  int8_t immediate;

  Instruction()
  {
    opCode = 0;
    regOperands[0] = regOperands[1] = regOperands[2] = 0;
    immediate = 0;
  }
};
