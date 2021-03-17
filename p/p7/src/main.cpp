#include "includes/window.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  window win;

  win.resize(800, 800);
  win.setWindowTitle("Sudoku");
  win.show();

  return app.exec();
}