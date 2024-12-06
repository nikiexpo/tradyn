/*Created by Nikilesh Ramesh on 6/12/2024 at 17:26
Motivation: Creating a Problem class that keeps track of the deciscion variables for all the jacobian/hessian compute
*/

#ifndef __PROBLEM__
#define __PROBLEM__

#include "typeDefinitions.h"

class Problem // TODO: Change types to Flat Matrix
{
private:
    StateVectors _X;
    InputVectors _U;
    TimeVector _T;
    Time _t0;
    Time _tf;
    Perturbation _e1;
    Perturbation _e2;
    bool _Constrained;
    int _TotalConstraints;
public:
    Problem(StateVectors X, InputVectors U, TimeVector T,
            Time t0, Time tf, Perturbation e1, Perturbation e2,
            bool Constrained, int TotalConstraints);
    ~Problem();
};

Problem::Problem(StateVectors X, InputVectors U, TimeVector T,
                Time t0, Time tf, Perturbation e1, Perturbation e2,
                bool Constrained, int TotalConstraints)
{
    _X = X;
    _U = U;
    _T = T;
    _t0 = t0;
    _tf = tf;
    _e1 = e1;
    _e2 = e2;
    _Constrained = Constrained;
    _TotalConstraints = TotalConstraints;
}

Problem::~Problem()
{
}

#endif