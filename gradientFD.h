/* Created by Nikilesh Ramesh on 01/11/24 at 20:04

Motivation: To compute the cost gradient of dynamic optimizaion problems using finite differences*/

#ifndef __GRADIENT_FD__
#define __GRADIENT_FD__

#include "typeDefinitions.h"
#include <cassert>

bool gradientFD_L(
    Index nz, Index M, States X,
    Inputs U, Time t0, Time tf, Time T,
    Perturbation e,
    SparseMatrix* Lz, Gradient* dJL
);

Gradient gradientFD_E(
    States x0, States xf,
    Inputs u0, Inputs uf, Time t0,  Time tf,
    Perturbation e
);

const float finiteDiff(
    const States pp_x0, const States pp_xf,
    const Inputs pp_u0, const States pp_uf,
    const Time pp_t0, const Time pp_tf,
    const States np_x0, const States np_xf,
    const Inputs np_u0, const States np_uf,
    const Time np_t0, const Time np_tf, Perturbation e
);

#endif
