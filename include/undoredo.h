#pragma once
#include "stack.h"
#include <string>

class UndoRedo
{
private:
public:
    Stack<char> *undos;
    Stack<char> *redos;

    UndoRedo();

    void input_char(char c);
    bool undo(void);
    bool redo(void);
    string show(void);
    string simulate(vector<string> op);
};

