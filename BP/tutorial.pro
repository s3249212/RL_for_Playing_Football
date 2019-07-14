#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T12:24:37
#
#-------------------------------------------------

QT       += core gui \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tutorial
TEMPLATE = app

# Path to cuda toolkit install
CUDA_DIR      = /usr/local/cuda
# Path to header and libs files
INCLUDEPATH  += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib64     # Note I'm using a 64 bits Operating system
# libs used in your code
LIBS += -lcudart -lcuda
# GPU architecture
CUDA_ARCH     = sm_20                # Yeah! I've a new device. Adjust with your compute capability
# Here are some NVCC flags I've always used by default.
NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v

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
    World/Gridworld/gridworld_simulation.cpp \
    Player/qv.cpp \
    Util/cnn.cpp \

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
    Interaction_Handler/Gridworld/visiongrid_ih.h \
    Player/qv.h \
    Util/cnn.h \

FORMS    += \
    mainwindow.ui

RESOURCES += \
    res.qrc

CONFIG += c++11 \
    o3

DISTFILES += \
    tutorial.pro.user.ad5f1f3.4.8-pre1 \
    Util/cytonRL/ale/emucore/m6502/src/M6502.m4 \
    Util/cytonRL/ale/emucore/m6502/src/M6502Hi.m4 \
    Util/cytonRL/ale/emucore/m6502/src/M6502Low.m4 \
    tutorial.pro.user.26da0f2 \
    tutorial.pro.user.3b11ee3 \
    tutorial.pro.user.ad5f1f3 \
    Util/cytonRL/ale/common/stella.png \
    Util/cytonRL/ale/common/stella.xpm \
    Util/cytonRL/ale/common/module.mk \
    Util/cytonRL/ale/controllers/module.mk \
    Util/cytonRL/ale/emucore/m6502/src/bspf/Copyright.txt \
    Util/cytonRL/ale/emucore/m6502/src/bspf/License.txt \
    Util/cytonRL/ale/emucore/m6502/Copyright.txt \
    Util/cytonRL/ale/emucore/m6502/License.txt \
    Util/cytonRL/ale/emucore/m6502/module.mk \
    Util/cytonRL/ale/emucore/rsynth/Elements.def \
    Util/cytonRL/ale/emucore/rsynth/kmap \
    Util/cytonRL/ale/emucore/rsynth/module.mk \
    Util/cytonRL/ale/emucore/rsynth/phones.def \
    Util/cytonRL/ale/emucore/rsynth/phtoelm.def \
    Util/cytonRL/ale/emucore/rsynth/PORTING \
    Util/cytonRL/ale/emucore/module.mk \
    Util/cytonRL/ale/environment/module.mk \
    Util/cytonRL/ale/external/TinyMT/LICENSE.txt \
    Util/cytonRL/ale/external/module.mk \
    Util/cytonRL/ale/games/module.mk \
    Util/cytonRL/ale/os_dependent/module.mk \
    Util/cytonRL/ale/module.mk \
    Util/cytonLib/ActivationLayer.cu \
    Util/cytonLib/basicHeads.cu \
    Util/cytonLib/ConvolutionLayer.cu \
    Util/cytonLib/DeviceMatrix.cu \
    Util/cytonLib/DevMatReal.cu \
    Util/cytonLib/DueLinLayer.cu \
    Util/cytonLib/Global.cu \
    Util/cytonLib/HostMatReal.cu \
    Util/cytonLib/HostMatrix.cu \
    Util/cytonLib/Layer.cu \
    Util/cytonLib/LinearLayer.cu \
    Util/cytonLib/Matrix.cu \
    Util/cytonLib/MatrixGradient.cu \
    Util/cytonLib/Network.cu \
    Util/cytonLib/NumberProbe.cu \
    Util/cytonLib/NumberProbes.cu \
    Util/cytonLib/SoftmaxLayer.cu \
    Util/cytonLib/utils.cu \
    Util/cytonLib/Variable.cu \
    Util/cytonLib/Weight.cu \
    Util/cytonLib/WeightFactory.cu \
    Util/cytonRL/Environment.cu \
    Util/cytonRL/mainRl.cu \
    Util/cytonRL/NetworkRl.cu \
    Util/cytonRL/ParamsRl.cu \
    Util/cytonRL/ReinforceLearner.cu \
    Util/cytonRL/ReplayMemory.cu \
    Util/cytonRL/Step.cu \
    Util/cytonRL/Steps.cu \
    Util/cytonRL/SumTree.cu \
    Util/cytonRL/ale/emucore/rsynth/COPYING \
    Util/cytonRL/ale/emucore/m6502/src/M6502Hi.ins \
    Util/cytonRL/ale/emucore/m6502/src/M6502Low.ins

SUBDIRS += \
    Util/cytonRL/ale/emucore/stella.pro
