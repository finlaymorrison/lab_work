TEMPLATE = app
TARGET = prog
INCLUDEPATH += . ../img ../src/includes

SOURCES +=  src/*.cpp

HEADERS +=  src/includes/*.h

CONFIG += CONSOLE silent

QT += core gui widgets