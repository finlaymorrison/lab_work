/*
 * Project: src
 * File: src/sudoku.cpp
 * -----
 * File Created: Wednesday, 10th March 2021 10:07:30 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:32:32 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "src/includes/sudoku.h"

bool sudoku_grid::possible_placement(int y, int x, int num) const
{
    for (int pos = 0; pos < board_size; ++pos)
    {
        if (grid[pos][x] == num || grid[y][pos] == num)
        {
            return false;
        }
    }
    int x_0 = grid_size * (x / grid_size);
    int y_0 = grid_size * (y / grid_size);
    for (int i = y_0; i < y_0 + grid_size; ++i)
    {
        for (int j = x_0; j < x_0 + grid_size; ++j)
        {
            if (grid[i][j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool sudoku_grid::solve()
{
    int s_i=-1, s_j=-1;
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            if (grid[i][j] == 0)
            {
                s_i = i; 
                s_j = j;
                goto exit; /* the only clean way to break out a doubly-nested for loop efficiently */
            }
        }
    }
    return true;
exit:

    for (int num = 1; num <= board_size; ++num)
    {
        if (possible_placement(s_i, s_j, num))
        {
            grid[s_i][s_j] = num;
            if (solve())
            {
                return true;
            }
            grid[s_i][s_j] = 0;
        }
    }
    return false;
}

std::vector<std::vector<int>> load_sudoku(std::string filename)
{
    constexpr int GRID_SIZE = 3;
    constexpr int SUDOKU_SIZE = GRID_SIZE * GRID_SIZE;

    std::vector<std::vector<int>> out(SUDOKU_SIZE, std::vector<int>(SUDOKU_SIZE));
    std::ifstream file(filename);
    char c;
    for (int i = 0; i < SUDOKU_SIZE; ++i)
    {
        for (int j = 0; j < SUDOKU_SIZE; ++j)
        {
            file >> c;
            if (c == 'X')
            {
                out[i][j] = 0;
            }
            else
            {
                out[i][j] = c - '0';
            }
        }
    }
    return out;
}

void sudoku_grid::inc_cell(int i, int j)
{
    grid[i][j]++;
    if (grid[i][j] > 9)
    {
        grid[i][j] = 0;
    }
}

sudoku_grid::sudoku_grid(int grid_size) :
    grid_size(grid_size),
    board_size(grid_size * grid_size),
    grid(grid_size * grid_size, std::vector<int>(grid_size * grid_size))
{}

sudoku_grid::sudoku_grid(const std::vector<std::vector<int>>& grid) :
    grid_size(std::sqrt(grid.size())),
    board_size(grid.size()),
    grid(grid)
{}

sudoku_grid::sudoku_grid(const sudoku_grid& s_grid) :
    grid_size(s_grid.grid_size), 
    board_size(s_grid.board_size),
    grid(s_grid.grid)
{}

sudoku_grid& sudoku_grid::operator= (const sudoku_grid& s_grid)
{
    grid_size = s_grid.grid_size;
    board_size = s_grid.board_size;
    grid = s_grid.grid;
    return *this;
}

sudoku_grid::sudoku_grid(const sudoku_grid&& s_grid) noexcept:
    grid_size(s_grid.grid_size), 
    board_size(s_grid.board_size),
    grid(std::move(s_grid.grid))
{}

sudoku_grid& sudoku_grid::operator= (const sudoku_grid&& s_grid) noexcept
{
    grid_size = s_grid.grid_size;
    board_size = s_grid.board_size;
    grid = std::move(s_grid.grid);
    return *this;
}

sudoku_grid_viewer::sudoku_grid_viewer(sudoku_grid* grid) : grid(grid) {}

void sudoku_grid_viewer::display_grid(QPainter* painter, int border_width, int subgrid_width, int window_width, int window_height)
{
    constexpr int h_padding = 50;
    constexpr int v_padding = 50;

    const int board_height=window_height - v_padding * 2, board_width=window_width - h_padding * 2;

    const float h_spacing = (window_width - 2 * h_padding) / static_cast<float>(grid->get_board_size());
    const float v_spacing = (window_height - 2 * v_padding) / static_cast<float>(grid->get_board_size());

    QPen border_pen;
    QPen subgrid_pen;
    border_pen.setWidth(border_width);
    subgrid_pen.setWidth(subgrid_width);

    painter->setPen(subgrid_pen);
    for(int i = 0; i < 10; ++i)
    {
        QPoint ah(h_padding + (i * h_spacing), v_padding), bh(h_padding + (i * h_spacing), window_height - v_padding);
        painter->drawLine(ah, bh);

        QPoint av(h_padding, v_padding + (i * v_spacing)), bv(window_width - h_padding, v_padding + (i * v_spacing));
        painter->drawLine(av, bv);
    }

    painter->setPen(border_pen);
    for(int i = 0; i < 4; ++i)
    {
        QPoint ah(h_padding + (i * 3 * h_spacing), v_padding), bh( h_padding + (i * 3 * h_spacing), window_height - v_padding);
        painter->drawLine(ah, bh);

        QPoint av(h_padding, v_padding + (i * 3 * v_spacing)), bv(window_width - h_padding, v_padding + (i * 3 * v_spacing));
        painter->drawLine(av, bv);
    }

    std::vector<std::vector<int>> board = grid->get_grid();

    QFont font;
    font.setPointSizeF(0.7);
    float factor = std::min(h_spacing, v_spacing) / QFontMetrics(font).width("m");
    font.setPointSizeF(font.pointSizeF() * factor);
    painter->setFont(font);

    for (int i = 0; i < 9; ++i)
    {
        const int x = h_padding + (i * h_spacing);
        for (int j = 0; j < 9; ++j)
        {
            const int y = v_padding + (j * v_spacing);
            if (board[i][j])
            {
                QRect cell_bounds(x, y, h_spacing, v_spacing);
                painter->drawText(cell_bounds, Qt::AlignCenter, std::to_string(board[i][j]).c_str());
            }
        }
    }
}

sudoku_grid_controller::sudoku_grid_controller(sudoku_grid* grid) : grid(grid) {}

std::pair<int, int> sudoku_grid_controller::cell_pos(int x_pixel, int y_pixel, int window_height, int window_width)
{
    constexpr int h_padding = 50;
    constexpr int v_padding = 50;

    const int board_height=window_height - v_padding * 2, board_width=window_width - h_padding * 2;

    const float h_spacing = (window_width - 2 * h_padding) / static_cast<float>(grid->get_board_size());
    const float v_spacing = (window_height - 2 * v_padding) / static_cast<float>(grid->get_board_size());

    x_pixel -= h_padding;
    y_pixel -= v_padding;

    if (x_pixel > 0 && y_pixel > 0 && x_pixel < board_width && y_pixel < board_height)
    {
        return {x_pixel / h_spacing, y_pixel / v_spacing};
    }
    else
    {
        return {-1, -1};
    }
}

void sudoku_grid_controller::manage_grid_click(int x_pixel, int y_pixel, int window_height, int window_width)
{
    std::pair<int, int> clicked_cell = cell_pos(x_pixel, y_pixel, window_height, window_width);
    grid->inc_cell(clicked_cell.first, clicked_cell.second);
}