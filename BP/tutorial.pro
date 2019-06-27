#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T12:24:37
#
#-------------------------------------------------

QT       += core gui \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tutorial
TEMPLATE = app


SOURCES += main.cpp \
    World/world.cpp \
    World/Gridworld/gridworld.cpp \
    World/Gridworld/gridworld_agent.cpp \
    World/Gridworld/gridworld_ball.cpp \
    World/Gridworld/gridworld_event.cpp \
    World/Gridworld/gridworld_getset.cpp \
    View/view.cpp \
    View/Gridworld/gridworldview.cpp \
    View/Gridworld/gridworldview_agent.cpp \
    View/Gridworld/gridworldview_ball.cpp \
    View/Gridworld/gridworldview_score.cpp \
    Player/player.cpp \
    Player/randomplayer.cpp \
    Player/tabularq.cpp \
    Interaction_Handler/Gridworld/gridworld_ih.cpp \
    Interaction_Handler/Gridworld/tabularqih.cpp \
    Interaction_Handler/Gridworld/mlpqih.cpp \
    Interaction_Handler/Gridworld/gridworld_ih_getset.cpp \
    Interaction_Handler/Gridworld/gridworld_ih_input.cpp \
    Interaction_Handler/Gridworld/gridworld_ih_reward.cpp \
    Interaction_Handler/Gridworld/randomih.cpp \
    Util/neural_network.cpp \
    World/Gridworld/gridworld_score.cpp \
    Player/mlpq.cpp \
    Util/util_functions.cpp \
    Player/qlearningplayer.cpp \
    Interaction_Handler/Gridworld/visiongrid_ih.cpp \
    World/Gridworld/gridworld_add_player.cpp \
    World/Gridworld/gridworld_event_log.cpp \
    World/Gridworld/gridworld_check_pixel.cpp \
    World/Gridworld/gridworld_reset.cpp \
    World/Gridworld/gridworld_simulation.cpp

HEADERS  += \
    World/world.h \
    World/Gridworld/gridworld.h \
    World/Gridworld/gridworld_agent.h \
    World/Gridworld/gridworld_ball.h \
    World/Gridworld/gridworld_event.h \
    World/Gridworld/gridworld_score.h \
    View/view.h \
    View/Gridworld/gridworldview_agent.h \
    View/Gridworld/gridworldview_ball.h \
    View/Gridworld/gridworldview.h \
    View/Gridworld/gridworldview_score.h \
    Player/player.h \
    Player/randomplayer.h \
    Player/tabularq.h \
    Util/neural_network.h \
    Interaction_Handler/Gridworld/gridworld_ih.h \
    Interaction_Handler/Gridworld/tabularqih.h \
    Interaction_Handler/Gridworld/mlpqih.h \
    Interaction_Handler/Gridworld/randomih.h \
    Player/mlpq.h \
    Util/util_functions.h \
    Player/qlearningplayer.h \
    Interaction_Handler/Gridworld/visiongrid_ih.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    res.qrc

CONFIG += c++11 \
    o3

DISTFILES += \
    tutorial.pro.user.ad5f1f3.4.8-pre1
