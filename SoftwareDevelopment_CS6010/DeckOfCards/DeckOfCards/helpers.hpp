//
//  helpers.hpp
//  DeckOfCards
//
//  Created by Derek Olson on 8/27/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//
#pragma once
#ifndef helpers_hpp
#define helpers_hpp
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// create a structure for playing cards 
struct Card{
    int rank;
    char suit;
};

int  MinIndex(const vector<int> & v, int start);

void SortHand(vector<int>& v);

vector<int> GetRanks(vector<Card> hand);

// function to create a deck of cards
vector<Card> DeckOfCards(vector<int> ranks, vector<char> suits);

//function to print a deck of cards
void PrintCards(vector<Card> cards);

void swap(Card& x, Card& y);

void shuffeledDeck(vector<Card>&);

vector<Card> pokerHand(vector<Card> deck);

bool IsFlush(vector<Card> hand);

bool IsStraight(vector<Card> hand);

bool IsStraightFlush(vector<Card> hand);

bool IsRoyalFlush(vector<Card> hand);

bool IsPair(vector<Card> hand);

bool IsThreeOfKind(vector<Card> hand);

bool IsFullHouse(vector<Card> hand);

float  stats(vector<Card> deck);

#endif /* helpers_hpp */
