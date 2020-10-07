//
//  helpers.cpp
//  StructsLab
//
//  Created by Derek Olson on 8/27/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "helpers.hpp"
#include <iostream>
#include <vector>
using namespace std;

std::vector<string> Democrats(std::vector <Politician> politicians){
    std::vector<string> democrats;
    for (Politician p : politicians){
        if (p.democrat){
            democrats.push_back(p.name);
        }
    }
    return democrats;
}

std::vector<Politician> FedRepublicans(std::vector<Politician> politicians){
    std::vector<Politician> fed_republicans;
    for (Politician p : politicians){
        if (!p.democrat && p.fed){
            fed_republicans.push_back(p);
        }
    }
    return fed_republicans;
}

string WhipVote(std::vector<Politician> politicians, bool federal_bill){
    int dem_votes = 0; int rep_votes = 0;
    for (Politician p : politicians){
        if (federal_bill){
            if (p.democrat && p.fed){dem_votes += 1;}
            else if (!p.democrat && p.fed){rep_votes += 1;}
        }
        else{
            if (p.democrat && !p.fed){dem_votes += 1;}
            else if (!p.democrat && !p.fed){rep_votes += 1;}
        }
    }
        if (dem_votes > rep_votes){return "Democrats \n";}
        else{return "Republicans \n";}
}
