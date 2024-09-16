#pragma once
#include <string>
#include <vector>
#include "stack.h"

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
        string get_opening_and_closing(const string s, string *opening, string *closing);
        Operation *get_operation(const string s);
        int get_precedence(const string s);
        bool is_unary_op(const string s);
        vector<string> split(const string s, const string delimiter);

    public:
        Stack<double> *operand_stack;

        RPN(void);
        string infix_to_postfix(string expresion);
        string eval_postfix(string expresion);
        void add_grouping(string opening, string closing);
        void add_operation(string symbol, int precedence, enum OpType type,
                           double (*func)(double a, double b));
};

