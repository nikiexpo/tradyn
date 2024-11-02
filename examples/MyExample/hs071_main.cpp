#include "IpIpoptApplication.hpp"
#include "hs071_nlp.hpp"

#include <iostream>

using namespace Ipopt;

int main(
    int, char**
){
    SmartPtr<TNLP> mynlp = new HS071_NLP(); // creating instance with smart pointer
    SmartPtr<IpoptApplication> app = IpoptApplicationFactory();

    // change options (depends on optimization problem)
    app->Options()->SetNumericValue("tol",3.82e-6);
    app->Options()->SetStringValue("mu_strategy", "adaptive");
    app->Options()->SetStringValue("output_file", "ipopt.out");

    // init IpoptApplication and process the options
    ApplicationReturnStatus status;
    status = app->Initialize();
    if (status != Solve_Succeeded)
    {
      std::cout << std::endl << std::endl << "*** Error during initialization!" << std::endl;
      return (int) status;       
    }

    // Ipopt to solve the optimization
    status = app->OptimizeTNLP(mynlp);

   if( status == Solve_Succeeded )
   {
      std::cout << std::endl << std::endl << "*** The problem solved!" << std::endl;
   }
   else
   {
      std::cout << std::endl << std::endl << "*** The problem FAILED!" << std::endl;
   }

    return (int) status;
    

}