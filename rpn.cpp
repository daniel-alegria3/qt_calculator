#include <stdlib.h>
#include "stack.h"
#include "rpn.h"

#include <stdio.h>

RPN::RPN(void)
{
    operand_stack = new Stack<double>();
}

string RPN::infix_to_postfix(string expresion)
{
    Stack<string> *stack = new Stack<string>();

    // expresion = expresion.trim();
    vector<string> infix = split(expresion, " ");
    string output = "";

    string type, ope, clo;
    string ty;

    for (int i = 0; i < infix.size(); ++i) {
        string s = infix[i];
        if (s == "") {
            continue;
        }

        type = get_opening_and_closing(s, &ope, &clo);

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
            while (!stack->is_empty() && stack->peek() != ope) {
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
    operand_stack->empty();

    // expresion = expresion.trim();
    vector<string> postfix = split(expresion, " ");

    double op1, op2;
    Operation *op;
    for (int i = 0; i < postfix.size(); ++i) {
        string s = postfix[i];
        if (s == "") {
            continue;
        }

        op = get_operation(s);

        if (op == NULL) {
            operand_stack->push(stof(s));

        } else if (op->type == BINARY) {
            if (operand_stack->is_empty()) {
                return "ERROR: Tried to pop empty stack";
            };
            op2 = operand_stack->pop();

            if (operand_stack->is_empty()) {
                return "ERROR: Tried to pop empty stack";
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
             // TODO
        }
    }

    return to_string(operand_stack->peek());
}

void RPN::add_grouping(string opening, string closing)
{
    Grouping gr = {.opening = opening, .closing = closing};
    groupings.push_back(gr);
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
}


string RPN::get_grouping_type(const string s)
{
    Grouping *gr;
    for (int i = 0; i < groupings.size(); ++i) {
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

string RPN::get_opening_and_closing(const string s, string *opening, string *closing)
{
    Grouping *gr;
    for (int i = 0; i < groupings.size(); ++i) {
        gr = &groupings[i];
        if (s == gr->opening) {
            *opening = s;
            *closing = gr->closing;
            return "OPENING";
        }
        if (s == gr->closing) {
            *closing = s;
            *opening = gr->opening;
            return "CLOSING";
        }
    }
    return "NONE";
}

Operation *RPN::get_operation(const string s)
{
    Operation *op;
    for (int i = 0; i < operations.size(); ++i) {
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
    for (int i = 0; i < operations.size(); ++i) {
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
    for (int i = 0; i < operations.size(); ++i) {
        op = &operations[i];
        if (s == op->symbol && op->type == UNARY) {
            return true;
        }
    }
    return false;
}

vector<string> RPN::split(const string s, const string delimiter)
{

    vector<string> tokens;
    size_t last = 0;
    size_t next = 0;
    string token;
    while ((next = s.find(delimiter, last)) != string::npos) {
        token = s.substr(last, next - last);
        tokens.push_back(token);
        last = next + 1;
    }
    token = s.substr(last);
    tokens.push_back(token);

    return tokens;
}

