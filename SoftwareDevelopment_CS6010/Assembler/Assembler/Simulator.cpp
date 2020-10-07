/*
  Author: Daniel Kopta
  August 2017
  
  CS 6010 Fall 2017
  Simple MIPS-like simulator

  * Students will provide an assembler that generates a binary file
  * containing machine code for the simulator to take as input.
  * Students are not required to write the simulator.
  * Instead, the simulator is used as a correctness checker. 
  * If the simulator runs the program correctly, then their assembler
  * is (most likely) correct.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
// Prefer C-style for binary file I/O
#include <cstdio>

#include "Instruction.h"
#include "Simulator.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::to_string;

int main(int argc, char** argv)
{    
  if(argc < 2 || argc > 3)
    ErrorExit("Invalid arguments to main. Please supply one file name as an argument, followed optionally by \"-debug\"");
  
  bool debug;
  
  if(argc == 3 && strcmp(argv[2], "-debug") == 0)
    debug = true;
  
  // Read the binary file in to a vector of "Instruction"s
  vector<Instruction> program = ReadBinary(argv[1], debug);

  // Set the initial state of registers and program counter to 0
  int registers[NUM_REGS];
  int programCounter = 0;
  memset(registers, 0, NUM_REGS * sizeof(int));

  // Exectue instructions one at a time until we've executed the last one.
  // The last instruction can't be a branch or jump, or else the program
  // will never terminate.
  while(programCounter != program.size())
  {
    Execute(program, programCounter, registers, debug);
  }
}

/*
 * Reads the provided binary file supplied to the simulator.
 * Performs error-checking while reading, and will attempt 
 * to indicate what went wrong, if anything.
 *
 * Parameters:
 *   filename -- the name of the binary file
 *   debug -- a switch to cause more detailed printing
 *
 * Returns:
 *   A vector of Instruction structs. This is the representation
 *   of a program that the simulator understands.
 */
vector<Instruction> ReadBinary(string filename, bool debug)
{
  FILE* input = fopen(filename.c_str(), "rb");
  if(!input)
  {
    ErrorExit("Unable to open input file: " + filename);
  }

  vector<Instruction> retval;
  
  if(debug)
    cout << "Reading instructions...\n";

  // Read until we can't read anymore (note the break or ErrorExit, so it's not actually an infinite loop).
  while(true)
  {
    raw_instr_t instr;
    // Attempt to read two 1-byte chunks, so we can report if the binary
    // has an uneven multiple of 2 bytes
    int read = fread(&instr, 1, 2, input);
    if(read == 0)
      break;
    else if(read != 2)
      ErrorExit("Found extraneous bytes in input file (file size not a multiple of 2 bytes).");
    else
    {
      Instruction decoded = PackInstruction(instr);
      retval.push_back(decoded);
      if(debug)
	cout << InstrToString(decoded) << endl;
    }
  }

  if(debug)
    cout << endl;

  return retval;
}



/*
 * Executes one instruction in the program. Updates which instruciton is next, 
 * and updates the registers depending on the instruction.
 *
 * Parameters:
 *   program -- the list of instructions making up the entire program
 *   programCounter -- the current instrucion to execute. 
 *                     this is updated by reference
 *   registers -- the registers in the simulated CPU
 *   debug -- a switch to cause more detailed printing
 *
 * Returns:
     Nothing, but has the potential side effect of changing the programCounter and the registers.
 */
void Execute(const vector<Instruction>& program, int& programCounter, int registers[NUM_REGS], bool debug)
{
  if(programCounter < 0 || programCounter >= program.size())
    ErrorExit("Program tried to jump to invalid instruction number: " + std::to_string(programCounter));

  // Get the current instruction
  Instruction toExecute = program[programCounter];

  if(debug)
    PrintState(toExecute, registers);

  int writeResult;

  /* Specify the behavior of each instruction. */ 
  switch(toExecute.opCode)
  {
    // op0 = op1 + imm
  case Opcode::addi:
    writeResult = ReadRegister(registers, toExecute.regOperands[1]) + toExecute.immediate;
    WriteRegister(registers, toExecute.regOperands[0], writeResult);
    break;
    // if(op0 < op1) goto imm
  case Opcode::blt:
    if(ReadRegister(registers, toExecute.regOperands[0]) < ReadRegister(registers, toExecute.regOperands[1]))
    {
      programCounter = toExecute.immediate;
      return;
    }
    break;
    // if(op0 != op1) goto imm
  case Opcode::bne:
    if(ReadRegister(registers, toExecute.regOperands[0]) != ReadRegister(registers, toExecute.regOperands[1]))
    {
      programCounter = toExecute.immediate;
      return;
    }
    break;
    // op0 = op1 * op2
  case Opcode::mul:
    writeResult = ReadRegister(registers, toExecute.regOperands[1]) * ReadRegister(registers, toExecute.regOperands[2]);
    WriteRegister(registers, toExecute.regOperands[0], writeResult);
    break;
    // op0 = op1 - op2
  case Opcode::sub:
    writeResult = ReadRegister(registers, toExecute.regOperands[1]) - ReadRegister(registers, toExecute.regOperands[2]);
    WriteRegister(registers, toExecute.regOperands[0], writeResult);
    break;
    // cin >> op0
  case Opcode::read:
    cout << "Enter a value for register r" << (int)toExecute.regOperands[0] << endl;
    cin >> writeResult;
    WriteRegister(registers, toExecute.regOperands[0], writeResult);
    break;
    // cout << op0
  case Opcode::print:
    cout << "Register r" << (int)toExecute.regOperands[0] << " has value " << ReadRegister(registers, toExecute.regOperands[0]) << endl;
    break;
    // goto imm
  case Opcode::j:
    programCounter = toExecute.immediate;
    return;
    break;

    // This should never happen, since the program is verified at decode time, but you never know...
  default:
    ErrorExit("Unknown opcode found during execution: " + std::to_string(toExecute.opCode));
    break;
  }

  // goto the next instruction
  programCounter++;

}


/*
 * Read the value in the specified register, used during simulation execution time.
 * Also perform error-checking
 *
 * Parameters:
 *   registers -- the registers in the simulated CPU
 *   which -- which register to read; this must be between 0-3
 *
 * Returns:
     The value of the register
 */
int ReadRegister(int registers[NUM_REGS], int which)
{
  if(which < 0 || which >= NUM_REGS)
    ErrorExit("Trying to read from invalid register during execution: " + to_string(which));

  return registers[which];

}

/*
 * Write the specified value to the specified register, used during simulation execution time.
 * Also perform error-checking
 *
 * Parameters:
 *   registers -- the registers in the simulated CPU
 *   which -- which register to write to; this must be between 0-3
 *   int val -- the new value for the register
 *
 * Returns:
     Nothing, but has the side-effect of changing a register
 */
void WriteRegister(int registers[NUM_REGS], int which, int val)
{
  if(which < 0 || which >= NUM_REGS)
    ErrorExit("Trying to write to invalid register during execution: " + to_string(which));

  registers[which] = val;
}

/*
 * Get the opcode bits out of a two-byte machine code instruction.
 * Used at program decode time, not simulation time.
 *
 * Parameters:
 *   bin -- the binary machine code representation of the instruction
 *
 * Returns:
     The opcode
 */
unsigned char ExtractOpcode(raw_instr_t bin)
{
  return bin.bytes[0] >> 4;
}

/*
 * Get the specified register bits out of a two-byte machine code instruction.
 * Used at program decode time, not simulation time.
 *
 * Parameters:
 *   bin -- the binary machine code representation of the instruction
 *   reg -- which register position to extract (reg0, reg1, or reg2)
 *
 * Returns:
     The register number (representing one of $0 through $3)
 */
unsigned char ExtractRegister(raw_instr_t bin, int reg)
{
  if(reg == 0)
    return (bin.bytes[0] & 0x0c) >> 2;
  if(reg == 1)
    return (bin.bytes[0] & 0x03);
  if(reg == 2)
    return bin.bytes[1] >> 6;
  
  // If this error is ever reached, it's probably a bug in the simulator, not the student's code.
  ErrorExit("Trying to extract an invalid register.");
  
  // This will never be reached, but it makes the compiler happy
  return 0; 
}

/*
 * Get the immediate value out of a two-byte machine code instruction.
 * Used at program decode time, not simulation time.
 *
 * Parameters:
 *   bin -- the binary machine code representation of the instruction
 *
 * Returns:
     The immediate
 */
int8_t ExtractImmediate(raw_instr_t bin)
{
  return bin.bytes[1];
}

/*
 * Fills in the Instruction "instr" with which registers it uses, and its immediate, if applicable.
 * Used at program decode time, not simulation time.
 *
 * Parameters:
 *   bin -- the binary machine code representation of the instruction
 *   instr -- the existing Instruction, which only has an opcode thus far
 *
 * Returns:
     Nothing, but fills in the Instruction passed by reference.
 */
void PackOperands(raw_instr_t bin, Instruction& instr)
{
  
  // Instructions use different operands depending on the opcode
  switch(instr.opCode)
  {
    // Two registers and the immediate
  case Opcode::addi:
  case Opcode::blt:
  case Opcode::bne:
    instr.regOperands[0] = ExtractRegister(bin, 0);
    instr.regOperands[1] = ExtractRegister(bin, 1);
    instr.immediate = ExtractImmediate(bin);
    break;
    // Three registers
  case Opcode::mul:
  case Opcode::sub:
    instr.regOperands[0] = ExtractRegister(bin, 0);
    instr.regOperands[1] = ExtractRegister(bin, 1);
    instr.regOperands[2] = ExtractRegister(bin, 2);
    break;
    // One register
  case Opcode::read:
  case Opcode::print:
    instr.regOperands[0] = ExtractRegister(bin, 0);
    break;
    // Just the immediate
  case Opcode::j:
    instr.immediate = ExtractImmediate(bin);
    break;
  default:
    ErrorExit("Unknown opcode found in binary.");
    break;
  }
  
}

/*
 * Creates an Instruciton struct from the machine code binary representation
 * Used at program decode time, not simulation time.
 *
 * Parameters:
 *   bin -- the binary machine code representation of the instruction
 *
 * Returns:
     The Instruction struct representation of the machine code
 */
Instruction PackInstruction(raw_instr_t bin)
{
  Instruction retval;

  retval.opCode = ExtractOpcode(bin);
  
  PackOperands(bin, retval);

  return retval;
}

/*
 * Returns the string representation of a register ID
 * Used for debugging
 *
 * Parameters:
 *   r -- which register
 *
 * Returns:
     The string representation of the register. This just prepends '$' to the number.
 */
string RegToString(int r)
{
  return "$" + to_string(r);
}

/*
 * Returns the assembly string representation of an Instruction struct
 * Used for debugging
 *
 * Parameters:
 *   instr -- the instruction
 *
 * Returns:
 *   The string representation of the instruction.
 *   This converts the Instruction back to its readable assembly form.
 */
string InstrToString(Instruction instr)
{
  // Start with the instruction name
  string retval = opNames[instr.opCode];
  
  // Then add the operands, which depends on the type of instruction
  switch(instr.opCode)
  {
  case Opcode::addi:
  case Opcode::blt:
  case Opcode::bne:
    retval += "\t" + RegToString(instr.regOperands[0]);
    retval += "\t" + RegToString(instr.regOperands[1]);
    retval += "\t" + to_string(instr.immediate);
    break;
  case Opcode::mul:
  case Opcode::sub:
    retval += "\t" + RegToString(instr.regOperands[0]);
    retval += "\t" + RegToString(instr.regOperands[1]);
    retval += "\t" + RegToString(instr.regOperands[2]);
    break;
  case Opcode::read:
  case Opcode::print:
    retval += "\t" + RegToString(instr.regOperands[0]);
    break;
  case Opcode::j:
    retval += "\t" + to_string(instr.immediate);
  }

  return retval;

}

/*
 * Prints the state of the simulated CPU.
 * Used for debuggin.
 *
 * Parameters:
 *   toExecute -- the next instruction to be executed
 *   registers -- the registers
 *
 * Returns:
 *   Nothing, but prints which instruction is about the execute,
 *   and the contents of all the registers before executing it.
 */
void PrintState(Instruction toExecute, int registers[NUM_REGS])
{
  cout << "About to execute\n\t" << InstrToString(toExecute);
  cout << "\n\tRegisters:   ";
  for(int i = 0; i < NUM_REGS; i++)
    cout << "$" << i << " = " << registers[i] << "   ";
  cout << endl;
}

/*
 * Helper for when an error is detected. Prints a message then exits.
 *
 * Parameters:
 *   message -- the message representing the error
 *
 * Returns:
 *   Nothing, but prints the message, then exits the program.
 */
void ErrorExit(string message)
{
  cout << "Error: " << message << endl;
  exit(1);
}
