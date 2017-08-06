#include <iostream>
#include <string>
#include <armadillo>
#include <time.h>
#include "ga.h"
#include "simpleNN.h"


using namespace std;
using namespace arma;

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
vec sigmoid(vec inp){
    return 1/(1 + exp(-inp));
}
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
vec simpleNN(vec inp, mat inpWeights , cube weights, mat outWeights ,vec inpBiases, mat biases, vec outBiases){ 

    vec buffVec;
    buffVec = sigmoid(inpWeights*inp + inpBiases);

    for(int l = 0; l < weights.n_slices; l++){

            buffVec = sigmoid(weights.slice(l)*buffVec + biases.col(l));

      }


      return outWeights*buffVec + outBiases;
}
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
vec simpleNNmat(mat X, vec inp, mat inpWeights , cube weights, mat outWeights ,vec inpBiases, mat biases, vec outBiases){ 

    vec buffVec;
    buffVec = sigmoid(inpWeights*inp + inpBiases);

    vec inpWeightsVec = X(0, span( 0, inpWeights.n_elem - 1)).t();
    vec weightsVec =    X(0, span( inpWeights.n_elem, weights.n_elem - 1)).t();
    vec outWeightsVec = X(0, span( weights.n_elem, outWeights.n_elem - 1)).t();
    vec inpBiasesVec =  X(0, span( outWeights.n_elem, inpBiases.n_elem - 1 )).t();
    vec biasesVec =     X(0, span( inpBiases.n_elem , biases.n_elem - 1 )).t();
    vec outBiasesVec=   X(0, span( biases.n_elem , outBiases.n_elem - 1 )).t();

    int inpWeightsNx = inpWeights.n_rows;
    int inpWeightsNy = inpWeights.n_cols;

    int weightsNx = weights.n_rows;
    int weightsNy = weights.n_cols;
    int weightsNz = weights.n_slices;

    int outWeightsNx = outWeights.n_rows;
    int outWeightsNy = outWeights.n_cols;
    
    int inpBiasesN = inpBiases.n_elem;

    int biasesNx = biases.n_rows;
    int biasesNy = biases.n_cols;
   
    int outBiasesN = outBiases.n_elem;

    mat Y(X.n_rows, buffVec.n_elem);

    for(int i = 0; i < X.n_rows; i++){

        inpWeights.reshape(1,inpWeights.n_elem);
        inpWeights = X(i, span(i, inpWeights.n_elem - 1));

        weights.reshape(1,1,weights.n_elem);
        weights(1,1,span(0,weights.n_elem -1))= X(i, span(inpWeights.n_elem, weights.n_elem - 1));

        outWeightsVec= X(i, span(weights.n_elem, outWeights.n_elem - 1));
        inpBiasesVec= X(i, span( outWeights.n_elem, inpBiases.n_elem - 1 ));
        biasesVec = X(i, span(  inpBiases.n_elem , biases.n_elem - 1 ));
        outBiasesVec= X(i, span( biases.n_elem , outBiases.n_elem - 1 ));
        
        inpWeights = inpWeightsVec.t();
//    weights=weightsVec.reshape(weights.n_rows, weights.n_cols, weights.n_slices);
//    outWeights=outWeightsVec.reshape(size(outWeights));
        inpBiases=inpBiasesVec.t();
//    biasesVec.reshape(biases.n_rows, biases.n_cols).print("AAA");
        outBiases=outBiasesVec.t();

        for(int l = 0; l < weights.n_slices; l++){

            buffVec = sigmoid(weights.slice(l)*buffVec + biases.col(l));

          }

          Y.row(i) = outWeights*buffVec + outBiases;
   }


      return Y;
}
//------------------------------------------------------------------------------------------------------------------------













