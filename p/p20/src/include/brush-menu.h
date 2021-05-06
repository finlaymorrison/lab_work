/*
 * Project: include
 * File: include/brush-menu.h
 * -----
 * File Created: Wednesday, 28th April 2021 12:32:42 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef SRC_INCLUDE_BRUSHMENU_H
#define SRC_INCLUDE_BRUSHMENU_H

#include "canvas.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class BrushMenu : public QWidget
{
    Q_OBJECT

private:
    QWidget *parent;
    Canvas *canvas;
    
    QPushButton *color;
    QLineEdit *width_input;

private slots:
    void color_pick();
    void width_changed();

private:
    void add_separator(QVBoxLayout *vbox);
    void setup_drawing_types(QVBoxLayout *vbox);
    void setup_colors(QVBoxLayout *vbox);
    void setup_thickness(QVBoxLayout *vbox);

public:
    BrushMenu(QWidget *parent, Canvas *canvas);
};

#endif