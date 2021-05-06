/*
 * Project: include
 * File: include/drawing-type.h
 * -----
 * File Created: Wednesday, 28th April 2021 2:14:17 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef SRC_INCLUDE_DRAWINGTYPE_H
#define SRC_INCLUDE_DRAWINGTYPE_H

#include <QPixmap>
#include <QVector>
#include <QMouseEvent>
#include <QColor>

enum class DrawingTypes
{
    RandomLine = 0,
    Circle = 1,
    Square = 2,
    StraightLine = 3
};

class DrawingType
{
protected:
    QColor color;
    int line_width;

public:
    DrawingType(QColor color, int line_width);

    virtual void draw(QPixmap &img) = 0;
    virtual void mouseDown(QMouseEvent *event) = 0;
    virtual void mouseMove(QMouseEvent *event) = 0;
    virtual void mouseUp(QMouseEvent *event) = 0;

    virtual DrawingTypes get_type() = 0;
};

class RandomLine : public DrawingType
{
private:
    QVector<QPoint> points;

public:
    RandomLine(QColor color, int line_width);

    void draw(QPixmap &img) override;
    void mouseDown(QMouseEvent *event) override;
    void mouseMove(QMouseEvent *event) override;
    void mouseUp(QMouseEvent *event) override;

    DrawingTypes get_type() override;
};

class Circle : public DrawingType
{
private:
    QPoint center;
    int radius;

    QPoint last_mouse_pos;

    bool complete;

public:
    Circle(QColor color, int line_width);

    void draw(QPixmap &img) override;
    void mouseDown(QMouseEvent *event) override;
    void mouseMove(QMouseEvent *event) override;
    void mouseUp(QMouseEvent *event) override;

    DrawingTypes get_type() override;
};

class Square : public DrawingType
{
private:
    QPoint tl, br;

public:
    Square(QColor color, int line_width);

    void draw(QPixmap &img) override;
    void mouseDown(QMouseEvent *event) override;
    void mouseMove(QMouseEvent *event) override;
    void mouseUp(QMouseEvent *event) override;

    DrawingTypes get_type() override;
};

class StraightLine : public DrawingType
{
private:
    QPoint start, finish;

public:
    StraightLine(QColor color, int line_width);

    void draw(QPixmap &img) override;
    void mouseDown(QMouseEvent *event) override;
    void mouseMove(QMouseEvent *event) override;
    void mouseUp(QMouseEvent *event) override;

    DrawingTypes get_type() override;
};

#endif