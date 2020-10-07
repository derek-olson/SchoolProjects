//
//  step.cpp
//  msdScript
//
//  Created by Derek Olson on 3/23/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#include "step.hpp"
#include "cont.hpp"
#include "env.hpp"
#include "expr.hpp"

Step::mode_t Step::mode;
PTR(Cont) Step::cont;
PTR(Expr) Step::expr;
PTR(Val) Step::val;
PTR(Env) Step::env;

PTR(Val) Step::interp_by_steps(PTR(Expr) e){
    Step::mode = Step::interp_mode;
    Step::expr = e;
    Step::env = NEW(EmptyEnv)();
    Step::val = nullptr;
    Step::cont = Cont::done;
    
    while(1){
        if(Step::mode == Step::interp_mode){
            Step::expr->step_interp();
        }
        else{
            if(Step::cont == Cont::done){
                return Step::val;
            }else{
                Step::cont->step_continue();
            }
        }
    }
}
