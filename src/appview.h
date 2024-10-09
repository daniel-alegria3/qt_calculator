#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QRegularExpressionValidator>
#include <QTextCursor>

#include <QDebug>

#include <cstddef>
#include <iterator>

class AppView : public QMainWindow
{
    Q_OBJECT

private:
    QPushButton *bequal;
    QPushButton *bclear;
    QPushButton *bdelete;
    QPushButton *bprev;
    QPushButton *bnext;

    QLineEdit *display;
    QLabel *result;

public:
    AppView(QWidget *parent = nullptr);

    void clear_display();
    void write_display(QString text);
    void append_display(QString text);
    QString read_display();

    void clear_result();
    void write_result(QString text);
    QString read_result();

    QPushButton *button_appends(QString text);
    template<typename Func>
    QPushButton *button_does(QString text, Func method);

    template<typename T, typename Func>
    void connect_on_equal_click(T *objectInstance, Func method);
    template<typename T, typename Func>
    void connect_on_clear_click(T *objectInstance, Func method);
    template<typename T, typename Func>
    void connect_on_delete_click(T *objectInstance, Func method);
    template<typename T, typename Func>
    void connect_on_prev_click(T *objectInstance, Func method);
    template<typename T, typename Func>
    void connect_on_next_click(T *objectInstance, Func method);

    ~AppView();
};

/* #include "appview.cpp" */

#define FRAME_PADDING 20
#define FRAME_WIDTH (WIN_WIDTH - 2*(FRAME_PADDING))
#define FRAME_HEIGHT (WIN_HEIGHT - 2*(FRAME_PADDING))

//#define DISPLAY_REGEX "([0-9+-/*(){}\\[\\]]+)"
//#define DISPLAY_REGEX "^(?:[0-9]+|sqrt|[\\+\\-*/(){}\\[\\]])*$"
#define DISPLAY_REGEX "^(?:[0-9]+(?:\\.[0-9]+)?|sqrt|[\\+\\-*/(){}\\[\\]])*$"
#define LEFT_ARROW QString::fromUtf8("\u2190")
#define RIGHT_ARROW QString::fromUtf8("\u2192")

inline AppView::AppView(QWidget *parent) : QMainWindow(parent)
{
    QWidget *window = new QWidget(this);

    // frame
    QFrame *f1 = new QFrame(window);
    f1->setObjectName("f1");
    f1->setStyleSheet("QFrame#b1 {border: 1px solid black}");

    // buttons
    QPushButton *b0 = button_appends("0");
    QPushButton *b1 = button_appends("1");
    QPushButton *b2 = button_appends("2");
    QPushButton *b3 = button_appends("3");
    QPushButton *b4 = button_appends("4");
    QPushButton *b5 = button_appends("5");
    QPushButton *b6 = button_appends("6");
    QPushButton *b7 = button_appends("7");
    QPushButton *b8 = button_appends("8");
    QPushButton *b9 = button_appends("9");

    QPushButton *bplus = button_appends("+");
    QPushButton *bdiff = button_appends("-");
    QPushButton *bmul = button_appends("*");
    QPushButton *bdiv = button_appends("/");
    QPushButton *bpow= button_appends("^");
    QPushButton *bsqrt= button_appends("sqrt");
    QPushButton *bdot = button_appends(".");

    QPushButton *blparenthesis= button_appends("(");
    QPushButton *brparenthesis= button_appends(")");
    QPushButton *blbrace= button_appends("[");
    QPushButton *brbrace= button_appends("]");
    QPushButton *blbracket= button_appends("{");
    QPushButton *brbracket= button_appends("}");

    bequal = new QPushButton("=");
    bclear= new QPushButton("AC");
    bdelete= new QPushButton("DEL");
    bprev = new QPushButton(LEFT_ARROW);
    bnext = new QPushButton(RIGHT_ARROW);

    // displays
    display = new QLineEdit();
    QRegularExpression regex(DISPLAY_REGEX);
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, display);
    display->setValidator(validator);

    result = new QLabel("test");
    result->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    result->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    // Grid layout
    QGridLayout *grid = new QGridLayout(f1);
    grid->setSpacing(0);
    grid->addWidget(display, 0, 0, 1, 7);
    grid->addWidget(result, 1, 0, 1, 7);

    grid->addWidget(b7, 2, 0);
    grid->addWidget(b8, 2, 1);
    grid->addWidget(b9, 2, 2);
    grid->addWidget(bdelete, 2, 3);
    grid->addWidget(bclear, 2, 4);
    grid->addWidget(brparenthesis, 2, 5);
    grid->addWidget(blparenthesis, 2, 6);

    grid->addWidget(b4, 3, 0);
    grid->addWidget(b5, 3, 1);
    grid->addWidget(b6, 3, 2);
    grid->addWidget(bmul, 3, 3);
    grid->addWidget(bdiv, 3, 4);
    grid->addWidget(brbrace, 3, 5);
    grid->addWidget(blbrace, 3, 6);

    grid->addWidget(b1, 4, 0);
    grid->addWidget(b2, 4, 1);
    grid->addWidget(b3, 4, 2);
    grid->addWidget(bplus, 4, 3);
    grid->addWidget(bdiff, 4, 4);
    grid->addWidget(brbracket, 4, 5);
    grid->addWidget(blbracket, 4, 6);


    grid->addWidget(b0, 5, 0);
    grid->addWidget(bdot, 5, 1);
    grid->addWidget(bprev, 5, 2);
    grid->addWidget(bnext, 5, 3);
    grid->addWidget(bequal, 5, 4, 1, 3);

    //
    setCentralWidget(window);
}

////////////////////////////////////////////////////////////////////////////////
inline void AppView::clear_display() {
    display->setText("");
}

inline void AppView::write_display(QString text) {
    display->setText(text);
}

inline void AppView::append_display(QString text) {
    display->insert(text);
}

inline QString AppView::read_display() {
    return display->text();
}
inline void AppView::clear_result() {
    result->setText("");
}

inline void AppView::write_result(QString text) {
    result->setText(text);
}

inline QString AppView::read_result() {
    return result->text();
}

////////////////////////////////////////////////////////////////////////////////
inline QPushButton *AppView::button_appends(QString text) {
    QPushButton *button = new QPushButton(text);
    connect(button, &QPushButton::clicked, this, [this, text]() {
        append_display(text);
    });
    return button;
}

template<typename T, typename Func>
void AppView::connect_on_equal_click(T *objectInstance, Func method)
{
    connect(bequal, &QPushButton::clicked, objectInstance, method);
}

template<typename T, typename Func>
void AppView::connect_on_clear_click(T *objectInstance, Func method)
{
    connect(bclear, &QPushButton::clicked, objectInstance, method);
}

template<typename T, typename Func>
void AppView::connect_on_delete_click(T *objectInstance, Func method)
{
    connect(bdelete, &QPushButton::clicked, objectInstance, method);
}

template<typename T, typename Func>
void AppView::connect_on_prev_click(T *objectInstance, Func method)
{
    connect(bprev, &QPushButton::clicked, objectInstance, method);
}

template<typename T, typename Func>
void AppView::connect_on_next_click(T *objectInstance, Func method)
{
    connect(bnext, &QPushButton::clicked, objectInstance, method);
}

////////////////////////////////////////////////////////////////////////////////
inline AppView::~AppView()
{
    delete bequal;
    bequal = nullptr;
}
