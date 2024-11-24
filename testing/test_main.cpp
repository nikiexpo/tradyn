#include "../jacobian.h"
#include "../typeDefinitions.h"
#include <iostream>
#include <vector>
#include "rapidcsv.h"


int main(void){

    rapidcsv::Document doc("test.csv", rapidcsv::LabelParams(-1, -1));

    Inputs u1 = doc.GetColumn<double>(3);
    std::cout << "Read " << u1.size() << " values." << std::endl;

    States x2 = doc.GetColumn<double>(2);
    States x1 = doc.GetColumn<double>(1);
    TimeVector T = doc.GetColumn<double>(0);
    
    // for (int i = 0; i < T.size(); i++)
    // {
    //     std::cout<< T[i] << ", " << x1[i] << ", " << x2[i] << ", " << u[i] << std::endl;
    // }
    
    Time t0 = 0;
    Time tf = 30;
    Perturbation e = 4.8062e-06;
    
    StateVectors X;
    InputVectors U;
    for (int i = 0; i < x1.size(); i++)
    {
        X.push_back({x1[i], x2[i]});
        U.push_back({u1[i]});
    }


    jacobianF(X, U, T, t0, tf, e);
    return 0;
}
