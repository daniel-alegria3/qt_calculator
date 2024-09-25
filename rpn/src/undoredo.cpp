#include "rpn/undoredo.h"

UndoRedo::UndoRedo()
{
    undos = new Stack<char>();
    redos = new Stack<char>();
}

void UndoRedo::input_char(char c)
{
    undos->push(c);
    redos->empty();
}

bool UndoRedo::undo(void)
{
    if (!undos->is_empty()) {
        char x = (char) undos->pop();
        redos->push(x);
        return true;
    }
    return false;
}

bool UndoRedo::redo(void)
{
    if (!redos->is_empty()) {
        char x = (char) redos->pop();
        undos->push(x);
        return true;
    }
    return false;
}

string UndoRedo::show(void)
{
    string values = "";
    for (int i = undos->length()-1; i >= 0 ; --i) {
        values += undos->get(i);
    }
    return values;
}

string UndoRedo::simulate(vector<string> op)
{
    int n = op.size();
    for (int i = 0; i < n; ++i) {
        if (op[i] == "UNDO") {
            if (undo()) {
            }
        } else if (op[i] == "REDO") {
            if (redo()) {
            }
        } else {
            input_char(op[i][0]);
        }
    }
    return show();
}

