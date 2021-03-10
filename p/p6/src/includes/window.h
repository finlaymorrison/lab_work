#ifndef WINDOW_H
#define WINDOW_H

#include "src/includes/sudoku.h"

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <map>

class Window : public QWidget
{
    Q_OBJECT

private:
    sudoku_grid* grid;
    sudoku_grid_viewer viewer;
    sudoku_grid_controller controller;

public:
    Window(QWidget *parent=nullptr);

    void set_grid(sudoku_grid* new_grid);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;

    std::pair<int, int> cell_pos(int x_pixel, int y_pixel);

};

#endif
