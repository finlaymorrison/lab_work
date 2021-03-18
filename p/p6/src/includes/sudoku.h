/*
 * Project: includes
 * File: includes/sudoku.h
 * -----
 * File Created: Wednesday, 10th March 2021 10:07:24 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:32:43 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <QPainter>
#include <QPen>
#include <QPoint>

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <functional>

std::vector<std::vector<int>> load_sudoku(std::string filename);

class sudoku_grid
{
private:
    int grid_size; /* size of the sub-grids */
    int board_size; /* size of the entire board */
    std::vector<std::vector<int>> grid;
    bool possible_placement(int y, int x, int num) const;
    
public:
    sudoku_grid(int grid_size=3);
    sudoku_grid(const std::vector<std::vector<int>>& grid);

    sudoku_grid(const sudoku_grid& s_grid);
    sudoku_grid& operator= (const sudoku_grid& s_grid);
    sudoku_grid(const sudoku_grid&& s_grid) noexcept;
    sudoku_grid& operator= (const sudoku_grid&& s_grid) noexcept;

    ~sudoku_grid() = default;

    int get_grid_size() const {return grid_size;}
    int get_board_size() const {return board_size;}
    std::vector<std::vector<int>> get_grid() const {return grid;};

    void inc_cell(int i, int j);

    bool solve();

};

class sudoku_grid_viewer
{
private:
    sudoku_grid* grid;
public:
    sudoku_grid_viewer(sudoku_grid* grid=nullptr);

    void display_grid(QPainter* painter, int border_width, int subgrid_width, int window_width, int window_height);
};

class sudoku_grid_controller
{
private:
    sudoku_grid* grid;
public:
    sudoku_grid_controller(sudoku_grid* grid=nullptr);

    std::pair<int, int> cell_pos(int x_pixel, int y_pixel, int window_height, int window_width);

    void manage_grid_click(int x_pixel, int y_pixel, int window_height, int window_width);
};

#endif