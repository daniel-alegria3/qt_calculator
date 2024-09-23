#pragma once
#include <cstddef>
#include <string>
#include "rpn/rpncalc.h"

typedef double Op;

class AppController
{
private:
public:
    RPNcalc *rpnc = new RPNcalc();

    AppController(void);
    void loop(void);
};


