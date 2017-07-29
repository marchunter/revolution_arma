
//// C++ with Armadillo library game called "Revolution"
//// Japanese game for any number of players
//// execution of the game

#include <iostream>
#include <armadillo>
#include "arma_func_example.h"
#include "init.h"
#include "cards.h"
#include "logic.h"
#include "human.h"
// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;


// Global variables
#define N_PLAYERS 4
#define DECKSIZE 55
#define N_GAMES  10


int main(int argc, char *argv[]) {

//  cpp random function, currently not needed.
//    srand(time(NULL));

// game modes currently not implemented.
// GAME_MODE = "onehuman"

// initiate Match
    // define game mode, number of players, sequence of players,
    // total number of games, starting player for next game.
struct Match
{
    Match() :   player_ranking(N_PLAYERS),
                ranking_history(N_GAMES, N_PLAYERS) 
            {
            player_ranking.zeros(); 
            ranking_history.zeros();
             }

    int n_players = N_PLAYERS;
    int n_total_games = N_GAMES;
    ivec player_ranking; 
    int n_games_played = 0;
    imat ranking_history; 
    int starting_player = 0;
    // match history, not implemented
    // game mode, not implemented

} Current_match;

Current_match.player_ranking.print("initialised Player Ranking: ");
Current_match.ranking_history.print("initialised Ranking History: ");

// repeat until total number of games is reached

// initiate Game //
// initiate Players, Discard, Table, empty Hands
imat state = init_state(Current_match.n_players, DECKSIZE);
state.print("initialised state of game:");

// shuffle deck
ivec indices = shuffle_deck(DECKSIZE);

// deal Hands

state = deal_hands(indices, state, 4);
state.raw_print("state of game after dealing Hands:");

if (Current_match.n_games_played > 0){
    // Exchange of cards between players    
    // sometimes, there is a choice left
    // (small action required) // currently ignored
        // first player and last player
        // swap cards
        // second player and second-to-last player
        // swap cards

    // for testing:
    // Current_match.player_ranking = {0,1,2,3};
    
    int first_player = Current_match.player_ranking(0);
    int second_player = Current_match.player_ranking(1);
    int last_player = Current_match.player_ranking(N_PLAYERS -1);
    int second_to_last_player = Current_match.player_ranking(N_PLAYERS -2);

    for (int i=0; i<=1; i++) {
        uvec lowest_card_index = find( state.row(4 + first_player), 
            1, "first" );
        state = move_card_from_to(state, 4 + first_player,
            4 + last_player, lowest_card_index(0));
        uvec highest_card_index = find( state.row(4 + last_player), 
            1, "last" );
        state = move_card_from_to(state, 4 + last_player,
            4 + first_player, highest_card_index(0));
        }

    uvec lowest_card_index = find( state.row(4 + second_player), 
        1, "first" );
    state = move_card_from_to(state, 4 + second_player,
        4 + second_to_last_player, lowest_card_index(0));
    uvec highest_card_index = find( state.row(4 + second_to_last_player), 
        1, "last" );
    state = move_card_from_to(state, 4 + second_to_last_player,
        4 + second_player, highest_card_index(0));


    state.raw_print("state of game after swapping cards:");

}

    ////// Start of turns //////
    int active_player = Current_match.starting_player;
    // repeat until game is over
    while (min(Current_match.player_ranking) == 0){

    //// Action of players ////
    // Action: Choose move or pass

    // Feeding current state and game struct to NN
    // TODO !!! //


    // Output of NN redirected --> Currently simulated by
    // dumb random move generator who mostly chooses "Pass".

    // Random move selection, might not be a valid move:
    bool is_valid = false;
    ivec move(DECKSIZE);
    do
    {
        ivec n_cards_vec = randi<ivec>(1,distr_param(0, 4));
        int n_cards = n_cards_vec(0);
        ivec move_idx = randi<ivec>(n_cards, distr_param(0, DECKSIZE -1));

        move.zeros();

        for (int i=0; i < move_idx.size(); i++){
            move(move_idx(i)) = 1;
        }

    is_valid = validate_move(state, move, Current_game, 0);

    } while (is_valid == false);

    //// End of Action ////


    print_state(state);
    printf("Current move: ");
    print_state_row(move, DECKSIZE);
    
    // Player passes
    if (sum(move) == 0) {
        active_player += 1;
        active_player % (Current_match.n_players -1);
        break;
        }
    // update Game

    ivec top_cards = state.row(2); 
    ivec sec_top_cards = state.row(3); 
        // check suite lock condition
    if (do_suites_match(move, top_cards) == 1) {
        Current_game.is_suite_lock = true;}
        // check straight condition
    if (is_straight(move) == 1) {Current_game.is_straight = true;}

    // move top cards to 2nd-top-cards, and those to Discard
    state = move_cards_from_to(state, 3, 1, sec_top_cards);
    state = move_cards_from_to(state, 2, 3, top_cards);

    // remove cards from hand and         
    // add top cards

    state = move_cards_from_to(state, active_player + 4, 2, move);

    ////// Special cards and revolution //////
    // if revolution is played
    if (sum(move) >= 4){
        Current_game.is_revolution = true;
    }
    // if 10 is played:

    for (int i=28; i<32; i++){
        ivec hand = state.row(active_player + 4);
        if ((move(i) == 1) && (sum(hand) > 1)){
            // discard one card for every 10
                // the last card can't be discarded
        // Action: Choose card in Hand
        
        // Feeding current state and game struct to NN
        // TODO !!! //


        // Output of NN redirected --> Currently simulated by
        // dumb move generator who chooses to discard the lowest.
            uvec lowest_card_index = find( 
                hand, 1, "first" );
            state = move_card_from_to(state, 4 + active_player,
                1, lowest_card_index(0));

        //// End of Action ////

            }
        }
    
    // if Jack is played:
    for (int i=32; i<36; i++){
        if (move(i) == 1) {
            Current_game.is_jack = !Current_game.is_jack;
            break;
            }
        }
        // update Table
    // if 8 is played:
    for (int i=20; i<24; i++){
        if (move(i) == 1) {
            // update Table
            top_cards = state.row(2); 
            sec_top_cards = state.row(3);
            state = move_cards_from_to(state, 3, 1, sec_top_cards);
            state = move_cards_from_to(state, 2, 1, top_cards); 

            // active player may play again    
            break;
            }
        }

    ////// Updating the game status //////

    // check if Hand of one Player is empty

        // repeat until all passed
            // check if all passed including player with top cards
    Current_game.top_player = active_player;

            // empty the Table, player who played the last cards becomes active player
                // update Table
            // check now wether the player is already done
            // next player's turn
            // exclude finished players
        // repeat until no players are left
    }
    // end of game - update
    // Game

    // Match, starting player
    // End of Game //
    // repeat Game until total number of games is reached
// End of Match //
// Anounce ranking and winner
// display match stats
// FINALISE //



return 0;
}
