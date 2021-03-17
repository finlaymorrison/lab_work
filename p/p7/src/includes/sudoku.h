#ifndef SUDOKU_SRC_INCLUDES_SUDOKU_H
#define SUDOKU_SRC_INCLUDES_SUDOKU_H

#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QLineEdit>
#include <QWidget>
#include <QMainWindow>
#include <QFont>
#include <QFrame>
#include <QSpinBox>

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <functional>
#include <algorithm>

std::vector<std::vector<int>> load_sudoku(std::string filename);

class sudoku_grid : public QWidget
{

    Q_OBJECT

private:
    int grid_size; /* size of the sub-grids */
    int board_size; /* size of the entire board */
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<QLineEdit*>> grid_edit;
    QMainWindow *parent;

    bool possible_placement(int y, int x, int num) const;

public slots:
    void new_sudoku();
    void save_sudoku();
    void open_sudoku();
    void solve_sudoku();
    void value_edit();

public:
    sudoku_grid(QMainWindow* parent, int grid_size=3);

    ~sudoku_grid() = default;

    void display_grid(QPainter* painter, int border_width, int subgrid_width, int window_width, int window_height);

    void load_grid(std::vector<std::vector<int>> nums);

    std::pair<int, int> cell_pos(int x_pixel, int y_pixel, int window_height, int window_width);
    void manage_grid_click(int x_pixel, int y_pixel, int window_height, int window_width);

    bool solve();

};

#endif