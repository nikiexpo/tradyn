/*Created by Nikilesh Ramesh on 09/11/2024 at 15:36
Motivating: To compute the jacobian of OCP problem*/

#ifndef __JACOBIAN__
#define __JACOBIAN__

#include "typeDefinitions.h"
#include "UserDefinedFunctions.h"

SparseMatrix jacobianF(StateVectors X, InputVectors U, TimeVector T, Time t0, Time tf, Perturbation e, int numStates, bool constraints);

const Gradient finiteDiff_jacF(
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e, int numStates
);

const Gradient finiteDiff_jacG(
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e, int numConstraints
);




#endif