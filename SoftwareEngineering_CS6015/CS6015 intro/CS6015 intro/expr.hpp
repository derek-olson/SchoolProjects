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

class Number ENABLE_THIS(Number) public Expr {
public:
    int val;
    
    Number(int val);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val)  new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class Add ENABLE_THIS(Add) public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    
    Add(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val)  new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class Mult ENABLE_THIS(Mult) public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    Mult(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    PTR(Val) value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class Variable ENABLE_THIS(Variable) public Expr {
public:
    std::string val;

    Variable(std::string val);
    bool equals(PTR(Expr) e);
    PTR(Val)  value(PTR(Env) env);
    PTR(Expr) subst(std::string var, PTR(Val) new_val);
    bool containsVar();
    PTR(Expr) optimize();
    std::string to_string();
    void step_interp();
};

class LetIn ENABLE_THIS(LetIn) public Expr{
public:
    std::string var;
    PTR(Expr) expr1;
    PTR(Expr) expr2;
    
    LetIn(std::string var, PTR(Expr) expr1, PTR(Expr) expr2);
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

class IfElse ENABLE_THIS(IfElse) public Expr{
public:
    PTR(Expr) ifExpr;
    PTR(Expr) thenExpr;
    PTR(Expr) elseExpr;
    
    IfElse(PTR(Expr) ifExpr, PTR(Expr) thenExpr, PTR(Expr) elseExpr);
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
