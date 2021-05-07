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

/* Time threads sleep through each loop */
#define SLEEP_TIME 0.001f

/* Utility function to convert an integer into a QVector<bool> binary representation. */
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

/* Utility function to convert a QVector<bool> binary representation into an interger. */
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

/* Start the thread. */
void WireManager::run()
{
    /* Chooses between the two modes of operation. */
    if (window_type == WindowType::Send)
    {
        run_send();
    }
    else if (window_type == WindowType::Receive)
    {
        run_receive();
    }
}

/* Infinite loop to check for data in the local canvas and send it over the wire. */
void WireManager::run_send()
{
    int drawing_count = 0;

    /* Infinite loop */
    forever
    {
        /* Sleeping so that the thread is not destroyed */
        sleep(SLEEP_TIME);

        /* Checking for a new completed drawing on the canvas. */
        if (canvas->drawings.length() > drawing_count && !canvas->is_drawing())
        {
            /* Transmitting a newly created drawing */
            transmit_drawing(canvas->drawings[drawing_count++]);
        }
    }
}

/* Infinite loop to check for data on the wire and interpret it into drawings to put on the local canvas. */
void WireManager::run_receive()
{
    /* Stores the previous transmissions so the bits can be converted into a single integer. */
    QVector<bool> curr_num;

    /* Infinite loop. */
    forever
    {
        /* Sleeping so that the thread is not destroyed. */
        sleep(SLEEP_TIME);

        /* If dirty bit is set, then there is data to read. */
        if (wire->dirty)
        {
            /* Reading data from to wire and unsetting the dirty bit to indicate that the wire is free for more data. */
            curr_num.push_back(wire->data);
            wire->dirty = false;
            
            /* Checking if 32 bits have been collected on the wire */
            if (curr_num.size() >= 32)
            {
                /* Getting the integer representation of the bits and passing them into the interpreter. */
                int num = binary_to_int(curr_num);
                interpreter.input_num(num);

                /* Clearing the bits for the next transmission. */
                curr_num.clear();
            }
        }
    }
}

/* Infinite loop to check for an addition to the local canvas to then sending that addition over the wire. */
void WireManager::transmit_drawing(DrawingType *drawing)
{
    /* Getting the drawing type so the correct encoding scheme may be used. */
    DrawingTypes drawing_type = drawing->get_type();

    /* Stores the numerical representation of the drawing. */
    QVector<int> buffer;

    /* Encodes the drawing into the buffer. */
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

    /* Looping through numerical representation of the drawing and transmitting it over the wire. */
    for (int i = 0; i < buffer.size(); ++i)
    {
        transmit_number(buffer[i]);
    }
}

/* Takes an integer and converts it into bits and sends it down the wire. */
void WireManager::transmit_number(int num)
{
    /* Getting the binary representation of the number to transmit. */
    QVector<bool> binary = int_to_binary(num);

    /* Looping through the bits in the binary representation. */
    for (int i = 0; i < 32; ++i)
    {
        /* Wait untill the wire is free. */
        while (wire->dirty)
        {
            sleep(SLEEP_TIME);
        }

        /* Putting the data on the wire and setting the dirty bit. */
        wire->data = binary[i];
        wire->dirty = true;
    }
}