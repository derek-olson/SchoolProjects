////
////  runner_main.cpp
////  CS6015 intro
////
////  Created by Derek Olson on 1/30/20.
////  Copyright © 2020 Derek Olson. All rights reserved.
////

#include <iostream>
#include <string>
#include <cstdlib>

#include "exec.hpp"
#include "TestGenerator.hpp"

const int N = 1000000;
const int RANDOM_ITERS = 100;

static void check_success(ExecResult &r);
static std::string make_big_string(std::string word, int size);
static std::string random_word();
const char * const cmd = "/Users/derekolson/Library/Developer/Xcode/DerivedData/CS6015_intro-fkhiigpkdqaunsbjvvjfrdlvurqk/Build/Products/Debug/CS6015 intro";

int main(int argc, const char * argv[]) {
    FuzzGen* fuzzGen = new FuzzGen();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Interp Tests
    
    //mult test
    const char * const interp_command[] = {cmd, "_interp", NULL};
    ExecResult interp_result = exec_program(interp_command, fuzzGen->genRandMult());
    check_success(interp_result);
    std::cout << interp_result.exit_code << "\n";
    
    //Add Tests
    const char * const add_command[] = {cmd, "_interp", NULL};
    ExecResult add_result = exec_program(add_command, fuzzGen->genRandAdd());
    check_success(add_result);
    std::cout << add_result.exit_code << "\n";
    
    //Comp Tests
    const char * const comp_command[] = {cmd, "_interp", NULL};
    ExecResult comp_result = exec_program(comp_command, fuzzGen->genRandCompExpr());
    check_success(comp_result);
    std::cout << comp_result.exit_code << "\n";
    
    //If Else Tests
    const char * const if_command[] = {cmd, "_interp", NULL};
    ExecResult if_result = exec_program(if_command, fuzzGen->genRandIfExpr());
    check_success(if_result);
    std::cout << if_result.exit_code << "\n";
    
    //Let Tests
    const char * const let_command[] = {cmd, "_interp", NULL};
    ExecResult let_result = exec_program(let_command, fuzzGen->genRandLetExpr());
    check_success(let_result);
    std::cout << let_result.exit_code << "\n";
    
    //Fun Tests
    const char * const fun_command[] = {cmd, "_interp", NULL};
    ExecResult fun_result = exec_program(fun_command, fuzzGen->genRandFunExpr());
    check_success(fun_result);
    std::cout << fun_result.exit_code << "\n";
    
    //Call Tests
    const char * const call_command[] = {cmd, "_interp", NULL};
    ExecResult call_result = exec_program(call_command, fuzzGen->genRandCallExpr());
    check_success(call_result);
    std::cout << call_result.exit_code<< "\n";
    
  std::string big_string = make_big_string("hello", N);

  // Example: running `wc`
  const char * const wc_command[] = { cmd, "_optimize", NULL };
  ExecResult wc_result = exec_program(wc_command, big_string);
  check_success(wc_result);
  std::cout << wc_result.out;

  // Example: checking that `cat` echos its input
  const char * const cat_command[] = { "/bin/cat", NULL };
  ExecResult cat_result = exec_program(cat_command, big_string);
  check_success(cat_result);
  if (big_string != cat_result.out)
    std::cerr << "bad cat result\n";

  // Stress test by checking `cat` even more
  for (int i = 0; i < RANDOM_ITERS; i++) {
    int size = rand() % N;
    std::string word = random_word();
    std::string random_big_string = make_big_string(word, size);
    ExecResult random_cat_result = exec_program(cat_command, random_big_string);
    check_success(random_cat_result);
    if (random_big_string != random_cat_result.out) {
      std::cerr << "bad random cat result\n";
      std::cerr << " word: ";
      for (int i = 0; i < word.length(); i++)
        std::cerr << " " << (int)(unsigned char)word[i];
      std::cerr << "\n";
      std::cerr << " word length: " << word.length() << "\n";
      std::cerr << " size: " << size << "\n";
      std::cerr << " input length:  " << random_big_string.length() << "\n";
      std::cerr << " output length: " << random_cat_result.out.length() << "\n";
    }
  }

  return 0;
}

static void check_success(ExecResult &result) {
  std::cerr << result.err;
  if (result.exit_code != 0)
    std::cerr << "non-zero exit: " << result.exit_code << "\n";
}

static std::string make_big_string(std::string word, int size) {
  std::string big;
  for (int i = 0; i < size; i++)
    big += word + "\n";
  return big;
}

static std::string random_word() {
  std::string word = "";
  for (int i = rand() % 32; i-- > 0; ) {
    word += rand() % 256;
  }
  return word;
}
