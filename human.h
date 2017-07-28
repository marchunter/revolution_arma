
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions for human readability

#include <iostream>
#include <armadillo>
#include <string>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

string index2card(int index,int decksize){
    // Takes the index of a card and the decksize as input.
    // Returns a human-readable string of that card
    // e.g. 4D = 4 of diamonds
    // D, H, S, C = diamonds, hearts, spades, clubs
    // 3,4,5,6,7,8,9,T,J,Q,K,A,2, jo (joker)
    std::string value = "";
    std::string suite = "";
    if (index >= decksize - 3){return "jo";}
    if (index / 4 == 0) {value = "3";}
    if (index / 4 == 1) {value = "4";}
    if (index / 4 == 2) {value = "5";}
    if (index / 4 == 3) {value = "6";}
    if (index / 4 == 4) {value = "7";}
    if (index / 4 == 5) {value = "8";}
    if (index / 4 == 6) {value = "9";}
    if (index / 4 == 7) {value = "T";}
    if (index / 4 == 8) {value = "J";}
    if (index / 4 == 9) {value = "Q";}
    if (index / 4 == 10) {value = "K";}
    if (index / 4 == 11) {value = "A";}
    if (index / 4 == 12) {value = "2";}

    if (index % 4 == 0) {suite = "D";}
    if (index % 4 == 1) {suite = "H";}
    if (index % 4 == 2) {suite = "S";}
    if (index % 4 == 3) {suite = "C";}

    return value + suite;
}

void print_state_row(ivec state_row, int decksize){
    // Takes a row in the state and the decksize as input
    // Return nothing,
    // But prints all cards in the state row (e.g. Hand, Deck, ...)

    uvec indices = find(state_row == 1);
    for (int i = 0; i < indices.n_elem; i++) {
        std::string cardname = index2card(indices(i), decksize);
        cout << cardname << " ";
    }
        cout << endl;
}


void print_state(imat State){
    // Takes a game state as input 
    // Returns nothing,
    // But prints where each card currently is
    // in a human-readable format.
    cout << "Current Game State: " << endl;
    cout << "------------------: " << endl;
    int n_players = State.n_rows - 4;
    int decksize = State.n_cols;

    // Deck
    ivec state_row = State.row(0).t();
    cout << "Deck: ";
    print_state_row(state_row, decksize);

    // Discard
    state_row = State.row(1).t();
    cout << "Discard: ";
    print_state_row(state_row, decksize);

    // Top cards on table
    state_row = State.row(2).t();
    cout << "Top Cards: ";
    print_state_row(state_row, decksize);

    // Cards on table 2nd-to-top
    state_row = State.row(3).t();
    cout << "2nd-To-Top Cards: ";
    print_state_row(state_row, decksize);

    // Hands of players
    for (int i = 0; i < n_players ;i++){
    state_row = State.row(4 + i).t();
    cout << "Hand of Player " << i << " ";
    print_state_row(state_row, decksize);
    }
    cout << "------------------: " << endl;

}




