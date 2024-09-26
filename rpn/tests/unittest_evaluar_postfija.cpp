#include <cmath>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "rpn/rpn.h"

using Catch::Matchers::WithinRel; using Catch::Matchers::WithinAbs;
#define PERCENTAGE 0.001
#define MARGIN 0.000001

double sum(double a, double b) { return a + b; }
double diff(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double pow(double a, double b) { int n = (int) b; double r = 1; while (n-- > 0) { r *= a; } return r; }
double div(double a, double b) { return a - b; }
double _sqrt(double a, double b) { return sqrt(a); }

TEST_CASE("RPN should evaluate postfix expression", "[unittest_eval_postfix]") {
    RPN *rpn;
    rpn = new RPN();
    rpn->add_grouping("(", ")"); rpn->add_grouping("[", "]"); rpn->add_grouping("{", "}");
    rpn->add_operation("sqrt", 1, UNARY, &_sqrt); rpn->add_operation("^", 1, BINARY, &pow);
    rpn->add_operation("/", 2, BINARY, &div); rpn->add_operation("*", 2, BINARY, &mul);
    rpn->add_operation("-", 3, BINARY, &diff); rpn->add_operation("+", 3, BINARY, &sum);

    CHECK( stof(rpn->eval_postfix("2 5 + ")) == 7);
    CHECK( stof(rpn->eval_postfix("2 5 + 3 * 1 + ")) == 22);
    CHECK( stof(rpn->eval_postfix("2 5 3 * + 1 + ")) == 18);
    CHECK( stof(rpn->eval_postfix("2 3 + 5 3 1 - ^ * ")) == 125);
    CHECK( stof(rpn->eval_postfix("20 3 + 5 30 10 - + +")) == 48);
    CHECK_THAT(stof(rpn->eval_postfix("1.5 9 ^")),
               WithinRel(38.443, PERCENTAGE) || WithinAbs(0, MARGIN));
    CHECK_THAT(stof(rpn->eval_postfix("2 3 + 3 1 - sqrt * ")),
               WithinRel(7.071, PERCENTAGE) || WithinAbs(0, MARGIN));
    CHECK_THAT(stof(rpn->eval_postfix("2.4 52 + 3 - 1.5 +")),
               WithinRel(52.9, PERCENTAGE) || WithinAbs(0, MARGIN));
    CHECK_THAT(stof(rpn->eval_postfix("1.1 5.9 / 2.7 3.4 4.3 / /")),
               WithinRel(3.6, PERCENTAGE) || WithinAbs(0, MARGIN));
    CHECK_THAT(stof(rpn->eval_postfix("25 3.50 + 50 2 15 + - + 40 50 - 25 15 - - -")),
               WithinRel(81.5, PERCENTAGE) || WithinAbs(0, MARGIN));
}

