
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions to manipulate card states

#include <iostream>
#include <armadillo>

#define DECKSIZE 55

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

void add_card(imat *State, int to_row, int index){
    // Takes the index of a card, a game state and a row as input. 
    // This function adds a card to the object (Deck, Hand, Table_top,
    // Table_2nd_top, Discard)
    // represented by the row.
    // Returns the state.
    
        State(to_row, index) += 1;
}

int remove_card(imat State, int from_row, int index){
    // Takes the index of a card, a game state and a row as input. 
    // This function removes a card from the object (Deck, Hand, Table_top,
    // Table_2nd_top, Discard)
    // represented by the row.
    // Returns the state.

    if (State(from_row, index) <= 0) {printf("ERROR! Illegal move: Card with index %d is not present in Object\n", index);
    State.t().print("Fix ERROR in here! The current object is:");
    return 1;
     }

    else {State(from_row, index) -= 1;}

    return 0;
}
/*

int move_card_from_to(imat State, int from_row, int to_row, int index) {
    // Takes Object one and two as input plus an index of a card.
    // Moves the card from object one to object 2.
    // Returns the index.

    // Objects are not returned but changed in-place
    int is_error = remove_card(State, from_row, index);
    if (is_error == 1) { return 1;}
    else {         
        add_card(State, to_row, index);
        return 0;
        }
}


int deal_hands(ivec deck_shuffled_idx, imat *State, int n_players) {
    // Takes the Deck and a Hand as well as the current player ID
    // and the total number of players as input and
    // Returns the player ID

    int n_cards_p_hand = DECKSIZE / n_players;


    for (int player_number = 0; player_number < n_players; player_number++){

        for (int i = n_cards_p_hand * player_number; 
            i <= (n_cards_p_hand * ( 1 + player_number)) - 1; i++) {
            int index = deck_shuffled_idx[i];
            printf("move card INDEX: %d \n", index);
            move_card_from_to(*State, 0, 4 + player_number, index);
        }   
    }
    return 0;
}
*/