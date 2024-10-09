#include <cmath>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include "rpn/rpn.h"

TEST_CASE("RPN should convert infix to postfix expression", "[unittest_infix_to_postfix]") {
    RPN *rpn;
    rpn = new RPN();
    rpn->add_grouping("(", ")"); rpn->add_grouping("[", "]"); rpn->add_grouping("{", "}");
    rpn->add_operation("sqrt", 1, UNARY, NULL); rpn->add_operation("^", 1, BINARY, NULL);
    rpn->add_operation("/", 2, BINARY, NULL); rpn->add_operation("*", 2, BINARY, NULL);
    rpn->add_operation("-", 3, BINARY, NULL); rpn->add_operation("+", 3, BINARY, NULL);

    CHECK(rpn->infix_to_postfix("(1)") ==
                                "1 " );
    CHECK(rpn->infix_to_postfix("([1])") ==
                                "1 " );
    CHECK(rpn->infix_to_postfix("([{1}])") ==
                                "1 " );
    CHECK(rpn->infix_to_postfix("{(2+3)*5^(3-1)}") ==
                                "2 3 + 5 3 1 - ^ * " );
    CHECK(rpn->infix_to_postfix("((21+2*[7*6)*(5-(2-1}+2") ==
                                "21 2 7 6 * * + 5 2 1 - - * 2 + " );
    CHECK(rpn->infix_to_postfix("{(2+3)*5^(3-1)}") ==
                                "2 3 + 5 3 1 - ^ * " );
    CHECK(rpn->infix_to_postfix("{(2+3)*sqrt(3-1)}") ==
                                "2 3 + 3 1 - sqrt * " );
    CHECK(rpn->infix_to_postfix("([{2+3}-4]/2)^2") ==
                                "2 3 + 4 - 2 / 2 ^ " );
    CHECK(rpn->infix_to_postfix("{[2+6*(75+11-4)]}*[5-(2-1)]") ==
                                "2 6 75 11 + 4 - * + 5 2 1 - - * " );
    CHECK(rpn->infix_to_postfix("{[2+10*(15+16-4)]}*[5-(2-1)+9]") ==
                                "2 10 15 16 + 4 - * + 5 2 1 - - 9 + * " );
}

