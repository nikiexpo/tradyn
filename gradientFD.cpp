/* Created by Nikilesh Ramesh on 01/11/24 at 20:04

Motivation: To compute the cost gradient of dynamic optimizaion problems using finite differences*/

#include "gradientFD.h"
#include "UserDefinedFunctions.h"


Gradient gradientFD_E(
    States x0, States xf,
    Inputs u0, Inputs uf, Time t0, Time tf,
    Perturbation e
){

    Gradient dJE;

    // dFdt_0
    Time pp_t0 = t0 + e;
    Time np_t0 = t0 - e;
    
    dJE.push_back(finiteDiff(x0,xf,u0,uf,pp_t0,tf,x0,xf,u0,uf,np_t0,tf,e));

    // dFdt_f
    Time pp_tf = tf + e;
    Time np_tf = tf - e;

    dJE.push_back(finiteDiff(x0,xf,u0,uf,t0,pp_tf,x0,xf,u0,uf,t0,np_tf,e));

    // dFdx_0
    States pp_x0 = x0;
    States np_x0 = x0;

    for (int i = 0; i < x0.size(); i++)
    {
        pp_x0[i] = pp_x0[i] + e;
        np_x0[i] = np_x0[i] - e;

        dJE.push_back(finiteDiff(pp_x0,xf,u0,uf,t0,tf,np_x0,xf,u0,uf,t0,tf,e));

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
        
        dJE.push_back(finiteDiff(x0,pp_xf,u0,uf,t0,tf,x0,np_xf,u0,uf,t0,tf,e));

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

        dJE.push_back(finiteDiff(x0,xf,pp_u0,uf,t0,tf,x0,xf,np_u0,uf,t0,tf,e));

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

        dJE.push_back(finiteDiff(x0,xf,u0,pp_uf,t0,tf,x0,xf,u0,np_uf,t0,tf,e));
        
        pp_uf[i] = uf[i];
        np_uf[i] = uf[i];
    }
    
    assert(dJE.size() == 2 + x0.size() + xf.size() + u0.size() + uf.size());
    
    return dJE;
}

const float finiteDiff(
    const States pp_x0, const States pp_xf,
    const Inputs pp_u0, const States pp_uf,
    const Time pp_t0, const Time pp_tf,
    const States np_x0, const States np_xf,
    const Inputs np_u0, const States np_uf,
    const Time np_t0, const Time np_tf, Perturbation e
){
    const float postive_perturbed_value =  E_unscaled(pp_x0, pp_xf, pp_u0, pp_uf, pp_t0, pp_tf);
    const float negative_perturbed_value = E_unscaled(np_x0, np_xf, np_u0, np_uf ,np_t0, np_tf);
    return (const float) (postive_perturbed_value - negative_perturbed_value) / (2.0*e);
}