#pragma once
#include <cstddef>
#include <string>
#include "stack.h"

typedef double Op;

class RPNcalc
{
private:
public:
    Stack *stack;

    RPNcalc(void);
    bool getOperands(Op *op1, Op *op2);
    bool getOperand(Op *op);
    void enterNumber(Op num);
    void select_op_sum(void);
    void select_op_diff(void);
    void select_op_mul(void);
    void select_op_pow(void);
    void select_op_div(void);
    void select_op_sqrt(void);
};

