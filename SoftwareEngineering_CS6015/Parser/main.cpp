//
//  main.cpp
//  CS6015 intro
//
//  Created by Derek Olson on 1/21/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

  
#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "parse.hpp"
#include "expr.hpp"
#include "value.hpp"
#include "env.hpp"
#include "catch.hpp"
#include "step.hpp"


int main(int argc, char **argv)
{
    PTR(Expr) e;
    //Catch::Session().run(argc, argv);
    try {
        e = parse(std::cin);
        if(argc < 2){
            std::cout << e->value(NEW(EmptyEnv)())->to_string()+"\n";
            return 0;
        }
        else if (strncmp(argv[1], "_optimize", 10) == 0) {
            std::cout << e->optimize()->to_string()+"\n";
            return 0;
        }
        else if (strncmp(argv[1], "_interp", 10) == 0) {
            std::cout << e->value(NEW(EmptyEnv)())->to_string()+"\n";
            return 0;
        }
        else if(strncmp(argv[1], "_step", 10) == 0){
            std::cout << Step::interp_by_steps(e) ->to_string()+"\n";
        }
        else{
            throw std::runtime_error("Invalid command line argument \n");
        }
    } catch (std::runtime_error& error) {
        std::cerr << error.what();
    }
  return 0;
}
