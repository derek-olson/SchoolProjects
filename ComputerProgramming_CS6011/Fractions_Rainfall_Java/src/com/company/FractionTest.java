package com.company;

import static org.junit.jupiter.api.Assertions.*;

class FractionTest {

    @org.junit.jupiter.api.Test
    static void plusTest(){
        Fraction frac1 = new Fraction(1,4);
        Fraction frac2 = new Fraction(1,2);
        Fraction frac3 = new Fraction(3,4);
        String compareFraction = frac3.toString();
        Fraction addedFractions = frac1.plus(frac2);
        String af = addedFractions.toString();
        assertEquals(compareFraction, af);
    }

    @org.junit.jupiter.api.Test
    static void minusTest(){
        Fraction frac1 = new Fraction(3,4);
        Fraction frac2 = new Fraction(1,2);
        Fraction frac3 = new Fraction(1,4);
        String cf = frac3.toString();
        Fraction sf = frac1.minus(frac2);
        String out = sf.toString();
        assertEquals(cf, out);
    }

    @org.junit.jupiter.api.Test
    static void timesTest(){
        Fraction frac1 = new Fraction(1,2);
        Fraction frac2 = new Fraction(1,2);
        Fraction frac3 = new Fraction(1,4);
        String cf = frac3.toString();
        Fraction sf = frac1.times(frac2);
        String out = sf.toString();
        assertEquals(cf, out);
    }

    @org.junit.jupiter.api.Test
    static void reciprocalTest(){
        Fraction frac1 = new Fraction(1,2);
        Fraction frac2 = new Fraction(2,1);
        String cf = frac2.toString();
        Fraction sf = frac1.reciprocal();
        String out = sf.toString();
        assertEquals(cf, out);
    }


}