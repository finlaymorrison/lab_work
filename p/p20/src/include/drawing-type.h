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
    None = 0,
    RandomLine = 1,
    Circle = 2,
    Square = 3,
    StraightLine = 4
};

class DrawingType
{
protected:
    QColor color;
    int line_width;

public:
    DrawingType(QColor color, int line_width);

    QColor get_color();
    int get_width();
    void set_color(QColor new_color);
    void set_width(int new_width);

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

    void add_point(QPoint point);
    QVector<QPoint> get_points();

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

    QPoint get_center();
    int get_radius();

    void set_center(QPoint new_center);
    void set_radius(int new_radius);
    void set_complete(bool new_complete);

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

    void set_tl(QPoint new_tl);
    void set_br(QPoint new_br);
    QPoint get_tl();
    QPoint get_br();

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

    void set_start(QPoint new_start);
    void set_finish(QPoint new_finish);
    QPoint get_start();
    QPoint get_finish();

    void draw(QPixmap &img) override;
    void mouseDown(QMouseEvent *event) override;
    void mouseMove(QMouseEvent *event) override;
    void mouseUp(QMouseEvent *event) override;

    DrawingTypes get_type() override;
};

#endif