//
//  expr.hpp
//  CS6015 intro
//
//  Created by Derek Olson on 1/20/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef expr_hpp
#define expr_hpp
#include <string>
#include "pointer.h"

class Env;
class Val;

//parent class which all other classes inhert from
//defines virtual methods to be overwritten by child classes
class Expr {
public:
    
    virtual bool equals(PTR(Expr) e) = 0;
    virtual PTR(Val) value(PTR(Env) env) = 0;
    virtual PTR(Expr) subst(std::string var, PTR(Val)  val) = 0;
    virtual bool containsVar() = 0;
    virtual PTR(Expr) optimize() = 0;
    virtual std::string to_string() = 0;
    virtual void step_interp() = 0;
};

class NumberExpr ENABLE_THIS(NumberExpr) public Expr {
public:
    int val;
    
    NumberExpr(int val);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val)  new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class AddExpr ENABLE_THIS(AddExpr) public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    
    AddExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val)  new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class MultExpr ENABLE_THIS(MultExpr) public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    MultExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class VariableExpr ENABLE_THIS(VariableExpr) public Expr {
public:
    std::string val;

    VariableExpr(std::string val);
    bool equals(PTR(Expr) e);
    PTR(Val)  value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class LetExpr ENABLE_THIS(LetExpr) public Expr{
public:
    std::string var;
    PTR(Expr) expr1;
    PTR(Expr) expr2;
    
    LetExpr(std::string var, PTR(Expr) expr1, PTR(Expr) expr2);
    bool equals(PTR(Expr) e);
    PTR(Val)  value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) exp);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class BoolExpr ENABLE_THIS(BoolExpr) public Expr {
public:
    bool rep;
  
    BoolExpr(bool rep);
    bool equals(PTR(Expr) e);
  
    PTR(Val)  value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class CompExpr ENABLE_THIS(CompExpr) public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
  
    CompExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
  
    PTR(Val)  value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class IfExpr ENABLE_THIS(IfExpr) public Expr{
public:
    PTR(Expr) ifExpr;
    PTR(Expr) thenExpr;
    PTR(Expr) elseExpr;
    
    IfExpr(PTR(Expr) ifExpr, PTR(Expr) thenExpr, PTR(Expr) elseExpr);
    bool equals(PTR(Expr) e);
    PTR(Val)  value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val)  exp);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class FunExpr ENABLE_THIS(FunExpr) public Expr{
public:
    std::string arg;
    PTR(Expr) body;
    
    FunExpr(std::string arg, PTR(Expr) body);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) exp);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class CallExpr ENABLE_THIS(CallExpr) public Expr{
public:
    PTR(Expr) toBeCalled;
    PTR(Expr) actualArg;
    
    CallExpr(PTR(Expr) toBeCalled, PTR(Expr) actualArg);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) exp);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

#endif /* expr_h */
