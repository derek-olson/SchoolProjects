//
//  Functions.hpp
//  TemplatesLab
//
//  Created by Derek Olson on 9/12/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <iostream>
#include <stdio.h>

template <typename T>
struct Triple{
    T first;
    T second;
    T third;
    
};

template <typename T>
void printEach(T x){
    for (int i = 0; i < x.size(); i++){
        std::cout << x[i] << std::endl;
    }
}


#endif /* Functions_hpp */
