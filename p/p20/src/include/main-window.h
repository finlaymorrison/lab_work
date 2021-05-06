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

enum class WindowType
{
    Send=0,
    Receive=1
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolBar *file_toolbar;
    Canvas *canvas;
    BrushMenu *brush_menu;

    WindowType window_type;

public:
    MainWindow(WindowType window_type, Wire *wire, int width=800, int height=800, QString title="Unnamed Window");

};

#endif