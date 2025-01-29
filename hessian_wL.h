/*Created by Nikilesh Ramesh on 28/11/2024 at 14:57
Motivation: To calculate the hessian of cost*/

#ifndef __HESSIAN_WL__
#define __HESSIAN_WL__

#include "typeDefinitions.h"
#include "UserDefinedFunctions.h"
#include "commonFuncs.h"

// HESSISAN IS size of NZxNZ where NZ = nt + np + M*n + N*m 

SparseMatrix hessian_wL(StateVectors X, InputVectors U, TimeVector T, Time t0, Time tf, Perturbation e);



#endif