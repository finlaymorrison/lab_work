/*
 * Project: src
 * File: src/wire-manager.cpp
 * -----
 * File Created: Thursday, 6th May 2021 7:17:09 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "include/wire-manager.h"
#include "include/wire.h"
#include "include/canvas.h"
#include "include/instruction-encoder.h"

#include <QDebug>
#include <QVector>

QVector<bool> int_to_binary(int num)
{
    QVector<bool> binary;

    for (int i = 0; i < 32; ++i)
    {
        binary.push_back(num & 0b1);
        num >>= 1;
    }

    return binary;
}

int binary_to_int(QVector<bool> binary)
{
    int num = 0;

    for (int i = 0; i < binary.size(); ++i)
    {
        num |= binary[i]<<i;
    }

    return num;
}

WireManager::WireManager(Wire *wire, Canvas *canvas, WindowType window_type) :
    wire(wire), canvas(canvas), interpreter(canvas), window_type(window_type)
{}

void WireManager::run()
{
    if (window_type == WindowType::Send)
    {
        run_send();
    }
    else if (window_type == WindowType::Receive)
    {
        run_receive();
    }
}

void WireManager::run_send()
{
    int drawing_count=0;
    forever
    {
        sleep(0.001);
        if (canvas->drawings.length() > drawing_count && !canvas->is_drawing())
        {
            transmit_drawing(canvas->drawings[drawing_count++]);
        }
    }
}

void WireManager::run_receive()
{
    QVector<bool> curr_num;
    forever
    {
        sleep(0.001);
        if (wire->dirty)
        {
            curr_num.push_back(wire->data);
            wire->dirty = false;
            
            if (curr_num.size() >= 32)
            {
                int num = binary_to_int(curr_num);
                interpreter.input_num(num);
                curr_num.clear();
            }
        }
    }
}

void WireManager::transmit_drawing(DrawingType *drawing)
{
    DrawingTypes drawing_type = drawing->get_type();

    QVector<int> buffer;

    switch(drawing_type)
    {
    case DrawingTypes::None:
        break;
    case DrawingTypes::RandomLine:
        buffer = InstructionEncoder::EncodeRandomLine(dynamic_cast<RandomLine*>(drawing));
        break;
    case DrawingTypes::Circle:
        buffer = InstructionEncoder::EncodeCircle(dynamic_cast<Circle*>(drawing));
        break;
    case DrawingTypes::Square:
        buffer = InstructionEncoder::EncodeSquare(dynamic_cast<Square*>(drawing));
        break;
    case DrawingTypes::StraightLine:
        buffer = InstructionEncoder::EncodeStraightLine(dynamic_cast<StraightLine*>(drawing));
        break;
    }

    for (int i = 0; i < buffer.size(); ++i)
    {
        transmit_number(buffer[i]);
    }
}

void WireManager::transmit_number(int num)
{
    QVector<bool> binary = int_to_binary(num);

    for (int i = 0; i < 32; ++i)
    {
        while (wire->dirty)
        {
            sleep(0.001);
        }
        wire->data = binary[i];
        wire->dirty = true;
    }
}