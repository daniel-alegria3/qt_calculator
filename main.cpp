#include <iostream>
#include "appcontroller.h"

using namespace std;

int main (int argc, char *argv[]) {
    AppController *ctrl = new AppController();
    ctrl->loop();
    return 0;
}

