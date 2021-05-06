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

WireManager::WireManager(Wire *wire, Canvas *canvas, WindowType window_type) :
    wire(wire), canvas(canvas), window_type(window_type)
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
        sleep(0.01);
        if (canvas->drawings.length() > drawing_count)
        {
            transmit_drawing(canvas->drawings[drawing_count++]);
        }
    }
}

void WireManager::run_receive()
{
    forever
    {
        sleep(0.01);
        if (wire->dirty)
        {
            qDebug() << wire->data;
            wire->dirty = false;
        }
    }
}

void WireManager::transmit_drawing(DrawingType *drawing)
{
    int type_id = static_cast<int>(drawing->get_type());
    transmit_number(type_id);
    
}

void WireManager::transmit_number(int num)
{
    QVector<bool> binary = int_to_binary(num);

    for (int i = 0; i < 32; ++i)
    {
        while (wire->dirty)
        {
            sleep(0.01);
        }
        wire->data = binary[i];
        wire->dirty = true;
    }
}