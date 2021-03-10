#include "src/includes/window.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include <map>
#include <vector>

void Window::set_grid(sudoku_grid* new_grid)
{
    grid = new_grid;
    viewer = sudoku_grid_viewer(grid);
    controller = sudoku_grid_controller(grid);
}

Window::Window(QWidget *parent) : QWidget(parent), viewer(grid)
{
   // set form size
   setBaseSize(900,900);
   setWindowTitle("Sudoku");
}

void Window::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    viewer.display_grid(&painter, 5, 2, width(), height());
}

void Window::mouseReleaseEvent(QMouseEvent *event) 
{
    controller.manage_grid_click(event->x(), event->y(), height(), width());

    repaint();
}
