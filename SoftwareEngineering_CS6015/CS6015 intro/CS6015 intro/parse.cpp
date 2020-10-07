//
//  parse.cpp
//  CS6015 intro
//
//  Created by Derek Olson on 1/20/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//


#include <iostream>
#include <sstream>

//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parse.hpp"
#include "expr.hpp"
#include "pointer.h"
#include "value.hpp"
#include "env.hpp"

/* The grammar that we're trying to parse is
     <expr> = <addend>
            | <expr> + <expr>
     <addend> = <number>
              | (<expr>)
              | <addend> * <addend>
   On further reflection, we can adjust this one step closer to a
   parser, since we're happy to have left-associative `+` and `*`:
     <expr> = <addend>
            | <addend> + <expr>
     <addend> = <number-or-paren>
              | <number-or-paren> * <addend>
     <number-or-paren> = <number>
                       | (<expr>)
   This revised deifnition of <expr> matches the same strings as the
   original, but it more directly suggests a parsing strategy:
   * An <expr> always has to start with an <addend>. We may immediate
     see a `+`, in which case there's another <expr>, and that's all.
     If we don't see a `+`, then we must be done with this <expr>.
   * An <addend> always has to start with an <number-or-paren>. We may
     see a `*`, in which case there's another <addend> and that's all.
     If we don't see a `*`, then we must be done with this <addend>.
   * For a <number-or-paren>, we can tell whether it's a <number> or
     <paren> by looking at one character.
   The parser can work by having a function for every <....> name, and
   the functions call each other to reflect the way the <....>
   grammars refer to each other. For example, the <expr> function will
   start by calling the <addend> function, and then it will check for
   a `+` and call the <expr> function (itself) if it finds a `+`.
*/

//This method kicks everything off by calling parse expression.
//If the end of file is not reached appropriately than an error
//is thrown. This function returns an expression.
PTR(Expr) parse(std::istream &in) {

    PTR(Expr) exp = parse_expr(in);
  
    peek_next(in);
    if (!in.eof()) {
        throw std::runtime_error("Expected end of file \n");
    }
    return exp;
}

//This function initially calls parse addened, which evaluates for numbers
//or parens and multiplication. Following if addition is found the function calls itself.
//A NEW(Add) class is constructed and an expression is returned.
static PTR(Expr) parse_expr(std::istream &in) {
    PTR(Expr) exp = parse_comparg(in);
    char c = peek_next(in);
    if (c == '=') {
        in.get();
        if(peek_next(in) == '='){
            in.get();
            PTR(Expr) rhs = parse_expr(in);
            exp = NEW(CompExpr)(exp, rhs);
        }
        else{
            throw std::runtime_error("Expected equals sign \n");
        }
    }
    return exp;
}

//parse comparg
static PTR(Expr) parse_comparg(std::istream &in){
    PTR(Expr) exp = parse_addend(in);
    char c = peek_next(in);
    if (c == '+') {
        in.get();
        PTR(Expr) rhs = parse_comparg(in);
        exp = NEW(Add)(exp, rhs);
    }
    return exp;
}

static PTR(Expr) parse_multicand(std::istream &in){
    PTR(Expr) exp = parse_number_or_paren(in);
    while(peek_next(in) == '('){
        in.get();
        PTR(Expr) actual_arg = parse_expr(in);
        exp = NEW(CallExpr)(exp, actual_arg);
        if(peek_next(in) != ')'){
            throw std::runtime_error("Expected closed parenthesis \n");
        }
        in.get();
    }
    return exp;
}

//This function intially evaluates for numbers and parens
//If multiplication is found the function calls itself
//An expression is returned
static PTR(Expr) parse_addend(std::istream &in) {
    PTR(Expr) exp = parse_multicand(in);
    char c = peek_next(in);

    if (c == '*') {
        c = in.get();
        PTR(Expr) rhs = parse_addend(in);
        exp = NEW(Mult)(exp, rhs);
  }
    return exp;
}

//Helper function to return strings from istream
static std::string parse_strings(std::istream &in){
    std::string string = "";
    while (true) {
       char c = in.peek();
       if (!isalpha(c)){
            break;
       }
      string += in.get();
    }
    return string;
}

//Helper function to parse let tokens. Returns LetIn object.
static PTR(Expr) parse_let(std::istream &in){
    char c;
    //consume space after let
    c = peek_next(in);
    //get the variable as a string
    std::string var = parse_strings(in);
    //consume the space after the variable
    c = peek_next(in);
    //check for =
    if(c != '='){
        throw std::runtime_error("Expected equals sign not found \n");
    }
    //consume =
    c = in.get();
    //consume any space
    c = peek_next(in);
    // get the first expression
    PTR(Expr) expr1 = parse_expr(in);
    //consume space
    c = peek_next(in);
    if(c != '_'){
        throw std::runtime_error("Expected underscore \n");
    }
    //consume _
    c = in.get();
    //check for in following underscore
    std::string in_str = parse_strings(in);
    if(in_str != "in"){
        throw std::runtime_error("Expected the word in \n");
    }
    //consume space
    c = peek_next(in);

    // parse the second expression
    PTR(Expr) expr2 = parse_expr(in);
    //contruct NEW(LetIn) object and return it
    PTR(LetIn) let_out = NEW(LetIn)(var, expr1, expr2);
    return let_out;
}

static PTR(Expr) parseIf(std::istream &in){
    PTR(Expr) ifexpr;
    PTR(Expr) thenexpr;
    PTR(Expr) elseexpr;
    
    char c;
    //consume space after if
    c = peek_next(in);
    
    //get the if expression as a string
    ifexpr = parse_expr(in);
    
    //consume the space after the variable
    c = peek_next(in);
    //check for =
    if(c != '_'){
        throw std::runtime_error("Expected underscore \n");
    }
    in.get();
    //check for then
    std::string then = parse_strings(in);
    if(then != "then"){
        throw std::runtime_error("Expected then \n");
    }
    
    //get the then expression
    thenexpr = parse_expr(in);
    
    //consume the space after the variable
    c = peek_next(in);
    //check for _
    in.get();
    if(c != '_'){
        throw std::runtime_error("Expected underscore \n");
    }
    
    //check for else
    std::string els = parse_strings(in);
    if(els != "else"){
        throw std::runtime_error("Expected else \n");
    }
    
    elseexpr = parse_expr(in);
    
    return NEW(IfElse)(ifexpr, thenexpr, elseexpr);
}

//Parse functions
static PTR(Expr) parse_fun(std::istream &in){
    std::string arg;
    PTR(Expr) body;
    char c;
    
    c = peek_next(in);
    if(c != '('){
        throw std::runtime_error("Expected open parenthesis \n");
    }
    in.get();
    arg = parse_strings(in);
    
    c = peek_next(in);
    if(c != ')'){
        throw std::runtime_error("Expected close parenthesis \n");
    }
    in.get();
    body = parse_expr(in);
    
    PTR(Expr) out = NEW(FunExpr)(arg, body);
    return out;
}

//This function evaluates whether the input is a number or a paren
//If the input is an opening paren it consumes the input and parses the expression
//If no closing paren is found than an exception is thrown
//Otherwise the method contiues to evaluate for numbers and variables
static PTR(Expr) parse_number_or_paren(std::istream &in) {
    PTR(Expr) exp;

    char c = peek_next(in);
  
    if (c == '(') {
        c = in.get();
        exp = parse_expr(in);
        c = peek_next(in);
        if(c != ')'){
            throw std::runtime_error("Expected a close parenthesis \n");
        }
        else{
            c = in.get();
        }
    }else if (isdigit(c) || c == '-') {
        exp = parse_number(in);
    }else if(isalpha(c)){
        exp = parse_variable(in);
    }else if(c == '_'){
        c = in.get();
        std::string s = parse_strings(in);
        if( s == "let"){
            exp = parse_let(in);
        }
        else if(s == "fun"){
            exp = parse_fun(in);
        }
        else if(s == "true"){
            return NEW(BoolExpr)(true);
        }
        else if(s == "false"){
            return NEW(BoolExpr)(false);
        }
        else if (s == "if"){
            exp = parseIf(in);
        }
        else{
            throw std::runtime_error("Unexpected keyword \n");
        }
    }
    else {
        throw std::runtime_error("Expected a digit or open parenthesis \n");
    }
    return exp;
}

//This function reads in an integer and returns a Number
static PTR(Expr) parse_number(std::istream &in) {
    int exp;
    in >> exp;
    return NEW(Number)(exp);
}

//This function takes an input stream and returns an expression.
//Specifically it looks for a variable in an expression by evaluating
//whether an input is a character, and continues to read in contiguous characters
//The return is of the Variable class, which inherets from Expr
static PTR(Expr) parse_variable(std::istream &in) {
    std::string var = "";
    while (true) {
        char c = in.peek();
        if (!isalpha(c)){
             break;
        }
       var += in.get();
     }
     return NEW(Variable)(var);
}

// This function peeks the next character.
// It ignores whitespace.
static char peek_next(std::istream &in) {
    char c = in.peek();
    while(c == ' ' || c == '\n'){
        in.get();
        c = in.peek();
    }
    return c;
}

/* for tests */
static PTR(Expr) parse_str(std::string s) {
    std::istringstream in(s);
    return parse(in);
}

/* for tests */
static std::string parse_str_error(std::string s) {
    std::istringstream in(s);
    std::ostringstream err(std::ios_base::out);
    (void)parse(in);
    return err.str();
}

TEST_CASE( "PARSE TESTS" ) {
    PTR(Expr) ten_plus_one = NEW(Add)(NEW(Number)(10), NEW(Number)(1));
  
//    CHECK_THROWS ( parse_str_error(" ( 1 ") == "Expected a close parenthesis \n" );

    //These tests check for appropriate expression outcomes for all arrangements of classes and include varing use of parens and variables
    CHECK( parse_str("10")->equals(NEW(Number)(10)) );
    CHECK( parse_str("(10)")->equals(NEW(Number)(10)) );
    CHECK( parse_str("10+1")->equals(ten_plus_one) );
    CHECK( parse_str("(10+1)")->equals(ten_plus_one) );
    CHECK( parse_str("(10)+1")->equals(ten_plus_one) );
    CHECK( parse_str("10+(1)")->equals(ten_plus_one) );
    CHECK( parse_str("1+2*3")->equals(NEW(Add)(NEW(Number)(1),NEW(Mult)(NEW(Number)(2), NEW(Number)(3)))) );
    CHECK( parse_str("1*2+3")->equals(NEW(Add)(NEW(Mult)(NEW(Number)(1), NEW(Number)(2)),NEW(Number)(3))) );
    CHECK( parse_str("4*2*3")->equals(NEW(Mult)(NEW(Number)(4),NEW(Mult)(NEW(Number)(2), NEW(Number)(3)))) );
    CHECK( parse_str("4+2+3")->equals(NEW(Add)(NEW(Number)(4),NEW(Add)(NEW(Number)(2), NEW(Number)(3)))) );
    CHECK( parse_str("4*(2+3)")->equals(NEW(Mult)(NEW(Number)(4),NEW(Add)(NEW(Number)(2), NEW(Number)(3)))) );
    CHECK( parse_str("(2+3)*4")->equals(NEW(Mult)(NEW(Add)(NEW(Number)(2), NEW(Number)(3)),NEW(Number)(4))) );
    CHECK( parse_str("xyz")->equals(NEW(Variable)("xyz")) );
    CHECK( parse_str("xyz+1")->equals(NEW(Add)(NEW(Variable)("xyz"), NEW(Number)(1))) );

    //These tests check for incorrect expressions and appropriate error handling
//    CHECK_THROWS ( parse_str_error("!") == "Expected a digit or open parenthesis \n" );
//    CHECK_THROWS ( parse_str_error("(1") == "Expected a close parenthesis \n" );

    //These tests include whitespace
    CHECK( parse_str(" 10 ")->equals(NEW(Number)(10)) );
    CHECK( parse_str(" (  10 ) ")->equals(NEW(Number)(10)) );
    CHECK( parse_str(" 10  + 1")->equals(ten_plus_one) );
    CHECK( parse_str(" ( 10 + 1 ) ")->equals(ten_plus_one) );
    CHECK( parse_str(" 11 * ( 10 + 1 ) ")->equals(NEW(Mult)(NEW(Number)(11),ten_plus_one)) );
    CHECK( parse_str(" ( 11 * 10 ) + 1 ")->equals(NEW(Add)(NEW(Mult)(NEW(Number)(11), NEW(Number)(10)),NEW(Number) (1))) );
    CHECK( parse_str(" 1 + 2 * 3 ")->equals(NEW(Add)(NEW(Number)(1),NEW(Mult)(NEW(Number)(2), NEW(Number)(3)))) );

    //These tests check for incorrect expressions and appropriate error handling with whitespace included
//    CHECK_THROWS ( parse_str_error(" ! ") == "Expected a digit or open parenthesis \n" );
//    CHECK_THROWS ( parse_str_error(" ( 1 ") == "Expected a close parenthesis \n" );
//    CHECK_THROWS ( parse_str_error(" 1 )") == "Expected end of file \n" );
    CHECK( parse_str("_fun(x)(10)")->equals(NEW(FunExpr)("x", NEW(Number)(10))) );
    
    CHECK( parse_str("_if _true _then _let f = _fun(x) x + 1 _in f(10) _else _let f = _fun(x) x + 1 _in f(100)")->value(NEW(EmptyEnv)())->equals(NEW(NumVal)(11)));
    CHECK( parse_str("_if _false _then _let f = _fun(x) x + 1 _in f(10) _else _let f = _fun(x) x + 1 _in f(100)")->value(NEW(EmptyEnv)())->equals(NEW(NumVal)(101)));
    CHECK(parse_str("( _fun(x) 2+x)(3)")->value(NEW(EmptyEnv)())->equals(NEW(NumVal)(5)));
}
    

TEST_CASE("OPTIMIZE TESTS"){
    CHECK( parse_str("_let x = 5 _in _let y = z + 2 _in x + y + (2 * 3)")->optimize()->equals(NEW(LetIn)("y", NEW(Add)(NEW(Variable)("z"), NEW(Number)(2)),NEW(Add)(NEW(Number)(5), NEW(Add)(NEW(Variable)("y"), NEW(Number)(6))))));
    CHECK( parse_str("_let x = 7 _in _let x = x _in x")->optimize()->equals(NEW(Number)(7)));
    CHECK( parse_str("_if _true _then _let y = 5 _in y + 3 _else _let y = 10 _in y + 3")->optimize()->equals(NEW(Number)(8)));
//    CHECK_THROWS( parse_str_error("_let x = 5 _ let _y = z + 2 _in x + 4 + (2 * 3)")->optimize()=="invalid expression; in not found");
//    CHECK_THROWS( parse_str_error("_let x = 5 _in let _y  z + 2 _in x + 4 + (2 * 3)")->optimize()=="invalid expression; = not found");
    CHECK(parse_str("_fun(x)(10)")->optimize()->equals(NEW(FunExpr)("x", NEW(Number)(10))));
    CHECK( parse_str("_if _true _then _let f = _fun(x) x + 1 _in f(10) _else _let f = _fun(x) x + 1 _in f(100)")->optimize()->equals(NEW(LetIn)("f", NEW(FunExpr)("x", NEW(Add)(NEW(Variable)("x"), NEW(Number)(1))), NEW(CallExpr)(NEW(Variable)("f"), NEW(Number)(10)))));
    CHECK( parse_str("_if _false _then _let f = _fun(x) x + 1 _in f(10) _else _let f = _fun(x) x + 1 _in f(100)")->optimize()->equals(NEW(LetIn)("f", NEW(FunExpr)("x", NEW(Add)(NEW(Variable)("x"), NEW(Number)(1))), NEW(CallExpr)(NEW(Variable)("f"), NEW(Number)(100)))));
    CHECK( parse_str("_if _false _then _let f = _fun(x) x + 1 _in f(10) _else _let f = _fun(x) x * 1 _in f(100)")->optimize()->equals(NEW(LetIn)("f", NEW(FunExpr)("x", NEW(Mult)(NEW(Variable)("x"), NEW(Number)(1))), NEW(CallExpr)(NEW(Variable)("f"), NEW(Number)(100)))));
    CHECK(!parse_str("_let x =5 _in x + y")->optimize()->equals(NEW(Add)(NEW(Number)(5), NEW(Variable)("5"))));
}
