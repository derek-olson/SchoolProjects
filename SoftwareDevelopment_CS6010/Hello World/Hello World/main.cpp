//
//  main.cpp
//  Hello World
//
//  Created by Derek Olson on 8/19/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << "test\n";
    
    static int x = 2;
    static int y = 4;
    
    static int z = x+y;
    
    std::cout << z;
    std::cout << "\n";
    
    return 2+2;
}




