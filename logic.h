
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Functions for game logic

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

struct Game
{
    bool is_revolution = false;
    bool is_jack = false;
    int top_player = -2;
    int starting_player = 0;
    bool is_suite_lock = false;
    bool is_straight = false;

    // game history, not implemented

} Current_game;

int is_higher(int index, int compare_idx){
    // Takes two indeces of cards as input.
    // Returns 1 if the first card is higher in value
    // and 0 otherwise.

    if (index / 4 > compare_idx / 4) return 1;

    else return 0;
}

int is_lowest_higher(ivec move, ivec top_cards){
    // Takes two vectors as input
    // Returns 1 if the lowest nonzero entry of the
    // first vector move has a higher index than the
    // one of the second vector top_cards.
    // Returns 0 otherwise.
    uvec lowest_move_idx = find(move, 
        1, "first" );
    uvec lowest_top_idx = find(top_cards, 
        1, "first" );
    if (lowest_move_idx(0) > lowest_top_idx(0)) {return 1;}
    else {return 0;}
}

// function no longer needed
int is_same_value(int index, int compare_idx){
    // Takes two indeces of cards as input.
    // Returns 1 if both cards have the same value
    // and 0 otherwise.

    if (index / 4 == compare_idx / 4) return 1;

    else return 0;
}

int are_all_same_value(ivec move){
    // Takes a vector as input
    // Returns 1 if all nonzero elements correspond to the same
    // card value, Returns 0 otherwise.
    uvec indices = find(move == 1) / 4;
    uvec unique_indices = unique(indices);
    int is_unique = unique_indices.n_elem;
    if (is_unique <= 1) {return 1;}
    else {return 0;}

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

int do_suites_match(ivec play1, ivec play2){
    // Takes two vectors as input
    // Checks wether all suites of the cards contained match
    // Then it returns 1, and 0 otherwise.

    // Truncate jokers:
    ivec truncated_play1 = play1.rows(0, play1.n_elem - 3 -1);
    ivec truncated_play2 = play2.rows(0, play2.n_elem - 3 -1);
    
    uvec indices1 = find(truncated_play1 == 1);
    if (indices1.n_elem == 0) {return true;}

    uvec indices2 = find(truncated_play2 == 1);
    if (indices2.n_elem == 0) {return true;}

    uvec mod_indices1 = indices1 - floor(indices1/4) * 4;
    uvec mod_indices2 = indices2 - floor(indices2/4) * 4;

    uvec comparison = (sort(mod_indices1) == sort(mod_indices2));

    if (sum(comparison) == comparison.n_elem) {return 1;}
    else {return 0;}

}

int are_all_same_suite(ivec move){
    // Takes a vector as input
    // Returns 1 if all nonzero elements correspond to the same
    // card value, Returns 0 otherwise.
    
    // Truncate jokers:
    ivec truncated_move = move.rows(0, move.n_elem - 3 -1);

    uvec indices = find(truncated_move == 1);
    // modulus to get suites 0,1,2,3
    uvec mod_indices = indices - floor(indices/4) * 4;
    uvec unique_indices = unique(mod_indices);
    int is_unique = unique_indices.n_elem;
    if (is_unique <= 1) {return 1;}
    else {return 0;}

}

int is_straight(ivec move){
    // Takes a vector as input
    // Returns 1 if the move is a straight
    // (adjacent values, same suite (jokers are 
    // treated as all suites))
    // Returns 0 otherwise.
    int n_cards_move = sum(move);

    if ((n_cards_move >= 3) && 
            (are_all_same_suite(move) == 1)) {
        uvec indices = find(move == 1) / 4;
        for (int i=0; i<indices.n_elem; i++){
            if (indices(0) + i != indices(i)) {return false;}
        }
        return true;
    }
    else {return false;}
}

bool validate_move(imat State, ivec move, 
    Game Current_game, int player_number){
    // Takes a game state as input, which contains the player's hand,
    // and the top cards.
    // The player's id and the Game struct are also given.
    // Takes an ivec with the length of the decksize as input. Zeros mean,
    // the cards are not played, while ones mean, that those cards are
    // played-
    // Returns a boolean, whether or not the move is valid
    
    // Check if move is empty:
    int n_cards_move = sum(move);
    if (n_cards_move == 0) {return true;}

    // Check if cards are in hand:
    ivec Hand = State.row(player_number + 4).t();

    ivec validation = Hand - move;
    int minimum = validation.min();
    if (minimum < 0){
        //printf("These cards are not in hand!\n");
        return false;
        }

    // Check if cards can be played on top

    // nothing on top?
    ivec top_cards = State.row(2).t();
    if (sum(top_cards) == 0) {
        // only one card?
        if (n_cards_move == 1) {
            return true;}
        // check for tuples
        else if (are_all_same_value(move) == 1) {
            return true;}
        // check for straight
        else if (is_straight(move)) { 
            // Note. Here, the game state could be updated.
            // Currently it is done separately for readability
            // of the code
            return true;
                }
        // otherwise, reject
        else {return false;}
        }

    // number of cards on top == number of cards in move?
    else if (sum(top_cards) == n_cards_move) {
        // has a straight been played?
        if (Current_game.is_straight == true) {
            // is the move actually a straight?
            if (is_straight(move) == 1) {}
            else {return false;}
            }
        // have cards with same value been played?
        else if (are_all_same_value(top_cards) == 1) {
            if (are_all_same_value(move) == 1) {}
            else {return false;}
        }

        else {return false;}

        // is suite locked?
        if ((Current_game.is_suite_lock == true) 
            && (Current_game.is_straight == false)) {
            if (do_suites_match(move, top_cards) == 1) {}
            else {return false;}
            }

        // check for inverse condition!
        bool is_inverse = (Current_game.is_jack != 
            Current_game.is_revolution); 

        // higher (sometimes lower)?
        if (is_inverse == false) {
            if (is_lowest_higher(move, top_cards) == 1) {return true;}
            else {return false;}    
        }
        else {
            if (is_lowest_higher(top_cards, move) == 1) {return true;}
            else {return false;}
        }

        }
        
    else {return false;}

    }


ivec choose_move_randomly(imat state, Game Current_game, 
        int active_player, int decksize){
    int is_valid = false;
    int n_tries = 0;
    ivec move(decksize);
    do
    {

        ivec n_cards_vec = randi<ivec>(1,distr_param(1, 4));
        int n_cards = n_cards_vec(0);
        ivec move_idx = randi<ivec>(n_cards, distr_param(0, decksize -1));

        move.zeros();

        for (int i=0; i < move_idx.size(); i++){
            move(move_idx(i)) = 1;
        }
        n_tries +=1;
        if (n_tries == 30){move.zeros();}


    is_valid = validate_move(state, move, Current_game, active_player);

    } while (is_valid == false);



    return move;
}



