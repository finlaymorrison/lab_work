/*
 * Project: src
 * File: src/brush-menu.cpp
 * -----
 * File Created: Wednesday, 28th April 2021 12:32:49 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "include/brush-menu.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QFrame>
#include <QString>
#include <QIcon>
#include <QColorDialog>
#include <QLineEdit>
#include <QIntValidator>
#include <QLabel>

BrushMenu::BrushMenu(QWidget* parent, Canvas *canvas) :
    parent(parent), canvas(canvas)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    setup_drawing_types(vbox);
    add_separator(vbox);
    setup_colors(vbox);
    add_separator(vbox);
    setup_thickness(vbox);

    vbox->addStretch(1);

    setLayout(vbox);
}

void BrushMenu::add_separator(QVBoxLayout *vbox)
{
    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vbox->addWidget(line);
}

void BrushMenu::setup_drawing_types(QVBoxLayout *vbox)
{
    QGridLayout *drawing_type_menu = new QGridLayout;

    QPixmap randomline_pix("img/random-line-icon.png");
    QPushButton *randomline_button = new QPushButton;
    randomline_button->setIcon(QIcon(randomline_pix));
    drawing_type_menu->addWidget(randomline_button, 0, 0);
    connect(randomline_button, &QPushButton::pressed, canvas, &Canvas::set_randomline_drawing);


    QPixmap circle_pix("img/circle-icon.png");
    QPushButton *circle_button = new QPushButton;
    circle_button->setIcon(QIcon(circle_pix));
    drawing_type_menu->addWidget(circle_button, 0, 1);
    connect(circle_button, &QPushButton::pressed, canvas, &Canvas::set_circle_drawing);

    QPixmap square_pix("img/square-icon.png");
    QPushButton *square_button = new QPushButton;
    square_button->setIcon(QIcon(square_pix));
    drawing_type_menu->addWidget(square_button, 0, 2);
    connect(square_button, &QPushButton::pressed, canvas, &Canvas::set_square_drawing);

    QPixmap straightline_pix("img/straight-line-icon.png");
    QPushButton *straightline_button = new QPushButton;
    straightline_button->setIcon(QIcon(straightline_pix));
    drawing_type_menu->addWidget(straightline_button, 0, 3);
    connect(straightline_button, &QPushButton::pressed, canvas, &Canvas::set_straightline_drawing);

    vbox->addLayout(drawing_type_menu);
}

void BrushMenu::setup_colors(QVBoxLayout *vbox)
{
    color = new QPushButton;
    connect(color, &QPushButton::pressed, this, &BrushMenu::color_pick);
    color->setStyleSheet("background-color: rgb(0,0,0)");
    vbox->addWidget(color);
}

void BrushMenu::setup_thickness(QVBoxLayout *vbox)
{
    QHBoxLayout *width_layout = new QHBoxLayout;

    QLabel *width_title = new QLabel;
    width_title->setText(QString("Width:"));
    width_layout->addWidget(width_title, 0);

    width_input = new QLineEdit;
    width_input->setValidator(new QIntValidator(1,50));
    width_input->setText(QString("1"));
    connect(width_input, &QLineEdit::textChanged, this, &BrushMenu::width_changed);
    width_layout->addWidget(width_input, 1);

    vbox->addLayout(width_layout);
}

void BrushMenu::color_pick()
{
    QColor selected_color = QColorDialog::getColor();
    QString style = "background-color: rgb(%1,%2,%3)";
    color->setStyleSheet(style.arg(selected_color.red()).arg(selected_color.green()).arg(selected_color.blue()));

    canvas->set_color(selected_color);
}

void BrushMenu::width_changed()
{
    int width = width_input->text().toInt();
    canvas->set_width(width);
}