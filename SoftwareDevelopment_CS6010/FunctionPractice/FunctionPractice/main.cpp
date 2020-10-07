//
//  main.cpp
//  FunctionPractice
//
//  Created by Derek Olson on 8/23/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

// function to print velocity in the x and y direction
void velocity(double speed, int angle){
    double x = speed*(std::cos(angle));
    double y = speed*(std::sin(angle));
    cout << "x = " << x << " y = " << y << "\n";
}

// function to return the hypotenuse of right triangle
double pyThrm(double a, double b){
    double c = std::sqrt(pow(a,2) + pow(b,2));
    cout << "c = "<< c << "\n";
    return c;
}

// function to identify even numers
string isEven(int input){
    string outMessage;
    if (input % 2 == 0){
        outMessage = "Your input is even \n";
        cout << outMessage;
        return outMessage;
    }
     outMessage = "Your input is odd \n";
    cout << outMessage;
    return outMessage;
}

// function to identify prime numbers
void isPrime(double input, double divisor){
    if (input <= 1){
        cout << "Not a prime number \n";
        exit(0);
    }
    while (divisor <= input){
        double x = input/divisor;
        
        // if x is a whole number it not a prime number
        if (floor(x) == x){
            cout << "Number is not prime \n";
            exit(0);
        }

        else if(floor(x) != x){
            divisor = divisor + 1;
            if (divisor == input){
                cout << "Your number is prime \n";
                exit(0);
            }
            isPrime(input , divisor);
        }
        else{ cout << "Number is prime \n";} // I do not think this is needed!
    }
}

int betterPrime(int input){
    for (int i = 2; i < input; i++){
        if (input <= 1){
            cout << "Not a prime number \n";
            exit(0);
        }
        else if (input % i == 0){
            cout << "Not a prime number \n";
        }
        else if (input % i != 0){
            cout << "The number is prime \n";
            return(0);
        }
    }
    return(0);
}

int main(int argc, const char * argv[]) {
    betterPrime(37);
    double a; double b; double speed; double angle;
    
    cout << "Pythagorean's thereom is a2 + b2 = c2 \n";
    cout << "To find the length of the hypotenuse (c), enter values for a and b \n";
    cout << "Enter a value for a \n";
    cin >> a;
    cout << "Enter a value for b \n";
    cin >> b;
    
    if (a <= 0 || b <= 0){
        cout << "Invalid input \n";
        return(1);
    }
    
    cout << "Enter the speed you are traveling \n";
    cin >> speed;
    
    cout << "Enter the angle (in radians) you are traveling \n";
    cin >> angle;
    
    pyThrm(a,b);
    
    velocity(speed, angle);
    
    isEven(34);
    
    isPrime(7, 2);
    
    return 0;
}


//a
//
//Ask the user to enter the right-angle side lengths of a triangle and then print the length of the hypotenuse (remember the pythagorean theorem?). You'll need to use the std::sqrt function that's defined in the <cmath> header.
//
//b
//
//Ask the user to input the speed they're going (a double) and the angle they're going in (a double, that's the angle in radians). Then use the std::cos and std::sin functions and the formulas x = length*cos(angle), y = length*sin(angle) to print out their x and y velocity.
//
//  c
//
//  Examine the run the code snippet from the example here
//
//  Confirm that the code works as expected. Which functions are being called? (We haven't talked about what the ampersand means yet, but we can ignore it for now)

