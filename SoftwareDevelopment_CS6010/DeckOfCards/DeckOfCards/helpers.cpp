//
//  helpers.cpp
//  DeckOfCards
//
//  Created by Derek Olson on 8/27/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include "helpers.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <iomanip>
using namespace std;

// function to create a deck of cards
vector<Card> DeckOfCards(vector<int> ranks, vector<char> suits ){
    vector<Card> cards;
    for (int r : ranks){
        for(char s : suits){
            Card c;
            c.rank = r;
            c.suit = s;
            cards.push_back(c);
        }
    }
    return cards;
}

// function to get the card ranks as a vector
vector<int> GetRanks(vector<Card> hand){
    vector<int> ranks;
    for (Card card : hand){
        ranks.push_back(card.rank);
    }
    return ranks;
}

//function to print a deck of cards
void PrintCards(vector<Card> cards){
    for (Card card : cards){
        if (card.rank < 11){
            cout << card.rank << card.suit << "\n";
        }
        else if (card.rank == 11){
            cout << "J" << card.suit << "\n";
        }
        else if (card.rank == 12){
            cout << "Q" << card.suit << "\n";
        }
        else if (card.rank == 13){
            cout << "K" << card.suit << "\n";
        }
        else if (card.rank == 14){
            cout << "A" << card.suit << "\n";
        }
    }
}

// function to swap
void swap(Card& x, Card& y){
    //vector<int> out;
    Card a;
    a = x;
    x = y;
    y = a;
}

// function to return a min index
int  MinIndex(const vector<int> & v, int start){
    int minIndex = start;
    for (int i = start +1; i < v.size(); i++){
        if (v[i] < v[minIndex]){
            minIndex = i;
        }
    }
    return minIndex;
}

// sort function
void SortHand(vector<int>& v){
    for (int i = 0; i < v.size()-1; i++){
        int minIndex = MinIndex(v,i);
        swap(v[i], v[minIndex]);
    }
}

// address sanitizer??????

// function to shuffle a deck
void shuffeledDeck(vector<Card>& deck){
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    
    for (int i = 51; i > 0; i--){
        std::uniform_int_distribution<> dis(0, i);
        int rand = dis(gen);
        swap(deck[i], deck[rand]);
    }
}

// function to deak a poker hand
vector<Card> pokerHand(vector<Card> deck){
    vector<Card> hand;
    for (int i = 0; i < 5; i++){
        hand.push_back(deck[i]);
    }
    return hand;
}

// function to test for flushes
bool IsFlush(vector<Card> hand){
    for (int i = 1; i < 5; i++){
        if (hand[0].suit != hand[i].suit){
            //cout << "Not a flush" << "\n";
            return false;
        }
    }
    //cout << "Hand is a flush \n";
    return true;
}

// deal with low straights
bool LowStraight(vector<Card> hand){
    vector<int> ranks = GetRanks(hand);
    SortHand(ranks);
    //sort(ranks.begin(), ranks.end());
    for (int i = 0; i < 5; i++){
        if (ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5 && ranks[4] == 14){
            return true;
        }
    }
    return false;
}

// function to test for straights
bool IsStraight(vector<Card> hand){
    vector<int> ranks = GetRanks(hand);
    SortHand(ranks);
    if (LowStraight(hand)){
        return true;
    }
    for (int i = 1; i < 5; i++){
        if (ranks[i] != ranks[i-1] + 1){
            //cout << "Hand is not a straight \n";
            return false;
        }
    }
    //cout << "Hand is a straight \n";
    return true;
}

// function to test for straigt flushes
bool IsStraightFlush(vector<Card> hand){
    if (IsStraight(hand) && IsFlush(hand)){
        //cout << "Straight Flush \n";
        return true;
    }
    //cout << "Not a Straight Flush \n";
    return false;
}

// function to test for royal flushes
bool IsRoyalFlush(vector<Card> hand){
    vector<int> ranks;
    for (Card card : hand){
        ranks.push_back(card.rank);
    }
    for (int r : ranks){
        if (r < 10){
            //cout << "Not a royal flush \n";
            return false;
        }
    }
    if (IsStraightFlush(hand)){
        //cout << "You've got a royal flush! \n";
        return true;
    }
    //cout << "Not a royal flush \n";
    return false;
}

// function to test for pairs
bool IsPair(vector<Card> hand){
    vector<int> ranks = GetRanks(hand);
    sort(ranks.begin(), ranks.end());
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (ranks[i] == ranks[i-1]){
            count += 1;
            if (count == 1){
                //cout << "You've got a pair! \n";
                return true;
            }
        }
    }
    //cout << "No Pairs \n";
    return false;
}

// function to test for a three of a kind
bool IsThreeOfKind(vector<Card> hand){
    vector<int> ranks = GetRanks(hand);
    sort(ranks.begin(), ranks.end());
    int count = 0;
    for (int i = 1; i <5; i++){
        if (ranks[i] == ranks[i-1]){
            count += 1;
            if (count == 2){
                //cout << "You've got a three of a kind! \n";
                return true;
            }
        }
    }
    //cout << "No three of a kind \n";
    return false;
}

// function to test for full houses
bool IsFullHouse(vector<Card> hand){
    vector<int> ranks = GetRanks(hand);
    sort(ranks.begin(), ranks.end());
    int count = 0;
    for (int i = 1; i <5; i++){
        if (ranks[i] == ranks[i-1]){
            count += 1;
            if (count == 3){
                //cout << "You've got a full house! \n";
                return true;
            }
        }
    }
    //cout << "No full house \n";
    return false;
}


// function to return statistics on hand probabilities
float stats(vector<Card> deck){
    float flush = 0.0; float straight = 0.0; float straightFlush = 0.0; float royalFlush = 0.0; float fullHouse = 0;
    float n = 1000000.0;
    for (int i = 0; i < n; i++){
        
        shuffeledDeck(deck);
        
        vector<Card> hand = pokerHand(deck);
        
        if (IsFlush(hand)){
            flush += 1.0;
        }
        
        if (IsStraight(hand)){
            straight += 1.0;
        }
        
        if(IsStraightFlush(hand)){
            straightFlush += 1.0;
        }
        
        if(IsRoyalFlush(hand)){
            royalFlush += 1.0;
        }
        
        if(IsFullHouse(hand)){
            fullHouse += 1.0;
        }
    }
    cout << "Flushes: " << (flush/n)*100 << "%\n";
    cout << "Straights: " << (straight/n)*100 << "%\n";
    cout << "Straight Flushes: " << setprecision(6)<< (straightFlush/n)*100 << "%\n";
    cout << "Royal Flushes: " << setprecision(6) << (royalFlush/n)*100 << "%\n";
    cout << "Full Houses: " << (fullHouse/n)*100 << "%\n";
    
    return 0;
}







