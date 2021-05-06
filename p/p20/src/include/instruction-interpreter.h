/*
 * Project: include
 * File: include/instruction-interpreter.h
 * -----
 * File Created: Thursday, 6th May 2021 8:33:51 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef INCLUDE_INSTRUCTIONINTERPRETER_H
#define INCLUDE_INSTRUCTIONINTERPRETER_H

#include "drawing-type.h"
#include "canvas.h"

#include <QVector>
#include <QPair>

class InstructionInterpreter
{
private:
    Canvas* canvas;

    DrawingTypes current_drawing;

    QVector<int> current_buffer;

public:
    InstructionInterpreter(Canvas *canvas);

    void input_num(int num);

    void interpret_randomline(int num);
    void interpret_circle(int num);
    void interpret_square(int num);
    void interpret_straightline(int num);
};

#endif