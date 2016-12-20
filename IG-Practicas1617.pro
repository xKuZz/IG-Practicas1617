TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
QT += opengl

LIBS += -lglut32 -lopengl32
SOURCES += \
    objetos.cc \
    file_ply_stl.cc \
    practica1.cc \
    transform_helpers.cpp \
    luz.cpp \
    textura.cpp \
    rgb.cpp \
    material.cpp \
    scene_p4.cpp

HEADERS += \
    objetos.h \
    file_ply_stl.h \
    vertex.h \
    transform_helpers.h \
    luz.h \
    textura.h \
    rgb.h \
    material.h \
    scene_p4.h
