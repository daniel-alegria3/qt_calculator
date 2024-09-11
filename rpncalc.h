#pragma once
#include <cstddef>
#include <string>
#include "stack.h"

typedef double Op;

class RPNcalc
{
private:
public:
    Stack<double> *stack;

    RPNcalc(void);
    bool get_operands(Op *op1, Op *op2);
    bool get_operand(Op *op);
    void enter_number(Op num);
    void select_op_sum(void);
    void select_op_diff(void);
    void select_op_mul(void);
    void select_op_pow(void);
    void select_op_div(void);
    void select_op_sqrt(void);
};

