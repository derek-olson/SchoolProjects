//
//  Functions.hpp
//  FractionClass
//
//  Created by Derek Olson on 9/10/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <stdio.h>
#include <string>

class Fraction{
public:
    Fraction();
    Fraction(long n, long d);
    long getNumerator();
    long getDenominator();
    Fraction plus(Fraction rhs);
    Fraction minus(Fraction rhs);
    Fraction times(Fraction rhs);
    Fraction dividedBy(Fraction rhs);
    Fraction reciprocal();
    std::string toString();
    double toDouble();
    
    Fraction& operator += (Fraction rhs);
    Fraction& operator -= (Fraction rhs);
    Fraction& operator *= (Fraction rhs);
    Fraction& operator /= (Fraction rhs);
    
private:
    long gcd();
    void reduce();
    long numerator;
    long denominator;
};

#endif /* Functions_hpp */

//double toDouble() - Returns a (double precision) floating point number that is the approximate value of this fraction, printed as a real number.
