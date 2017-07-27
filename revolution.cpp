
//// C++ with Armadillo library game called "Revolution"
//// Japanese game for any number of players
//// execution of the game

#include <iostream>
#include <armadillo>
#include "arma_func_example.h"
#include "init.h"
#include "cards.h"
#include "logic.h"

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;


// Global variables
#define N_PLAYERS 4
#define DECKSIZE 55
#define N_GAMES  10

/*
// initiate Match
// define game mode
// define number of players
// define sequence of players
// initiate Players
// initiate empty Table
// initiate empty Discard
// repeat until total number of games is reached
    // initiate Game //
    // create deck with size according to the number of players
    // shuffle deck
    // distribute cards to hands of players, remaining cards are discarded (face-down)
        // update Players
        // update Discard
    // Exchange of cards between players    
    // sometimes, there is a choice left
    // (small action required) // currently ignored
        // first player and last player
        // swap cards
        // second player and second-to-last player
        // swap cards
        //    second_card, second_to_last_card)
    // define starting player (first game random, otherwise last player begins)
    ////// Start of turns //////
    // repeat until game is over
    // Check possible moves
    // includes suite lock, doubles, triples, quadruples, revolution, straight
        // split into same value pools
        // calculate possible moves:
        // 1) Single, Double, Triple, ...
        // 2) Straights
        // remove duplicates (cards with same suite and value)
        // split into same suite pools
        // find neighbouring values
                        // calculate possible moves:
                        // Straight
        // unite moves
        ////// INFO SECTION //////
        // check which of the possible moves are allowed considering the table
        // if table is not empty
            // straight
            // single, double, triple, ...
            // number of cards on top
            // check equality of suite with top cards if necessary
            // check whether the possible moves have a higher value
                // if greater than 0, then move is possible
                    // -13 for only 3 can top joker, joker can go under 3
            // append "Pass"
    //// Action of players ////
    // Action: Choose move or pass
    // update Player
        // remove cards from hand
    // update Game
    // update Table
        // add top cards
            // check suite lock condition
            // check straight condition
    ////// Special cards and revolution //////
    // if revolution is played
        // update Game
    // if 10 is played:
            // discard one card for every 10
                // the last card can't be discarded
            // Action: Choose card in Hand
    //// End of Action ////
    // if Jack is played:
        // update Table
    // if 8 is played:
        // update Table
        // update Game (starting player)
                    // active player may play again
    ////// Updating the game status //////
    // check if Hand of one Player is empty
        // repeat until all passed
            // check if all passed including player with top cards
            // empty the Table, player who played the last cards becomes active player
                // update Table
            // check now wether the player is already done
            // next player's turn
            // exclude finished players
        // repeat until one Player is left
    // end of game - update
    // Game
    // Match
    // End of Game //
    // repeat Game until total number of games is reached
// End of Match //
// Anounce ranking and winner
// display match stats
// FINALISE //
*/


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
struct Game
{
    bool is_revolution = false;
    bool is_jack = false;
    int top_player = 0;
    int starting_player = 0;
    bool is_suite_lock = false;
    bool is_straight = false;
    // game history, not implemented

} Current_game;


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
    // repeat until game is over

    

    // Check possible moves
    // includes suite lock, doubles, triples, quadruples, revolution, straight
        // split into same value pools
        // calculate possible moves:
        // 1) Single, Double, Triple, ...
        // 2) Straights
        // remove duplicates (cards with same suite and value)
        // split into same suite pools
        // find neighbouring values
                        // calculate possible moves:
                        // Straight
        // unite moves
        ////// INFO SECTION //////
        // check which of the possible moves are allowed considering the table
        // if table is not empty
            // straight
            // single, double, triple, ...
            // number of cards on top
            // check equality of suite with top cards if necessary
            // check whether the possible moves have a higher value
                // if greater than 0, then move is possible
                    // -13 for only 3 can top joker, joker can go under 3
            // append "Pass"

    //// Action of players ////
    // Action: Choose move or pass

    // Feeding current state and game struct to NN

    // Random move selection, might not be a valid move:
    bool is_valid = false;
    do
    {
        ivec n_cards_vec = randi<ivec>(1,distr_param(0, 4));
        int n_cards = n_cards_vec(0);
        ivec move_idx = randi<ivec>(n_cards, distr_param(0, DECKSIZE -1));

        ivec move(DECKSIZE);
        move.zeros();

        for (int i=0; i < move_idx.size(); i++){
            move(move_idx(i)) = 1;
        }
        move.t().raw_print("selected unvalidated move");

        // Validate move
        //int is_same_value = are_all_same_value(move);

        //int is_same_suite = are_all_same_suite(move);

        //printf("n cards: %d, same value?: %d, same suite?: %d\n", 
        //    sum(move), is_same_value, is_same_suite);


    // TESTING move, state, top_cards, ...
        
    ivec same_move = move;
    ivec other_move = move;
    move(1) = 1;

    other_move(0) = 1;
    other_move.t().print("other move for comparison, testing:");
    int is_suite_matching = do_suites_match(move, other_move);
    printf("suites are matching?: %d\n", is_suite_matching);

    validate_move(state, move, Current_game, 0)

        is_valid = true;
    } while (is_valid == false);

    // Choose move


    // update Player
        // remove cards from hand
    // update Game
    // update Table
        // add top cards
            // check suite lock condition
            // check straight condition
    ////// Special cards and revolution //////
    // if revolution is played
        // update Game
    // if 10 is played:
            // discard one card for every 10
                // the last card can't be discarded
            // Action: Choose card in Hand
    //// End of Action ////
    // if Jack is played:
        // update Table
    // if 8 is played:
        // update Table
        // update Game (starting player)
                    // active player may play again
    ////// Updating the game status //////
    // check if Hand of one Player is empty
        // repeat until all passed
            // check if all passed including player with top cards
            // empty the Table, player who played the last cards becomes active player
                // update Table
            // check now wether the player is already done
            // next player's turn
            // exclude finished players
        // repeat until one Player is left
    // end of game - update
    // Game
    // Match, starting player
    // End of Game //
    // repeat Game until total number of games is reached
// End of Match //
// Anounce ranking and winner
// display match stats
// FINALISE //







// Testing ground 


/*
state = add_card(state, 4, 2);
state.print("state of game, card 2 added to row 4:");


state = move_card_from_to(state, 0, 1, 5);
state.print("state of game, card 5 moved from 0 to 1:");

state = deal_hands(indices, state, 4);
state.print("state of game, after dealing all hands");
*/

return 0;
}
