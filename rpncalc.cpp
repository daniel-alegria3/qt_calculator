#include <iostream>
#include <cmath>
#include "rpncalc.h"

using namespace std;

RPNcalc::RPNcalc (void) {
    stack = new Stack();
}

bool RPNcalc::getOperands(Op *op1, Op *op2) {
    if (stack->is_empty()) {
        cout << "Pila vacia! Ingrese un numero" << endl;
        return false;
    }
    *op2 = stack->pop();

    if (stack->is_empty()) {
        cout << "Se requiere dos numeros!" << endl;
        stack->push(*op2);
        return false;
    }
    *op1 = stack->pop();

    return true;
}

bool RPNcalc::getOperand(Op *op) {
    if (stack->is_empty()) {
        cout << "Pila vacia! Ingrese un numero" << endl;
        return false;
    }
    *op = stack->pop();

    return true;
}

void RPNcalc::enterNumber(Op num) {
    stack->push(num);
}

void RPNcalc::select_op_sum(void) {
    Op op1, op2;
    bool check = getOperands(&op1, &op2);
    if (!check) {
        return;
    }
    stack->push(op1+op2);
}

void RPNcalc::select_op_diff(void) {
    Op op1, op2;
    bool check = getOperands(&op1, &op2);
    if (!check) {
        return;
    }
    stack->push(op1-op2);
}

void RPNcalc::select_op_mul(void) {
    Op op1, op2;
    bool check = getOperands(&op1, &op2);
    if (!check) {
        return;
    }
    stack->push(op1*op2);
}

void RPNcalc::select_op_pow(void) {
    Op op1, op2;
    bool check = getOperands(&op1, &op2);
    if (!check) {
        return;
    }
    // Op res = 1;
    // int n = op2;
    // for (int i = 0; i < n; ++i) {
    //     res *= op1;
    // }
    stack->push(pow(op1,op2));
}

void RPNcalc::select_op_div(void) {
    Op op1, op2;
    bool check = getOperands(&op1, &op2);
    if (!check) {
        return;
    }
    stack->push(op1/op2);
}

void RPNcalc::select_op_sqrt(void) {
    Op op;
    bool check = getOperand(&op);
    if (!check) {
        return;
    }
    stack->push(sqrt(op));
}

