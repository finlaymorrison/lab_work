/*
 * Project: includes
 * File: includes/window.h
 * -----
 * File Created: Wednesday, 17th March 2021 11:00:42 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:33:18 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef SUDOKU_SRC_INCLUDES_WINDOW_H
#define SUDOKU_SRC_INCLUDES_WINDOW_H

#include <QMainWindow>
#include <QApplication>

#include "sudoku.h"

class window : public QMainWindow
{
    Q_OBJECT

private:
    sudoku_grid board;

public:
    window(QWidget *parent=nullptr);

    QToolBar *toolbar;

    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
};

#endif