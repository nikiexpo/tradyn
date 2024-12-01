/*Created by Nikilesh Ramesh on 02/11/2024 at 19:08

Motivation: to test the functions written*/

#include "gradientFD.h"
#include "jacobian.h"
#include <iostream>

int main(void){

    States x0 = {0.0,0.0};
    States xf = {2.0, 3.0};

    Inputs u0 = {0.0};
    Inputs uf = {2};

    Time t0 = 0;
    Time tf = 4;

    Gradient dJE = gradientFD_E(x0, xf, u0, uf, t0, tf, 0.001);

    for (auto &&i : dJE)
    {
        std::cout << i << ",";
    }
    std::cout << "\n";


    StateVectors X = {
        {0.0, 1.0},
        {0.5, 1.5},
        {1.0, 2.0},
        {1.5, 2.5},
        {2.0, 3.0}
    };

    InputVectors U = {
        {0.0},
        {0.5},
        {1.0},
        {1.5},
        {2.0}
    };

    TimeVector T = {0.0, 0.250, 0.50, 0.750, 1.0};

    std::vector<CostVector> dJL = gradientFD_L(X, U, t0, tf, T, 0.001);
    for (auto &&i : dJL)
    {
        for (auto &&j : i)
        {
            std::cout << j << ",";
        }
        
        std::cout << "\n";
    }


    SparseMatrix test = jacobianF(X,U,T,t0,tf,0.001, true);

    return 0;
}