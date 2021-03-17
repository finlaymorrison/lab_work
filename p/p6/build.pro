TEMPLATE = app
TARGET = prog
INCLUDEPATH += . ../ ../

SOURCES +=  ../src/*.cpp

HEADERS +=  ../src/includes/*.h

CONFIG += CONSOLE silent

QT += widgets core gui