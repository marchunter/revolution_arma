
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
    else if (index % 4 = compare_idx % 4) return 1;
    else return 0; 
}

imat check_singles(){
    // TODO
}

imat check_doubles()

