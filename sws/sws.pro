#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T23:41:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT += multimedia


TARGET = sws
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    generator.cpp \
    player.cpp

HEADERS += \
    generator.h \
    player.h
