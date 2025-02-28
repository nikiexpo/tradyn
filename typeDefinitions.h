/*Created by Nikilesh Ramesh on 02/11/2024 at 13:33

Motivation: To consolidate all the type definitions into one file
*/

#ifndef __TYPE_DEFINITIONS__
#define __TYPE_DEFINITIONS__

#include <vector>
#include <iostream>

// SHOULD THE PRECISION BE DOUBLE INSTEAD OF FLOAT?? --- YES ! IPOPT uses double as default
// https://stackoverflow.com/questions/57542919/how-to-reserve-a-multi-dimensional-vector-without-increasing-the-vector-size (IMP READ)

#define FLOAT_PRECISION double

typedef const unsigned int Index;
typedef std::vector<FLOAT_PRECISION> Gradient;
typedef FLOAT_PRECISION Perturbation; 
typedef std::vector<FLOAT_PRECISION> States;
typedef std::vector<std::vector<FLOAT_PRECISION>> StateVectors;
typedef std::vector<FLOAT_PRECISION> StateGradientVectors;
typedef std::vector<FLOAT_PRECISION> Inputs;
typedef std::vector<std::vector<FLOAT_PRECISION>> InputVectors;
typedef FLOAT_PRECISION Time;
typedef std::vector<FLOAT_PRECISION> TimeVector;
typedef FLOAT_PRECISION Cost;
typedef std::vector<FLOAT_PRECISION> CostVector;
typedef std::vector<FLOAT_PRECISION> ConstraintVector;

// operator overloading on std::vector
template <typename T>
std::vector<T> operator+(std::vector<T> v, T val){
    for (auto &&i : v)
    {
        i += val;
    }
    return v;
}
template <typename T>
std::vector<T> operator+(std::vector<T> v1, std::vector<T> v2){
    for (int i = 0; i < v1.size(); i++)
    {
        v1[i] = v1[i] + v2[i]; //collecting in v1 to avoid making another copy
    }
    
    return v1;
}
template <typename T>
std::vector<T> operator-(std::vector<T> v1, std::vector<T> v2){
    for (int i = 0; i < v1.size(); i++)
    {
        v1[i] = v1[i] - v2[i]; //collecting in v1 to avoid making another copy
    }
    
    return v1;
}
template <typename T>
std::vector<T> operator*(std::vector<T> v, T val){
    for (auto &&i : v)
    {
        i *= val;
    }
    return v;
}
template <typename T>
std::vector<T> operator*(std::vector<T> v1, std::vector<T> v2){
    for (int i = 0; i < v1.size(); i++)
    {
        v1[i] = v1[i] * v2[i]; //collecting in v1 to avoid making another copy
    }
    
    return v1;
}



typedef struct TripletSparsityFormat {
    std::vector<unsigned int> rows;
    std::vector<unsigned int> cols;
    std::vector<FLOAT_PRECISION> values;

    TripletSparsityFormat(const int size){
        rows.resize(size);
        cols.resize(size);
        values.resize(size);
    }
    TripletSparsityFormat(void){} // does nothing
    void printInfo(){
        std::cout<< "Rows: " << rows.size() << " | Cols: " << cols.size() << std::endl;
    }
    void printFull(){
        for (int k = 0; k < rows.size(); k++)
        {
            std::cout << "(" << rows[k] <<"," << cols[k] <<") = " << values[k] << std::endl;
        }
        
    }
}SparseMatrix;




typedef struct FlatMatrix {
    std::vector<FLOAT_PRECISION> vals;
    FlatMatrix& operator +(FLOAT_PRECISION x){
        for (auto &&i : vals)
        {
            i += x;
        }
        return *this;
    }
}FlatMatrix;



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
//     std::vector<double> grad_f;
// }Gradient;

#endif