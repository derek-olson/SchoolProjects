//
//  main.cpp
//  FractionClass
//
//  Created by Derek Olson on 9/10/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//


#include "Functions.hpp"
#include <iostream>
#include <cmath>
using namespace std;


int main(int argc, const char * argv[]) {

    // test default constructor
    Fraction test1 = Fraction();
    assert(test1.getNumerator() == 0);
    assert(test1.getDenominator() == 1);
    
    // test constructor for 2 negative numbers
    Fraction test2 = Fraction(-2,-2);
    assert(test2.getNumerator() == 1);
    assert(test2.getDenominator() == 1);
    
    // test constructor for negative denominator
    Fraction test3 = Fraction(2,-2);
    assert(test3.getNumerator() == -1);
    assert(test3.getDenominator() == 1);
    
    // test that constructor reduces
    Fraction test4 = Fraction(4, 12);
    assert(test4.getNumerator() == 1);
    assert(test4.getDenominator() == 3);
    
    // test addition
    Fraction test5 = test4.plus(test3);
    assert(test5.getNumerator() == -2);
    assert(test5.getDenominator() == 3);
    
    //test subtraction
    Fraction test6 = test4.minus(test3);
    assert(test6.getNumerator() == 4);
    assert(test6.getDenominator() == 3);
    
    //test multiplication
    Fraction test7 = test4.times(test3);
    assert(test7.getNumerator() == -1);
    assert(test7.getDenominator() == 3);
    
    //test division
    Fraction test8 = test4.dividedBy(test3);
    assert(test8.getNumerator() == -1);
    assert(test8.getDenominator() == 3);
    
    //test reciprocal
    Fraction test9 = Fraction(84,98);
    test9.reciprocal();
    assert(test9.getNumerator() == 7);
    assert(test9.getDenominator() == 6);
    
    // test to double
    Fraction test10 = Fraction(3,102);
    double doubleTest = test10.toDouble();
    assert(doubleTest == 0.029411764705882353);
    
    
    
    return 0;
}





