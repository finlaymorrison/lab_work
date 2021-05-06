/*
 * Project: include
 * File: include/canvas.h
 * -----
 * File Created: Wednesday, 14th April 2021 2:42:09 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef SRC_INCLUDE_CANVAS_H
#define SRC_INCLUDE_CANVAS_H

#include <QWidget>
#include <QMainWindow>
#include <QPixmap>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QList>
#include <QPoint>
#include <QVector>

#include "drawing-type.h"

class Canvas : public QWidget
{
    Q_OBJECT

private:
    QWidget* parent;

    DrawingTypes drawing_type;
    QBrush brush;
    int line_width;

    QColor color;

    bool enable_drawing;

public:
    QList<DrawingType*> drawings;

public slots:
    void set_randomline_drawing();
    void set_circle_drawing();
    void set_square_drawing();
    void set_straightline_drawing();

public:
    Canvas(bool enable_drawing, QWidget *parent);

    void set_color(QColor new_color);
    void set_width(int new_width);

    void add_drawing(DrawingType* drawing);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

};

#endif