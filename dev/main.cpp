#include <vector>
#include <iostream>
#include "../typeDefinitions.h"



void vectOpt(std::vector<float>* ex, const float e);
float func(std::vector<float> x, std::vector<float> u);
void finiteDiff(const std::vector<float> x, int idx, std::vector<float> u, float e, std::vector<float>& grad);
const float acc(int count);

int main(void){
    FlatMatrix V;
    V.vals = {1,0,0,0};
    V = V + 1.0;
    FlatMatrix nV = V + 1.0;
    for (auto &&i : nV.vals)
    {
        std::cout << i << ",";
    }
    std::cout<<"\n";
    
    std::vector<float> ex = {1,0,0,0,0};
    float e = 4.0;
    Perturbation ee = 0.4;
    Time t = 10.0;
    vectOpt(&ex, e);

    for (auto &&i : ex)
    {
        std::cout << i << " ";
    }
    
    std::vector<float> x = {1};
    std::vector<float> u = {14};
    std::vector<float> grad = {0,0};
    finiteDiff(x,0,u,0.001,grad);

    std::cout << "\n" << grad[0] << ", " << grad[1] << std::endl;
    std::cout << t + ee << std::endl;

    std::vector<std::vector<float>> testVec = {{1,0,0}, {2,0,0}};
    std::cout << testVec.size() << "," << testVec[1].size() << std::endl;
    std::cout << acc(10) << std::endl;

    int indx= 0;
    for (int  i = 0; i < 99; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            indx = i*4 + j;
        }
        
    }

    std::cout << "\n INDEX ::: " << indx << std::endl;

    std::vector<float> t1 = {1,0,0,0};
    std::vector<float> t2 = {1,0,0,0};
    std::vector<float> tt;
    
    for (auto &&i : t1)
    {
        tt.push_back(i);
    }
    for (auto &&i : t2)
    {
        tt.push_back(i);
    }
    for (auto &&i : tt)
    {
        std::cout<<i << "," ;
    }
    std::cout << "\n" << std::endl;
    
    
    std::vector<FLOAT_PRECISION> vv = {1,2,3,4,5};
    std::vector<FLOAT_PRECISION> vv_new = vv*vv + vv;

    for (auto &&i : vv_new)
    {
        std::cout << i << ", ";
    }
    std::cout << "\n" << std::endl;

    for (auto &&i : vv)
    {
        std::cout << i << ", ";
    }
    std::cout << "\n" << std::endl;
    
    SparseMatrix test(5);
    test.printInfo();
    std::cout << vec_sum(vv) << std::endl;
    return 0;
}

void vectOpt(std::vector<float>* ex, const float e){
    for (auto & element : *ex)
    {
        element = element*e;
    }
    
}

float func(std::vector<float> x, std::vector<float> u){
    return x[0]*u[0];
}

void finiteDiff(const std::vector<float> x, int idx, std::vector<float> u, float e, std::vector<float>& grad){
    std::vector<float> x_ng = x;
    x_ng[idx] = x_ng[idx] - e;
    std::vector<float> x_ps = x;
    x_ps[idx] = x_ps[idx] + e;
    
    std::vector<float> u_ng = u;
    u_ng[idx] = u_ng[idx] - e;
    std::vector<float> u_ps = u;
    u_ps[idx] = u_ps[idx] + e;

    float f_x = (func(x_ps, u) - func(x_ng, u)) / (2.0*e) ;
    float f_u = (func(x, u_ps) - func(x, u_ng)) / (2.0*e) ;

    grad[0] = f_x;
    grad[1] = f_u;
}

const float acc(int count){
    float L = 1.5;
    for (int i = 0; i < count; i++)
    {
        L += 1;
    }

    return (const float) L;
}