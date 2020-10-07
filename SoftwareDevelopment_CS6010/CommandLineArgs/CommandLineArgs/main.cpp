//
//  main.cpp
//  CommandLineArgs
//
//  Created by Derek Olson on 8/30/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    for (int i = 0; i < argc; i++){
        std::cout << argv[i] << std::endl;
    }
    return 0;
}
