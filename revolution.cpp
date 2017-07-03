
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# execution of the game

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

//### Helper Functions ### 


void create_deck(int n_players) {
    // initialise deck
    int n_single_decks = n_players / 4 + 1;
    int n_jokers = 3;
    int n_cards = n_single_decks * (n_jokers + 13 * 4);
    imat deck(n_cards , 2);

    for (int single_deck_num=1; single_deck_num <= n_single_decks; single_deck_num++) {
        // add jokers
        int first_card = (single_deck_num -1) * n_cards / n_single_decks; 
        int last_card = single_deck_num * (n_cards -1) / n_single_decks;

        deck.rows(first_card, first_card 1) = vec({0,13});
        //deck.rows(first_card, first_card + n_jokers - 1).each_row() = rowvec({0,13});
        for (int suite=1; suite <= 4; suite++) {
            //vec s = suite * (ones<vec>(13));
            vec s(13);  s.fill(suite);
            vec v = linspace<vec>(0,12, 13);

            mat deck_part = join_rows(s,v);
            //deck.rows(first_card +  n_jokers, last_card) = deck_part;    
            }
        };
            deck.print(" Matrix");

}

/*
# initiate Match
# define game mode
# define number of players
# define sequence of players
# initiate Players
# initiate empty Table
# initiate empty Discard
# repeat until total number of games is reached
    # initiate Game #
    # create deck with size according to the number of players
    # shuffle deck
    # distribute cards to hands of players, remaining cards are discarded (face-down)
        # update Players
        # update Discard
    # Exchange of cards between players    
    # sometimes, there is a choice left
    # (small action required) # currently ignored
        # first player and last player
        # swap cards
        # second player and second-to-last player
        # swap cards
        #    second_card, second_to_last_card)
    # define starting player (first game random, otherwise last player begins)
    ### Start of turns ###
    # repeat until game is over
    # Check possible moves
    # includes suite lock, doubles, triples, quadruples, revolution, straight
        # split into same value pools
        # calculate possible moves:
        # 1) Single, Double, Triple, ...
        # 2) Straights
        # remove duplicates (cards with same suite and value)
        # split into same suite pools
        # find neighbouring values
                        # calculate possible moves:
                        # Straight
        # unite moves
        ### INFO SECTION ###
        # check which of the possible moves are allowed considering the table
        # if table is not empty
            # straight
            # single, double, triple, ...
            # number of cards on top
            # check equality of suite with top cards if necessary
            # check whether the possible moves have a higher value
                # if greater than 0, then move is possible
                    # -13 for only 3 can top joker, joker can go under 3
            # append "Pass"
    ## Action of players ##
    # Action: Choose move or pass
    # update Player
        # remove cards from hand
    # update Game
    # update Table
        # add top cards
            # check suite lock condition
            # check straight condition
    ### Special cards and revolution ###
    # if revolution is played
        # update Game
    # if 10 is played:
            # discard one card for every 10
                # the last card can't be discarded
            # Action: Choose card in Hand
    ## End of Action ##
    # if Jack is played:
        # update Table
    # if 8 is played:
        # update Table
        # update Game (starting player)
                    # active player may play again
    ### Updating the game status ###
    # check if Hand of one Player is empty
        # repeat until all passed
            # check if all passed including player with top cards
            # empty the Table, player who played the last cards becomes active player
                # update Table
            # check now wether the player is already done
            # next player's turn
            # exclude finished players
        # repeat until one Player is left
    # end of game - update
    # Game
    # Match
    # End of Game #
    # repeat Game until total number of games is reached
# End of Match #
# Anounce ranking and winner
# display match stats
# FINALISE #
*/


int main(int argc, char *argv[]) {
// input GLOBALS
/*
N_GAMES = 10
N_PLAYERS = 4
GAME_MODE = "onehuman"
*/

create_deck(1);

return 0;
}