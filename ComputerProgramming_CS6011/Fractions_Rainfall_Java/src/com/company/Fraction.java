package com.company;

public class Fraction implements Comparable<Fraction>{
    private long numerator;
    private long denominator;


    public Fraction(){
        numerator = 0;
        denominator = 1;
    }

    public Fraction(long n, long d){
        if(d == 0){
            throw new ArithmeticException();
        }
        if (d < 0) {
            n *= -1;
            d *= -1;
        }
        numerator = n;
        denominator = d;

        reduce();
    }

    public long gcd(){
        long gcd = this.numerator;
        long remainder = this.denominator;
        while(remainder != 0){
            long temp = remainder;
            remainder = gcd % remainder;
            gcd = temp;
        }
        return gcd;
    }

    public void reduce(){
        long div = gcd();
        if (div < 0){
            div *= -1;
        }
        this.numerator = this.numerator/div;
        this.denominator = this.denominator/div;
    }

    public Fraction plus(Fraction rhs){
        Fraction plusFraction = new Fraction();
        plusFraction.numerator = (this.numerator * rhs.denominator) + (rhs.numerator * this.denominator);
        plusFraction.denominator = (this.denominator * rhs.denominator);
        return plusFraction;
    }
    public Fraction minus(Fraction rhs){
        Fraction minusFraction = new Fraction();
        minusFraction.numerator = (this.numerator * rhs.denominator) - (rhs.numerator * this.denominator);
        minusFraction.denominator = (this.denominator * rhs.denominator);
        return minusFraction;
    }

    public Fraction times(Fraction rhs){
        Fraction timesFraction = new Fraction();
        timesFraction.numerator = (this.numerator * rhs.numerator);
        timesFraction.denominator = (this.denominator * rhs.denominator);
        return timesFraction;
    }

    public Fraction dividedBy(Fraction rhs){
        Fraction dividedByFraction = new Fraction();
        dividedByFraction.numerator = (this.numerator * rhs.denominator);
        dividedByFraction.denominator = (this.denominator * rhs.numerator);
        return dividedByFraction;
    }

    Fraction reciprocal(){
        Fraction reciprocalFraction = new Fraction();
        reciprocalFraction.numerator = denominator;
        reciprocalFraction.denominator = numerator;
        return reciprocalFraction;
    }

    // a method to get the decimal value of a fraction
    public double toDouble(){
        return Double.valueOf(this.numerator)/Double.valueOf(this.denominator);
    }

    public String toString(){
        String numerator = String.valueOf(this.numerator);
        String denominator = String.valueOf(this.denominator);
        return numerator + "/" + denominator;
    }

    @Override
    public int compareTo(Fraction o) {
        if(this.toDouble() - o.toDouble() < 0){
            return -1;
        }
        if(this.toDouble() - o.toDouble() == 0){
            return 0;
        }
        return 1;
    }
}







