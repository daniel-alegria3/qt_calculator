#include <cmath>
#include <stdlib.h>
#include "rpn/stack.h"
#include "rpn/tokenizer.h"
#include "rpn/rpn.h"

#include <stdio.h>

RPN::RPN(void)
{
    operand_stack = new Stack<double>();
    tokenizer = new Tokenizer();
}

string RPN::infix_to_postfix(string expresion)
{
    Stack<string> *stack = new Stack<string>();

    vector<string> infix = tokenizer->tokenize(expresion);
    string output = "";

    string type, opposite;
    string ty;

    for (size_t i = 0; i < infix.size(); ++i) {
        string s = infix[i];

        type = get_grouping_type_and_opposite(s, &opposite);

        // printf("%s\n", s.c_str());

        if ( is_unary_op(s) ) { // solucion temporal a operaciones unarias
            stack->push(s);
        } else

        if ( get_precedence(s) > 0) { // es una operacion
            int prec;
            while (!stack->is_empty()
                   && (prec = get_precedence(stack->peek())) > 0
                   && prec <= get_precedence(s)) {
                output += stack->pop() + " ";
            }
            stack->push(s);

        } else if (type == "OPENING") { // (, [, {
            stack->push(s);

        } else if (type == "CLOSING") { // ), ], }
            while (!stack->is_empty() && stack->peek() != opposite) {
                string top = stack->pop();
                ty = get_grouping_type(top);
                if (ty != "OPENING") {
                    output += top + " ";
                }
            }
            if (!stack->is_empty()) {
                stack->pop();
            }

        } else {
            output += s + " ";
        }
    }

    while (!stack->is_empty()) {
        output += stack->pop() + " ";
    }

    return output;
}

string RPN::eval_postfix(string expresion)
{
    if (expresion == "") {
        return "";
    }

    operand_stack->empty();

    vector<string> postfix = tokenizer->tokenize(expresion);

    double op1, op2;
    Operation *op;
    for (size_t i = 0; i < postfix.size(); ++i) {
        string s = postfix[i];

        // printf("%s\n", s.c_str());

        op = get_operation(s);

        if (op == NULL) {
            operand_stack->push(stof(s));

        } else if (op->type == BINARY) {
            if (operand_stack->is_empty()) {
                // "ERROR: Tried to pop empty stack";
                return "";
            };
            op2 = operand_stack->pop();

            if (operand_stack->is_empty()) {
                // "ERROR: Tried to pop empty stack";
                return "";
            };
            op1 = operand_stack->pop();

            operand_stack->push(op->func(op1, op2));

        } else if (op->type == UNARY) {
            if (operand_stack->is_empty()) {
                return "ERROR: Tried to pop empty stack";
            };
            op1 = operand_stack->pop();

            operand_stack->push(op->func(op1, 0)); // TODO: fix unary functions
                                                   // being defined with two
        } else if (op->type == FUNCTION) {
            op->func(0, 0);
        }
    }

    return to_string(operand_stack->peek());
}

bool RPN::is_correct_parenthesis(string expresion) {
    Stack<string> *stack = new Stack<string>();

    vector<string> parenthesis = tokenizer->tokenize(expresion);

    string s;
    string type, opposite;
    for (size_t i = 0; i < parenthesis.size(); ++i) {
        s = parenthesis[i];
        type = get_grouping_type_and_opposite(s, &opposite);
        if (type == "OPENING") {
            stack->push(s);
        } else if (type == "CLOSING" && (stack->is_empty() || stack->pop() != opposite)) {
            return false;
        }
    }

    if (stack->is_empty()) {
        return true;
    } else {
        return false;
    }
}


void RPN::add_grouping(string opening, string closing)
{
    Grouping gr = {.opening = opening, .closing = closing};
    groupings.push_back(gr);
    update_tokenizer();
}

void RPN::add_operation(string symbol, int precedence, enum OpType type,
                   double (*func)(double a, double b))
{
    Operation op = {
        .symbol = symbol,
        .precedence = precedence,
        .type = type,
        .func = func,
    };
    operations.push_back(op);
    update_tokenizer();
}


string RPN::get_grouping_type(const string s)
{
    Grouping *gr;
    for (size_t i = 0; i < groupings.size(); ++i) {
        gr = &groupings[i];
        if (s == gr->opening) {
            return "OPENING";
        }
        if (s == gr->closing) {
            return "CLOSING";
        }
    }
    return "NONE";
}

string RPN::get_grouping_type_and_opposite(const string s, string *opposite)
{
    Grouping *gr;
    for (size_t i = 0; i < groupings.size(); ++i) {
        gr = &groupings[i];
        if (s == gr->opening) {
            *opposite = gr->closing;
            return "OPENING";
        }
        if (s == gr->closing) {
            *opposite = gr->opening;
            return "CLOSING";
        }
    }
    return "NONE";
}

Operation *RPN::get_operation(const string s)
{
    Operation *op;
    for (size_t i = 0; i < operations.size(); ++i) {
        op = &operations[i];
        if (s == op->symbol) {
            return op;
        }
    }
    return NULL;
}

int RPN::get_precedence(const string s)
{
    Operation *op;
    for (size_t i = 0; i < operations.size(); ++i) {
        op = &operations[i];
        if (s == op->symbol) {
            return op->precedence;
        }
    }
    return -1;
}

bool RPN::is_unary_op(const string s)
{
    Operation *op;
    for (size_t i = 0; i < operations.size(); ++i) {
        op = &operations[i];
        if (s == op->symbol && op->type == UNARY) {
            return true;
        }
    }
    return false;
}

void RPN::update_tokenizer() {
    vector<string> delims;
    Operation *op;
    Grouping *gr;

    for (size_t i = 0; i < operations.size(); ++i) {
        op = &operations[i];
        delims.push_back(op->symbol);
    }

    for (size_t i = 0; i < groupings.size(); ++i) {
        gr = &groupings[i];
        delims.push_back(gr->opening);
        delims.push_back(gr->closing);
    }

    tokenizer->update_regex_pattern(delims);
}

bool RPN::is_expresion_tokenizable(string expresion) {
    return tokenizer->is_tokenizable(expresion);
}

