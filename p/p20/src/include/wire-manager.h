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
#include "instruction-interpreter.h"

#include <QThread>

/* Controls the communication of a window on the wire. */
class WireManager : public QThread
{
private:
    /* Shared wire. */
    Wire *wire;
    /* Canvas to read/write drawings to. */
    Canvas *canvas;
    /* State-machine class that interprets streams of numbers into drawings. */
    InstructionInterpreter interpreter;

    /* Send or receive window. */
    WindowType window_type;

public:
    WireManager(Wire *wire, Canvas* canvas, WindowType window_type);

    /* Start the thread. */
    void run() override;

    /* Functions for the two modes of operation for this class. */
    void run_send();
    void run_receive();

    /* Transmits the drawing passed in using the transmit_number function. */
    void transmit_drawing(DrawingType *drawing);
    /* Takes in an integer and sends it over the wire. */
    void transmit_number(int num);
};

#endif