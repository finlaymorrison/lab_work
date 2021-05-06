/*
 * Project: include
 * File: include/wire-manager.h
 * -----
 * File Created: Thursday, 6th May 2021 7:17:02 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef INCLUDE_WIREMANAGER_H
#define INCLUDE_WIREMANAGER_H

#include "wire.h"
#include "canvas.h"
#include "main-window.h"
#include "drawing-type.h"

#include <QThread>

class WireManager : public QThread
{
private:
    Wire *wire;
    Canvas *canvas;

    WindowType window_type;

public:
    WireManager(Wire *wire, Canvas* canvas, WindowType window_type);

    void run() override;
    void run_send();
    void run_receive();

    void transmit_drawing(DrawingType *drawing);
    void transmit_number(int num);
};

#endif