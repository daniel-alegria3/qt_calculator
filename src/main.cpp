#include <iostream>
#include <cmath>

using namespace std;

double sum(double a, double b);
double diff(double a, double b);
double mul(double a, double b);
double pow(double a, double b);
double div(double a, double b);
double _sqrt(double a, double b);

#include "rpn.h"

int main(void)
{

    RPN *rpn = new RPN();
    rpn->add_grouping("(", ")");
    rpn->add_grouping("[", "]");
    rpn->add_grouping("{", "}");

    rpn->add_operation("sqrt", 1, UNARY, &_sqrt);
    rpn->add_operation("^", 1, BINARY, &pow);
    rpn->add_operation("/", 2, BINARY, &div);
    rpn->add_operation("*", 2, BINARY, &mul);
    rpn->add_operation("-", 3, BINARY, &diff);
    rpn->add_operation("+", 3, BINARY, &sum);

    string s0 = "( 2 + 5 ) * 3 + 1";
    string s1 = "2 + 5 * 3 + 1";
    string s2 = "{ ( 2 + 3 ) * 5 ^ ( 3 - 1 ) }";
    string s3 = "{ ( 2 + 3 ) * 5 ^ ( 2 + 1 ) - [ 4 * 5 - ( 2 - 1 ) ] }";

    string s4 = "{ ( 2 + 3 ) * 5 ^ ( 3 - 1 ) }";
    string s5 = "{ ( 2 + 3 ) * sqrt ( 3 - 1 ) }";

    string s;

    printf("---------------------------------\n");
    s = s0;
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->infix_to_postfix(s).c_str());
    printf("%s\n", rpn->eval_postfix(rpn->infix_to_postfix(s)).c_str());

    printf("---------------------------------\n");
    s = s1;
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->infix_to_postfix(s).c_str());
    printf("%s\n", rpn->eval_postfix(rpn->infix_to_postfix(s)).c_str());

    printf("---------------------------------\n");
    s = s2;
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->infix_to_postfix(s).c_str());
    printf("%s\n", rpn->eval_postfix(rpn->infix_to_postfix(s)).c_str());

    printf("---------------------------------\n");
    s = s3;
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->infix_to_postfix(s).c_str());
    printf("%s\n", rpn->eval_postfix(rpn->infix_to_postfix(s)).c_str());

    printf("---------------------------------\n");
    printf("---------------------------------\n");
    s = s4;
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->infix_to_postfix(s).c_str());
    printf("%s\n", rpn->eval_postfix(rpn->infix_to_postfix(s)).c_str());

    printf("---------------------------------\n");
    s = s5;
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->infix_to_postfix(s).c_str());
    printf("%s\n", rpn->eval_postfix(rpn->infix_to_postfix(s)).c_str());

    printf("---------------------------------\n");
    printf("---------------------------------\n");
    s = "2.4 52 + 3 - 1.5 +";
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->eval_postfix(s).c_str());

    printf("---------------------------------\n");
    s = "2 50 3 - + 10 +";
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->eval_postfix(s).c_str());

    printf("---------------------------------\n");
    s = "20 3 + 5 30 10 - + +";
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->eval_postfix(s).c_str());

    printf("---------------------------------\n");
    s = "25 3.5 + 50 2 15 + - + 40 50 - 25 15 - - -";
    printf("%s\n", s.c_str());
    printf("%s\n", rpn->eval_postfix(s).c_str());

    printf("---------------------------------\n");
    printf("---------------------------------\n");
    s = "( 1 )";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    printf("---------------------------------\n");
    s = "( [ { 2 + 3 } - 4 ] / 2 ) ^ 2";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    printf("---------------------------------\n");
    s = "{ [ 2 + 6 * ( 75 + 11 - 4 ) ] } * [ 5 - ( 2 - 1 ) ]";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    printf("---------------------------------\n");
    s = "{ [ 2 + 10 * ( 15 + 16 - 4 ) ] } * [ 5 - ( 2 - 1 ) + 9 ]";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    printf("---------------------------------\n");
    printf("---------------------------------\n");
    s = "( 5 + 4 ) + 3 )";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    printf("---------------------------------\n");
    s = "( ( 12 + 7 * [ 35 + 14 - 3 ] * ( 5 - ( 2 - 1 )";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    printf("---------------------------------\n");
    s = "( ( 21 + 3 * [ 52 + 7 * 4 ) * ( 5 - ( 2 -1 } + 4";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    printf("---------------------------------\n");
    s = "( ( 21 + 2 * [ 7 * 6 ) * ( 5- ( 2 - 1 } + 2 (";
    printf("%d\n", rpn->is_correct_parenthesis(s));

    return 0;
}

double sum(double a, double b) { return a + b; }
double diff(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double pow(double a, double b) {
    int n = (int) b;
    double r = 1;
    while (n-- > 0) {
        r *= a;
    }
    return r;
}
double div(double a, double b) { return a - b; }
double _sqrt(double a, double b) { return sqrt(a); }


