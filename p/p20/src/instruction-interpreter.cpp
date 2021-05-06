/*
 * Project: src
 * File: src/instruction-interpreter.cpp
 * -----
 * File Created: Thursday, 6th May 2021 8:33:57 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "include/instruction-interpreter.h"

#include <QPoint>
#include <QDebug>
#include <QVector>

InstructionInterpreter::InstructionInterpreter(Canvas* canvas) :
    canvas(canvas), current_drawing(DrawingTypes::None)
{}

void InstructionInterpreter::input_num(int num)
{
    if (current_drawing == DrawingTypes::None)
    {
        current_buffer.clear();
        current_drawing = static_cast<DrawingTypes>(num);
    }
    else
    {
        switch(current_drawing)
        {
        case DrawingTypes::None:
            break;
        case DrawingTypes::RandomLine:
            interpret_randomline(num);
            break;
        case DrawingTypes::Circle:
            interpret_circle(num);
            break;
        case DrawingTypes::Square:
            interpret_square(num);
            break;
        case DrawingTypes::StraightLine:
            interpret_straightline(num);
            break;
        default:
            break;
        }
    }
}

void InstructionInterpreter::interpret_randomline(int num)
{
    if (current_buffer.size() < 5)
    {
        current_buffer.push_back(num);
    }
    else
    {
        if (current_buffer.size() - 4 < current_buffer[4] * 2)
        {
            current_buffer.push_back(num);
        }
        else
        {
            QColor color(current_buffer[0], current_buffer[1], current_buffer[2]);
            RandomLine *drawing = new RandomLine(color, current_buffer[3]);
            for (int i = 5; i < current_buffer.size() - 1; i += 2)
            {
                drawing->add_point({current_buffer[i], current_buffer[i+1]});
            }
            canvas->add_drawing(drawing);
            current_drawing = DrawingTypes::None;
        }
    }
}

void InstructionInterpreter::interpret_circle(int num)
{
    current_buffer.push_back(num);
    if (current_buffer.size() == 7)
    {
        QColor color(current_buffer[0], current_buffer[1], current_buffer[2]);
        Circle *drawing = new Circle(color, current_buffer[3]);
        drawing->set_center({current_buffer[4], current_buffer[5]});
        drawing->set_radius(current_buffer[6]);
        drawing->set_complete(true);
        canvas->add_drawing(drawing);
        current_drawing = DrawingTypes::None;
    }
}

void InstructionInterpreter::interpret_square(int num)
{
    current_buffer.push_back(num);
    if (current_buffer.size() == 8)
    {
        QColor color(current_buffer[0], current_buffer[1], current_buffer[2]);
        Square *drawing = new Square(color, current_buffer[3]);
        drawing->set_tl({current_buffer[4], current_buffer[5]});
        drawing->set_br({current_buffer[6], current_buffer[7]});
        canvas->add_drawing(drawing);
        current_drawing = DrawingTypes::None;
    }
}

void InstructionInterpreter::interpret_straightline(int num)
{
    current_buffer.push_back(num);
    if (current_buffer.size() == 8)
    {
        QColor color(current_buffer[0], current_buffer[1], current_buffer[2]);
        StraightLine *drawing = new StraightLine(color, current_buffer[3]);
        drawing->set_start({current_buffer[4], current_buffer[5]});
        drawing->set_finish({current_buffer[6], current_buffer[7]});
        canvas->add_drawing(drawing);
        current_drawing = DrawingTypes::None;
    }
}