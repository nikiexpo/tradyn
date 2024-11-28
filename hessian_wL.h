/*Created by Nikilesh Ramesh on 28/11/2024 at 14:57
Motivation: To calculate the hessian of cost*/

#ifndef __HESSIAN_WL__
#define __HESSIAN_WL__

#include "typeDefinitions.h"
#include "UserDefinedFunctions.h"

SparseMatrix hessian_wL(StateVectors X, InputVectors U, TimeVector T, Time t0, Time tf, Perturbation e);

// use for double derivatie with respect to same variable
const Gradient hessWL_CD_xx(
    const StateVectors X, const InputVectors U,
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time t0, const Time tf, const TimeVector T,
    const Time delta_T, const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e
);

// use for partial derivatie with respect to different variables
const Gradient hessWL_CD_xy(
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e
);


#endif