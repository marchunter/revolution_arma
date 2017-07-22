
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions to initialise the game

#include <iostream>
#include <armadillo>
#include <random>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;


imat init_state(int n_players, int decksize){
    // Initialise state of the game as a matrix
    // Each row contains elements each of which
    // represent a card
    // They are ordered by value; among the same values
    // diamond < hearts < spades < clubs
    // The last entries represent jokers (3)
    // Total size of array = 13 values * 4 suites + 3 jokers = 55.

    // First row:   Deck (initialised to all ones)
    // Second row:  Discard
    // Third row:   Top cards on table
    // Fourth row:  Cards under top cards on table
    // Fifth to 5+xth row:  Each row represents a hand of a 
    //                      player with x players

    // Takes number of players as input
    // Returns initial state matrix

    imat state(4 + n_players, decksize);
    state.zeros();
    state.row(0).fill(1); // = ones<irowvec>(DECKSIZE);

    return state;
}


ivec shuffle_deck(int decksize) {
    // Takes the deck size as input.
    // Returns a vector of indices from 0 to deck size in random order.
    arma_rng::set_seed_random();
    ivec indices = linspace<ivec>(0, decksize -1, decksize);
    ivec deck_shuffled_idx = shuffle(indices);

    return deck_shuffled_idx;
}


