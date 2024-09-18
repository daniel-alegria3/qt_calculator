#pragma once
#include <cstddef>
#include <string>
#include "stack.h"
#include "rpn.h"

/* typedef double double; */

class RPNcalc
{
private:
public:
    RPN *rpn;
    Stack<double> *stack;

    RPNcalc(void);
    string solve(string expresion);
};

