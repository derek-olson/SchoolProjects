//
//  step.hpp
//  msdScript
//
//  Created by Derek Olson on 3/23/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef step_hpp
#define step_hpp
#include "pointer.h"
#include <iostream>
#include <stdio.h>

class Expr;
class Cont;
class Val;
class Env;

class Step{
public:
    typedef enum {
        interp_mode,
        continue_mode
    }mode_t;
public:
    static mode_t mode;
    static PTR(Expr) expr;
    static PTR(Env) env;
    static PTR(Val) val;
    static PTR(Cont) cont;
    
    static PTR(Val)interp_by_steps(PTR(Expr) e);

};

#endif /* step_hpp */
