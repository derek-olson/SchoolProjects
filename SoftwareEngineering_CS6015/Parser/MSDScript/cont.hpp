//
//  cont.hpp
//  msdScript
//
//  Created by Derek Olson on 3/23/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef cont_hpp
#define cont_hpp
#include "pointer.h"
#include "iostream"
#include <stdio.h>

class Expr;
class Env;
class Val;
class step;

class Cont{
public:
    virtual void step_continue() = 0;
    static PTR(Cont) done;
};

class RightThenAddCont ENABLE_THIS(RightThenAddCont) public Cont {
public:
    RightThenAddCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest);
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
};

class AddCont ENABLE_THIS(AddCont) public Cont{
public:
    AddCont(PTR(Val) lhs_val, PTR(Cont) rest);
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    
    void step_continue();
};

class RightThenMultCont ENABLE_THIS(RightThenMultCont) public Cont {
public:
    RightThenMultCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest);
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
};

class MultCont ENABLE_THIS(MultCont) public Cont{
    public:
    MultCont(PTR(Val) lhs_val, PTR(Cont) rest);
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    
    void step_continue();
};

class CompCont ENABLE_THIS(CompCont) public Cont{
    public:
    CompCont(PTR(Val) lhs_val, PTR(Cont) rest);
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    
    void step_continue();
};

class RightThenCompCont ENABLE_THIS(RightThenCompCont) public Cont{
    public:
    RightThenCompCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest);
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
};

class LetBodyCont ENABLE_THIS(LetBodyCont) public Cont{
public:
    LetBodyCont(std::string var, PTR(Expr) body, PTR(Env) env, PTR(Cont) rest);
    
    std::string var;
    PTR(Expr) body;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
};

class IfBranchCont ENABLE_THIS(IfBranchCont) public Cont{
public:
    IfBranchCont(PTR(Expr) then, PTR(Expr) els, PTR(Env) env, PTR(Cont) cont);
    PTR(Expr) then_part;
    PTR(Expr) else_part;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
};

class DoneCont ENABLE_THIS(DoneCont) public Cont{
public:
    
    DoneCont();
    void step_continue();
};

class CallCont ENABLE_THIS(CallCont) public Cont{
public:
    CallCont(PTR(Val) to_be_called_val, PTR(Cont) rest);
    PTR(Val) to_be_called_val;
    PTR(Cont) rest;
    
    void step_continue();
};

class ArgThenCallCont ENABLE_THIS(ArgThenCallCont) public Cont{
public:
    ArgThenCallCont(PTR(Expr) actual_arg, PTR(Env) env, PTR(Cont) rest);
    PTR(Expr) actual_arg;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
};

#endif /* cont_hpp */
