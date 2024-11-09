/*Created by Nikilesh Ramesh on 09/11/2024 at 15:56*/

#include "jacobian.h"


SparseMatrix jacobianF(StateVectors X, InputVectors U, TimeVector T){
    SparseMatrix jacobian;
    
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

    for (int  i = 0; i < pp_T.size(); i++)
    {
        for (int j = 0; j < pp_X[0].size(); j++)
        {
            jacF[i*pp_X[0].size() + j] = (pp_delta_T*pp_dx[j*pp_T.size() + i] - np_delta_T*np_dx[j*pp_T.size() + i])/(2*e); // reshuffling to have [dx1 dx2 ... dxn]^T, check jacConstFD
        }
        
    }

    return (const Gradient) jacF;
}