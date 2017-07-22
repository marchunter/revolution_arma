
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions to manipulate card states

#include <iostream>
#include <armadillo>

#define DECKSIZE 55

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

imat add_card(imat State, int to_row, int index){
    // Takes the index of a card, a game state and a row as input. 
    // This function adds a card to the object (Deck, Hand, Table_top,
    // Table_2nd_top, Discard)
    // represented by the row.
    // Returns the state.

    State(to_row, index) += 1;
    return State;
}

imat remove_card(imat State, int from_row, int index){
    // Takes the index of a card, a game state and a row as input. 
    // This function removes a card from the object (Deck, Hand, Table_top,
    // Table_2nd_top, Discard)
    // represented by the row.
    // Returns the state.

    if (State(from_row, index) <= 0) {printf("ERROR! Illegal move: Card with index %d is not present in Object\n", index);
    State.t().print("Fix ERROR in here! The current object is:");
     }

    else {State(from_row, index) -= 1;}

    return State;
}


imat move_card_from_to(imat State, int from_row, int to_row, int index) {
    // Takes a game state, a source row and a destination row
    // plus an index of a card as input.
    // Moves the card from source row to destination row.
    // Returns the state.
    
    State = remove_card(State, from_row, index);
    State = add_card(State, to_row, index);
    return State;
}


imat deal_hands(ivec deck_shuffled_idx, imat State, int n_players) {
    // Takes the Deck and a Hand as well as the current player ID
    // and the total number of players as input and
    // Returns the player ID

    int n_cards_p_hand = DECKSIZE / n_players;


    for (int player_number = 0; player_number < n_players; player_number++){

        for (int i = n_cards_p_hand * player_number; 
            i <= (n_cards_p_hand * ( 1 + player_number)) - 1; i++) {
            int index = deck_shuffled_idx[i];
            printf("move card INDEX: %d \n", index);
            State = move_card_from_to(State, 0, 4 + player_number, index);
        }   
    }
    return State;
}
