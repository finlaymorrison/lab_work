#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QInputDialog>

#include "includes/window.h"

window::window(QWidget *parent) :
    QMainWindow(parent), board(this, 3)
{
    // loading images for toolbar icons
    QPixmap new_pix("img/new.png");
    QPixmap open_pix("img/open.png");
    QPixmap save_pix("img/save.png");
    QPixmap solve_pix("img/wizard.png");
    QPixmap quit_pix("img/quit.png");

    // initializing toolbar
    toolbar = addToolBar("main toolbar");

    // setting up toolbar icons
    QAction *new_action = toolbar->addAction(QIcon(new_pix), "new file");
    QAction *open_action = toolbar->addAction(QIcon(open_pix), "open file");
    QAction *save_action = toolbar->addAction(QIcon(save_pix), "save file");
    toolbar->addSeparator();
    QAction *solve_action = toolbar->addAction(QIcon(solve_pix), "solve");
    toolbar->addSeparator();
    QAction *quit_action = toolbar->addAction(QIcon(quit_pix), "quit");

    // connecting signals to their corresponding slots
    connect(new_action, &QAction::triggered, &board, &sudoku_grid::new_sudoku);
    connect(open_action, &QAction::triggered, &board, &sudoku_grid::open_sudoku);
    connect(save_action, &QAction::triggered, &board, &sudoku_grid::save_sudoku);
    connect(solve_action, &QAction::triggered, &board, &sudoku_grid::solve_sudoku);
    connect(quit_action, &QAction::triggered, qApp, &QApplication::quit);
}

void window::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    board.display_grid(&painter, 5, 2, width(), height());
}

void window::mouseReleaseEvent(QMouseEvent *event) 
{
    //board.manage_grid_click(event->x(), event->y(), height(), width());

    //repaint();
}