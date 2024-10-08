#pragma once
#include <QObject>
//#include "rpn/rpncalc.h"

class AppController : public QObject
{
    Q_OBJECT

private:
    //RPNcalc *rpnc;

public:
    AppController(void);
    int loop(int argc, char *argv[]);
    ~AppController();

public slots:
    void onEqualClick(void);
};

