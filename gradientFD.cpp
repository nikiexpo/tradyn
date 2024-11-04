/* Created by Nikilesh Ramesh on 01/11/24 at 20:04

Motivation: To compute the cost gradient of dynamic optimizaion problems using finite differences*/

#include "gradientFD.h"
#include "UserDefinedFunctions.h"
#include <iostream>

Gradient gradientFD_E(
    States x0, States xf,
    Inputs u0, Inputs uf, Time t0, Time tf,
    Perturbation e
){

    Gradient dJE;

    // dFdt_0
    Time pp_t0 = t0 + e;
    Time np_t0 = t0 - e;
    
    dJE.push_back(finiteDiff_E(x0,xf,u0,uf,pp_t0,tf,x0,xf,u0,uf,np_t0,tf,e));

    // dFdt_f
    Time pp_tf = tf + e;
    Time np_tf = tf - e;

    dJE.push_back(finiteDiff_E(x0,xf,u0,uf,t0,pp_tf,x0,xf,u0,uf,t0,np_tf,e));

    // dFdx_0
    States pp_x0 = x0;
    States np_x0 = x0;

    for (int i = 0; i < x0.size(); i++)
    {
        pp_x0[i] = pp_x0[i] + e;
        np_x0[i] = np_x0[i] - e;

        dJE.push_back(finiteDiff_E(pp_x0,xf,u0,uf,t0,tf,np_x0,xf,u0,uf,t0,tf,e));

        pp_x0[i] = x0[i];
        np_x0[i] = x0[i];
    }
    
    // dFdx_f
    States pp_xf = xf;
    States np_xf = xf;

    for (int i = 0; i < xf.size(); i++)
    {
        pp_xf[i] = pp_xf[i] + e;
        np_xf[i] = np_xf[i] - e;
        
        dJE.push_back(finiteDiff_E(x0,pp_xf,u0,uf,t0,tf,x0,np_xf,u0,uf,t0,tf,e));

        pp_xf[i] = xf[i];
        np_xf[i] = xf[i];

    }
    
    // dFdu_0
    Inputs pp_u0 = u0;
    Inputs np_u0 = u0;

    for (int i = 0; i < u0.size(); i++)
    {
        pp_u0[i] = pp_u0[i] + e;
        np_u0[i] = np_u0[i] - e;

        dJE.push_back(finiteDiff_E(x0,xf,pp_u0,uf,t0,tf,x0,xf,np_u0,uf,t0,tf,e));

        pp_u0[i] = u0[i];
        np_u0[i] = u0[i];

    }

    // dFdu_f
    Inputs pp_uf = uf;
    Inputs np_uf = uf;

    for (int i = 0; i < uf.size(); i++)
    {
        pp_uf[i] = pp_uf[i] + e;
        np_uf[i] = np_uf[i] - e;

        dJE.push_back(finiteDiff_E(x0,xf,u0,pp_uf,t0,tf,x0,xf,u0,np_uf,t0,tf,e));
        
        pp_uf[i] = uf[i];
        np_uf[i] = uf[i];
    }
    
    assert(dJE.size() == 2 + x0.size() + xf.size() + u0.size() + uf.size());
    std::cout<< "\nGradient of JE: Done" << std::endl;
    
    return dJE;
}

const double finiteDiff_E(
    const States pp_x0, const States pp_xf,
    const Inputs pp_u0, const States pp_uf,
    const Time pp_t0, const Time pp_tf,
    const States np_x0, const States np_xf,
    const Inputs np_u0, const States np_uf,
    const Time np_t0, const Time np_tf, Perturbation e
){
    const Cost postive_perturbed_value =  E_unscaled(pp_x0, pp_xf, pp_u0, pp_uf, pp_t0, pp_tf);
    const Cost negative_perturbed_value = E_unscaled(np_x0, np_xf, np_u0, np_uf ,np_t0, np_tf);
    return (const double) (postive_perturbed_value - negative_perturbed_value) / (2.0*e);
}


Gradient gradientFD_L(
    StateVectors X, InputVectors U,
    Time t0, Time tf, TimeVector T,
    Perturbation e
){
    Gradient dJL;

    // dJL_t0;
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
    
    // dJL_t0
    dJL.push_back(finiteDiff_L(X, U, X, U, pp_deltaT_t0, np_deltaT_t0, pp_T_t0, np_T_t0, e));
    // dJL_tf
    dJL.push_back(finiteDiff_L(X, U, X, U, pp_deltaT_tf, np_deltaT_tf, pp_T_tf, np_T_tf, e));

    // Set delta T back
    const Time deltaT = tf - t0;
    
    // dJL_X
    StateVectors pp_X = X;
    StateVectors np_X = X;

    for (int i = 0; i < X[0].size(); i++)
    {
        for (int j = 0; j < X.size(); j++)
        {
            pp_X[j][i] = pp_X[j][i] + e;
            np_X[j][i] = np_X[j][i] - e;
        }

        dJL.push_back(finiteDiff_L(pp_X, U, np_X, U, deltaT, deltaT, T, T, e));

        for (int j = 0; j < X.size(); j++)
        {
            pp_X[j][i] = X[j][i];
            np_X[j][i] = X[j][i];
        }        
        
    }
    InputVectors pp_U = U;
    InputVectors np_U = U;

    for (int i = 0; i < U[0].size(); i++)
    {
        for (int j = 0; j < U.size(); j++)
        {
            pp_U[j][i] = pp_U[j][i] + e;
            np_U[j][i] = np_U[j][i] - e;
        }

        dJL.push_back(finiteDiff_L(X, pp_U, X, np_U, deltaT, deltaT, T, T, e));

        for (int j = 0; j < U.size(); j++)
        {
            pp_U[j][i] = U[j][i];
            np_U[j][i] = U[j][i];
        }        
        
    }

    assert(dJL.size() == 2 + X[0].size() + U[0].size());
    std::cout<< "\nGradient of JL: Done" << std::endl;

    return dJL;
     
} 

const double finiteDiff_L(
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e
){
    const Cost postive_perturbed_value = L_unscaled(pp_X, pp_U, pp_T);
    const Cost negative_perturbed_value = L_unscaled(np_X, np_U, np_T);
    return (const double) ((pp_delta_T)*postive_perturbed_value - (np_delta_T)*negative_perturbed_value) / (2.0*e); 
}