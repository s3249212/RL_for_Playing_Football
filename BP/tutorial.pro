#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T12:24:37
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tutorial
TEMPLATE = app


SOURCES += main.cpp \
    bullet.cpp \
    enemy.cpp \
    game.cpp \
    player.cpp \
    score.cpp \
    health.cpp \
    View/Gridworld/gridworldview.cpp \
    World/Gridworld/gridworld.cpp \
    mainwindow.cpp \
    View/view.cpp \
    View/Gridworld/agent.cpp \
    View/Gridworld/ball.cpp \
    View/Gridworld/goal.cpp \

HEADERS  += \
    bullet.h \
    enemy.h \
    game.h \
    player.h \
    score.h \
    health.h \
    View/Gridworld/gridworldview.h \
    World/Gridworld/gridworld.h \
    World/world.h \
    mainwindow.h \
    View/view.h \
    View/Gridworld/agent.h \
    View/Gridworld/ball.h \
    View/Gridworld/goal.h \

FORMS    += \
    mainwindow.ui

RESOURCES += \
    res.qrc

CONFIG += c++11
