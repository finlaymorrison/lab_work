/*
 * Project: src
 * File: src/canvas.cpp
 * -----
 * File Created: Wednesday, 14th April 2021 2:42:20 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "include/canvas.h"

#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QBrush>

Canvas::Canvas(bool enable_drawing, QWidget* parent) :
    parent(parent), drawing_type(DrawingTypes::RandomLine), line_width(1), enable_drawing(enable_drawing), drawing(false)
{
    repaint();
}

void Canvas::set_randomline_drawing()
{
    drawing_type = DrawingTypes::RandomLine;
}

void Canvas::set_circle_drawing()
{
    drawing_type = DrawingTypes::Circle;
}

void Canvas::set_square_drawing()
{
    drawing_type = DrawingTypes::Square;
}

void Canvas::set_straightline_drawing()
{
    drawing_type = DrawingTypes::StraightLine;
}

void Canvas::mousePressEvent(QMouseEvent *event) 
{
    if (!enable_drawing)
    {
        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        drawing = true;

        switch (drawing_type)
        {
        case DrawingTypes::None:
            break;
        case DrawingTypes::RandomLine:
            drawings.push_back(new RandomLine(color, line_width));
            break;
        case DrawingTypes::Circle:
            drawings.push_back(new Circle(color, line_width));
            break;
        case DrawingTypes::Square:
            drawings.push_back(new Square(color, line_width));
            break;
        case DrawingTypes::StraightLine:
            drawings.push_back(new StraightLine(color, line_width));
            break;
        }

        drawings.back()->mouseDown(event);

        repaint();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) 
{
    if (!enable_drawing)
    {
        return;
    }

    if (event->buttons() & Qt::LeftButton)
    {
        drawings.back()->mouseMove(event);

        repaint();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) 
{
    if (!enable_drawing)
    {
        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        drawings.back()->mouseUp(event);

        repaint();

        drawing = false;
    }
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::white);

    for (DrawingType *drawing : drawings)
    {
        drawing->draw(pixmap);
    }

    QPainter painter(this);
    painter.drawPixmap(0,0, pixmap);
}

void Canvas::set_color(QColor new_color)
{
    color = new_color;
}

void Canvas::set_width(int new_width)
{
    line_width = new_width;
}

void Canvas::add_drawing(DrawingType* drawing)
{
    drawings.push_back(drawing);
    repaint();
}

bool Canvas::is_drawing()
{
    return drawing;
}