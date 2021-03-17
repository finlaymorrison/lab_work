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