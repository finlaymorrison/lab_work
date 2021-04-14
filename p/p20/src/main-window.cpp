/*
 * File: main-window.cpp
 * File Created: Thursday, 18th March 2021 3:52:07 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 3:57:05 pm
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com>)
 * -----
 * Copyright (CC BY-SA) - 2021 Finlay Morrison
 */

#include "include/main-window.h"
#include "include/canvas.h"

#include <QApplication>
#include <QPixmap>
#include <QAction>
#include <QIcon>

MainWindow::MainWindow(int width, int height, QString title)
{
    // Setting up window.
    resize(width,height);
    setWindowTitle(title);

    // creating canvas.
    canvas = new Canvas(this);

    // Setting up GUI.
    menuBar()->addMenu("File");
    menuBar()->addMenu("Edit");
    menuBar()->addMenu("Brush");

    // Displaying canvas.
    setCentralWidget(canvas);
}