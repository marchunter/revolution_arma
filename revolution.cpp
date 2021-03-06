
//// C++ with Armadillo library game called "Revolution"
//// Japanese game for any number of players
//// execution of the game

#include <unistd.h>
#include <iostream>
#include <armadillo>
#include "revolution.h"
#include "init.h"
#include "cards.h"
#include "logic.h"
#include "human.h"
#include "action.h"
#include "simpleNN.h"
#include "ga.h"
// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

int main(int argc, char *argv[]) {

//  cpp random function, currently not needed.
//    srand(time(NULL));

// game modes currently not implemented.
// GAME_MODE = "onehuman"

// GLOBALS
bool is_valid = false; // is the randomly selected play valid?
ivec move(DECKSIZE);  // vector with current move (play or pass)
int n_total_pass = 0;


// GA variables
int population = 100;
vec fitness=zeros<vec>(population);
int n_generations = 20;

vec gen_best_fitness(n_generations);
ivec gen_n_passes(n_generations);

// initialise structure for NN:
vec inp(4 * DECKSIZE);
//vec inp = ones<vec>(1);
int inpSize = inp.n_elem;
int height = 10;
int depth = 5;
int outputSize = DECKSIZE;


// initialise weights for NN:
mat inpWeights = ones<mat>(height,inpSize);
cube weights = ones<cube>(height,height,depth);
mat outWeights = ones<mat>(outputSize,height);

// initialise biases for NN:
vec inpBiases = ones<vec>(height);
mat biases = ones<mat>(height,depth);
vec outBiases = ones<vec>(outputSize);



// initialise random weights with population for NN:
mat DNAS=1 - 2*randu<mat>(fitness.n_elem, 
    inpWeights.n_elem + weights.n_elem + outWeights.n_elem + 
    inpBiases.n_elem + biases.n_elem + outBiases.n_elem);


// buffers for NN:
mat outputs = zeros<mat>(population,outBiases.n_elem);
vec outputsFinal = zeros<vec>(outBiases.n_elem);
//vec finalResult(myx.n_elem);



// Start of GA for loop
for (int generation = 0; generation < n_generations; generation++){

n_total_pass = 0;
fitness.zeros();
printf("Starting generation %d\n", generation);

// initiate Match
    // define game mode, number of players, sequence of players,
    // total number of games, starting player for next game.


//Current_match.player_ranking.print("initialised Player Ranking: ");
//Current_match.ranking_history.print("initialised Ranking History: ");

// repeat until total number of games is reached
for (int game_count = 0; 
    game_count < Current_match.n_total_games;
    game_count++) {
    //printf("Starting game number %d\n", game_count + 1);

// Divide population into player seats.
ivec pop_shuffled_indices = shuffle_deck(population);
ivec pop_seating(population);
for (int i=0; i < pop_shuffled_indices.n_elem; i++){
    // will take values between 0 and N_PLAYERS - 1.
    pop_seating(pop_shuffled_indices(i)) 
        = (Current_match.n_players) * (i)/ pop_seating.n_elem;

}

//pop_seating.t().print("Population Seating distributed: ");
//cout << sum(pop_seating) << endl;

// initiate Game //
// initiate Players, Discard, Table, empty Hands
imat state = init_state(Current_match.n_players, DECKSIZE);

// shuffle deck
ivec indices = shuffle_deck(DECKSIZE);

// deal Hands
state = deal_hands(indices, state, 4);
//printf("state of game after dealing Hands:\n");
//print_state(state);


if (Current_match.n_games_played > 0){
    // Exchange of cards between players    
    // sometimes, there is a choice left
    // (small action required) // currently ignored
        // first player and last player
        // swap cards
        // second player and second-to-last player
        // swap cards

    state = swap_cards(state, Current_match, N_PLAYERS);

    //printf("state of game after swapping cards:\n");
    //print_state(state);

    // setting player ranking back for game logic
    Current_match.player_ranking.ones();
    Current_match.player_ranking = Current_match.player_ranking * -1;

}
    ////// Start of turns //////
    int active_player = Current_match.starting_player;
    // repeat until game is over
    while (min(Current_match.player_ranking) == -1){
    //printf("------------\nTurn starts\n--------------\n");

    //// Action of players ////
    // Action: Choose move or pass
    ivec move(DECKSIZE);

    // default move is PASS
    move.zeros();

    // Feeding current state and game struct to NN
    // TODO !!! //

    ivec nn_i_inp(4 * DECKSIZE);
    uvec in_rows = zeros<uvec>(4);
    in_rows(0) = 1;
    in_rows(1) = 2;
    in_rows(2) = 3;
    in_rows(3) = active_player + 4;
    nn_i_inp = vectorise(state.rows(in_rows));
    inp = conv_to<vec>::from(nn_i_inp);

    vec nn_out(DECKSIZE);

    outputs = simpleNNmat(DNAS,inp, inpWeights, weights, outWeights, 
        inpBiases, biases, outBiases);

    int is_at_least_one_valid = false;
    for (int person=0; person < population; person++){
  	    int is_valid = false;

    	nn_out = outputs.row(person).t();
    	//uvec max_move_uvec(DECKSIZE);
		int maximum_index = index_max(nn_out);
    	ivec max_move(DECKSIZE);
    	max_move.zeros();
    	max_move(maximum_index) = 1; 
    	//conv_to<ivec>::from(max_move_uvec);
   		is_valid = validate_move(state, max_move, 
   			    Current_game, active_player);
   		if (is_valid == true){
   			move = max_move;
   			is_at_least_one_valid = true;
   		}
   		/* // Punish whenever passing, not good strategy 
        else {
   			// increase fitness
   			fitness(person) += 1;
   		}
        */
    }

    // Random move selection after all the NNs have failed:
    if (is_at_least_one_valid == false){
	    
	    move = choose_move_randomly(state, Current_game, 
    	    active_player, DECKSIZE);
    }
    
    //// End of Action ////
    
    // Player passes
    if (sum(move) == 0) {
        //printf("PASS \n");
        n_total_pass +=1;
        //usleep(100000);
    }
    // update Game
    else {

        //printf("PLAY \n");

        // check suite lock condition
        ivec top_cards = state.row(2).t(); 
    if (do_suites_match(move, top_cards) == 1) {
        Current_game.is_suite_lock = true;}
        // check straight condition
    if (is_straight(move) == 1) {Current_game.is_straight = true;}

    // Card(s) played, table, hand and discard updated.
    state = play_cards(state, move, active_player);
    
    //printf("Current move (player %d): ", active_player);
    //print_state_row(move, DECKSIZE);
    //print_state(state);




    ////// Special cards and revolution //////
    //printf("Special cards are triggered\n");

    // if revolution is played
    if (sum(move) >= 4){
        Current_game.is_revolution = true;
    }
    // if 10 is played:

    for (int i=28; i<32; i++){
        ivec hand = state.row(active_player + 4).t();
        if ((move(i) == 1) && (sum(hand) > 1)){
            //printf("Discard after a 10 is played\n");

            // discard one card for every 10
                // the last card can't be discarded
        // Action: Choose card in Hand
        
        // Feeding current state and game struct to NN
        // TODO !!! //

          /*
        ivec nn_in(4 * DECKSIZE);
        uvec in_rows = zeros<uvec>(4);
        in_rows(0) = 1;
        in_rows(1) = 2;
        in_rows(2) = 3;
        in_rows(3) = active_player + 4;
        nn_in = vectorise(state.rows(in_rows));
            ivec nn_out(DECKSIZE);

        // TODO: needs to be validated by
        //int is_valid = false; 
        //if (sum(nn_out) == 1){is_valid = true;}

        // Output of NN redirected --> Currently simulated by
        // dumb move generator who chooses to discard the lowest.
            uvec lowest_card_index = find( 
                hand, 1, "first" );
            state = move_card_from_to(state, 4 + active_player,
                1, lowest_card_index(0));
		*/
        //// End of Action ////

            }
        }
    // if Jack is played:
    for (int i=32; i<36; i++){
        if (move(i) == 1) {
            //printf("A Jack has been played\n");
            Current_game.is_jack = !Current_game.is_jack;
            break;
            }
        }
        // update Table
    // if 8 is played:
    int is_eight = false;
    for (int i=20; i<24; i++){
        if (move(i) == 1) {
            //printf("An eight has been played\n");
            // clear Table
            state = clear_table(state);

            // update game struct
            Current_game.is_jack = false;
            Current_game.is_suite_lock = false;
            Current_game.is_straight = false;
            Current_game.top_player = -2;

            is_eight = true;    
            }
        }
    if (is_eight == true){
        // check if Hand of active Player is empty
        if (sum(state.row(active_player + 4) == 0)){}
        else { 
            // active player may play again
            continue;
            }
        }
    }
    ////// Updating the game status //////
       //printf("Updating Game Status\n");

    // check if Hand of active Player is empty
    if (sum(state.row(active_player + 4)) == 0){
        uvec lowest_zero_index = find( 
            Current_match.player_ranking == -1, 
            1, "first" );
        // Player has finished!
        //printf("Player %d has finished!\n", active_player);
        Current_match.player_ranking(lowest_zero_index(0)) = active_player;
        //Current_match.player_ranking.raw_print("Ranking in Running Game");
        }


        // repeat until all passed
            // check if all passed including player with top cards
        //printf("Whose cards are on top?: %d\n", Current_game.top_player);
        //printf("Whose turn is it?: %d\n", active_player);
        if ((Current_game.top_player == active_player) 
            && (sum(move) == 0)){
            // Empty table
            state = clear_table(state);

            Current_game.is_jack = false;
            Current_game.is_suite_lock = false;
            Current_game.is_straight = false;
            Current_game.top_player = -2;

            // Top player = active player may play again.
            if (sum(state.row(active_player + 4)) != 0){
                //printf("All passed. Player %d opens\n", active_player);
                continue;                
            }
     
        }
        else {
            if (sum(move) != 0) {
                Current_game.top_player = active_player;
                }
            }

        // change top player if he or she has already finished.
        while ((any(Current_match.player_ranking 
            == Current_game.top_player) == true) &&
            (all(Current_match.player_ranking > -1) == false)){

            Current_game.top_player += 1;
            Current_game.top_player = Current_game.top_player 
                % Current_match.n_players;
            //printf("Top player virtually changed: %d\n", 
                //Current_game.top_player);

                } 

        // next player's turn, skip players who have already finished
        do {
        active_player += 1;
        active_player = 
            active_player % Current_match.n_players;
        //printf("Next player's turn, Player: %d\n", active_player);
        //Current_match.player_ranking.raw_print("Ranking of Running game");
        //printf("Check booleans: break, all done? %d, Player done? %d\n",
        //    all(Current_match.player_ranking > -1),
        //    any(Current_match.player_ranking == active_player)
        //    ); 
            // check if all players are already done
            if (all(Current_match.player_ranking > -1) == true) {break;}
            } while
            // check now wether the player is already done
            (any(Current_match.player_ranking == active_player) == true);

    }
    // end of game - update ...
        // ... Game
    Current_game.is_revolution = false;
    Current_game.is_jack = false;
    Current_game.top_player = -2;
    Current_game.starting_player = Current_match.player_ranking(0);
    Current_game.is_suite_lock = false;
    Current_game.is_straight = false;

        // ... Match, starting player
    Current_match.starting_player = Current_match.player_ranking(0);

    Current_match.n_games_played += 1;
    Current_match.ranking_history.row(Current_match.n_games_played -1) 
        = Current_match.player_ranking.t();


    // Winners of the population will get a treat
    for (int i = 0; i < pop_seating.n_elem; i++){
        if (pop_seating(i) == Current_game.starting_player){
            fitness(i) -= 1;
        }
    
    }
    

    // End of Game //
    }
// End of Match //

// display match stats
Current_match.ranking_history.print("Ranking history:");

// Anounce ranking and winner
//hist(Current_match.ranking_history.col(0)).print("Histogram of wins");

// reset Match:
Current_match.player_ranking.ones();
Current_match.player_ranking = Current_match.player_ranking * -1; 
Current_match.ranking_history.ones();
Current_match.ranking_history = Current_match.ranking_history * -1;
 
Current_match.n_games_played = 0;
Current_match.starting_player = 0;

// update GA
int temperature = 10;
int alpha = 1;

printf("before DNA breeding\n");

DNAS = ga_eval(DNAS, fitness, alpha,0.00000001, temperature);


fitness.print("Fitness of current generation");
printf("Fittest person: %f\n", min(fitness));
printf("Total number of passes: %d\n", n_total_pass);


gen_best_fitness(generation) = min(fitness);
gen_n_passes(generation) = n_total_pass;

sleep(2);
// End of GA for loop
}

// FINALISE //

printf("Final total number of passes%d\n", n_total_pass);
fitness.print("Fitness Final");

printf("Summary:\n");
printf("-----------------------\n");

gen_best_fitness.print("Best Fitness per Generation:");

gen_n_passes.print("Total number of passes per Generation:");

return 0;
}
