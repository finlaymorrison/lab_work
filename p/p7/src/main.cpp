/*
 * Project: src
 * File: src/main.cpp
 * -----
 * File Created: Wednesday, 17th March 2021 10:50:03 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:33:07 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "includes/window.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  window win;

  win.resize(800, 800);
  win.setWindowTitle("Sudoku");
  win.show();

  return app.exec();
}