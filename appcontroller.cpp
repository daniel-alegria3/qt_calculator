#include <iostream>
#include <stdio.h>
#include "appcontroller.h"
#include "rpncalc.h"

using namespace std;

AppController::AppController (void) {
    rpn = new RPNcalc();
}

void AppController::loop(void) {
    string input;
    int ok; double num; char c;
    bool running;
    while (running) {
        cout << "Ingrese un numero o un operador ('q' para salir): ";
        // cin >> input;
        //
        ok = scanf(" %lf", &num);

        if (ok != EOF) {
            rpn->enterNumber(num);

        } else {
            scanf(" %c", &c);
            switch (c) {
                case 'q':
                    running = false;
                    break;
                case '+':
                    rpn->select_op_sum();
                    break;
                case '-':
                    rpn->select_op_diff();
                    break;
                case '*':
                    rpn->select_op_mul();
                    break;
                case '^':
                    rpn->select_op_pow();
                    break;
                case '/':
                    rpn->select_op_div();
                    break;
                case 's':
                    rpn->select_op_sqrt();
                    break;
                default:
                    cout << "Error: Ingrese un operador valido!" << endl;
                    break;
                cout << "--------------\n"+rpn->stack->dump()+"--------------\n";
            }
        }
    }
}

