#pragma once
#include <cstddef>
#include <string>
#include "rpncalc.h"

typedef double Op;

class AppController
{
private:
public:
    RPNcalc *rpn = new RPNcalc();

    AppController(void);
    void loop(void);
};


