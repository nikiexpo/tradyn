/* Created by Nikilesh Ramesh on 01/11/24 at 20:04

Motivation: To compute the cost gradient of dynamic optimizaion problems using finite differences*/

#ifndef __GRADIENT_FD__
#define __GRADIENT_FD__

#include "typeDefinitions.h"
#include <cassert>

Gradient gradientFD_L(
    StateVectors X, InputVectors U,
    Time t0, Time tf, TimeVector T,
    Perturbation e
);

Gradient gradientFD_E(
    States x0, States xf,
    Inputs u0, Inputs uf, Time t0,  Time tf,
    Perturbation e
);

const double finiteDiff_E(
    const States pp_x0, const States pp_xf,
    const Inputs pp_u0, const States pp_uf,
    const Time pp_t0, const Time pp_tf,
    const States np_x0, const States np_xf,
    const Inputs np_u0, const States np_uf,
    const Time np_t0, const Time np_tf, Perturbation e
);

const double finiteDiff_L(
    const StateVectors pp_X, const InputVectors pp_U,
    const StateVectors np_X, const InputVectors np_U,
    const Time pp_delta_T, const Time np_delta_T,
    const TimeVector pp_T, const TimeVector np_T, Perturbation e
);

#endif
