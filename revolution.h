//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# Match structure
#ifndef REVOLUTION_H
#define REVOLUTION_H


// Global variables
#define N_PLAYERS 4

#define DECKSIZE 55 

#define N_GAMES 100

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;



struct Match{
    Match() :   player_ranking(N_PLAYERS),
                ranking_history(N_GAMES, N_PLAYERS) 
            {
            player_ranking.ones();
            player_ranking = player_ranking * -1; 
            ranking_history.ones();
            ranking_history = ranking_history * -1;
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


#endif