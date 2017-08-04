//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Helper functions for main functino

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

imat play_cards(imat state, ivec move, int active_player){

    ivec top_cards = state.row(2).t(); 
    ivec sec_top_cards = state.row(3).t();

    // move top cards to 2nd-top-cards, and those to Discard
    state = move_cards_from_to(state, 3, 1, sec_top_cards);
    state = move_cards_from_to(state, 2, 3, top_cards);

    // remove cards from hand and         
    // add top cards

    state = move_cards_from_to(state, active_player + 4, 2, move);


    return state;
}

imat clear_table(imat state){

    ivec top_cards = state.row(2).t(); 
    ivec sec_top_cards = state.row(3).t();
    state = move_cards_from_to(state, 3, 1, sec_top_cards);
    state = move_cards_from_to(state, 2, 1, top_cards); 

    return state;
}


/* Currently not working because of struct
    state = swap_cards(state, Current_match, N_PLAYERS);


imat swap_cards(imat state, Match Current_match, int N_PLAYERS){

    int first_player = Current_match.player_ranking(0);
    int second_player = Current_match.player_ranking(1);
    int last_player = Current_match.player_ranking(N_PLAYERS -1);
    int second_to_last_player = Current_match.player_ranking(N_PLAYERS -2);
    
    for (int i=0; i<=1; i++) {
        uvec lowest_card_index = find( state.row(4 + first_player).t(), 
            1, "first" );
        state = move_card_from_to(state, 4 + first_player,
            4 + last_player, lowest_card_index(0));
        uvec highest_card_index = find( state.row(4 + last_player).t(), 
            1, "last" );
        state = move_card_from_to(state, 4 + last_player,
            4 + first_player, highest_card_index(0));
        }
    
    uvec lowest_card_index = find( state.row(4 + second_player).t(), 
        1, "first" );
    state = move_card_from_to(state, 4 + second_player,
        4 + second_to_last_player, lowest_card_index(0));
    uvec highest_card_index = find( state.row(4 + second_to_last_player).t(), 
        1, "last" );
    state = move_card_from_to(state, 4 + second_to_last_player,
        4 + second_player, highest_card_index(0));


    return state;
}
*/