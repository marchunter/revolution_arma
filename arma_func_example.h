
//# C++ with Armadillo library game called "Revolution"
//# Japanese game for any number of players
//# execution of the game

#include <iostream>
#include <armadillo>

// shortening the names vec instead of arma::vec
using namespace std;
using namespace arma;

imat manip_hands(imat A, imat a, int x){
    // add smaller mat between row x in mat A;
    // from indices x to x + (rows of a)
    int j = 0;
    for(int i = x; i < x + a.n_rows; i++){
        A.row(i) = a.row(j);    
        j++;
    }

cout << "function manip_hands done" << endl;
    return A;
}

    


