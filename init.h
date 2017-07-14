
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions to initialise the game

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

ivec init_deck(){
    // initialise deck as a vector of cards
    // in the beginning all cards are present (all entries = 1),
    // as soon as a card leaves the deck, the entry will become
    // zero.
    // They are ordered by value; among the same values
    // diamond < hearts < spades < clubs
    // The last entries represent jokers (3)
    // Total size of array = 13 values * 4 suites + 3 jokers = 55.
    ivec Deck = ones<ivec>(55);

    return Deck;
}


ivec init_discard(){
    // initialise deck as a vector of cards
    // in the beginning all cards are present (all entries = 1),
    // as soon as a card leaves the deck, the entry will become
    // zero.
    // They are ordered by value; among the same values
    // diamond < hearts < spades < clubs
    // The last entries represent jokers (3)
    // Total size of array = 13 values * 4 suites + 3 jokers = 55.
    ivec Discard = zeros<ivec>(55);

    return Discard;
}    


ivec init_hand(){
	// TODO

	ivec Hand = zeros<ivec>(55);
 

	return Hand;
}


