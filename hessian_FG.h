

#ifndef __HESSIAN_FG__
#define __HESSIAN_FG__

#include "typeDefinitions.h"
#include "UserDefinedFunctions.h"
#include "commonFuncs.h"

// HESSISAN IS size of NZxNZ where NZ = nt + np + M*n + N*m 

SparseMatrix hessian_FG(StateVectors X, InputVectors U, TimeVector T, Time t0, Time tf, Perturbation e, int numState);

#endif