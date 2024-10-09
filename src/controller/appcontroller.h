#pragma once
#include <QObject>
#include <string>
#include "rpn/rpn.h"
#include "rpn/undoredo.h"
#include "appview.h"

class AppController : public QObject
{
    Q_OBJECT

private:
    RPN *rpn;
    UndoRedo *ur;
    AppView *view;

public:
    AppController(void);
    int loop(int argc, char *argv[]);
    string solve(string expresion);
    ~AppController();

public slots:
    void on_display_change(void);
    void on_equal_click(void);
    void on_clear_click(void);
    void on_delete_click(void);
    void on_next_click(void);
    void on_prev_click(void);
};

