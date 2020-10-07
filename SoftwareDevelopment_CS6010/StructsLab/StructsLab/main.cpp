//
//  main.cpp
//  StructsLab
//
//  Created by Derek Olson on 8/27/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//
#include "helpers.hpp"
#include <iostream>

using namespace std;


int main(int argc, const char * argv[]) {

    Politician a{"Donald Trump", false, true};
    Politician b{"Barak Obama", true, true};
    Politician c{"George W Bush", false, true};
    Politician d{"Bill Clinton", true, true};
    Politician e{"George HW Bush", false, true};
    Politician f{"sd1", true, false};
    Politician g{"sd2", true, false};
    Politician h{"sr1", false, false};
    
    std::vector<Politician> politicians = {a, b, c, d, e, f, g, h};
    
    std::vector<string> dm = Democrats(politicians);
    for (string d : dm){cout << d << "\n";}
    
    std::vector<Politician> fr = FedRepublicans(politicians);
    for (Politician f : fr){cout << f.name << "\n";}
    
    string wv = WhipVote(politicians, false);
    cout << wv << "\n";
    
    return 0;
}
