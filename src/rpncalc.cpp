#include <cmath>
#include <cstdlib>
#include "rpncalc.h"

using namespace std;

double op_sum(double a, double b);
double op_diff(double a, double b);
double op_mul(double a, double b);
double op_pow(double a, double b);
double op_div(double a, double b);
double op_sqrt(double a, double b);

RPNcalc::RPNcalc (void) {
    rpn = new RPN();

    rpn->add_grouping("(", ")");
    rpn->add_grouping("[", "]");
    rpn->add_grouping("{", "}");

    rpn->add_operation("sqrt", 1, UNARY, &op_sqrt);
    rpn->add_operation("^", 1, BINARY, &op_pow);
    rpn->add_operation("/", 2, BINARY, &op_div);
    rpn->add_operation("*", 2, BINARY, &op_mul);
    rpn->add_operation("-", 3, BINARY, &op_diff);
    rpn->add_operation("+", 3, BINARY, &op_sum);
}

string RPNcalc::solve(string expresion) {
    return rpn->eval_postfix(rpn->infix_to_postfix(expresion));
}

double op_sum(double a, double b) { return a + b; }
double op_diff(double a, double b) { return a - b; }
double op_mul(double a, double b) { return a * b; }
double op_pow(double a, double b) {
    int n = (int) b;
    double r = 1;
    while (n-- > 0) {
        r *= a;
    }
    return r;
}
double op_div(double a, double b) { return a - b; }
double op_sqrt(double a, double b) { return sqrt(a); }

