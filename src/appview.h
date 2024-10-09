#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QLabel>

#include <cstddef>
#include <iterator>

class AppView : public QMainWindow
{
    Q_OBJECT

private:
    QPushButton *bequal;

public:
    AppView(QWidget *parent = nullptr);

    void clear_display();
    void write_display();
    QString read_display();

    template<typename T, typename Func>
    void connect_on_equal_click(T *objectInstance, Func method);

    ~AppView();
};

/* #include "appview.cpp" */

#define FRAME_PADDING 20
#define FRAME_WIDTH (WIN_WIDTH - 2*(FRAME_PADDING))
#define FRAME_HEIGHT (WIN_HEIGHT - 2*(FRAME_PADDING))

inline AppView::AppView(QWidget *parent) : QMainWindow(parent)
{
    QWidget *window = new QWidget(this);

    QFrame *f1 = new QFrame(window);
    f1->setObjectName("f1");
    f1->setStyleSheet("QFrame#b1 {border: 1px solid black}");

    // Creamos los labels
    QPushButton *b0 = new QPushButton("0");
    QPushButton *b1 = new QPushButton("1");
    QPushButton *b2 = new QPushButton("2");
    QPushButton *b3 = new QPushButton("3");
    QPushButton *b4 = new QPushButton("4");
    QPushButton *b5 = new QPushButton("5");
    QPushButton *b6 = new QPushButton("6");
    QPushButton *b7 = new QPushButton("7");
    QPushButton *b8 = new QPushButton("8");
    QPushButton *b9 = new QPushButton("9");
    QPushButton *bplus = new QPushButton("+");
    QPushButton *bdiff = new QPushButton("-");
    QPushButton *bmul = new QPushButton("*");
    QPushButton *bdiv = new QPushButton("/");
    QPushButton *bdot = new QPushButton(".");
    bequal = new QPushButton("=");

    QLineEdit *display = new QLineEdit();
    QLabel *result = new QLabel("test");
    result->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    result->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    // Creamos un layout Grid
    QGridLayout *grid = new QGridLayout(f1);
    grid->setSpacing(0);
    grid->addWidget(display, 0, 0, 1, 4);
    grid->addWidget(result, 1, 0, 1, 4);
    grid->addWidget(b1, 2, 0);
    grid->addWidget(b2, 2, 1);
    grid->addWidget(b3, 2, 2);
    grid->addWidget(bplus, 2, 3);
    grid->addWidget(b4, 3, 0);
    grid->addWidget(b5, 3, 1);
    grid->addWidget(b6, 3, 2);
    grid->addWidget(bdiff, 3, 3);
    grid->addWidget(b7, 4, 0);
    grid->addWidget(b8, 4, 1);
    grid->addWidget(b9, 4, 2);
    grid->addWidget(bmul, 4, 3);
    grid->addWidget(bequal, 5, 0);
    grid->addWidget(b0, 5, 1);
    grid->addWidget(bdot, 5, 2);
    grid->addWidget(bdiv, 5, 3);

    setCentralWidget(window);

}

inline void AppView::clear_display()
{
    qDebug() << "clear_display";
}

inline void AppView::write_display()
{
    qDebug() << "write_display";
}

inline QString AppView::read_display()
{
    qDebug() << "read_display";
    return "";
}

template<typename T, typename Func>
void AppView::connect_on_equal_click(T *objectInstance, Func method)
{
    connect(bequal, &QPushButton::clicked, objectInstance, method);
}

inline AppView::~AppView()
{
    delete bequal;
    bequal = nullptr;
}
