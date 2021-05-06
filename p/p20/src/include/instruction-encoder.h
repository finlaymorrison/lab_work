/*
 * Project: include
 * File: include/instruction-encoder.h
 * -----
 * File Created: Thursday, 6th May 2021 8:57:03 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef INCLUDE_INSTRUCTIONENCODER_H
#define INCLUDE_INSTRUCTIONENCODER_H

#include "drawing-type.h"

#include <QVector>
#include <QDebug>

class InstructionEncoder
{
public:
    static QVector<int> EncodeRandomLine(RandomLine *drawing)
    {
        QVector<int> buffer;
        buffer.push_back(static_cast<int>(DrawingTypes::RandomLine));

        QColor drawing_color = drawing->get_color();
        buffer.push_back(drawing_color.red());
        buffer.push_back(drawing_color.green());
        buffer.push_back(drawing_color.blue());

        buffer.push_back(drawing->get_width());

        QVector<QPoint> points = drawing->get_points();

        buffer.push_back(points.size());

        for (int i = 0; i < points.size(); ++i)
        {
            buffer.push_back(points[i].x());
            buffer.push_back(points[i].y());
        }

        return buffer;
    }

    static QVector<int> EncodeCircle(Circle *drawing)
    {
        QVector<int> buffer;
        buffer.push_back(static_cast<int>(DrawingTypes::Circle));

        QColor drawing_color = drawing->get_color();
        buffer.push_back(drawing_color.red());
        buffer.push_back(drawing_color.green());
        buffer.push_back(drawing_color.blue());

        buffer.push_back(drawing->get_width());

        buffer.push_back(drawing->get_center().x());
        buffer.push_back(drawing->get_center().y());
        buffer.push_back(drawing->get_radius());

        return buffer;
    }

    static QVector<int> EncodeSquare(Square *drawing)
    {
        QVector<int> buffer;
        buffer.push_back(static_cast<int>(DrawingTypes::Square));

        QColor drawing_color = drawing->get_color();
        buffer.push_back(drawing_color.red());
        buffer.push_back(drawing_color.green());
        buffer.push_back(drawing_color.blue());

        buffer.push_back(drawing->get_width());

        buffer.push_back(drawing->get_tl().x());
        buffer.push_back(drawing->get_tl().y());

        buffer.push_back(drawing->get_br().x());
        buffer.push_back(drawing->get_br().y());

        return buffer;
    }

    static QVector<int> EncodeStraightLine(StraightLine *drawing)
    {
        QVector<int> buffer;
        buffer.push_back(static_cast<int>(DrawingTypes::StraightLine));

        QColor drawing_color = drawing->get_color();
        buffer.push_back(drawing_color.red());
        buffer.push_back(drawing_color.green());
        buffer.push_back(drawing_color.blue());

        buffer.push_back(drawing->get_width());

        buffer.push_back(drawing->get_start().x());
        buffer.push_back(drawing->get_start().y());

        buffer.push_back(drawing->get_finish().x());
        buffer.push_back(drawing->get_finish().y());

        return buffer;
    }
};

#endif