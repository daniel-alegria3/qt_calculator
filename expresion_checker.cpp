#include "stack.h"

enum SYMBOL { PHARENTHESIS, BRACE, BRACKET, NONE };
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

enum SYMBOL get_symbol(const char ch) {
    if (ch == closing[PHARENTHESIS] || ch == opening[PHARENTHESIS]) {
        return PHARENTHESIS;
    } else if (ch == closing[BRACE] || ch == opening[BRACE]) {
        return BRACE;
    } else if (ch == closing[BRACKET] || ch == opening[BRACKET]) {
        return BRACKET;
    }
    return NONE;
}

#define OPENING_COND(ch) ((ch) == opening[PHARENTHESIS] \
                          || (ch) == opening[BRACE] \
                          || (ch) == opening[BRACKET])
#define CLOSING_COND(ch) ((ch) == closing[PHARENTHESIS] \
                          || (ch) == closing[BRACE] \
                          || (ch) == closing[BRACKET])

bool isCorrectParentesis(const char *expresion) {
    Stack *stack = new Stack();

    enum SYMBOL type;
    for (const char *ch = expresion; *ch != '\0'; ++ch) {
        type = get_symbol(*ch);
        if (OPENING_COND(*ch)) {
            stack->push(*ch);
        } else if (CLOSING_COND(*ch) && (stack->is_empty() || stack->pop() != opening[type])) {
            return false;
        }
    }

    if (stack->is_empty()) {
        return true;
    } else {
        return false;
    }

}

// void print_check(const char *str) {
//     printf("%d\n", isCorrectParentesis(str));
// }
//
// int main (int argc, char *argv[]) {
//
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
