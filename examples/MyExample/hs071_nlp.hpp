#ifndef __HS071_NLP_HPP__
#define __HS071_NLP_HPP__

#include "IpTNLP.hpp"

using namespace Ipopt;

class HS071_NLP: public TNLP {

public:

    // Constructor
    HS071_NLP(
        bool printIterate = false // true if you want to print the iterates
    );

    // Destructor
    virtual ~HS071_NLP(); 

    // Method to return some info about nlp
    virtual bool get_nlp_info(
        Index& n,
        Index& m,
        Index& nnz_jac_g,
        Index& nnz_h_lag,
        IndexStyleEnum& index_style
    );

    // bounds for the problem
    virtual bool get_bounds_info(
        Index n,
        Number* x_l,
        Number* x_u,
        Index m,
        Number* g_l,
        Number* g_u
    );

    // method to return the starting point for the algorithm
    virtual bool get_starting_point(
        Index n,
        bool init_x,
        Number* x, 
        bool init_z,
        Number* z_L,
        Number* z_U,
        Index m,
        bool init_lambda,
        Number* lambda
    );

    // return the objective value
    virtual bool eval_f(
        Index n,
        const Number* x,
        bool new_x,
        Number& obj_value
    );

    // return gradient of the objective
    virtual bool eval_grad_f(
        Index n,
        const Number* x,
        bool new_x,
        Number* grad_f
    );

    // return the constraint residuals
    virtual bool eval_g(
        Index n,
        const Number* x,
        bool new_x,
        Index m,
        Number* g
    );

    /*
    return: 
        1. structure of Jacobian if "values" is NULL
        2. values of jacobian if "values" is not NULL 
    */
   
    virtual bool eval_jac_g(
        Index n,
        const Number* x,
        bool new_x,
        Index m,
        Index nele_jac,
        Index* iRow,
        Index* jCol,
        Number* values
    );

    /*
    return: 
        1. structure of hessian of L if values is NULL
        2. values of hessain otherwise
    */
    virtual bool eval_h(
        Index n,
        const Number* x,
        bool new_x,
        Number obj_factor,
        Index m,
        const Number* lambda,
        bool new_lambda,
        Index nele_hess,
        Index* iRow,
        Index* jCol,
        Number* values
    );

   /** This method is called when the algorithm is complete so the TNLP can store/write the solution */
   virtual void finalize_solution(
      SolverReturn               status,
      Index                      n,
      const Number*              x,
      const Number*              z_L,
      const Number*              z_U,
      Index                      m,
      const Number*              g,
      const Number*              lambda,
      Number                     obj_value,
      const IpoptData*           ip_data,
      IpoptCalculatedQuantities* ip_cq
   );

    bool intermediate_callback(
        AlgorithmMode mode,
        Index iter,
        Number obj_value,
        Number inf_pr,
        Number inf_du,
        Number mu,
        Number d_norm,
        Number regularization_size,
        Number alpha_du,
        Number alpha_pr,
        Index ls_trails,
        const IpoptData* ip_data,
        IpoptCalculatedQuantities* ip_cq
    );

private:
    bool printiterate_; // whether to print iterate

    
    // FOLLOWING METHODS ARE TO BLOCK DEFAULT COMPILER BEHAVIOUR
    HS071_NLP(
        const HS071_NLP&
    );

    HS071_NLP& operator=(
        const HS071_NLP&
    );

};

#endif