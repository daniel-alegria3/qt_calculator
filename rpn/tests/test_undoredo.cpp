#include <iostream>
#include <string>
#include <catch2/catch_test_macros.hpp>
// #include <catch2/generators/catch_generators_all.hpp>
#include "rpn/undoredo.h"

using namespace std;

TEST_CASE("Undoredo works", "[undoredo]") {
    UndoRedo *ur = new UndoRedo();
    vector<string> vec;
    string res;

    vec = {
        "(","1","+","2",")",
        "UNDO","UNDO","UNDO","UNDO","UNDO","UNDO","UNDO",
        "REDO","REDO","REDO","REDO","REDO","REDO"
    };
    res = ur->simulate(vec);
    CHECK(res == "(1+2)");

    vec = {
        "{","4","+","(","5","+","6",")","-","3","*","5",
        "UNDO","UNDO",
        "^","4","}","-","5","*","9",
        "UNDO","UNDO","REDO",
        "10",
    };
    res = ur->simulate(vec);
    CHECK(res == "(1+2){4+(5+6)-3^4}-5*1");

    vec = {
        "(","7","*","3",")","-","4",
        "UNDO","UNDO","UNDO","REDO","REDO",
        "+","(","2","*","(","3","+","1",")",")",
        "UNDO","UNDO","REDO"
    };
    res = ur->simulate(vec);
    CHECK(res == "(1+2){4+(5+6)-3^4}-5*1(7*3)-+(2*(3+1)");

    vec = {
        "{","9","+","2","-","(","8","/","4",")",
        "UNDO","UNDO",
        "*","(","6","-","1",")","/","2",
        "UNDO","REDO","REDO","UNDO",
        "+","5","}"
    };
    res = ur->simulate(vec);
    CHECK(res == "(1+2){4+(5+6)-3^4}-5*1(7*3)-+(2*(3+1){9+2-(8/*(6-1)/+5}");

    vec = {
        "(","10","+","3",")","*","5",
        "UNDO","UNDO",
        "-","(","4","/","2",")","*","3",
        "UNDO","UNDO","REDO",
        "+","7","*","(","5","+","2",")",
        "REDO","UNDO"
    };
    res = ur->simulate(vec);
    CHECK(res == "(1+2){4+(5+6)-3^4}-5*1(7*3)-+(2*(3+1){9+2-(8/*(6-1)/+5}(1+3)-(4/2)*+7*(5+2");
}

