#include <iostream>
#include <QApplication>
#include <QLabel>
#include "appcontroller.h"

using namespace std;

int main (int argc, char *argv[]) {
    // QApplication app(argc, argv);
    // QLabel hello("Hello world!");
    // hello.show();

    AppController *ctrl = new AppController();
    ctrl->loop();

    // return app.exec();
}
