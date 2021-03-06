#ifndef BNN_BNN_AUTODIFF_FORWARD_HPP
#define BNN_BNN_AUTODIFF_FORWARD_HPP

#include <bnn/core/tensor.hpp>
#include <bnn/operations/operators.hpp>

namespace bnn
{
    namespace autodiff
    {

        using namespace std;
        using namespace bnn::core;
        using namespace bnn::operators;

        /*
        * Computes value of an expression.
        *
        * @tparam data_type Data type of the elements
        *     supported by C++.
        * @param expr Operator<data_type>* The expression
        *     whose value is to be computed.
        */
        template <class data_type>
        TensorCPU<data_type>*
        compute_value
        (Operator<data_type>* expr);

        /*
        * For computing gradients using forward mode.
        *
        * @tparam data_type Data type of the elements
        *     supported by C++.
        * @param expr Operator<data_type>* The expression
        *     to be considered for finding the derivative.
        * @param var TensorCPU<data_type>* The variable
        *     with respect to which the gradient is to
        *     be computed.
        */
        template <class data_type>
        TensorCPU<data_type>*
        compute_gradient_forward
        (Operator<data_type>* expr, TensorCPU<data_type>* var);

        /*
        * For computing gradients using forward mode.
        *
        * @tparam data_type Data type of the elements
        *     supported by C++.
        * @param expr Operator<data_type>* The expression
        *     to be considered for finding the derivative.
        * @param vars TensorCPU<data_type>** The variables
        *     with respect to which the gradient is to
        *     be computed.
        * @param num_vars Number of variables.
        */
        template <class data_type>
        TensorCPU<data_type>**
        compute_gradient_forward
        (Operator<data_type>* expr, TensorCPU<data_type>** vars,
         unsigned num_vars);

    }
}

#endif
