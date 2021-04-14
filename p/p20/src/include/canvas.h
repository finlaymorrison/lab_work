/*
 * Project: include
 * File: include/canvas.h
 * -----
 * File Created: Wednesday, 14th April 2021 2:42:09 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Wednesday, 14th April 2021 2:51:14 pm
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
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

class Canvas : public QWidget
{
    Q_OBJECT

private:
    QMainWindow* parent;

    QList<QVector<QPoint>> points;

    bool drawing;

public:
    Canvas(QMainWindow *parent);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

};

#endif