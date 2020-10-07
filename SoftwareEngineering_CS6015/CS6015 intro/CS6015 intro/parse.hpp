//
//  parse.hpp
//  CS6015 intro
//
//  Created by Derek Olson on 1/20/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#ifndef parse_hpp
#define parse_hpp

#include <stdio.h>
#include <string>
#include "expr.hpp"
#include "pointer.h"

PTR(Expr) parse(std::istream &in);

static PTR(Expr) parse_expr(std::istream &in);

static PTR(Expr) parse_comparg(std::istream &in);

static PTR(Expr) parse_addend(std::istream &in);

static PTR(Expr) parse_number_or_paren(std::istream &in);

static PTR(Expr) parse_number(std::istream &in);

static PTR(Expr) parse_variable(std::istream &in);

static char peek_next(std::istream &in);

static PTR(Expr) parse_let(std::istream &in);

static std::string parse_strings(std::istream &in);

static std::string parse_str_error(std::string s);

static PTR(Expr) parse_str(std::string s);

#endif /* parse_hpp */
