/*
 * Project: src
 * File: src/main.cpp
 * -----
 * File Created: Wednesday, 14th April 2021 2:38:35 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "include/main-window.h"

#include <QApplication>
#include "include/wire.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Wire wire{false, false};

    MainWindow send_window(WindowType::Send, &wire, 800, 800, "Send Window");
    MainWindow receive_window(WindowType::Receive, &wire, 800, 800, "Receive Window");
    send_window.show();
    receive_window.show();

    return app.exec();
}