#pragma once
#include <QObject>
#include <string>
#include "rpn/rpn.h"

class AppController : public QObject
{
    Q_OBJECT

private:
    RPN *rpn;

public:
    AppController(void);
    int loop(int argc, char *argv[]);
    string solve(string expresion);
    ~AppController();

public slots:
    void on_equal_click(void);
};

