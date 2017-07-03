
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# execution of the game

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

mat manip_hands(mat A, mat a, int x){
    // add vec between row x in A;
    int j;

    for(int i = x; i <= a.n_rows; i++){
        A.row(i) = a.row(j);    
        j++;
    }

    return A;
}

    


