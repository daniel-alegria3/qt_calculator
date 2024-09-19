#include <iostream>
#include <cmath>
#include <string>
#include "undoredo.h"

using namespace std;

int main(void)
{
    UndoRedo *ur = new UndoRedo();

    vector<string> op1 = {
        "(","1","+","2",")",
        "UNDO","UNDO","UNDO","UNDO","UNDO","UNDO","UNDO",
        "REDO","REDO","REDO","REDO","REDO","REDO"
    };

    vector<string> op2 = {
        "{","4","+","(","5","+","6",")","-","3","*","5",
        "UNDO","UNDO",
        "^","4","}","-","5","*","9",
        "UNDO","UNDO","REDO",
        "10",
    };

    vector<string> op3 = {
        "(","7","*","3",")","-","4",
        "UNDO","UNDO","UNDO","REDO","REDO",
        "+","(","2","*","(","3","+","1",")",")",
        "UNDO","UNDO","REDO"
    };

    vector<string> op4 = {
        "{","9","+","2","-","(","8","/","4",")",
        "UNDO","UNDO",
        "*","(","6","-","1",")","/","2",
        "UNDO","REDO","REDO","UNDO",
        "+","5","}"
    };

    vector<string> op5 = {
        "(","10","+","3",")","*","5",
        "UNDO","UNDO",
        "-","(","4","/","2",")","*","3",
        "UNDO","UNDO","REDO",
        "+","7","*","(","5","+","2",")",
        "REDO","UNDO"
    };

    printf("--------------------------------------------\n");
    ur->simulate(op1);
    printf("--------------------------------------------\n");
    ur->simulate(op2);
    printf("--------------------------------------------\n");
    ur->simulate(op3);
    printf("--------------------------------------------\n");
    ur->simulate(op4);
    printf("--------------------------------------------\n");
    ur->simulate(op5);
    printf("--------------------------------------------\n");

    return 0;
}

