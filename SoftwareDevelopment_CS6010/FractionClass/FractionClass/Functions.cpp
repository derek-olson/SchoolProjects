//
//  Functions.cpp
//  FractionClass
//
//  Created by Derek Olson on 9/10/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "Functions.hpp"
#include <string>

// default constructor
Fraction::Fraction(){
    numerator = 0;
    denominator = 1;
};

// construtor that checks for negatives and reduces
Fraction::Fraction(long n, long d){
    if ((n > 0 && d < 0) || (n < 0 && d < 0)){
        n *= -1;
        d *= -1;
    }
    numerator = n;
    denominator = d;
    
    reduce();
};

// method to overload += oerator
Fraction& Fraction::operator+=(Fraction rhs){
    Fraction result = plus(rhs);
    *this = result;
    return *this;
    
}
// method to overload -= oerator
Fraction& Fraction::operator-=(Fraction rhs){
    Fraction result = minus(rhs);
    *this = result;
    return *this;
    
}
// method to overload *= oerator
Fraction& Fraction::operator*=(Fraction rhs){
    Fraction result = times(rhs);
    *this = result;
    return *this;
    
}
// method to overload /= oerator
Fraction& Fraction::operator/=(Fraction rhs){
    Fraction result = dividedBy(rhs);
    *this = result;
    return *this;
    
}
// function to overload + operator
Fraction operator +(Fraction f1, Fraction f2){
    return f1 += f2;
}
//function to overload - operator
Fraction operator -(Fraction f1, Fraction f2){
    return f1 -= f2;
}
//function to overload * operator
Fraction operator *(Fraction f1, Fraction f2){
    return f1 *= f2;
}
//function to overload / operator
Fraction operator /(Fraction f1, Fraction f2){
    return f1 /= f2;
}
//function to overload < operator
bool operator <(Fraction f1, Fraction f2){
    return f1.toDouble() < f2.toDouble();
}
//function to overload > operator
bool operator >(Fraction f1, Fraction f2){
    return f1.toDouble() > f2.toDouble();
}
//function to overload == operator
bool operator ==(Fraction f1, Fraction f2){
    return f1.toDouble() == f2.toDouble();
}
//function to overload >= operator
bool operator >=(Fraction f1, Fraction f2){
    return f1.toDouble() >= f2.toDouble();
}
//function to overload <= operator
bool operator <=(Fraction f1, Fraction f2){
    return f1.toDouble() <= f2.toDouble();
}
//function to overload != operator
bool operator !=(Fraction f1, Fraction f2){
    return f1.toDouble() != f2.toDouble();
}

// a method that gets the numerator
long Fraction::getNumerator(){
    return numerator;
}
// a method that gets the denominator
long Fraction::getDenominator(){
    return denominator;
}

// a method to add two fractions
Fraction Fraction::plus(Fraction rhs){
    Fraction plusFraction(
                      ((numerator * rhs.denominator) + (rhs.numerator * denominator)),(denominator * rhs.denominator));
    return plusFraction;
}

// a method to subtract two fractions
Fraction Fraction::minus(Fraction rhs){
    Fraction minusFraction(((numerator * rhs.denominator) - (rhs.numerator * denominator)), (denominator * rhs.denominator));
    return minusFraction;
}

// a method to multiply two fractions
Fraction Fraction::times(Fraction rhs){
    Fraction timesFraction((numerator * rhs.numerator), (denominator * rhs.denominator));
    return timesFraction;
}

// a method to divide two fractions
Fraction Fraction::dividedBy(Fraction rhs){
    Fraction dividedFraction((numerator * rhs.denominator),(denominator * rhs.numerator));
    return dividedFraction;
}

// a method to return the reciprocal of a fraction
Fraction Fraction::reciprocal(){
    long temp = numerator;
    numerator = denominator;
    denominator = temp;
    Fraction reciprocalFraction(numerator, denominator);
    return reciprocalFraction;
}

// a method to get the decimal value of a fraction
double Fraction::toDouble(){
    double out = numerator/double(denominator);
    return out;
}

// a method to get the greatest common divisor
long Fraction::gcd(){
    long gcd = numerator;
    long remainder = denominator;
    while(remainder != 0) {
        long temp = remainder;
        remainder = gcd % remainder;
        gcd = temp;
    }
    return gcd;
}

// a method to reduce a fraction using the greatest common divisor
void Fraction::reduce(){
    long div = gcd();
    if (div < 0){
        div *= -1;
    }
    numerator = numerator/div;
    denominator = denominator/div;
}

// a methood to turn a fraction into a string
std::string Fraction::toString(){
    // assumes constructor used to create fraction
    std::string outFraction;
    std::string outFractionNumerator = std::to_string(numerator);
    std::string outFractionDenominator = std::to_string(denominator);
    outFraction = outFractionNumerator + "/" + outFractionDenominator;

    return outFraction;
}
