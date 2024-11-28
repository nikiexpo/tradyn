/*Created by Nikilesh Ramesh on 28/11/2024 at 14:57
Motivation: To calculate the hessian of cost*/

#include "hessian_wL.h"

SparseMatrix hessian_wL(StateVectors X, InputVectors U, TimeVector T, Time t0, Time tf, Perturbation e){

}

const Gradient hessWL_CD_xx(
    const StateVectors X, const InputVectors U,
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time t0, const Time tf, const TimeVector T,
    const Time delta_T, const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e
){
    Gradient hessWL_xx; 
    CostVector Lo =  L_unscaled(X,U,T);
    CostVector Lp2 = L_unscaled(pp_X, pp_U, pp_T);
    CostVector Lm2 = L_unscaled(np_X, np_U, np_T);
    double grad = 0.0;
    for (int i = 0; i < Lo.size(); i++)
    {
        Lo[i] = Lo[i] * delta_T;
        Lp2[i] = Lp2[i] * pp_delta_T;
        Lm2[i] = Lm2[i] * np_delta_T;
        grad = (Lp2[i] - 2*Lo[i] + Lm2[i]) / (e*e);
        hessWL_xx.push_back(grad);
    }
    return hessWL_xx;
}