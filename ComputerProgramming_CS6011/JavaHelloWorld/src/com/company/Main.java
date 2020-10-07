package com.company;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static int[] list() {
        int[] intArray = new int[10];
        for(int i=0;i<intArray.length;i++)
        {
            Random rand = new Random();
            int randomNum = rand.nextInt();
            intArray[i] = randomNum;
        }
        return intArray;
    }


    public static void main(String[] args) {
	System.out.println("Hello world");

        Scanner name = new Scanner(System.in);
        System.out.println("Enter name");

        String userName = name.nextLine();
        System.out.println("Name is: " + userName);

        Scanner age = new Scanner(System.in);
        System.out.println("Enter age");

        String userAge = age.nextLine();
        System.out.println("User age is: " + userAge);

        if(Integer.parseInt(userAge) > 18){
            System.out.println("User can vote");
        }
        if(Integer.parseInt(userAge) < 18){
            System.out.println("User can't vote");
        }

        if(Integer.parseInt(userAge) > 80){
            System.out.println("User is part of the greatest generation");
        }
        if(Integer.parseInt(userAge) >= 60 && Integer.parseInt(userAge) < 80){
            System.out.println("User is part of the baby boomers");
        }
        if(Integer.parseInt(userAge) >= 40 && Integer.parseInt(userAge) < 60){
            System.out.println("User is part of gen x");
        }
        if(Integer.parseInt(userAge) >= 20 && Integer.parseInt(userAge) < 40){
            System.out.println("User is part of the millenial generation");
        }
        if(Integer.parseInt(userAge) < 20){
            System.out.println("User is part of igen");
        }
    }


}
