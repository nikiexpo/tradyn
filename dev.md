# Dev log

## 02/11/2024
- Creating UserDefined functions for boundary and path costs without the data struct for now, to test the gradient evaluations
- alternative to PerturbationSelectionVector : so idea is only one variable of the decision variable is perturbed at one time so like if you the diff wrt a single x_0 i.e. f_{x_0(i)} then you would choose i so have a vector = {i, j, k...} where i, j, k etc are the idices to choose the value to perturb for x_0, x_f, u_0... etc
- dont forget link all your cpp files 
    g++ -std=c++11 main.cpp gradientFD.cpp UserDefinedFunctions.cpp -o main