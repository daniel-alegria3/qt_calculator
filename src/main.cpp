#include <iostream>
#include "appcontroller.h"

using namespace std;

int main (int argc, char *argv[]) {
    AppController c;
    return c.loop(argc, argv);
}

