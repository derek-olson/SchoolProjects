//
//  tests.m
//  tests
//
//  Created by Derek Olson on 1/21/20.
//  Copyright © 2020 Derek Olson. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "run.h"

@interface test : XCTestCase

@end

@implementation test

- (void)testAll {
  if (!run_tests())
    XCTFail(@"failed");
}

@end
