
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions to manipulate card states

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

ivec add_card(ivec Object, int index){
    // Takes the index of a card and an ivec object as input. 
    // This function adds a card to the object (Deck, Hand, Table, Discard).
    // Returns the object.

        //Object.row(index) += 1;
        Object(index) += 1;

    return Object;
}

ivec remove_card(ivec Object, int index){
    // Takes the index of a card and an ivec object as input. 
    // This function adds a card to the object (Deck, Hand, Table, Discard).
    // Returns the object.

        //Object.row(index) += 1;
    if (Object(index) <= 0) {printf("ERROR! Illegal move: Card with index %d is not present in Object\n", index);
    Object.print("Fix ERROR in here! The current object is:"); }
    else {Object(index) -= 1;}

    return Object;
}


int move_card_from_to(ivec *source,ivec *destination, int index) {
    // Takes Object one and two as input plus an index of a card.
    // Moves the card from object one to object 2.
    // Returns the index.

    // Objects are not returned but changed in-place
    *source = remove_card(*source, index);
    *destination = add_card(*destination, index);

    return index;
}


