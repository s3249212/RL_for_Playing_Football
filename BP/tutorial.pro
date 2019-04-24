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
    score.cpp \
    health.cpp \
    View/Gridworld/gridworldview.cpp \
    World/Gridworld/gridworld.cpp \
    mainwindow.cpp \
    View/view.cpp \
    World/world.cpp \
    View/Gridworld/gridworldview_agent.cpp \
    View/Gridworld/gridworldview_ball.cpp \
    World/Gridworld/gridworld_agent.cpp \
    World/Gridworld/gridworld_ball.cpp \
    Player/player.cpp \
    World/Gridworld/gridworld_event.cpp \
    Player/randomplayer.cpp \
    World/Gridworld/gridworld_score.cpp \
    View/Gridworld/gridworldview_score.cpp \
    Interaction_Handler/Gridworld/gridworld_ih.cpp \
    Interaction_Handler/Gridworld/ih_oneagentperplayer.cpp \
    Interaction_Handler/interactionhandler.cpp \
    Player/tabularq.cpp

HEADERS  += \
    bullet.h \
    enemy.h \
    score.h \
    health.h \
    View/Gridworld/gridworldview.h \
    World/Gridworld/gridworld.h \
    World/world.h \
    mainwindow.h \
    View/view.h \
    View/Gridworld/gridworldview_agent.h \
    View/Gridworld/gridworldview_ball.h \
    World/Gridworld/gridworld_agent.h \
    World/Gridworld/gridworld_ball.h \
    World/Gridworld/interactionhandler.h \
    World/Gridworld/ih_oneagentperplayer.h \
    Player/player.h \
    World/Gridworld/gridworld_event.h \
    World/Gridworld/gridworld_ih.h \
    Player/randomplayer.h \
    World/Gridworld/gridworld_score.h \
    View/Gridworld/gridworldview_score.h \
    Interaction_Handler/Gridworld/gridworld_ih.h \
    Interaction_Handler/Gridworld/ih_oneagentperplayer.h \
    Interaction_Handler/interactionhandler.h \
    Player/tabularq.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    res.qrc

CONFIG += c++11

DISTFILES += \
    tutorial.pro.user.ad5f1f3.4.8-pre1
