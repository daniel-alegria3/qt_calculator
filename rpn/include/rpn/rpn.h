#pragma once
#include <string>
#include <vector>
#include "stack.h"
#include "rpn/tokenizer.h"

using namespace std;

enum OpType {
    UNARY,
    BINARY,
    FUNCTION,
};

typedef struct {
    string opening;
    string closing;
} Grouping;
typedef struct {
    string symbol;
    int precedence;
    enum OpType type;
    double (*func)(double a, double b);
} Operation;

class RPN
{
private:
    vector<Operation> operations;
    vector<Grouping> groupings;

    string get_grouping_type(const string s);
    string get_grouping_type_and_opposite(const string s, string *opposite);
    /* bool is_correct_parenthesis(string expresion); */
    Operation *get_operation(const string s);
    int get_precedence(const string s);
    bool is_unary_op(const string s);

    void update_tokenizer();

public:
    Tokenizer *tokenizer;

    bool is_correct_parenthesis(string expresion);
    Stack<double> *operand_stack;

    RPN(void);
    string infix_to_postfix(string expresion);
    string eval_postfix(string expresion);
    void add_grouping(string opening, string closing);
    void add_operation(string symbol, int precedence, enum OpType type,
                       double (*func)(double a, double b));
    bool is_expresion_tokenizable(string expresion);
};

