#include <iostream>
#include <stdexcept>
#include "appcontroller.h"

using namespace std;

AppController::AppController (void) {
    rpn = new RPNcalc();
}

void AppController::loop(void) {
    string input;
    int ok;
    double num;
    char ch;

    bool running = true;
    while (running) {
        cout << "Ingrese un numero o un operador ('q' para salir): ";
        cin >> input;

        ok = sscanf(input.c_str(), " %lf", &num);
        if (ok != 0) {
            rpn->enterNumber(num);
        } else if (ok != EOF) {
            sscanf(input.c_str(), " %c", &ch);
            switch (ch) {
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
            }
            cout << "--------------\n"+rpn->stack->dump()+"--------------\n";
        }
    }
}

