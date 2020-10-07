//
//  run.cpp
//  tests
//
//  Created by Derek Olson on 1/30/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

extern "C" {
#include "run.h"
};

bool run_tests() {
  const char *argv[] = { "arith" };
  return (Catch::Session().run(1, argv) == 0);
}
