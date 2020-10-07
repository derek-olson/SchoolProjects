//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "expr.hpp"
#include <sstream>
#include <iostream>
#include "parse.hpp"
#include "pointer.h"
#include "value.hpp"
#include "env.hpp"
#include "step.hpp"
#include "cont.hpp"

////////////////////// NUMBER METHODS ////////////////////////////////////
//NumberExpr constructor, takes an int and sets the member variable
NumberExpr::NumberExpr(int val){
    this -> val = val;
    //this -> rep = NEW(NumVal)(rep);
}

//NumberExpr test of equality casts the input expression to a NumberExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool NumberExpr::equals(PTR(Expr) e) {
    PTR(NumberExpr)n = CAST(NumberExpr)(e);
    if (n == NULL){
        return false;
    }
    else{
        return val == n->val;
    }
}

//Method to return the value of the NumberExpr
PTR(Val) NumberExpr::value(PTR(Env) env){
    return NEW(NumVal)(val);
}

//NumberExpr substitution method returns a NEW(NumberExpr)
PTR(Expr) NumberExpr::subst(std::string var, PTR(Val) new_val){
    return NEW(NumberExpr)(val);
}

//The containsVar method for a NumberExpr always returns false
bool NumberExpr::containsVar(){
    return false;
}

//The NumberExpr optimize method just returns THIS, nothing to reduce
PTR(Expr) NumberExpr::optimize(){
    return NEW(NumberExpr)(val);;
}

std::string NumberExpr::to_string(){
    return std::to_string(val);
}

void NumberExpr::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = NEW(NumVal)(val);
    Step::cont = Step::cont;
}

////////////////////// ADD METHODS ////////////////////////////////////
//The AddExpr constructor sets the lhs and rhs member variables
AddExpr::AddExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

//AddExpr test of equality casts the input expression to an AddExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool AddExpr::equals(PTR(Expr)e) {
    PTR(AddExpr) a = CAST(AddExpr)(e);
    if (a == NULL){
        return false;
    }else{
        return (lhs->equals(a->lhs) && rhs->equals(a->rhs));
    }
}

//Returns the value of the lhs + the value of the rhs
PTR(Val) AddExpr::value(PTR(Env) env){
    return lhs->value(env)->add_to(rhs->value(env));
}

//Returns a NEW(AddExpr) with the lhs and rhs substituted
PTR(Expr) AddExpr::subst(std::string var, PTR(Val) new_val){
    return NEW(AddExpr)(lhs->subst(var, new_val), rhs->subst(var, new_val));
}

//Determines if either the lhs or rhs contain a variable
bool AddExpr::containsVar(){
    return lhs->containsVar() || rhs->containsVar();
}

//Optimize is called on both lhs and rhs to reduce. If the MultExpr
//object does not contain a variable a NEW(NumberExpr) is returned else
//THIS is returned, avoiding optimization where there is a variable
PTR(Expr) AddExpr::optimize(){
    PTR(AddExpr) out = NEW(AddExpr)(lhs->optimize(), rhs->optimize());
    if(!out->containsVar()){
        return out->value(NEW(EmptyEnv)())->to_expr();
    }
    return out;
}

std::string AddExpr::to_string(){
    return lhs->to_string() + " + " + rhs->to_string();
}

void AddExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenAddCont)(rhs, Step::env, Step::cont);
}

////////////////////// MULT METHODS ////////////////////////////////////

//MultExpr constructor, set lhs and rhs member variables
MultExpr::MultExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

//MultExpr test of equality casts the input expression to a MultExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool MultExpr::equals(PTR(Expr)e) {
    PTR(MultExpr) m = CAST(MultExpr)(e);
    if (m == NULL){
      return false;
  }else{
      return (lhs->equals(m->lhs) && rhs->equals(m->rhs));
  }
}

//Returns the value of lhs * the value of rhs
PTR(Val) MultExpr::value(PTR(Env) env){
    return lhs->value(env)->mult_with(rhs->value(env)) ;
}

//Calls the substitute method on both the lhs and rhs of the MultExpr object
PTR(Expr) MultExpr::subst(std::string var, PTR(Val) new_val){
    return NEW(MultExpr)(lhs->subst(var, new_val), rhs->subst(var, new_val));
}

//Determimes whether lhs or rhs of MultExpr object contains a variable
bool MultExpr::containsVar(){
    return lhs->containsVar() || rhs->containsVar();
}

//Optimize is called on both lhs and rhs to reduce. If the MultExpr
//object does not contain a variable a NEW(NumberExpr) is returned else
//THIS is returned, avoiding optimization where there is a variable
PTR(Expr) MultExpr::optimize(){
    PTR(MultExpr) out = NEW(MultExpr)(lhs->optimize(), rhs->optimize());
    if(!out->containsVar()){
        return out->value(NEW(EmptyEnv)())->to_expr();
    }
    return out;
}

std::string MultExpr::to_string(){
    return lhs->to_string() + " * " + rhs->to_string();
}

void MultExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenMultCont)(rhs, Step::env, Step::cont);
}

////////////////////// VARIABLE METHODS ////////////////////////////////////

//VariableExpr constructor set the string value
VariableExpr::VariableExpr(std::string val) {
    this->val = val;
}

//VariableExpr test of equality casts the input expression to a VariableExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool VariableExpr::equals(PTR(Expr)e) {
    PTR(VariableExpr) v = CAST(VariableExpr)(e);
    if (v == NULL){
      return false;
  }else{
      return val == v->val;
  }
}

//THIS method returns 0
PTR(Val) VariableExpr::value(PTR(Env) env){
    return env->lookup(THIS->val);
}


//a method to substitue variables 
PTR(Expr) VariableExpr::subst(std::string var, PTR(Val) new_val){
    if(val == var){
        return new_val->to_expr();
    }
    return NEW(VariableExpr)(val);
}

//Returns true because variables always contain variables
bool VariableExpr::containsVar(){
    return true;
}

//VariableExpr can't be reduced further, returns the variable
PTR(Expr) VariableExpr::optimize(){
    return NEW(VariableExpr)(val);
}

std::string VariableExpr::to_string(){
    return val;
}

void VariableExpr::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = value(Step::env);
    Step::cont = Step::cont;
}
////////////////////// LET-IN METHODS ////////////////////////////////////

//The LetExpr object constructor takes the variable name in the form of a string and
//two expressions. The first follows the variable name and the second is in the body
LetExpr::LetExpr(std::string var, PTR(Expr) expr1, PTR(Expr) expr2){
    this->var = var;
    this->expr1 = expr1;
    this->expr2 = expr2;
}

//LetExpr test of equality casts the input expression to a LetExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool LetExpr::equals(PTR(Expr) exp){
    PTR(LetExpr) l = CAST(LetExpr)(exp);
    if (l == NULL){
        return false;
    }else{
        return (expr1->equals(l->expr1) && expr2->equals(l->expr2) && var == l->var);
    }
}

//Returns the value following the substitution of the body expression with the first expression
PTR(Val) LetExpr::value(PTR(Env) env){
    PTR(Val) rhs_val = expr1->value(env);
    PTR(Env) new_env = NEW(ExtendedEnv) (var, rhs_val, env);
    return expr2 -> value(new_env);
}

//Tests if the variable input matches the member variable.
//If not than the member expressions are substituted
PTR(Expr) LetExpr::subst(std::string var, PTR(Val) expr){
    PTR(LetExpr) out = NEW(LetExpr)(THIS->var, expr1, expr2);
    if(var != out->var ){
        out->expr2 = expr2->subst(var, expr);
        out->expr1 = expr1->subst(var, expr);
        return out;
    }
    else{
        out->expr1 = expr1->subst(var, expr);
        return out;
    }
}

//LeIn always contains are variable, returns true
bool LetExpr::containsVar(){
    return true;
}

//If the body expression contains a variable and the first expression does not
// the first expression is substituted into the body and optimize is called again.
//If the body expression contains a variable a NEW(LetExpr) object is constructed with
// optimize being called on the body expression. Otherwise a NEW(NumberExpr) is constructed
//and returned as an Expr
PTR(Expr) LetExpr::optimize(){
    PTR(LetExpr) out = NEW(LetExpr)(THIS->var, expr1, expr2);
    out->expr1 = expr1->optimize();
    if(out->expr2->containsVar() && !out->expr1->containsVar()){
        return out->expr2->subst(out->var, (out->expr1->value(NEW(EmptyEnv)())))->optimize();
    }else if(out->expr2->containsVar()){
        return NEW(LetExpr)(out->var, out->expr1, out->expr2->optimize());
    }else{
        return out->value(NEW(EmptyEnv)())->to_expr();
    }
}

std::string LetExpr::to_string(){
    return "_let " + var + " = " + expr1->to_string() + " _in " + expr2->to_string();
}

void LetExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = expr1;
    Step::env = Step::env;
    Step::cont = NEW(LetBodyCont)(var, expr2, Step::env, Step::cont);
}

////////////////////// BoolExpr  METHODS ////////////////////////////////////
BoolExpr::BoolExpr(bool rep) {
  this->rep = rep;
}

bool BoolExpr::equals(PTR(Expr)e) {
  PTR(BoolExpr) b = CAST(BoolExpr)(e);
  if (b == NULL)
    return false;
  else
    return rep == b->rep;
}

PTR(Val) BoolExpr::value(PTR(Env) env) {
  return NEW(BoolVal)(rep);
}

PTR(Expr)BoolExpr::subst(std::string var, PTR(Val) new_val) {
  return NEW(BoolExpr)(rep);
}

PTR(Expr)BoolExpr::optimize() {
  return NEW(BoolExpr)(rep);
}

bool BoolExpr::containsVar() {
  return false;
}

std::string BoolExpr::to_string(){
    if(rep){
        return "_true";
    }
    return "_false";
}

void BoolExpr::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = NEW(BoolVal)(rep);
    Step::cont = Step::cont;
}
////////////////////// COMP METHODS ////////////////////////////////////
//The CompExpr constructor sets the lhs and rhs member variables
CompExpr::CompExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

//CompExpr test of equality casts the input expression to an CompExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool CompExpr::equals(PTR(Expr)e) {
    PTR(CompExpr) a = CAST(CompExpr)(e);
    if (a == NULL){
        return false;
    }else{
        return (lhs->equals(a->lhs) && rhs->equals(a->rhs));
    }
}

//Returns a NEW(BoolVal) comparing lhs to rhs
PTR(Val) CompExpr::value(PTR(Env) env){
    return NEW(BoolVal)(lhs->value(env)->equals(rhs->value(env)));
}

//Returns a NEW(CompExpr) with the lhs and rhs substituted
PTR(Expr) CompExpr::subst(std::string var, PTR(Val) new_val){
    return NEW(CompExpr)(lhs->subst(var, new_val),rhs->subst(var, new_val));
}

//Determines if either the lhs or rhs contain a variable
bool CompExpr::containsVar(){
    return (lhs->containsVar() || rhs->containsVar());
}

//Optimize is called on both lhs and rhs to reduce. If the CompExpr
//object does not contain a variable a NEW(NumberExpr) is returned else
//THIS is returned, avoiding optimization where there is a variable
PTR(Expr) CompExpr::optimize(){

    if(lhs->containsVar() || rhs->containsVar()){
        return NEW(CompExpr)(lhs->optimize(), rhs->optimize());
    }else{
        return NEW(BoolExpr)(lhs->value(NEW(EmptyEnv)())->equals(rhs->value(NEW(EmptyEnv)())));
    }
}

std::string CompExpr::to_string(){
    return lhs->to_string() + " == " + rhs->to_string();
}

void CompExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenCompCont)(rhs, Step::env, Step::cont);
}
////////////////////// IF THEN ELSE METHODS ////////////////////////////////////

//The LetExpr object constructor takes the variable name in the form of a string and
//two expressions. The first follows the variable name and the second is in the body
IfExpr::IfExpr(PTR(Expr) ifExpr, PTR(Expr) thenExpr, PTR(Expr) elseExpr){
    this->ifExpr = ifExpr;
    this->thenExpr = thenExpr;
    this->elseExpr = elseExpr;
}

//LetExpr test of equality casts the input expression to a LetExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool IfExpr::equals(PTR(Expr) exp){
    PTR(IfExpr) l = CAST(IfExpr)(exp);
    if (l == NULL){
        return false;
    }else{
        return (ifExpr->equals(l->ifExpr) && thenExpr->equals(l->thenExpr) && elseExpr == l->elseExpr);
    }
}

//Returns the value following the substitution of the body expression with the first expression
PTR(Val) IfExpr::value(PTR(Env) env){
    if(ifExpr->value(env)->equals(NEW(BoolVal)(true))){
        return thenExpr->value(env);
    }
    else if(ifExpr->value(env)->equals(NEW(BoolVal)(false))){
        return elseExpr->value(env);
    }else{
        throw std::runtime_error("Did not return true or false \n");
    }
}

//Tests if the variable input matches the member variable.
//If not than the member expressions are substituted
PTR(Expr) IfExpr::subst(std::string var, PTR(Val) expr){
    return NEW(IfExpr)(THIS->ifExpr->subst(var, expr), THIS->thenExpr->subst(var, expr), THIS->elseExpr->subst(var, expr));
}

//LeIn always contains are variable, returns true
bool IfExpr::containsVar(){
    return ifExpr->containsVar() || thenExpr->containsVar() || elseExpr->containsVar();
}

//If the body expression contains a variable and the first expression does not
// the first expression is substituted into the body and optimize is called again.
//If the body expression contains a variable a NEW(LetExpr) object is constructed with
// optimize being called on the body expression. Otherwise a NEW(NumberExpr) is constructed
//and returned as an Expr
PTR(Expr) IfExpr::optimize(){
    PTR(IfExpr) out = NEW(IfExpr)(THIS->ifExpr, THIS->thenExpr, THIS->elseExpr);
    if(out->ifExpr->optimize()->containsVar()){
        return NEW(IfExpr)(out->ifExpr->optimize(), out->thenExpr->optimize(), out->elseExpr->optimize());
    }
    else{
        if(out->ifExpr->value(NEW(EmptyEnv)())->equals(NEW(BoolVal)(true))){
            return out->thenExpr->optimize();
        }
        else if(out->ifExpr->value(NEW(EmptyEnv)())->equals(NEW(BoolVal)(false))){
            return out->elseExpr->optimize();
        }
        else{
            throw std::runtime_error("Incorrect if else \n");
        }
    }
    return out;
}

std::string IfExpr::to_string(){
    return "_if " + ifExpr->to_string() + " _then " + thenExpr->to_string() + " _else " + elseExpr->to_string();
}

void IfExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = ifExpr;
    Step::env = Step::env;
    Step::cont = NEW(IfBranchCont)(thenExpr, elseExpr, Step::env, Step::cont);
}
////////////////////// FUN EXPR ELSE METHODS ////////////////////////////////////

//The FunExpr object constructor takes the variable name in the form of a string and
//two expressions. The first follows the arg and the second is in the body
FunExpr::FunExpr(std::string arg, PTR(Expr) body){
    this->arg = arg;
    this->body = body;
}

//FunExpr test of equality casts the input expression to a FunExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool FunExpr::equals(PTR(Expr) exp){
    PTR(FunExpr) l = CAST(FunExpr)(exp);
    if (l == NULL){
        return false;
    }else{
        return (THIS->arg == (l->arg) && THIS->body->equals(l->body));
    }
}

//Returns the value following the substitution of the body expression with the first expression
PTR(Val) FunExpr::value(PTR(Env) env){
    return NEW(FunVal)(THIS->arg, THIS->body, env);
}

//Tests if the variable input matches the member variable.
//If not than the member expressions are substituted
PTR(Expr) FunExpr::subst(std::string var, PTR(Val) expr){
    PTR(FunExpr) out = NEW(FunExpr)(arg, body);
    if(arg == var){
        return out->body->subst(arg, expr);
    }
    return out;
}

//FunExpr always contains are variable, returns true
bool FunExpr::containsVar(){
    return true;
}

//Returns a NEW(FunExpr) with the body optimized
PTR(Expr) FunExpr::optimize(){
    return NEW(FunExpr)(THIS->arg, THIS->body->optimize());
}

std::string FunExpr::to_string(){
    return "(_fun (" + arg + ")" + body->to_string() + ")";
}

void FunExpr::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = NEW(FunVal)(arg, body, Step::env);
    Step::cont = Step::cont;
}
////////////////////// CALL EXPR ELSE METHODS ////////////////////////////////////

//The CallExpr object constructor takes an expression of to be called and an expression
//for the actual argument
CallExpr::CallExpr(PTR(Expr) toBeCalled, PTR(Expr) actualArg){
    this->toBeCalled = toBeCalled;
    this->actualArg = actualArg;
}

//LetExpr test of equality casts the input expression to a LetExpr
//then checks for  Null. If not NUll returns true or false based on
//whether or not the values are equal
bool CallExpr::equals(PTR(Expr) exp){
    PTR(CallExpr) l = CAST(CallExpr)(exp);
    if (l == NULL){
        return false;
    }else{
        return (THIS->toBeCalled->equals(l->toBeCalled) && THIS->actualArg->equals(l->actualArg));
    }
}

//Returns the value following the substitution of the body expression with the first expression
PTR(Val) CallExpr::value(PTR(Env) env){
    return THIS->toBeCalled->value(env)->call(actualArg->value(env));
}

//Tests if the variable input matches the member variable.
//If not than the member expressions are substituted
PTR(Expr) CallExpr::subst(std::string var, PTR(Val) expr){
    PTR(CallExpr) out = NEW(CallExpr)(toBeCalled->subst(var, expr), actualArg->subst(var, expr));
    return out;
}

//LeIn always contains are variable, returns true
bool CallExpr::containsVar(){
    return true;
}

//If the body expression contains a variable and the first expression does not
// the first expression is substituted into the body and optimize is called again.
//If the body expression contains a variable a NEW(LetExpr) object is constructed with
// optimize being called on the body expression. Otherwise a NEW(NumberExpr) is constructed
//and returned as an Expr
PTR(Expr) CallExpr::optimize(){
    return NEW(CallExpr)(THIS->toBeCalled->optimize(), THIS->actualArg->optimize());
}

std::string CallExpr::to_string(){
    return "(" + toBeCalled->to_string() + "(" + actualArg->to_string() + "))";
}

void CallExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = toBeCalled;
    Step::cont = NEW(ArgThenCallCont)(actualArg, Step::env, Step::cont);
}

///////////////////////////// EXPR TESTS //////////////////////////////////

//TEST_CASE( "EQUALS TESTS" ) {
//    CHECK((NEW(NumberExpr)(1))->equals(NEW(NumberExpr)(1)) );
//    CHECK(!(NEW(NumberExpr)(1))->equals(NEW(NumberExpr)(2)) );
//    CHECK(!(NEW(NumberExpr)(1))->equals(NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(4))) );
//    CHECK((NEW(AddExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(1)))->equals(NEW(AddExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(1))));
//    CHECK(!(NEW(AddExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(2)))->equals(NEW(AddExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(1))));
//    CHECK((NEW(MultExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(1)))->equals(NEW(MultExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(1))));
//    CHECK(!(NEW(AddExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(1)))->equals(NEW(MultExpr)(NEW(NumberExpr)(10), NEW(NumberExpr)(1))));
//    CHECK(!(NEW(VariableExpr)("var"))->equals(NEW(NumberExpr)(0)) );//change to run time error
//    CHECK((NEW(VariableExpr)("var"))->equals(NEW(VariableExpr)("var")) );
//    CHECK(!(NEW(NumberExpr)(1))->equals(NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(4))) );
//    CHECK((NEW(LetExpr)("x", NEW(NumberExpr)(5), NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(2))))
//          ->equals(NEW(LetExpr)("x", NEW(NumberExpr)(5), NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(2)))));
//    CHECK(!(NEW(LetExpr)("x", NEW(NumberExpr)(5), NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(2))))
//          ->equals(NEW(LetExpr)("x", NEW(NumberExpr)(5), NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(3)))));
//    CHECK((NEW(CallExpr)(NEW(VariableExpr)("f"), NEW(NumberExpr)(10)))->equals(NEW(CallExpr)(NEW(VariableExpr)("f"), NEW(NumberExpr)(10))));
//    CHECK(!(NEW(CallExpr)(NEW(VariableExpr)("f"), NEW(NumberExpr)(10)))->equals(NEW(CallExpr)(NEW(VariableExpr)("f"), NEW(NumberExpr)(100))));
//    CHECK(!(NEW(CallExpr)(NEW(VariableExpr)("f"), NEW(NumberExpr)(10)))->equals(NEW(CallExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(10))));
//    CHECK((NEW(FunExpr)("x", NEW(MultExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(1))))->equals(NEW(FunExpr)("x", NEW(MultExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(1)))));
//    CHECK(!(NEW(FunExpr)("x", NEW(MultExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(1))))->equals(NEW(FunExpr)("x", NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(1)))));
//    CHECK(!(NEW(FunExpr)("x", NEW(MultExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(1))))->equals(NEW(CallExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(10))));
//}
//
//TEST_CASE( "VALUE TESTS" ) {
////CHECK(((NEW(NumberExpr)(55))->value(NEW(EmptyEnv)())))->equals((NEW(NumberExpr)(55))->value(NEW(EmptyEnv)())));
//
//    CHECK(((NEW(NumberExpr)(55))->value(NEW(EmptyEnv)())) != ((NEW(NumberExpr)(5))->value(NEW(EmptyEnv)())));
//    CHECK(((NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)()))->equals((NEW(MultExpr)(NEW(NumberExpr)(4), NEW(NumberExpr)(1)))->value(NEW(EmptyEnv)())));
//    CHECK(((NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)()))->equals((NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)())));
//    CHECK(((NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)())) != ((NEW(MultExpr)(NEW(NumberExpr)(4), NEW(NumberExpr)(3)))->value(NEW(EmptyEnv)())));
//    CHECK(((NEW(AddExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)()))->equals((NEW(AddExpr)(NEW(NumberExpr)(3), NEW(NumberExpr)(1)))->value(NEW(EmptyEnv)())));
//    CHECK(((NEW(AddExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)()))->equals((NEW(AddExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)())));
//    CHECK(((NEW(AddExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(2)))->value(NEW(EmptyEnv)())) != ((NEW(MultExpr)(NEW(NumberExpr)(4), NEW(NumberExpr)(3)))->value(NEW(EmptyEnv)())));
//}
//
//TEST_CASE("SUBSTITUTE TESTS"){
//    CHECK((NEW(NumberExpr)(10)) -> subst("sub", NEW(NumVal)(3)) -> equals(NEW(NumberExpr)(10)));
//    CHECK(((NEW(MultExpr)(NEW(NumberExpr)(2), NEW(VariableExpr)("sub")))) -> subst("sub", NEW(NumVal)(3)) -> equals(NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(3))));
//    CHECK(!((NEW(AddExpr)(NEW(NumberExpr)(2), NEW(VariableExpr)("sub")))) -> subst("sub", NEW(NumVal)(3)) -> equals(NEW(MultExpr)(NEW(NumberExpr)(2), NEW(NumberExpr)(3))));
//    CHECK(!((NEW(LetExpr)("x", NEW(NumberExpr)(5), NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(2))))) -> subst("y", NEW(NumVal)(3))
//          -> equals(NEW(LetExpr)("x", NEW(NumberExpr)(3), NEW(AddExpr)(NEW(VariableExpr)("x"), NEW(NumberExpr)(3)))));
//}


