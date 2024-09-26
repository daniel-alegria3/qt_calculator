#include <string>
#include <catch2/catch_test_macros.hpp>
#include "rpn/rpn.h"

using namespace std;

TEST_CASE("RPN should check parenthesis", "[unittest_parenthesis]") {
    RPN *rpn;
    rpn = new RPN();
    rpn->add_grouping("(", ")");
    rpn->add_grouping("[", "]");
    rpn->add_grouping("{", "}");

    string s;

    s = "{ [ 2 + 6 * ( 75 + 11 - 4 ) ] } * [ 5 - ( 2 - 1 ) ]";
    CHECK(rpn->is_correct_parenthesis(s));
    s = "( ( 21 + 3 * [ 52 + 7 * 4 ) * ( 5 - ( 2 - 1 } + 4";
    CHECK_FALSE(rpn->is_correct_parenthesis(s));
    s = ") ) ) ] }";
    CHECK_FALSE(rpn->is_correct_parenthesis(s));
    s = "( )";
    CHECK(rpn->is_correct_parenthesis(s));
    s = "{ [ ( ) ] }";
    CHECK(rpn->is_correct_parenthesis(s));
    s = "( }";
    CHECK_FALSE(rpn->is_correct_parenthesis(s));
    s = "{ [ 2 + 10 * ( 15 + 16 - 4 ) ] } * [ 5 - ( 2 - 1 ) + 9 ]";
    CHECK(rpn->is_correct_parenthesis(s));
    s = "( ( 12 + 7 * [ 35 + 14 - 3 ] * ( 5 - ( 2 - 1 )";
    CHECK_FALSE(rpn->is_correct_parenthesis(s));
    s = "( [ { 2 + 3 } - 4 ] / 2 ) ^ 2";
    CHECK(rpn->is_correct_parenthesis(s));
    s = "( ( 21 + 2 * [ 7 * 6 ) * ( 5- ( 2 - 1 } + 2 (";
    CHECK_FALSE(rpn->is_correct_parenthesis(s));
}

