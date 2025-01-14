#include "commonFuncs.h"

FLOAT_PRECISION vec_sum(const Gradient v){
    FLOAT_PRECISION sum = 0.0;
    for (auto &&i : v)
    {
        sum += i;
    }
    return sum;
}