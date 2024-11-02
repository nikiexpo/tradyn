/*Created by Nikilesh Ramesh on 02/11/2024 at 19:08

Motivation: to test the functions written*/

#include "gradientFD.h"
#include <iostream>

int main(void){

    States x0 = {0.0,0.0,0.0,0.0};
    States xf = {2.0, 3.0, 4.0, 1.0};

    Inputs u0 = {0.0, 0.0};
    Inputs uf = {2, 2};

    Time t0 = 0;
    Time tf = 4;

    Gradient dJE = gradientFD_E(x0, xf, u0, uf, t0, tf, 0.001);

    for (auto &&i : dJE)
    {
        std::cout << i << ",";
    }
    std::cout << "\n";


    return 0;
}