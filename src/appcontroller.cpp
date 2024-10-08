#include <QApplication>
#include <QDebug>

#include "appcontroller.h"
#include "appview.h"
//#include "rpn/rpncalc.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 500

AppController::AppController (void) {
    //rpnc = new RPNcalc();
}

int AppController::loop(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AppView view;

    view.setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    view.setWindowTitle("Calculadora Basica");
    view.setWindowIcon(QIcon("imgs/calculadora.ico"));

    view.connectOnEqualClick(this, &AppController::onEqualClick);

    view.show();

    return app.exec();
}

void AppController::onEqualClick(void) {
    qDebug() << "Button clicked, action performed!";
}

AppController::~AppController()
{
    //delete rpnc;
    //rpnc = nullptr;
}

