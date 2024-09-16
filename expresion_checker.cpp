#include "stack.h"

// both SYMB_NONE and TYPE_NONE need to be less than 0
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

const char opening[] = {
    [PHARENTHESIS] = '(',
    [BRACE] = '[',
    [BRACKET] = '{',
};
const char closing[] = {
    [PHARENTHESIS] = ')',
    [BRACE] = ']',
    [BRACKET] = '}',
};

static void get_grouping_name_and_type(
        const char ch,
        enum GROUPING_SYMB *name,
        enum GROUPING_TYPE *type
);

bool is_correct_parentesis(string expresion) {
    Stack<double> *stack = new Stack<double>();

    enum GROUPING_SYMB name;
    enum GROUPING_TYPE type;
    char ch;
    for (int i = 0; i < expresion.length(); ++i) {
        ch = expresion[i];
        get_grouping_name_and_type(ch, &name, &type);
        if (type == OPENING) {
            stack->push(ch);
        } else if (type == CLOSING && (stack->is_empty() || stack->pop() != opening[name])) {
            return false;
        }
    }

    if (stack->is_empty()) {
        return true;
    } else {
        return false;
    }

}

static void get_grouping_name_and_type(
        const char ch,
        enum GROUPING_SYMB *symb,
        enum GROUPING_TYPE *type
) {
    *symb = SYMB_NONE;
    *type = TYPE_NONE;

    int len = sizeof(opening)/sizeof(opening[0]);
    for (int i = 0; i < len; ++i) {
        if (ch == opening[i]) {
            *symb = (enum GROUPING_SYMB) i;
            *type = OPENING;
            return;
        }
        if (ch == closing[i]) {
            *symb = (enum GROUPING_SYMB) i;
            *type = CLOSING;
            return;
        }
    }
}

// void print_check(const char *str) {
//     printf("%d\n", is_correct_parentesis(str));
// }
//
// int main (void) {
//     print_check("(1)");
//     print_check("([{2+3}-4]/2)^2");
//     print_check("{[2+6*(75+11-4)]}*[5-(2-1)]");
//     print_check("{[2+10*(15+16-4)]}*[5-(2-1)+9]");
//
//     print_check("(5+4)+3)");
//     print_check("((12+7*[35+14-3]*(5-(2-1)");
//     print_check("((21+3*[52+7*4)*(5-(2-1}+4");
//     print_check("((21+2*[7*6)*(5-(2-1}+2(");
//
//     return 0;
// }
