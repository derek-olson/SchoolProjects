package com.company;

import java.util.ArrayList;
import java.util.Collections;

public class Main {

    public static void main(String[] args) {

        //Rainfall rf = new Rainfall();

        //rf.readData(rf._scanner, rf._arrayList);

        ArrayList<Fraction> fractions = new ArrayList<Fraction>();
        fractions.add(new Fraction(1,2));
        fractions.add(new Fraction(3,2));
        fractions.add(new Fraction(-1,2));
        fractions.add(new Fraction(1,4));
        fractions.add(new Fraction(1,6));

        Collections.sort(fractions);

        System.out.println(fractions);

//        try {
//            Fraction fraction = new Fraction(1, 0);
//        }catch(ArithmeticException ae){
//            System.out.println("Caught ArithmeticException");
//        }
    }
}
