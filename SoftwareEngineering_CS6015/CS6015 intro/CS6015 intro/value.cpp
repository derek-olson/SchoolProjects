//
//  value.cpp
//  CS6015 intro
//
//  Created by Derek Olson on 2/4/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#include "value.hpp"
#include <stdexcept>
#include "catch.hpp"
#include "pointer.h"
#include "expr.hpp"
#include "env.hpp"
#include "cont.hpp"

NumVal::NumVal(int rep) {
  this->rep = rep;
}

bool NumVal::equals(PTR(Val)other_val) {
  PTR(NumVal)other_num_val = CAST(NumVal)(other_val);
  if (other_num_val == nullptr)
    return false;
  else
    return rep == other_num_val->rep;
}

PTR(Val)NumVal::add_to(PTR(Val)other_val) {
  PTR(NumVal)other_num_val = CAST(NumVal)(other_val);
  if (other_num_val == nullptr)
    throw std::runtime_error("not a number \n");
  else
    return NEW(NumVal)((unsigned)rep + (unsigned)other_num_val->rep);
}

PTR(Val)NumVal::mult_with(PTR(Val)other_val) {
  PTR(NumVal)other_num_val = CAST(NumVal)(other_val);
  if (other_num_val == nullptr)
    throw std::runtime_error("not a number \n");
  else
    return NEW(NumVal)((unsigned)rep * (unsigned)other_num_val->rep);
}

PTR(Expr) NumVal::to_expr() {
  return NEW(Number)(rep);
}

std::string NumVal::to_string() {
  return std::to_string(rep);
}

PTR(Val) NumVal::call(PTR(Val) actualArg){
    throw std::runtime_error("ERROR: Invalid call \n");
}

bool NumVal::is_true(){
    throw std::runtime_error("Numbers are not true or false");
}

void NumVal::call_step(PTR(Val) actual_arg_val, PTR(Cont) rest){
    throw std::runtime_error("ERROR: No numval call step");
}

BoolVal::BoolVal(bool rep) {
  this->rep = rep;
}

bool BoolVal::equals(PTR(Val)other_val) {
  PTR(BoolVal)other_bool_val = CAST(BoolVal)(other_val);
  if (other_bool_val == nullptr)
    return false;
  else
    return rep == other_bool_val->rep;
}

PTR(Val)BoolVal::add_to(PTR(Val)other_val) {
  throw std::runtime_error("no adding booleans \n");
}

PTR(Val)BoolVal::mult_with(PTR(Val)other_val) {
  throw std::runtime_error("no multiplying booleans \n");
}

PTR(Expr) BoolVal::to_expr() {
  return NEW(BoolExpr)(rep);
}

std::string BoolVal::to_string() {
  if (rep)
    return "_true";
  else
    return "_false";
}

PTR(Val) BoolVal::call(PTR(Val) actualArg){
    throw std::runtime_error("ERROR: Invalid call \n");
}

bool BoolVal::is_true(){
    return rep;
}

void BoolVal::call_step(PTR(Val) actual_arg_val, PTR(Cont) rest){
    throw std::runtime_error("ERROR: No boolval call step");
}

FunVal::FunVal(std::string formalArg, PTR(Expr) body, PTR(Env) env) {
    this->formalArg = formalArg;
    this->body = body;
    this-> env = env;
}

//FUNCTIONS CANNOT BE COMPARED CHANGE THIS AND TEST BELOW
bool FunVal::equals(PTR(Val)other_val) {
  PTR(FunVal) other_fun_val = CAST(FunVal)(other_val);
  if (other_fun_val == nullptr)
    return false;
  else
    return formalArg == other_fun_val->formalArg && body->equals(other_fun_val->body);
}

PTR(Val)FunVal::add_to(PTR(Val)other_val) {
  throw std::runtime_error("no adding functions \n");
}

PTR(Val)FunVal::mult_with(PTR(Val)other_val) {
  throw std::runtime_error("no multiplying functions \n");
}

PTR(Expr) FunVal::to_expr() {
  return NEW(FunExpr)(formalArg, body);
}

std::string FunVal::to_string() {
    return "[function] \n"; 
}

PTR(Val) FunVal::call(PTR(Val) actualArg){
    return body->value(NEW(ExtendedEnv)(formalArg, actualArg, env));
}

bool FunVal::is_true(){
    throw std::runtime_error("Functions are not true or false");
}

void FunVal::call_step(PTR(Val) actual_arg_val, PTR(Cont) rest){
    Step::mode = Step::interp_mode;
    Step::expr = body;
    Step::env = NEW(ExtendedEnv)(formalArg, actual_arg_val, env);
    Step::cont = rest; 
}

TEST_CASE("values equals") {
    CHECK((NEW(NumVal)(5))->equals(NEW(NumVal)(5)));
    CHECK(!(NEW(NumVal)(7))->equals(NEW(NumVal)(5)));
    CHECK((NEW(BoolVal)(true))->equals(NEW(BoolVal)(true)));
    CHECK(!(NEW(BoolVal)(true))->equals(NEW(BoolVal)(false)));
    CHECK(!(NEW(BoolVal)(false))->equals(NEW(BoolVal)(true)));
    CHECK(!(NEW(NumVal)(7))->equals(NEW(BoolVal)(false)));
    CHECK(!(NEW(BoolVal)(false))->equals(NEW(NumVal)(8)));
    CHECK((NEW(FunVal)("x", NEW(Number)(10), NEW(EmptyEnv)()))->equals(NEW(FunVal)("x", NEW(Number)(10), NEW(EmptyEnv)())));
}

TEST_CASE("add_to") {
    CHECK((NEW(NumVal)(5))->add_to(NEW(NumVal)(8))->equals(NEW(NumVal)(13)));
//    CHECK_THROWS_WITH ((NEW(NumVal)(5))->add_to(NEW(BoolVal)(false)), "not a number");
//    CHECK_THROWS_WITH ((NEW(BoolVal)(false))->add_to(NEW(BoolVal)(false)),"no adding booleans");
//    CHECK_THROWS_WITH ((NEW(FunVal)("x", NEW(Number)(10), NEW(EmptyEnv)()))->add_to(NEW(FunVal)("x", NEW(Number)(10000), NEW(EmptyEnv)())),"no adding functions");
}

TEST_CASE("mult_with") {
    CHECK((NEW(NumVal)(5))->mult_with(NEW(NumVal)(8))->equals(NEW(NumVal)(40)));
//    CHECK_THROWS_WITH((NEW(NumVal)(5))->mult_with(NEW(BoolVal)(false)), "not a number");
//    CHECK_THROWS_WITH((NEW(BoolVal)(false))->mult_with(NEW(BoolVal)(false)), "no multiplying booleans");
//    CHECK_THROWS_WITH((NEW(FunVal)("y", NEW(Number)(10), NEW(EmptyEnv)()))->mult_with(NEW(FunVal)("x", NEW(Number)(46), NEW(EmptyEnv)())),"no multiplying functions");
}

TEST_CASE("value to_expr") {
    CHECK((NEW(NumVal)(5))->to_expr()->equals(NEW(Number)(5)));
    CHECK(!(NEW(NumVal)(5))->to_expr()->equals(NEW(Number)(50)));
    CHECK(!(NEW(NumVal)(5))->to_expr()->equals(NEW(Variable)("five")));
    CHECK((NEW(BoolVal)(true))->to_expr()->equals(NEW(BoolExpr)(true)));
    CHECK((NEW(BoolVal)(false))->to_expr()->equals(NEW(BoolExpr)(false)));
    CHECK(!(NEW(BoolVal)(false))->to_expr()->equals(NEW(BoolExpr)(true)));
    CHECK((NEW(FunVal)("x",NEW(Number)(10), NEW(EmptyEnv)()))->to_expr()->equals(NEW(FunExpr)("x",NEW(Number)(10))));
    CHECK(!(NEW(FunVal)("x",NEW(Number)(10), NEW(EmptyEnv)()))->to_expr()->equals(NEW(FunExpr)("x",NEW(Number)(1))));
}

TEST_CASE("value to_string") {
    CHECK((NEW(NumVal)(5))->to_string() == "5");
    CHECK((NEW(BoolVal)(true))->to_string() == "_true");
    CHECK((NEW(BoolVal)(false))->to_string() == "_false");
}
