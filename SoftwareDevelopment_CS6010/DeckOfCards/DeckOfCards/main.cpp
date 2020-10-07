//
//  main.cpp
//  DeckOfCards
//
//  Created by Derek Olson & David Scovel on 8/27/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#include <iostream>
#include <vector>
#include "helpers.hpp"
#include <cstdlib>
#include <random>
#include <algorithm>

int main(int argc, const char * argv[]) {
    // initiate a vector of ranks
    vector<int> ranks = {2,3,4,5,6,7,8,9,10,11,12,13,14};
    // initiate a vector of suits
    vector<char> suits = {'H', 'S', 'C', 'D'};
    // call the function DeckOfCards to create a deck from the two vectors
    vector<Card> cards = DeckOfCards(ranks, suits);
    // print the deck of cards
    //PrintCards(cards);
    
    // check to see if all cards are avaiable
    
    //shuffle
    shuffeledDeck(cards);

    //PrintCards(cards);
    
    vector<Card> hand = pokerHand(cards);
    
    PrintCards(hand);
    
    // flush test
    Card flushA1 = {2,'H'};
    Card flushA2 = {6,'H'};
    Card flushA3 = {11,'H'};
    Card flushA4 = {9,'H'};
    Card flushA5 = {14,'H'};
    vector<Card> flush {flushA1,flushA2,flushA3,flushA4,flushA5};
    
    // Straight test
    Card straightA1 = {2,'H'};
    Card straightA2 = {6,'S'};
    Card straightA3 = {3,'H'};
    Card straightA4 = {5,'C'};
    Card straightA5 = {4,'H'};
    vector<Card> straight {straightA1 ,straightA2 ,straightA3 ,straightA4 ,straightA5};
    
    // straight flush test
    Card straightFlushA1 = {2,'H'};
    Card straightFlushA2 = {6,'H'};
    Card straightFlushA3 = {3,'H'};
    Card straightFlushA4 = {5,'H'};
    Card straightFlushA5 = {4,'H'};
    vector<Card> straightFlush {straightFlushA1 ,straightFlushA2 ,straightFlushA3 ,straightFlushA4 ,straightFlushA5};
    
    // Royal Flush test
    Card RoyalFlushA1 = {11,'H'};
    Card RoyalFlushA2 = {13,'H'};
    Card RoyalFlushA3 = {10,'H'};
    Card RoyalFlushA4 = {14,'H'};
    Card RoyalFlushA5 = {12,'H'};
    vector<Card> RoyalFlush {RoyalFlushA1 ,RoyalFlushA2 ,RoyalFlushA3 ,RoyalFlushA4 ,RoyalFlushA5};
    
    // full house test
    Card FullHouse1 = {12,'H'};
    Card FullHouse2 = {13,'S'};
    Card FullHouse3 = {13,'D'};
    Card FullHouse4 = {12,'C'};
    Card FullHouse5 = {13,'H'};
    vector<Card> FullHouse {FullHouse1,FullHouse2,FullHouse3,FullHouse4,FullHouse5};
    
//    // function to test for a flush
//    IsFlush(flush);
//    
//    //function to test for a straight
//    IsStraight(straight);
//    
//    // function to test for a straight flush
//    IsStraightFlush(straightFlush);
//    
//    // function to test for a royal flush
//    IsRoyalFlush(RoyalFlush);
//    
//    // function to test for a pair
//    IsPair(hand);
//    
//    // function to test for 3 of a kind
//    IsThreeOfKind(FullHouse);
//    
//    // function to test for a full house
//    IsFullHouse(FullHouse);
    
    stats(cards);
   
    return 0;
}
