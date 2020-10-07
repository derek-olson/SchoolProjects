//
//  env.cpp
//  CS6015 intro
//
//  Created by Derek Olson on 3/2/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//
#include "pointer.h"
#include "value.hpp"
#include "env.hpp"
#include <sstream>
#include <iostream>

ExtendedEnv::ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest){
    this->name = name;
    this->val = val;
    this->rest = rest;
}

PTR(Val) ExtendedEnv::lookup(std::string find_name){
    if(find_name == name){
        return val;
    }
    else{
        return rest -> lookup(find_name);
    }
}

PTR(Val) EmptyEnv::lookup(std::string find_name){
    throw std::runtime_error("Free variable: "+ find_name);
}
