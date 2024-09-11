#include "stack.h"

#include <stdio.h>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// both SYMB_NONE and TYPE_NONE need to be less than 0
enum GROUPING_SYMB {
    PHARENTHESIS,
    BRACE,
    BRACKET,
    SYMB_NONE = -1,
};
enum GROUPING_TYPE {
    OPENING,
    CLOSING,
    TYPE_NONE = -1,
};
const string opening[] = {
    [PHARENTHESIS] = "(",
    [BRACE] = "[",
    [BRACKET] = "{",
};
const string closing[] = {
    [PHARENTHESIS] = ")",
    [BRACE] = "]",
    [BRACKET] = "}",
};

enum OPERATION {
    SUM,
    SUB,
    MUL,
    DIV,
    POW,
    SQRT,
    OPERATION_NONE = -1,
};
const string operation[] = {
    [SUM] = "+",
    [SUB] = "-",
    [MUL] = "*",
    [DIV] = "/",
    [POW] = "^",
    [SQRT] = "sqrt",
};
const int precedence[] = {
    [SUM] = 3,
    [SUB] = 3,
    [MUL] = 2,
    [DIV] = 2,
    [POW] = 1,
    [SQRT] = 1,
};

static void get_grouping_symb_and_type(
    const string s,
    enum GROUPING_SYMB* name,
    enum GROUPING_TYPE* type);
static int get_precedence(const string s);
vector<string> split(const string s, const string delimiter);
///////////////////////////////////////////////////////////////////////////////

string infix_to_postfix(string expresion)
{
    Stack<string> *stack = new Stack<string>();

    // expresion = expresion.trim();
    vector<string> infix = split(expresion, " ");
    string output = "";

    enum GROUPING_SYMB symb, sy;
    enum GROUPING_TYPE type, ty;
    for (int i = 0; i < infix.size(); ++i) {
        string s = infix[i];
        if (s == "") {
            continue;
        }

        get_grouping_symb_and_type(s, &symb, &type);

        // printf("%s\n", s.c_str());

        if ( s == operation[SQRT] ) { // solucion temporal a operaciones unarias
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

        } else if (type == OPENING) { // (, [, {
            stack->push(s);

        } else if (type == CLOSING) { // ), ], }
            while (!stack->is_empty() && stack->peek() != opening[symb]) {
                string top = stack->pop();
                get_grouping_symb_and_type(top, &sy, &ty);
                if (ty != OPENING) {
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

static void get_grouping_symb_and_type(
    const string s,
    enum GROUPING_SYMB* symb,
    enum GROUPING_TYPE* type)
{
    *symb = SYMB_NONE;
    *type = TYPE_NONE;

    int len = sizeof(opening) / sizeof(opening[0]);
    for (int i = 0; i < len; ++i) {
        if (s == opening[i]) {
            *symb = (enum GROUPING_SYMB)i;
            *type = OPENING;
            return;
        }
        if (s == closing[i]) {
            *symb = (enum GROUPING_SYMB)i;
            *type = CLOSING;
            return;
        }
    }
}

static int get_precedence(const string s)
{
    int len = sizeof(operation) / sizeof(operation[0]);
    for (int i = 0; i < len; ++i) {
        if (s == operation[i]) {
            return precedence[i];
        }
    }
    return -1;
}

vector<string> split(const string s, const string delimiter)
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

void print_check(string s) {
    printf("%s\n", s.c_str());
    printf("%s\n", infix_to_postfix(s).c_str());
}

int main(void)
{
    string s0 = "( 2 + 5 ) * 3 + 1";
    string s1 = "2 + 5 * 3 + 1";
    string s2 = "{ ( 2 + 3 ) * 5 ^ ( 3 - 1 ) }";
    string s3 = "{ ( 2 + 3 ) * 5 ^ ( 2 + 1 ) - [ 4 * 5 - ( 2 - 1 ) ] }";

    string s4 = "{ ( 2 + 3 ) * 5 ^ ( 3 - 1 ) }";
    string s5 = "{ ( 2 + 3 ) * sqrt ( 3 - 1 ) }";

    printf("---------------------------------\n");
    print_check(s0);

    printf("---------------------------------\n");
    print_check(s1);

    printf("---------------------------------\n");
    print_check(s2);

    printf("---------------------------------\n");
    print_check(s3);

    printf("---------------------------------\n");
    printf("---------------------------------\n");
    print_check(s4);

    printf("---------------------------------\n");
    print_check(s5);

    return 0;
}

