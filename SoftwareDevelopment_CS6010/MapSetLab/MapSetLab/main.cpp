//
//  main.cpp
//  MapSetLab
//
//  Created by Derek Olson on 9/18/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<map>
#include<set>
#include <iterator>
using namespace std;

set<string> create_set(string bookTitle){
    //vector<string> words;
    set<string> words;
    string word;
    string line;
    ifstream inBook(bookTitle);
    if (inBook.fail()){
        cout << "Book is unavailable";
    }
    while (inBook >> word){
        words.insert(word);
    }
    return words;
}

map<string, int> create_map(string bookTitle){
    vector<string> words;
    set<string> uw = create_set(bookTitle);
    string word;
    string line;
    ifstream inBook(bookTitle);
    map<string, int> wordMap;
    while (inBook >> word){
        //uw.insert(word);
        //words.push_back(word);
        wordMap[word] += 1;
    }

    return wordMap;
}
    
int main(int argc, const char * argv[]) {
    
    set<string> uniqueWords = create_set("Huck_Finn.txt");
    
    long size = uniqueWords.size();
    cout << size << endl;
    
    map<string, int> wordCount = create_map("Huck_Finn.txt");
    
    
    return 0;
}
