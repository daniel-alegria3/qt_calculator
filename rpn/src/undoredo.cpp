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
    cout << "undo: (pila 'undos' vacia)" << endl;
    return false;
}

bool UndoRedo::redo(void)
{
    if (!redos->is_empty()) {
        char x = (char) redos->pop();
        undos->push(x);
        return true;
    }
    cout << "redo: (pila 'redos' vacia)" << endl;
    return false;
}

string UndoRedo::show(void)
{
    string values = "";
    for (int i = 0; i < undos->length(); ++i) {
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
                cout << "undo: " << show() << endl;
            }
        } else if (op[i] == "REDO") {
            if (redo()) {
                cout << "redo: " << show() << endl;
            }
        } else {
            input_char(op[i][0]);
            cout << "inserta: " << show() << endl;
        }
    }
    return show();
}

