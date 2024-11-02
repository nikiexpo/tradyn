/*Created by Nikilesh Ramesh on 02/11/2024 at 13:33

Motivation: To consolidate all the type definitions into one file
*/

#ifndef __TYPE_DEFINITIONS__
#define __TYPE_DEFINITIONS__

#include <vector>

// SHOULD THE PRECISION BE DOUBLE INSTEAD OF FLOAT??

typedef const unsigned int Index;
typedef std::vector<float> Gradient;
typedef const float Perturbation; 
typedef std::vector<float> States;
typedef std::vector<float> Inputs;
typedef const float Time;
typedef float Cost;

typedef struct TripletSparsityFormat {
    std::vector<unsigned int> rows;
    std::vector<unsigned int> cols;
    std::vector<float> values;
}SparseMatrix;

typedef std::vector<unsigned int> PerturbationSelectionVector;

// IS THIS NEEDED? THINK! MAYBE BETTER OF WITH SOME OTHER METHOD
/* so idea is only one variable of the decision variable is perturbed at one time so like if you 
the diff wrt a single x_0 i.e. f_{x_0(i)} then you would choose i so have a vector = {i, j, k...}
where i, j, k etc are the idices to choose the value to perturb for x_0, x_f, u_0... */
// SHOULD THIS BE CONST? ONCE INITIALIZED THEY SHOULDN'T CHANGE 
// THE NEXT ITERATION THEY SHOULD CREATE A NEW INSTANCE IF THAT MAKES SENSE
// typedef struct PerturbationSelectionVectors {
//     std::vector<unsigned int> et0;
//     std::vector<unsigned int> etf;
//     std::vector<unsigned int> ex0;
//     std::vector<unsigned int> exf;
//     std::vector<unsigned int> eu0;
//     std::vector<unsigned int> euf;
//     // std::vector<unsigned int> ep; // for parameters
// } PerturbationSelectionVectors; 

// typedef struct Gradient
// {
//     Index n;
//     std::vector<float> grad_f;
// }Gradient;

#endif