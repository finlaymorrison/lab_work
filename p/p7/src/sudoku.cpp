/*
 * Project: src
 * File: src/sudoku.cpp
 * -----
 * File Created: Wednesday, 17th March 2021 12:30:20 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:33:10 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "includes/sudoku.h"

#include <QGridLayout>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMainWindow>
#include <QStatusBar>

sudoku_grid::sudoku_grid(QMainWindow* parent, int grid_size) :
    grid_size(grid_size),
    board_size(grid_size * grid_size),
    grid(grid_size * grid_size, std::vector<int>(grid_size * grid_size)),
    grid_edit(grid_size * grid_size, std::vector<QLineEdit*>(grid_size * grid_size)),
    parent(parent)
{
    constexpr int padding = 100;
    constexpr int spacing = 10;
    constexpr float font_scale = 0.8;

    const int board_pixel_size = std::min(parent->height(), parent->width()) - 2 * padding;
    const int input_pixel_size = (board_pixel_size - (board_size - 1) * spacing) / board_size;

    QGridLayout *sudoku_grid = new QGridLayout;
    sudoku_grid->setSpacing(spacing);

    QFont font;
    font.setPointSize(input_pixel_size * font_scale);

    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            grid_edit[i][j] = new QLineEdit(parent);
            grid_edit[i][j]->setMaxLength(1);
            grid_edit[i][j]->setBaseSize(input_pixel_size, input_pixel_size - spacing);
            grid_edit[i][j]->setFont(font);
            grid_edit[i][j]->setAlignment(Qt::AlignCenter);

            connect(grid_edit[i][j], &QLineEdit::textChanged, this, &sudoku_grid::value_edit);

            sudoku_grid->addWidget(grid_edit[i][j], i, j);
        }
    }

    QGridLayout *screen_grid = new QGridLayout;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (i == 1 && j == 1)
            {
                screen_grid->addLayout(sudoku_grid, i, j);
            }
            else
            {
                QFrame* frame = new QFrame;
                frame->setMaximumSize(padding, padding);
                screen_grid->addWidget(frame, i, j);
            }
        }
    }

    QWidget* widget = new QWidget();
    widget->setLayout(screen_grid);
    parent->setCentralWidget(widget);
}

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

void sudoku_grid::display_grid(QPainter* painter, int border_width, int subgrid_width, int window_width, int window_height)
{
    constexpr int padding = 100;
    constexpr int spacing = 10;
    constexpr float font_scale = 0.7;

    const int board_pixel_size = std::min(parent->height(), parent->width()) - 2 * padding;
    const int input_pixel_size = (board_pixel_size - (board_size - 1) * spacing) / board_size;

    QFont font;
    font.setPointSize(input_pixel_size * font_scale);

    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            grid_edit[i][j]->setFixedSize(input_pixel_size, input_pixel_size);
            grid_edit[i][j]->setFont(font);
        }
    }
}

std::pair<int, int> sudoku_grid::cell_pos(int x_pixel, int y_pixel, int window_height, int window_width)
{
    constexpr int h_padding = 50;
    constexpr int v_padding = 50;

    const int board_height=window_height - v_padding * 2, board_width=window_width - h_padding * 2;

    const float h_spacing = (window_width - 2 * h_padding) / static_cast<float>(board_size);
    const float v_spacing = (window_height - 2 * v_padding) / static_cast<float>(board_size);

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

void sudoku_grid::manage_grid_click(int x_pixel, int y_pixel, int window_height, int window_width)
{
    std::pair<int, int> clicked_cell = cell_pos(x_pixel, y_pixel, window_height, window_width);
    grid[clicked_cell.first][clicked_cell.second]++;
    if (grid[clicked_cell.first][clicked_cell.second] > 9)
    {
        grid[clicked_cell.first][clicked_cell.second] = 0;
    }
}

void sudoku_grid::load_grid(std::vector<std::vector<int>> nums)
{
    for (int i = 0; i < nums.size() && i < board_size; ++i)
    {
        for (int j = 0; j < nums[i].size() && j < board_size; ++j)
        {
            grid_edit[i][j]->setText(QString(nums[i][j] + '0'));
        }
    }
}

void sudoku_grid::new_sudoku()
{
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            grid_edit[i][j]->setText("");
        }
    }
}

void sudoku_grid::open_sudoku()
{
    QString filename = QInputDialog::getText(parent, "Open File", "Filename");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) 
    {
        qWarning("Cannot open file for reading");
    }
    QTextStream stream(&file);

    int line_count = 0;
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (line.size() != board_size)
        {
            qWarning("Line in file incorrect length");
        }
        else
        {
            for (int i = 0; i < board_size; ++i)
            {
                if (line[i] != 'X')
                {
                    grid_edit[line_count][i]->setText(QString(line[i]));
                }
                else
                {
                    grid_edit[line_count][i]->setText("");
                }
            }
        }
        ++line_count;
    }
    if (line_count != board_size)
    {
        qWarning("Incorrect line count in file");
    }

}

void sudoku_grid::save_sudoku()
{
    QString filename = QInputDialog::getText(parent, "Save File:", "Filename");

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) 
    {
        qWarning("Cannot open file for writing");
    }
    QTextStream stream(&file);

    for (int i = 0; i < board_size; ++i)
    {
        QString line;
        for (int j = 0; j < board_size; ++j)
        {
            if (grid_edit[i][j]->text() != "")
            {
                line.append(grid_edit[i][j]->text());
            }
            else
            {
                line.append("X");
            }
        }
        stream << line << '\n';
    }
}

void sudoku_grid::solve_sudoku()
{
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            grid[i][j] = grid_edit[i][j]->text().toInt();
        }
    }
    solve();
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            grid_edit[i][j]->setText(QString(grid[i][j] + '0'));
        }
    }
}

void sudoku_grid::value_edit()
{
    bool correct = true;
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            int tempnum = grid[i][j];
            grid[i][j] = 0;
            if (!possible_placement(i, j, grid_edit[i][j]->text().toInt()))
            {
                grid_edit[i][j]->setStyleSheet("Color: red;");
                correct = false;
            }
            else
            {
                grid_edit[i][j]->setStyleSheet("Color: black;");
            }
            grid[i][j] = tempnum;
        }
    }
    if (correct)
    {
        parent->statusBar()->showMessage("solved");
    }
    else
    {
        parent->statusBar()->clearMessage();
    }
}