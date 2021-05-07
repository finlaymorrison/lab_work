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
#include "include/brush-menu.h"
#include "include/wire.h"
#include "include/wire-manager.h"

#include <QApplication>
#include <QPixmap>
#include <QAction>
#include <QIcon>
#include <QHBoxLayout>
#include <QFrame>
#include <QThread>

MainWindow::MainWindow(WindowType window_type, Wire *wire, int width, int height, QString title) :
    window_type(window_type)
{
    /* Setting up window. */
    resize(width,height);
    setWindowTitle(title);

    /* Setting up UI layout. */
    QFrame *frame = new QFrame(this);
    QHBoxLayout *hbox = new QHBoxLayout(frame);
    canvas = new Canvas(window_type == WindowType::Send, frame);
    brush_menu = new BrushMenu(frame, canvas);
    hbox->addWidget(brush_menu, 0);
    hbox->addWidget(canvas, 1);

    /* Creating a wire manager object to control the communication with the corresponding window. */
    WireManager *wire_manager = new WireManager(wire, canvas, window_type);
    wire_manager->start();

    /* Setting up toolbar. */
    file_toolbar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, file_toolbar);
    file_toolbar->setAllowedAreas(Qt::TopToolBarArea);
    file_toolbar->setMovable(false);

    /* Adding toolbar icon. */
    QPixmap exit_pixmap("img/close-icon.png");
    QAction* exit_action = file_toolbar->addAction(QIcon(exit_pixmap), "exit");
    connect(exit_action, &QAction::triggered, qApp, &QApplication::quit);

    /* Displaying UI. */
    setCentralWidget(frame);
}