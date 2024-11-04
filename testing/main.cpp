#include <vector>
#include <iostream>

typedef const float Time;
typedef float Perturbation;

void vectOpt(std::vector<float>* ex, const float e);
float func(std::vector<float> x, std::vector<float> u);
void finiteDiff(const std::vector<float> x, int idx, std::vector<float> u, float e, std::vector<float>& grad);
const float acc(int count);

int main(void){
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