/*
 * Project: src
 * File: src/drawing-type.cpp
 * -----
 * File Created: Wednesday, 28th April 2021 2:15:59 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "include/drawing-type.h"

#include <QPainter>
#include <QPen>

#include <cmath>

DrawingType::DrawingType(QColor color, int line_width) :
    color(color), line_width(line_width)
{}

RandomLine::RandomLine(QColor color, int line_width) :
    DrawingType(color, line_width)
{}

Circle::Circle(QColor color, int line_width) :
    DrawingType(color, line_width), complete(false)
{}

Square::Square(QColor color, int line_width) :
    DrawingType(color, line_width)
{}

StraightLine::StraightLine(QColor color, int line_width) :
    DrawingType(color, line_width)
{}



DrawingTypes RandomLine::get_type()
{
    return DrawingTypes::RandomLine;
}

DrawingTypes Circle::get_type()
{
    return DrawingTypes::Circle;
}

DrawingTypes Square::get_type()
{
    return DrawingTypes::Square;
}

DrawingTypes StraightLine::get_type()
{
    return DrawingTypes::StraightLine;
}



void RandomLine::draw(QPixmap &img)
{
    QPainter pixmap_painter(&img);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(line_width);
    pixmap_painter.setPen(pen);

    for (int i = 1; i < points.size(); ++i)
    {
        pixmap_painter.drawLine(points[i-1], points[i]);
    }
}

void RandomLine::mouseDown(QMouseEvent *event)
{
    points.push_back(event->pos());
}

void RandomLine::mouseMove(QMouseEvent *event)
{
    points.push_back(event->pos());
}

void RandomLine::mouseUp(QMouseEvent *event)
{
    points.push_back(event->pos());
}




void Circle::draw(QPixmap &img)
{
    QPainter pixmap_painter(&img);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(line_width);
    pixmap_painter.setPen(pen);

    pixmap_painter.drawEllipse(center, radius, radius);

    if (!complete)
    {
        pixmap_painter.drawLine(center, last_mouse_pos);
    }
}

void Circle::mouseDown(QMouseEvent *event)
{
    center = event->pos();

    last_mouse_pos = event->pos();
}

void Circle::mouseMove(QMouseEvent *event)
{
    QPoint radius_vector = event->pos() - center;
    radius = std::sqrt(std::pow(radius_vector.x(), 2) + std::pow(radius_vector.y(), 2));

    last_mouse_pos = event->pos();
}

void Circle::mouseUp(QMouseEvent *event)
{
    QPoint radius_vector = event->pos() - center;
    radius = std::sqrt(std::pow(radius_vector.x(), 2) + std::pow(radius_vector.y(), 2));

    complete = true;
}





void Square::draw(QPixmap &img)
{
    QPainter pixmap_painter(&img);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(line_width);
    pixmap_painter.setPen(pen);

    pixmap_painter.drawRect(tl.x(), tl.y(), br.x() - tl.x(), br.y() - tl.y());
}

void Square::mouseDown(QMouseEvent *event)
{
    br = tl = event->pos();
}

void Square::mouseMove(QMouseEvent *event)
{
    br = event->pos();
}

void Square::mouseUp(QMouseEvent *event)
{
    br = event->pos();
}




void StraightLine::draw(QPixmap &img)
{
    QPainter pixmap_painter(&img);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(line_width);
    pixmap_painter.setPen(pen);

    pixmap_painter.drawLine(start, finish);
}

void StraightLine::mouseDown(QMouseEvent *event)
{
    start = finish = event->pos();
}

void StraightLine::mouseMove(QMouseEvent *event)
{
    finish = event->pos();
}

void StraightLine::mouseUp(QMouseEvent *event)
{
    finish = event->pos();
}