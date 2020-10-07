//
//  exec.hpp
//  CS6015 intro
//
//  Created by Derek Olson on 1/30/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef exec_hpp
#define exec_hpp

#include <string>

class ExecResult {
public:
  int exit_code;
  std::string out;
  std::string err;
  ExecResult() {
    exit_code = 0;
    out = "";
    err = "";
  }
};

extern ExecResult exec_program(const char * const *command, std::string input);

#endif /* exec_hpp */
