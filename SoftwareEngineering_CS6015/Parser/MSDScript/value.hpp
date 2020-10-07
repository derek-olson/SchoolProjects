//
//  value.hpp
//  CS6015 intro
//
//  Created by Derek Olson on 2/4/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef value_hpp
#define value_hpp
#include <string>
#include "pointer.h"
//#include "cont.hpp"

class Expr;
class Env;
class Cont;

class Val {
public:
    virtual bool equals(PTR(Val) val) = 0;
    virtual PTR(Val) add_to(PTR(Val) other_val) = 0;
    virtual PTR(Val) mult_with(PTR(Val) other_val) = 0;
    virtual PTR(Expr) to_expr() = 0;
    virtual std::string to_string() = 0;
    virtual PTR(Val) call(PTR(Val)  actualArg) = 0;
    virtual bool is_true() = 0;
    virtual void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest) = 0;
};

class NumVal ENABLE_THIS(NumVal) public Val {
public:
    int rep;
    
    NumVal(int rep);
    
    bool equals(PTR(Val) val);
    PTR(Val) add_to(PTR(Val) other_val);
    PTR(Val) mult_with(PTR(Val) other_val);
    PTR(Expr) to_expr();
    std::string to_string();
    PTR(Val) call(PTR(Val)  actualArg);
    bool is_true();
    void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

class BoolVal ENABLE_THIS(BoolVal) public Val {
public:
    bool rep;
    
    BoolVal(bool rep);
    
    bool equals(PTR(Val) val);
    PTR(Val) add_to(PTR(Val) other_val);
    PTR(Val) mult_with(PTR(Val) other_val);
    PTR(Expr) to_expr();
    std::string to_string();
    PTR(Val) call(PTR(Val)  actualArg);
    virtual bool is_true();
    void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

class FunVal ENABLE_THIS(FunVal) public Val{
public:
    std::string formalArg;
    PTR(Expr) body;
    PTR(Env) env;
    
    FunVal(std::string formalArg, PTR(Expr) body, PTR(Env) env);
    
    bool equals(PTR(Val) val);
    PTR(Val) add_to(PTR(Val) other_val);
    PTR(Val) mult_with(PTR(Val) other_val);
    PTR(Expr) to_expr();
    std::string to_string();
    PTR(Val) call(PTR(Val) actualArg);
    virtual bool is_true();
    void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

#endif /* value_hpp */
