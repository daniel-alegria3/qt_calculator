#include <cmath>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// #include <catch2/generators/catch_generators_all.hpp>
#include "rpn/rpn.h"

using namespace std;
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

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


RPN *rpn;
void init_rpn(void) {
    rpn = new RPN();
    rpn->add_grouping("(", ")");
    rpn->add_grouping("[", "]");
    rpn->add_grouping("{", "}");

    rpn->add_operation("sqrt", 1, UNARY, &_sqrt);
    rpn->add_operation("^", 1, BINARY, &pow);
    rpn->add_operation("/", 2, BINARY, &div);
    rpn->add_operation("*", 2, BINARY, &mul);
    rpn->add_operation("-", 3, BINARY, &diff);
    rpn->add_operation("+", 3, BINARY, &sum);
}


TEST_CASE("RPN can eval infix expression", "[rpn]") {
    init_rpn();
    string s, pos, eva;

    s = "( 2 + 5 ) * 3 + 1";
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 5 + 3 * 1 + ");
    CHECK(stof(eva) == 22);

    s = "2 + 5 * 3 + 1";
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 5 3 * + 1 + ");
    CHECK(stof(eva) == 18);

    s = "{ ( 2 + 3 ) * 5 ^ ( 3 - 1 ) }",
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 3 + 5 3 1 - ^ * ");
    CHECK(stof(eva) == 125);

    s = "{ ( 2 + 3 ) * 5 ^ ( 2 + 1 ) - [ 4 * 5 - ( 2 - 1 ) ] }";
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 3 + 5 2 1 + ^ * 4 5 * 2 1 - - - ");
    CHECK(stof(eva) == 606);

    s = "{ ( 2 + 3 ) * 5 ^ ( 3 - 1 ) }";
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 3 + 5 3 1 - ^ * ");
    CHECK(stof(eva) == 125);

    s = "{ ( 2 + 3 ) * sqrt ( 3 - 1 ) }";
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 3 + 3 1 - sqrt * ");
    CHECK_THAT(stof(eva), WithinRel(7.071, 0.001) || WithinAbs(0, 0.000001)
    );
}


TEST_CASE("RPN can eval postfix expression", "[rpn]") {
    init_rpn();
    string pos, eva;

    pos = "2.4 52 + 3 - 1.5 +";
    eva = rpn->eval_postfix(pos);
    CHECK_THAT(stof(eva), WithinRel(52.9, 0.001) || WithinAbs(0, 0.000001));

    pos = "2 50 3 - + 10 +";
    eva = rpn->eval_postfix(pos);
    CHECK(stof(eva) == 59);

    pos = "20 3 + 5 30 10 - + +";
    eva = rpn->eval_postfix(pos);
    CHECK(stof(eva) == 48);

    pos = "25 3.5 + 50 2 15 + - + 40 50 - 25 15 - - -";
    eva = rpn->eval_postfix(pos);
    CHECK_THAT(stof(eva), WithinRel(81.5, 0.001) || WithinAbs(0, 0.000001));
}


TEST_CASE("RPN can eval infix expression, checking parenthesis", "[rpn]") {
    init_rpn();
    string s, pos, eva;
    bool par;

    s = "( 1 )";
    par = rpn->is_correct_parenthesis(s);
    CHECK(par == true);
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "1 ");
    CHECK(stof(eva) == 1);

    s = "( [ { 2 + 3 } - 4 ] / 2 ) ^ 2";
    par = rpn->is_correct_parenthesis(s);
    CHECK(par == true);
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 3 + 4 - 2 / 2 ^ ");
    CHECK(stof(eva) == 1);

    s = "{ [ 2 + 6 * ( 75 + 11 - 4 ) ] } * [ 5 - ( 2 - 1 ) ]";
    par = rpn->is_correct_parenthesis(s);
    CHECK(par == true);
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 6 75 11 + 4 - * + 5 2 1 - - * ");
    CHECK(stof(eva) == 1976);

    s = "{ [ 2 + 10 * ( 15 + 16 - 4 ) ] } * [ 5 - ( 2 - 1 ) + 9 ]";
    par = rpn->is_correct_parenthesis(s);
    CHECK(par == true);
    pos = rpn->infix_to_postfix(s);
    eva = rpn->eval_postfix(pos);
    CHECK(pos == "2 10 15 16 + 4 - * + 5 2 1 - - 9 + * ");
    CHECK(stof(eva) == 3536);

    /// TODO: IMPLEMENT

    s = "( ( 12 + 7 * [ 35 + 14 - 3 ] * ( 5 - ( 2 - 1 )";
    par = rpn->is_correct_parenthesis(s);
    CHECK(par == false);
    // pos = rpn->infix_to_postfix(s);
    // eva = rpn->eval_postfix(pos);
    // CHECK(pos == "");
    // CHECK(stof(eva) == 0);

    s = "( ( 21 + 3 * [ 52 + 7 * 4 ) * ( 5 - ( 2 -1 } + 4";
    CHECK(par == false);
    // pos = rpn->infix_to_postfix(s);
    // eva = rpn->eval_postfix(pos);
    // CHECK(pos == "");
    // CHECK(stof(eva) == 0);

    s = "( ( 21 + 2 * [ 7 * 6 ) * ( 5- ( 2 - 1 } + 2 (";
    CHECK(par == false);
    // pos = rpn->infix_to_postfix(s);
    // eva = rpn->eval_postfix(pos);
    // CHECK(pos == "");
    // CHECK(stof(eva) == 0);
}

