#pragma once
#include "stack.h"
#include <string>
#include <vector>

#include <iostream>
using namespace std;

class UndoRedo
{
private:
public:
    Stack<string> *undos;
    Stack<string> *redos;

    UndoRedo();

    void input_string(string s);
    string undo(void);
    string redo(void);
    void empty(void);
    string show(void);
    string simulate(vector<string> op);

    bool is_undos_empty(void);
    bool is_redos_empty(void);
};

