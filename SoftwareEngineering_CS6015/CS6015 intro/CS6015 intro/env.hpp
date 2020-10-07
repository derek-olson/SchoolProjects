//
//  env.hpp
//  CS6015 intro
//
//  Created by Derek Olson on 3/2/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef env_hpp
#define env_hpp
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "pointer.h"

class Val;

class Env{
public:
    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class EmptyEnv ENABLE_THIS(EmptyEnv) public Env{
public:
    PTR(Val) lookup(std::string find_name);
};

class ExtendedEnv ENABLE_THIS(ExtendedEnv) public Env{
public:
    std::string name;
    PTR(Val) val;
    PTR(Env) rest;
    
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);
    PTR(Val) lookup(std::string find_name);
};
#endif /* env_hpp */
