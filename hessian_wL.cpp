/*Created by Nikilesh Ramesh on 28/11/2024 at 14:57
Motivation: To calculate the hessian of cost*/

#include "hessian_wL.h"

SparseMatrix hessian_wL(StateVectors X, InputVectors U, TimeVector T, Time t0, Time tf, Perturbation e){

    // Figure out the total size for perturbation vec
    int timeSize = T.size();
    int stateNum = X[0].size();
    int inputNum = U[0].size();
    int rowSize = 2 + stateNum + inputNum;
    int hessSize = 2 + stateNum*timeSize + inputNum*timeSize;
    
    // SparseMatrix hessian(hessSize); // the whole point of Sparse Matrix is to not have to store all values
    SparseMatrix hessian;

    // vector to encode where the perturbation is happening for 1st and 2nd perturb
    std::vector<FLOAT_PRECISION> pertub_vec_i; 
    std::vector<FLOAT_PRECISION> pertub_vec_j; 

    pertub_vec_i.resize(rowSize, 0.0);
    pertub_vec_j.resize(rowSize, 0.0);

    for (int i = 0; i < rowSize; i++)
    {
        pertub_vec_i[i] = e;

        // code for CD
        // Lower Triangle Matrix since Hessian symettry j : 0->i
        for (int j = 0; j <= i; j++) 
        {
            pertub_vec_j[j] = e;
            CostVector L_tt;
            if (i == j)
            {
                
                // DT and T vec
                FLOAT_PRECISION dt_o = (tf - t0);
                FLOAT_PRECISION dt_p = dt_o + pertub_vec_i[1] - pertub_vec_i[0];
                FLOAT_PRECISION dt_m = dt_o - pertub_vec_i[1] + pertub_vec_i[0];
                TimeVector T_p = T*(dt_p) + (t0 + pertub_vec_i[0]);
                TimeVector T_m = T*(dt_m) + (t0 + pertub_vec_i[0]);
                // states
                // collect the state perturbation vec here
                std::vector<FLOAT_PRECISION> statePerturbVec_i;
                statePerturbVec_i.resize(stateNum);
                for (int k = 0; k < stateNum; k++)
                {
                    statePerturbVec_i[k] = pertub_vec_i[k+2];
                }
                
                StateVectors X_p;
                StateVectors X_m;

                X_p.resize(timeSize);
                X_m.resize(timeSize);

                for (int k = 0; k < timeSize; k++)
                {
                    X_p[k] = X[k] + (statePerturbVec_i);
                    X_m[k] = X[k] - (statePerturbVec_i);                    
                }

                // collect the Input perturbation vec here
                std::vector<FLOAT_PRECISION> inputPerturbVec_i;
                inputPerturbVec_i.resize(inputNum);
                for (int k = 0; k < inputNum; k++)
                {
                    inputPerturbVec_i[k] = pertub_vec_i[k+stateNum+2];
                }

                InputVectors U_p;
                InputVectors U_m;

                U_p.resize(timeSize);
                U_m.resize(timeSize);

                for (int k = 0; k < timeSize; k++)
                {
                    U_p[k] = U[k] + (inputPerturbVec_i);
                    U_p[k] = U[k] - (inputPerturbVec_i);                   
                }

                CostVector L_o =  L_unscaled(X,U,T);
                CostVector L_p = L_unscaled(X_p, U_p, T_p);
                CostVector L_m = L_unscaled(X_m, U_m, T_m);
                L_tt = (L_p + L_o*((FLOAT_PRECISION)-2.0) + L_m)*((FLOAT_PRECISION) e*e);
            } else {
                // if i != j
                // init 4 vectors to record the total perturbation for ++, +-, -+ and -- case
                std::vector<FLOAT_PRECISION> perturb_pp;
                std::vector<FLOAT_PRECISION> perturb_pm;
                std::vector<FLOAT_PRECISION> perturb_mp;
                std::vector<FLOAT_PRECISION> perturb_mm;

                perturb_pp.resize(rowSize,0.0);
                perturb_pm.resize(rowSize,0.0);
                perturb_mp.resize(rowSize,0.0);
                perturb_mm.resize(rowSize,0.0);

                // find the total perturb
                for (int k = 0; k < rowSize; k++)
                {
                    perturb_pp[k] =  + pertub_vec_i[k] + pertub_vec_j[k];
                    perturb_pm[k] =  + pertub_vec_i[k] - pertub_vec_j[k];
                    perturb_mp[k] =  - pertub_vec_i[k] + pertub_vec_j[k];
                    perturb_mm[k] =  - pertub_vec_i[k] - pertub_vec_j[k]; 
                }
                
                // DT and T
                FLOAT_PRECISION dt_pp = (tf - t0) + perturb_pp[1] + perturb_mm[0];
                FLOAT_PRECISION dt_pm = (tf - t0) + perturb_pm[1] + perturb_mp[0];
                FLOAT_PRECISION dt_mp = (tf - t0) + perturb_mp[1] + perturb_pm[0];
                FLOAT_PRECISION dt_mm = (tf - t0) + perturb_mm[1] + perturb_pp[0];

                TimeVector T_pp = T*(dt_pp) + (t0 + perturb_pp[0]);
                TimeVector T_pm = T*(dt_pm) + (t0 + perturb_pm[0]);
                TimeVector T_mp = T*(dt_mp) + (t0 + perturb_mp[0]);
                TimeVector T_mm = T*(dt_mm) + (t0 + perturb_mm[0]);

                // collect the state perturbation vec here
                std::vector<FLOAT_PRECISION> statePerturbVec_i;
                std::vector<FLOAT_PRECISION> statePerturbVec_j;
                statePerturbVec_i.resize(stateNum);
                statePerturbVec_j.resize(stateNum);
                for (int k = 0; k < stateNum; k++)
                {
                    statePerturbVec_i[k] = pertub_vec_i[k+2];
                    statePerturbVec_j[k] = pertub_vec_j[k+2];
                }
                
                StateVectors X_pp;
                StateVectors X_pm;
                StateVectors X_mp;
                StateVectors X_mm;

                X_pp.resize(timeSize);
                X_pm.resize(timeSize);
                X_mp.resize(timeSize);
                X_mm.resize(timeSize);

                for (int k = 0; k < timeSize; k++)
                {
                    X_pp[k] = X[k] + (statePerturbVec_i + statePerturbVec_j);
                    X_pm[k] = X[k] + (statePerturbVec_i - statePerturbVec_j);
                    X_mp[k] = X[k] + (statePerturbVec_i*((FLOAT_PRECISION)-1.0) + statePerturbVec_j); // careful : operator overloading 
                    X_mm[k] = X[k] + (statePerturbVec_i*((FLOAT_PRECISION)-1.0) - statePerturbVec_j);
                    
                }

                // collect the intput perturbation vec here
                std::vector<FLOAT_PRECISION> inputPerturbVec_i;
                std::vector<FLOAT_PRECISION> inputPerturbVec_j;
                inputPerturbVec_i.resize(inputNum);
                inputPerturbVec_j.resize(inputNum);

                for (int k = 0; k < inputNum; k++)
                {
                    inputPerturbVec_i[k] = pertub_vec_i[k+ stateNum + 2]; // input comes after state
                    inputPerturbVec_j[k] = pertub_vec_j[k+ stateNum + 2];
                }

                InputVectors U_pp;
                InputVectors U_pm;
                InputVectors U_mp;
                InputVectors U_mm;

                U_pp.resize(timeSize);
                U_pm.resize(timeSize);
                U_mp.resize(timeSize);
                U_mm.resize(timeSize);

                for (int k = 0; k < timeSize; k++)
                {
                    U_pp[k] = U[k] + (inputPerturbVec_i + inputPerturbVec_j);
                    U_pm[k] = U[k] + (inputPerturbVec_i - inputPerturbVec_j);
                    U_mp[k] = U[k] + (inputPerturbVec_i*((FLOAT_PRECISION)-1.0) + inputPerturbVec_j); // careful : operator overloading 
                    U_mm[k] = U[k] + (inputPerturbVec_i*((FLOAT_PRECISION)-1.0) - inputPerturbVec_j);
                    
                }

                // finally, start evaluating the Lagrange
                const CostVector L_pp = L_unscaled(X_pp, U_pp, T_pp)*dt_pp;
                const CostVector L_pm = L_unscaled(X_pm, U_pm, T_pm)*dt_pm;
                const CostVector L_mp = L_unscaled(X_mp, U_mp, T_mp)*dt_mp;
                const CostVector L_mm = L_unscaled(X_mm, U_mm, T_mm)*dt_mm;
                L_tt = ((L_pp - L_mp) + (L_mm - L_pm))*((FLOAT_PRECISION) 1/(4*e*e));
            }
            
            

            if (i < 2 && j < 2)
            {
                hessian.rows.push_back(i);
                hessian.cols.push_back(j);
                hessian.values.push_back(vec_sum(L_tt));
            } else if (j < 2)
            {
                for (int k = 0; k < T.size(); k++)
                {
                    hessian.rows.push_back(i+(rowSize-2)*k);
                    hessian.cols.push_back(j);
                    hessian.values.push_back(L_tt[k]); /// DOUBLE CHEKC
                }
            }
            
            else {
                for (int k = 0; k < T.size(); k++)
                {
                    hessian.rows.push_back(i+(rowSize-2)*k);
                    hessian.cols.push_back(j+(rowSize-2)*k);
                    hessian.values.push_back(L_tt[k]); /// DOUBLE CHEKC
                }
                                
            }
            
            
            
            pertub_vec_j[j] = 0.0;
        }
        

        pertub_vec_i[i] = 0.0; // set it back to zero 
    }
    
    return hessian;
}