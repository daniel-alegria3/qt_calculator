#include <QApplication>
#include <QDebug>
#include <cmath>
#include <cstddef>

#include "appcontroller.h"
#include "appview.h"
#include "rpn/rpn.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 500

double op_sum(double a, double b);
double op_diff(double a, double b);
double op_mul(double a, double b);
double op_pow(double a, double b);
double op_div(double a, double b);
double op_sqrt(double a, double b);

AppController::AppController (void) {
    rpn = new RPN();
    rpn->add_grouping("(", ")");
    rpn->add_grouping("[", "]");
    rpn->add_grouping("{", "}");

    rpn->add_operation("sqrt", 1, UNARY, &op_sqrt);
    rpn->add_operation("^", 1, BINARY, &op_pow);
    rpn->add_operation("/", 2, BINARY, &op_div);
    rpn->add_operation("*", 2, BINARY, &op_mul);
    rpn->add_operation("-", 3, BINARY, &op_diff);
    rpn->add_operation("+", 3, BINARY, &op_sum);
}

int AppController::loop(int argc, char *argv[]) {
    QApplication app(argc, argv);

    view = new AppView();

    // view.setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    view->setWindowTitle("Calculadora Basica");

    view->setWindowIcon(QIcon(":/imgs/calculator.ico"));

    // TODO: FIX regex in rpn/src/tokenizer.cpp
    // "([0-9+-/*(){}\\[\\]]+)"
    // "^(?:[0-9]+|sqrt|[\\+\\-*/(){}\\[\\]])*$"
    #define DISPLAY_REGEX "^(?:[0-9]+(?:\\.[0-9]+)?|sqrt|[\\+\\-*/(){}\\[\\]])*$"
    // view->set_display_regex_validator(rpn->tokenizer->regex_pattern_string);
    view->set_display_regex_validator(DISPLAY_REGEX);

    view->connect_on_equal_click(this, &AppController::on_equal_click);
    view->connect_on_clear_click(this, &AppController::on_clear_click);
    view->connect_on_delete_click(this, &AppController::on_delete_click);
    view->connect_on_prev_click(this, &AppController::on_prev_click);
    view->connect_on_next_click(this, &AppController::on_next_click);

    view->show();

    return app.exec();
}

string AppController::solve(string expresion) {
    if (!rpn->is_correct_parenthesis(expresion)) {
        view->warn_display_parenthesis();
    }
    string postfix = rpn->infix_to_postfix(expresion);
    string result = rpn->eval_postfix(postfix);
    if (result == "") {
        view->warn_display_eval();
    }
    return rpn->eval_postfix(postfix);
}

void AppController::on_equal_click(void) {
    string expresion = view->read_display();
    view->write_result(solve(expresion));
}

void AppController::on_clear_click(void) {
    view->clear_display();
}

void AppController::on_delete_click(void) {
    qDebug() << "DELETE";
}

void AppController::on_prev_click(void) {
    qDebug() << "PREV";
}

void AppController::on_next_click(void) {
    qDebug() << "NEXT";
}


AppController::~AppController()
{
    delete rpn;
    rpn = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
double op_sum(double a, double b) { return a + b; }
double op_diff(double a, double b) { return a - b; }
double op_mul(double a, double b) { return a * b; }
double op_pow(double a, double b) {
    int n = (int) b;
    double r = 1;
    while (n-- > 0) {
        r *= a;
    }
    return r;
}
double op_div(double a, double b) { return a - b; }
double op_sqrt(double a, double b) { return sqrt(a); }

