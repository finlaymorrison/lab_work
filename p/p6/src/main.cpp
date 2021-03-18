/*
 * Project: src
 * File: src/main.cpp
 * -----
 * File Created: Tuesday, 9th March 2021 9:55:34 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:32:27 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "src/includes/window.h"
#include "src/includes/sudoku.h"

#include <QApplication>

int main(int argc, char *argv[])
{  
    QApplication app(argc, argv);
    Window window;

    window.show();

    std::vector<std::vector<int>> grid = load_sudoku("SUDOKU.txt");
    sudoku_grid* board = new sudoku_grid(grid);

    window.set_grid(board);

    board->solve();

    return app.exec();
}
