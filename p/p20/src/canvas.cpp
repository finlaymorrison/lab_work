/*
 * Project: src
 * File: src/canvas.cpp
 * -----
 * File Created: Wednesday, 14th April 2021 2:42:20 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Wednesday, 14th April 2021 2:51:17 pm
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "include/canvas.h"

#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QBrush>

Canvas::Canvas(QMainWindow* parent) :
    parent(parent), drawing(false)
{
    repaint();
}

void Canvas::mousePressEvent(QMouseEvent *event) 
{
    drawing = true;
    points.push_back({});
    points.back().push_back({event->x(), event->y()});
}

void Canvas::mouseMoveEvent(QMouseEvent *event) 
{
    if (drawing)
    {
        points.back().push_back({event->x(), event->y()});

        repaint();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) 
{
    Q_UNUSED(event);

    drawing = false;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::white);
    QPainter pixmap_painter(&pixmap);
    QPen pen;
    pen.setColor(Qt::black);

    for (const QVector<QPoint>& line : points)
    {
        for (int i = 1; i < line.size(); ++i)
        {
            pixmap_painter.drawLine(line[i-1], line[i]);
        }
    }

    QPainter painter(this);
    painter.drawPixmap(0,0, pixmap);
}