#include <iostream>
#include <QApplication>
#include <QGridLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>

using namespace std;

#define WIN_WIDTH 250
#define WIN_HEIGHT 200
#define FRAME_PADDING 20

#define FRAME_WIDTH (WIN_WIDTH - 2*(FRAME_PADDING))
#define FRAME_HEIGHT (WIN_HEIGHT - 2*(FRAME_PADDING))

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Creamos el widget que representara la ventana
    QWidget window;
    // window.setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    window.setWindowTitle("Calculadora Basica");
    window.setWindowIcon(QIcon("imgs/calculadora.ico"));

    // Creamos el marco
    QFrame f1(&window);
    // f1.setGeometry(FRAME_PADDING, FRAME_PADDING, FRAME_WIDTH, FRAME_HEIGHT/2);
    f1.setObjectName("f1");
    f1.setStyleSheet("QFrame#b1 {border: 1px solid black}");
    f1.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Creamos los labels
    QPushButton b0("0");
    QPushButton b1("1");
    QPushButton b2("2");
    QPushButton b3("3");
    QPushButton b4("4");
    QPushButton b5("5");
    QPushButton b6("6");
    QPushButton b7("7");
    QPushButton b8("8");
    QPushButton b9("9");
    QPushButton bplus("+");
    QPushButton bdiff("-");
    QPushButton bmul("*");
    QPushButton bdiv("/");
    QPushButton bdot(".");
    QPushButton bequal("=");

    // Les damos ID's (hay otra forma de cambiar estilos que no involucra esto)
    b0.setObjectName("b0");
    b1.setObjectName("b1"); b2.setObjectName("b2"); b3.setObjectName("b3");
    b4.setObjectName("b4"); b5.setObjectName("b5"); b6.setObjectName("b6");
    b7.setObjectName("b7"); b8.setObjectName("b8"); b9.setObjectName("b9");
    bplus.setObjectName("bplus"); bdiff.setObjectName("bdiff"); bmul.setObjectName("bmul");
    bdiv.setObjectName("bdiv"); bdot.setObjectName("bdot"); bequal.setObjectName("bequal");

    b0.setStyleSheet("QPushButton#b0 {background-color: white; color: red}");
    b1.setStyleSheet("QPushButton#b1 {background-color: white; color: red}");
    b2.setStyleSheet("QPushButton#b2 {background-color: white; color: red}");
    b3.setStyleSheet("QPushButton#b3 {background-color: white; color: red}");
    b4.setStyleSheet("QPushButton#b4 {background-color: white; color: red}");
    b5.setStyleSheet("QPushButton#b5 {background-color: white; color: red}");
    b6.setStyleSheet("QPushButton#b6 {background-color: white; color: red}");
    b7.setStyleSheet("QPushButton#b7 {background-color: white; color: red}");
    b8.setStyleSheet("QPushButton#b8 {background-color: white; color: red}");
    b9.setStyleSheet("QPushButton#b9 {background-color: white; color: red}");
    bplus.setStyleSheet("QPushButton#bplus {background-color: cyan; color: black}");
    bdiff.setStyleSheet("QPushButton#bdiff {background-color: cyan; color: black}");
    bmul.setStyleSheet("QPushButton#bmul {background-color: cyan; color: black}");
    bdiv.setStyleSheet("QPushButton#bdiv {background-color: cyan; color: black}");
    bdot.setStyleSheet("QPushButton#bdot {background-color: green; color: black}");
    bequal.setStyleSheet("QPushButton#bequal {background-color: red; color: red}");

    b0.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b1.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b2.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b3.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b4.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b5.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b6.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b7.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b8.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b9.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bplus.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bdiff.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bmul.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bdiv.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bdot.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bequal.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    //
    QLineEdit le(&window);
    le.setStyleSheet("QLineEdit { font-family: Arial; font-size: 12pt; font-weight: bold; }");



    // Creamos un layout Grid
    QGridLayout grid(&f1);
    grid.setSpacing(0);
    grid.addWidget(&le, 0, 0, 1, 4);
    grid.addWidget(&b1, 1, 0);
    grid.addWidget(&b2, 1, 1);
    grid.addWidget(&b3, 1, 2);
    grid.addWidget(&bplus, 1, 3);
    grid.addWidget(&b4, 2, 0);
    grid.addWidget(&b5, 2, 1);
    grid.addWidget(&b6, 2, 2);
    grid.addWidget(&bdiff, 2, 3);
    grid.addWidget(&b7, 3, 0);
    grid.addWidget(&b8, 3, 1);
    grid.addWidget(&b9, 3, 2);
    grid.addWidget(&bmul, 3, 3);
    grid.addWidget(&bequal, 4, 0);
    grid.addWidget(&b0, 4, 1);
    grid.addWidget(&bdot, 4, 2);
    grid.addWidget(&bdiv, 4, 3);

    window.show();
    return app.exec();
}

