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
#include <QMessageBox>
#include <QSizePolicy>
#include <QShortcut>
#include <QKeySequence>

#include <QDebug>

#include <cstddef>
#include <iterator>
#include <string>

class AppView : public QMainWindow
{
    Q_OBJECT

private:
    QShortcut *enter_sc;

    QPushButton *bequal;
    QPushButton *bclear;
    QPushButton *bdelete;
    QPushButton *bundo;
    QPushButton *bredo;

    QLineEdit *display;
    QLabel *result;

    QMessageBox *warn_msgbox;

public:
    AppView(QWidget *parent = nullptr);

    void clear_display();
    void write_display(string text);
    void append_display(string text);
    string read_display();

    void clear_result();
    void write_result(string text);
    string read_result();

    void set_display_regex_validator(string text);
    void display_backspace();

    void warn_display_parenthesis();
    void warn_display_eval();

    void enable_redo_btn();
    void enable_undo_btn();
    void disable_redo_btn();
    void disable_undo_btn();

    QPushButton *button_appends(QString text);
    QPushButton *button_slots(QString text);
    template<typename Func>
    QPushButton *button_does(QString text, Func method);

    template<typename T, typename Func>
    void connect_on_display_change(T *objectInstance, Func method);

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

    void keep_display_focus();

    ~AppView();
};

/* #include "appview.cpp" */

#define FRAME_PADDING 20
#define FRAME_WIDTH (WIN_WIDTH - 2*(FRAME_PADDING))
#define FRAME_HEIGHT (WIN_HEIGHT - 2*(FRAME_PADDING))

#define LEFT_ARROW QString::fromUtf8("\u2190")
#define RIGHT_ARROW QString::fromUtf8("\u2192")

inline AppView::AppView(QWidget *parent) : QMainWindow(parent)
{
    QWidget *window = new QWidget(this);

    // frame
    QFrame *f1 = new QFrame();
    f1->setFrameShape(QFrame::Box);
    f1->setFrameShadow(QFrame::Raised);
    f1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    f1->setContentsMargins(5, 5, 5, 5);
    f1->setLineWidth(3);

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
    QPushButton *bpow = button_appends("^");
    QPushButton *bsqrt = button_appends("sqrt");
    QPushButton *bdot = button_appends(".");

    QPushButton *blparenthesis = button_appends("(");
    QPushButton *brparenthesis = button_appends(")");
    QPushButton *blbrace = button_appends("[");
    QPushButton *brbrace = button_appends("]");
    QPushButton *blbracket = button_appends("{");
    QPushButton *brbracket = button_appends("}");

    bequal =  button_slots("=");
    bclear= button_slots("AC");
    bdelete = button_slots("DEL");
    // bundo = new QPushButton(LEFT_ARROW);
    // bredo = new QPushButton(RIGHT_ARROW);
    bundo = button_slots("");
    bundo->setIcon(QIcon(":icons/undo-circular-arrow.png"));
    bundo->setEnabled(false);
    bredo = button_slots("");
    bredo->setIcon(QIcon(":icons/redo-arrow-symbol.png"));
    bredo->setEnabled(false);

    // displays
    display = new QLineEdit();
    connect(display, &QLineEdit::editingFinished, this, &AppView::keep_display_focus);
    display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    result = new QLabel();
    result->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    result->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    result->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Grid layout
    QGridLayout *grid = new QGridLayout(f1);
    grid->setContentsMargins(5, 5, 5, 5);
    grid->setSizeConstraint(QLayout::SetDefaultConstraint);
    grid->setAlignment(Qt::AlignJustify);
    grid->setSpacing(2);

    grid->addWidget(display, 0, 0, 1, 7);
    grid->addWidget(result, 1, 0, 1, 7);

    grid->addWidget(b7, 2, 0);
    grid->addWidget(b8, 2, 1);
    grid->addWidget(b9, 2, 2);
    grid->addWidget(bdelete, 2, 3);
    grid->addWidget(bclear, 2, 4);
    grid->addWidget(blparenthesis, 2, 5);
    grid->addWidget(brparenthesis, 2, 6);

    grid->addWidget(b4, 3, 0);
    grid->addWidget(b5, 3, 1);
    grid->addWidget(b6, 3, 2);
    grid->addWidget(bmul, 3, 3);
    grid->addWidget(bdiv, 3, 4);
    grid->addWidget(blbrace, 3, 5);
    grid->addWidget(brbrace, 3, 6);

    grid->addWidget(b1, 4, 0);
    grid->addWidget(b2, 4, 1);
    grid->addWidget(b3, 4, 2);
    grid->addWidget(bplus, 4, 3);
    grid->addWidget(bdiff, 4, 4);
    grid->addWidget(blbracket, 4, 5);
    grid->addWidget(brbracket, 4, 6);


    grid->addWidget(b0, 5, 0);
    grid->addWidget(bdot, 5, 1);
    grid->addWidget(bequal, 5, 2);
    grid->addWidget(bsqrt, 5, 3, 1, 2);
    grid->addWidget(bundo, 5, 5);
    grid->addWidget(bredo, 5, 6);

    //
    warn_msgbox = new QMessageBox(window);
    warn_msgbox->setIcon(QMessageBox::Information);
    warn_msgbox->setStandardButtons(QMessageBox::Ok);
    warn_msgbox->setDefaultButton(QMessageBox::Ok);

    //
    QShortcut *enter_sc = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(enter_sc, &QShortcut::activated, [this](){
        bequal->click();
    });

    //
    window->setLayout(grid);
    setCentralWidget(window);
}

////////////////////////////////////////////////////////////////////////////////
inline void AppView::clear_display() {
    display->setText("");
}

inline void AppView::write_display(string text) {
    display->blockSignals(true);
    display->setText(QString::fromStdString(text));
    display->blockSignals(false);
}

inline void AppView::append_display(string text) {
    display->insert(QString::fromStdString(text));
}

inline string AppView::read_display() {
    return display->text().toStdString();
}
inline void AppView::clear_result() {
    result->setText("");
}

inline void AppView::write_result(string text) {
    result->setText(QString::fromStdString(text));
}

inline string AppView::read_result() {
    return result->text().toStdString();
}

////////////////////////////////////////////////////////////////////////////////
inline QPushButton *AppView::button_appends(QString text) {
    QPushButton *button = new QPushButton(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(button, &QPushButton::clicked, this, [this, text]() {
        append_display(text.toStdString());
    });
    return button;
}

inline QPushButton *AppView::button_slots(QString text) {
    QPushButton *button = new QPushButton(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return button;
}

inline void AppView::set_display_regex_validator(string text) {
    QRegularExpression regex(QString::fromStdString("^(?:" + text + ")*$"));
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    display->setValidator(validator);
}

inline void AppView::display_backspace() {
    display->backspace();
}

inline void AppView::warn_display_parenthesis() {
    warn_msgbox->setText("Advertencia");
    warn_msgbox->setInformativeText("Parentesis Incorrecto!");
    warn_msgbox->exec();
}
inline void AppView::warn_display_eval() {
    warn_msgbox->setText("Advertencia");
    warn_msgbox->setInformativeText("Expresion Aritmetica Incorrecta!");
    warn_msgbox->exec();
}

////////////////////////////////////////////////////////////////////////////////
inline void AppView::enable_redo_btn() {
    bredo->setEnabled(true);
}
inline void AppView::enable_undo_btn() {
    bundo->setEnabled(true);
}

inline void AppView::disable_redo_btn() {
    bredo->setEnabled(false);
}
inline void AppView::disable_undo_btn() {
    bundo->setEnabled(false);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T, typename Func>
void AppView::connect_on_display_change(T *objectInstance, Func method)
{
    connect(display, &QLineEdit::textChanged, objectInstance, method);
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
    connect(bundo, &QPushButton::clicked, objectInstance, method);
}

template<typename T, typename Func>
void AppView::connect_on_next_click(T *objectInstance, Func method)
{
    connect(bredo, &QPushButton::clicked, objectInstance, method);
}

////////////////////////////////////////////////////////////////////////////////
inline void AppView::keep_display_focus() {
    display->setFocus();
}

inline AppView::~AppView()
{
    delete bequal;
    bequal = nullptr;
}
