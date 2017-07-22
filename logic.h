
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions for game logic

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

int is_higher(int index, int compare_idx){
    // Takes two indeces of cards as input.
    // Returns 1 if the first card is higher in value
    // and 0 otherwise.

    if (index / 4 > compare_idx / 4) return 1;

    else return 0;
}


int is_same_value(int index, int compare_idx){
    // Takes two indeces of cards as input.
    // Returns 1 if both cards have the same value
    // and 0 otherwise.

    if (index / 4 == compare_idx / 4) return 1;

    else return 0;
}

int is_same_suite(int index, int compare_idx){
    // Takes two indeces of cards as input.
    // Returns 1 if both cards have the same suite
    // and 0 otherwise.

    // jokers have no suite and are treated as if they had all suites.
    if (index >= 52) return 1;
    else if (index % 4 == compare_idx % 4) return 1;
    else return 0; 
}

bool validate_move(imat State, ivec move, int player_number){
    // Takes a game state as input, which contains the player's hand,
    // and the top cards.
    // The player's id is also given.
    // Takes an ivec with the length of the decksize as input. Zeros mean,
    // the cards are not played, while ones mean, that those cards are
    // played-
    // Returns a boolean, whether or not the move is valid

    // Check if cards are in hand:



    // Check if cards can be played on top
}

imat check_singles(){
    // TODO
}

imat check_doubles() {
    //  TODO
}

