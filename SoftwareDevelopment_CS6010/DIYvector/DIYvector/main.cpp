//
//  main.cpp
//  DIYvector
//
//  Created by Derek Olson on 9/9/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "Functions.hpp"
#include <iostream>
#include <numeric>

int main(int argc, const char * argv[]) {
    
    Vector<int> test = Vector<int>(50);
    assert(test.getCapacity() == 50);
    assert(test.getSize() == 0);
    
//    test.freeVector();
//    assert(test.getCapacity() == 50);
//    assert(test.getSize() == 0);

    test.pushBack(5);
    assert(test.getSize() == 1);
    assert(test.get(0) == 5);

    //test.popBack();
    //assert(test.getSize() == 0);
    //assert(test.get(0) != 5);

    test.set(0, 2);
    assert(test.get(0) == 2);

    test.growVector();
    assert(test.getCapacity() == 100);
    //assert(test.getSize() == 0);
    
    test.pushBack(3);
    test.pushBack(4);
    test.pushBack(5);
    test.pushBack(6);
    test.pushBack(7);
    test.pushBack(8);
    
    Vector<int> test2(test);
    Vector<int> test3;
    
    test3 = test2;
    test3.set(0,9);
    //std::cout<< test3[0] << "\n";
    //std::cout<< test3[3] << "\n";
    std::cout << test << "\n";
    std::cout << test3 << "\n";
    
    if (test == test3){
        std::cout << "are equal \n";
    }
    
    if (test != test3){
        std::cout << "are not equal \n";
    }
    
    if (test <= test3){
        std::cout << "is <= \n";
    }
    
    if (test >= test3){
        std::cout << "is >= \n";
    }
    if (test < test3){
        std::cout << "is < \n";
    }
    
    if (test > test3){
        std::cout << "is > \n";
    }
    
    Vector<std::string> s1 = Vector<std::string>(1);
    s1.pushBack("hello");
    Vector<std::string> s2 = Vector<std::string>(1);
    s2.pushBack("and");
    
    Vector<std::string> s3 = Vector<std::string>(10);
    Vector<std::string> s4 = Vector<std::string>(10);
    s3.pushBack("hello");
    s3.pushBack("world");
    s3.pushBack("apples");
    s4.pushBack("hello");
    s4.pushBack("world");
    s4.pushBack("hello");
    assert(s1>s2);
    assert(s3<s4);
    assert(s4>s3);
    
    Vector<std::string> s5 = Vector<std::string>(10);
    Vector<std::string> s6 = Vector<std::string>(10);
    s5.pushBack("hello");
    s5.pushBack("world");
    s6.pushBack("hello");
    s6.pushBack("world");
    assert(s5 == s6);
    //assert(s5 != s6);

    Vector<std::string> s7 = Vector<std::string>(10);
    Vector<std::string> s8 = Vector<std::string>(10);
    s7.pushBack("Hello");
    s7.pushBack("world");
    s8.pushBack("hello");
    s8.pushBack("world");
    assert(s7<s8);

    test3.Sort();
    std::cout << test3 << std::endl;
    
    s3.Sort();
    std::cout << s3 << std::endl;
    
    int sum = std::accumulate(test3.begin(), test3.end(), 0);
    std::cout << sum << "\n";
    
    auto min = std::min_element(test3.begin(), test3.end());
    std::cout << *min << "\n";
    
    auto count = std::count_if(test3.begin(), test3.end(), [](int x){return((x%2)==0);});
    std::cout << count << "\n";
    
    test3.pushBack(2);
    std::sort(test3.begin(), test3.end());
    std::cout << test3 << std::endl;
    
    auto remove = std::remove_if(test3.begin(), test3.end(), [](int x){return((x%2)==0);});
    std::cout << test3 << std::endl;
    for (auto x = test3.end(); x > remove; x--){
        test3.popBack();
    }
     std::cout << test3 << std::endl;
    
    
    return 0;
}
