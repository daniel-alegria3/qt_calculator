#include <iostream>
#include <stdexcept>
#include "appcontroller.h"

using namespace std;

AppController::AppController (void) {
    rpnc = new RPNcalc();
}

void AppController::loop(void) {
    string input;
    string output;

    char temp[128];
    bool running = true;
    while (running) {
        cout << ">> ";
        getline (cin, input);

        printf(": %s\n", input.c_str());

        if (input == "q") {
            running = false;
        } else {
            output = rpnc->solve(input);
            cout << output << endl;
        }
    }
}

