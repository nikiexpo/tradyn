# Dev log

## 02/11/2024
- Creating UserDefined functions for boundary and path costs without the data struct for now, to test the gradient evaluations
- alternative to PerturbationSelectionVector : so idea is only one variable of the decision variable is perturbed at one time so like if you the diff wrt a single x_0 i.e. f_{x_0(i)} then you would choose i so have a vector = {i, j, k...} where i, j, k etc are the idices to choose the value to perturb for x_0, x_f, u_0... etc
- dont forget link all your cpp files 
    g++ -std=c++11 main.cpp gradientFD.cpp UserDefinedFunctions.cpp -o main

## 04/11/2024
- Changed everything to double precision cause IPOPT uses double as default. Also noticed improvment in gradient approximation
    single precision ans - 0,3.99971,0,0,0,0,7.9999,0,0,0,0,0,7.9999,0
    double precision ans - 0,4,0,0,0,0,8,0,0,0,0,0,8,0
- Done with cost grad calc of J_E and J_L but need to write verification code 

## 06/12/2024
- Need to refactor the code base so theres less boilerplate to write down the line. 
    - Introduce Problem, Jacobian and Hessian classes to not have pass in a bunch of variables
    - better way of perturbation
- More robust type system, create custom type with operator overloading
- Move to Cmake and add unit testing via Catch2