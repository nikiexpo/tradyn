/*Created by Nikilesh Ramesh on 09/11/2024 at 15:56*/

#include "jacobian.h"
#include <iostream>


SparseMatrix jacobianF(StateVectors X, InputVectors U, TimeVector T, Time t0, Time tf, Perturbation e){
    SparseMatrix jacobian;

    // d(dx/dt)_t0;
    Time pp_deltaT_t0 = tf - (t0 - e); // deltaT increases with decrease in t0
    Time np_deltaT_t0 = tf - (t0 + e);

    TimeVector pp_T_t0;
    TimeVector np_T_t0;

    
    // dJL_tf
    Time pp_deltaT_tf = (tf + e) - t0; // deltaT increases with increase in tf
    Time np_deltaT_tf = (tf - e) - t0;

    TimeVector pp_T_tf;
    TimeVector np_T_tf;

    // doing both dJL_t0 and dJL_tf in a single for loop for efficiency
    for (auto &&i : T)
    {
        // t0
        pp_T_t0.push_back(pp_deltaT_t0*i + t0 + e);
        np_T_t0.push_back(np_deltaT_t0*i + t0 - e);
        // tf
        pp_T_tf.push_back(pp_deltaT_tf*i + t0 + e);
        np_T_tf.push_back(np_deltaT_tf*i + t0 - e);
    }
    

    // std::cout << "\nlog check" << std::endl;

    const Gradient jacDynamics_t0 = finiteDiff_jacF(X, U, X, U, pp_deltaT_t0, np_deltaT_t0, pp_T_t0, np_T_t0, e);
    const Gradient jacDynamics_tf = finiteDiff_jacF(X, U, X, U, pp_deltaT_tf, np_deltaT_tf, pp_T_tf, np_T_tf, e);
    
    // std::cout << "\nlog check" << std::endl;

    // Set delta T back
    const Time deltaT = tf - t0;
    
    // d(dx/dt)_X
    StateVectors pp_X = X;
    StateVectors np_X = X;

    Gradient jacDynamics_X; 
    // jacDynamics_X.reserve(X[0].size()*X.size()); // change later
    // std::cout << "\nlog check" << std::endl;
    for (int i = 0; i < X[0].size(); i++)
    {
        for (int j = 0; j < X.size(); j++)
        {
            pp_X[j][i] = pp_X[j][i] + e;
            np_X[j][i] = np_X[j][i] - e;
        }

        Gradient temp = finiteDiff_jacF(pp_X, U, np_X, U, deltaT, deltaT, T, T, e);

        for (auto &&i : temp)
        {
            jacDynamics_X.push_back(i);
            // std::cout << i << std::endl;
        }
        

        for (int j = 0; j < X.size(); j++)
        {
            pp_X[j][i] = X[j][i];
            np_X[j][i] = X[j][i];
        }        
        
    }

    InputVectors pp_U = U;
    InputVectors np_U = U;

    Gradient jacDynamics_U;

    for (int i = 0; i < U[0].size(); i++)
    {
        for (int j = 0; j < U.size(); j++)
        {
            pp_U[j][i] = pp_U[j][i] + e;
            np_U[j][i] = np_U[j][i] - e;
        }

        Gradient temp = finiteDiff_jacF(X, pp_U, X, np_U, deltaT, deltaT, T, T, e);
        std::cout << "Size of temp U : " << temp.size() << std::endl;
        for (auto &&i : temp)
        {
            jacDynamics_U.push_back(i);
        }

        for (int j = 0; j < U.size(); j++)
        {
            pp_U[j][i] = U[j][i];
            np_U[j][i] = U[j][i];
        }        
        
    }
    
    // printing the jacobian to debug (i know the sizes for now!!! 2 states and 1 input)
    // std::cout << "Jacobian Size: "<< jacDynamics_t0.size() << ", " << jacDynamics_tf.size() << ", " << jacDynamics_X.size() << ", " << jacDynamics_U.size() << std::endl; 

    std::cout << "\nDynamics part of the Jacobian Jfi : \n" << std::endl;
    for (int i = 0; i < T.size()*X[0].size(); i++)
    {
        std::cout << jacDynamics_t0[i] << ",\t" << jacDynamics_tf[i] << ",\t" << jacDynamics_X[i] << ",\t" << jacDynamics_X[1*T.size() + i] << ",\t" << jacDynamics_U[i] << std::endl; 
    }
    std::cout << "\n" << std::endl;
    

    return jacobian;
}

const Gradient finiteDiff_jacF(
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e
){
    const StateGradientVectors pp_dx = f_unscaled(pp_X, pp_U, pp_T);
    const StateGradientVectors np_dx = f_unscaled(np_X, np_U, np_T); 
    StateGradientVectors jacF;
    jacF.reserve(pp_dx.size());

    // std::cout << "\nlog check jacF: " << pp_T.size() << ", " << pp_X[0].size() << ", " << pp_X.size() << ", " << pp_U[0].size() << ", " << pp_U.size() << ", " << pp_dx.size() << std::endl;
    // std::cout << "dx"
    std::cout << " LOG  CHECK !" << std::endl;

    for (int  i = 0; i < pp_T.size(); i++)
    {
        for (int j = 0; j < pp_X[0].size(); j++)
        {
            jacF.push_back((pp_delta_T*pp_dx[j*pp_T.size() + i] - np_delta_T*np_dx[j*pp_T.size() + i])/(2*e)); // reshuffling to have [dx1 dx2 ... dxn]^T, check jacConstFD
        }        
    }
    // std::cout << "\nlog check" << std::endl;


    return (const Gradient) jacF;
}