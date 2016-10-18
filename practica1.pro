HEADERS = objetos.h vertex.h file_ply_stl.h

SOURCES = \
    practica1.cc \
    objetos.cc \
    file_ply_stl.cc

LIBS += -lglut

CONFIG += console c++11
QT += opengl

