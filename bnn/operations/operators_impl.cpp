#ifndef BNN_BNN_OPERATIONS_OPERATORS_IMPL_CPP
#define BNN_BNN_OPERATIONS_OPERATORS_IMPL_CPP

#include <vector>
#include <bnn/core/tensor.hpp>
#include <bnn/core/tensor_ops.hpp>
#include <bnn/operations/operators.hpp>
#include <bnn/utils/utils.hpp>

namespace bnn
{
    namespace operators
    {

        using namespace std;
        using namespace bnn::core;

        string msg = "This is an abstract method";

        template <class data_type>
        Operator<data_type>::
        Operator
        (string _name):
        name(_name),
        value(NULL),
        gradient(NULL)
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        Operator<data_type>::
        Operator
        (TensorCPU<data_type>* _value, string _name):
        name(_name),
        value(_value),
        gradient(NULL)
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        string
        Operator<data_type>::
        get_name
        ()
        {
            return this->name;
        }

        template <class data_type>
        Operator<data_type>*
        Operator<data_type>::
        get_arg
        ()
        {
            check(false, msg);
        }

        template <class data_type>
        Operator<data_type>*
        Operator<data_type>::
        get_arg
        (bool index)
        {
            check(false, msg);
        }

        template <class data_type>
        bool
        Operator<data_type>::
        is_variable
        ()
        {
            return variable;
        }

        template <class data_type>
        void
        Operator<data_type>::
        set_variable
        (bool _val)
        {
            this->variable = _val;
        }

        template <class data_type>
        TensorCPU<data_type>*
        Operator<data_type>::
        compute_gradient
        (TensorCPU<data_type>* var)
        {
            check(false, msg);
        }

        template <class data_type>
        void
        Operator<data_type>::
        compute_gradient_reverse
        ()
        {
            check(false, msg);
        }

        template <class data_type>
        TensorCPU<data_type>*
        Operator<data_type>::
        compute_value
        ()
        {
            check(false, msg);
        }

        template <class data_type>
        TensorCPU<data_type>*
        Operator<data_type>::
        get_value
        ()
        {
            return this->value;
        }

        template <class data_type>
        TensorCPU<data_type>*
        Operator<data_type>::
        get_gradient
        ()
        {
            return this->gradient;
        }

        template <class data_type>
        void
        Operator<data_type>::
        set_gradient
        (TensorCPU<data_type>* _gradient)
        {
            this->gradient = _gradient;
        }

        template <class data_type>
        void
        Operator<data_type>::
        set_value
        (TensorCPU<data_type>* _value)
        {
            this->value = _value;
        }

        template <class data_type>
        unsigned
        Operator<data_type>::
        num_args
        ()
        {
            return 0;
        }

        template <class data_type>
        Operator<data_type>::
        ~Operator
        ()
        {
            BNNMemory->invalidate(this);
        }

        template <class data_type>
        UnaryOperator<data_type>::
        UnaryOperator
        (string _name):
        x(NULL),
        Operator<data_type>::Operator(_name)
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        UnaryOperator<data_type>::
        UnaryOperator
        (Operator<data_type>* a, string _name):
        x(a),
        Operator<data_type>::Operator(_name)
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        Operator<data_type>*
        UnaryOperator<data_type>::
        get_arg
        ()
        {
            return this->x;
        }

        template <class data_type>
        unsigned
        UnaryOperator<data_type>::
        num_args
        ()
        {
            return 1;
        }

        template <class data_type>
        UnaryOperator<data_type>::
        ~UnaryOperator
        ()
        {
            BNNMemory->invalidate(this);
        }

        template <class data_type>
        BinaryOperator<data_type>::
        BinaryOperator
        (string _name):
        x(NULL),
        y(NULL),
        Operator<data_type>::Operator(_name)
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        BinaryOperator<data_type>::
        BinaryOperator
        (Operator<data_type>* a,
         Operator<data_type>* b,
         string _name):
        x(a),
        y(b),
        Operator<data_type>::Operator(_name)
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        Operator<data_type>*
        BinaryOperator<data_type>::
        get_arg
        (bool idx)
        {
            return idx ? this->y : this->x;
        }

        template <class data_type>
        unsigned
        BinaryOperator<data_type>::
        num_args
        ()
        {
            return 2;
        }

        template <class data_type>
        BinaryOperator<data_type>::
        ~BinaryOperator
        ()
        {
            BNNMemory->invalidate(this);
        }

        template <class data_type>
        unsigned long int
        TensorWrapper<data_type>::_id = 0;

        template <class data_type>
        TensorWrapper<data_type>::
        TensorWrapper
        ():
        Operator<data_type>::Operator
        ("TensorWrapper")
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        TensorWrapper<data_type>::
        TensorWrapper
        (TensorCPU<data_type>* _t):
        Operator<data_type>::Operator
        (_t, "TensorWrapper_" + to_string(_id++))
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        TensorCPU<data_type>*
        TensorWrapper<data_type>::
        compute_value
        ()
        {
            return this->get_value();
        }

        template <class data_type>
        TensorCPU<data_type>*
        TensorWrapper<data_type>::
        compute_gradient
        (TensorCPU<data_type>* var)
        {
            TensorCPU<data_type>* t;
            t = this->get_value();
            vector<unsigned> shape
            (t->get_shape(), t->get_shape() + t->get_ndims());
            TensorCPU<data_type>* grad = new TensorCPU<data_type>(shape);
            bnn::core::fill(grad, (data_type)(var == t));
            return grad;
        }

        template <class data_type>
        void
        TensorWrapper<data_type>::
        compute_gradient_reverse
        ()
        {
        }

        template <class data_type>
        unsigned
        TensorWrapper<data_type>::
        num_args
        ()
        {
            return 0;
        }

        template <class data_type>
        TensorWrapper<data_type>::
        ~TensorWrapper
        ()
        {
            BNNMemory->invalidate(this);
        }

        template <class data_type>
        unsigned long int
        Add<data_type>::_id = 0;

        template <class data_type>
        Add<data_type>::
        Add
        ():
        BinaryOperator<data_type>::BinaryOperator("Add")
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        Add<data_type>::
        Add
        (Operator<data_type>* a, Operator<data_type>* b):
        BinaryOperator<data_type>::BinaryOperator
        (a, b, "Add_" + std::to_string(_id++))
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        TensorCPU<data_type>*
        Add<data_type>::
        compute_value
        ()
        {
            Operator<data_type> *x, *y;
            x = this->get_arg(0), y =  this->get_arg(1);
            return add(x->get_value(), y->get_value());
        }

        template <class data_type>
        TensorCPU<data_type>*
        Add<data_type>::
        compute_gradient
        (TensorCPU<data_type>* var)
        {
            Operator<data_type> *x, *y;
            x = this->get_arg(0), y =  this->get_arg(1);
            return add(x->get_gradient(), y->get_gradient());
        }

        template <class data_type>
        void
        Add<data_type>::
        compute_gradient_reverse
        ()
        {
            Operator<data_type>* arg1 = this->get_arg(0);
            Operator<data_type>* arg2 = this->get_arg(1);
            TensorCPU<data_type>* dy_dcurr = this->get_gradient();
            if(arg1->is_variable())
            {
                TensorCPU<data_type>* dy_darg1 = new TensorCPU<data_type>
                (dy_dcurr->get_shape(), dy_dcurr->get_ndims());
                bnn::core::copy(dy_darg1, dy_dcurr);
                arg1->set_gradient(dy_darg1);
            }
            if(arg2->is_variable())
            {
                TensorCPU<data_type>* dy_darg2 = new TensorCPU<data_type>
                (dy_dcurr->get_shape(), dy_dcurr->get_ndims());
                bnn::core::copy(dy_darg2, dy_dcurr);
                arg2->set_gradient(dy_darg2);
            }
        }

        template <class data_type>
        Add<data_type>::
        ~Add
        ()
        {
            BNNMemory->invalidate(this);
        }

        template <class data_type>
        unsigned long int
        Exp<data_type>::_id = 0;

        template <class data_type>
        Exp<data_type>::
        Exp
        ():
        UnaryOperator<data_type>::UnaryOperator("Exp")
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        Exp<data_type>::
        Exp
        (Operator<data_type>* a):
        UnaryOperator<data_type>::UnaryOperator
        (a, "Exp_" + std::to_string(_id++))
        {
            BNNMemory->push(this);
        }

        template <class data_type>
        TensorCPU<data_type>*
        Exp<data_type>::
        compute_value
        ()
        {
            Operator<data_type> *x;
            x = this->get_arg();
            return exp(x->get_value());
        }

        template <class data_type>
        TensorCPU<data_type>*
        Exp<data_type>::
        compute_gradient
        (TensorCPU<data_type>* var)
        {
            Operator<data_type> *x;
            x = this->get_arg();
            return mul(exp(x->get_value()), x->get_gradient());
        }

        template <class data_type>
        void
        Exp<data_type>::
        compute_gradient_reverse
        ()
        {
            Operator<data_type>* arg = this->get_arg();
            if(arg->is_variable())
            {
                TensorCPU<data_type>* dy_dcurr = this->get_gradient();
                TensorCPU<data_type>* dcurr_darg = this->get_value();
                arg->set_gradient(bnn::core::mul(dy_dcurr, dcurr_darg));
            }
        }

        template <class data_type>
        Exp<data_type>::
        ~Exp
        ()
        {
            BNNMemory->invalidate(this);
        }

        #include "bnn/templates/operations/operators.hpp"

    }
}

#endif
