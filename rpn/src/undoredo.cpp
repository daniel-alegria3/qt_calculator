#include "rpn/undoredo.h"

UndoRedo::UndoRedo()
{
    undos = new Stack<string>();
    redos = new Stack<string>();
}

void UndoRedo::input_string(string s)
{
    undos->push(s);
    redos->empty();
}

string UndoRedo::undo(void)
{
    if (undos->is_empty()) {
        return "";
    }

    string x = undos->pop();
    redos->push(x);

    if ( !undos->is_empty() ) {
        return undos->peek();
    }
    return "";
}

string UndoRedo::redo(void)
{
    if (redos->is_empty()) {
        return "";
    }

    string x = redos->pop();
    undos->push(x);

    return undos->peek();
}

void UndoRedo::empty(void)
{
    undos->empty();
    redos->empty();
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
            if (undo() != "") {
            }
        } else if (op[i] == "REDO") {
            if (redo() != "") {
            }
        } else {
            input_string(op[i]);
        }
    }
    return show();
}

bool UndoRedo::is_undos_empty()
{
    return undos->is_empty();
}

bool UndoRedo::is_redos_empty()
{
    return redos->is_empty();
}

