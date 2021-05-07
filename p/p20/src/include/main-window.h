/*
 * Project: include
 * File: include/main-window.h
 * -----
 * File Created: Wednesday, 14th April 2021 2:38:35 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef SRC_INCLUDE_MAINWINDOW_H
#define SRC_INCLUDE_MAINWINDOW_H

#include "canvas.h"
#include "brush-menu.h"
#include "wire.h"

#include <QMainWindow>
#include <QWheelEvent>
#include <QToolBar>
#include <QString>
#include <QMenuBar>
#include <QMenu>

/* Used to differentiate between wether a window will send or receive. */
enum class WindowType
{
    Send=0,
    Receive=1
};

/* An entire instance of a send or receive window */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /* Top toolbar, quit, TODO: new, open, load. */
    QToolBar *file_toolbar;
    /* Displays and stores the current drawings. */
    Canvas *canvas;
    /* Left menu for choosing drawing type and parameters. */
    BrushMenu *brush_menu;

    /* Send or receive window. */
    WindowType window_type;

public:
    MainWindow(WindowType window_type, Wire *wire, int width=800, int height=800, QString title="Unnamed Window");

};

#endif