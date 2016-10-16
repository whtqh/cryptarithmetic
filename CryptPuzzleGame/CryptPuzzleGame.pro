#-------------------------------------------------
#
# Project created by QtCreator 2016-10-16T14:44:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CryptPuzzleGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cryptarithmetic/cryptarithmetic.cpp \
    cryptarithmetic/divide_formula.cpp \
    cryptarithmetic/formula.cpp \
    cryptarithmetic/minus_formula.cpp \
    cryptarithmetic/symbol.cpp \
    cryptarithmetic/times_formula.cpp

HEADERS  += mainwindow.h \
    cryptarithmetic/divide_formula.h \
    cryptarithmetic/formula.h \
    cryptarithmetic/minus_formula.h \
    cryptarithmetic/symbol.h \
    cryptarithmetic/times_formula.h \
    cryptarithmetic/cryptarithmetic.h

FORMS    += mainwindow.ui

DISTFILES += \
    cryptarithmetic/Debug/cryptarithmetic.obj.enc \
    cryptarithmetic/Debug/formula.obj.enc \
    cryptarithmetic/Debug/minus_formula.obj.enc \
    cryptarithmetic/Debug/times_formula.obj.enc \
    cryptarithmetic/Debug/vc140.idb \
    cryptarithmetic/Debug/vc140.pdb \
    cryptarithmetic/Debug/cryptarithmetic.tlog/CL.command.1.tlog \
    cryptarithmetic/Debug/cryptarithmetic.tlog/CL.read.1.tlog \
    cryptarithmetic/Debug/cryptarithmetic.tlog/CL.write.1.tlog \
    cryptarithmetic/Debug/cryptarithmetic.tlog/cryptarithmetic.lastbuildstate \
    cryptarithmetic/Debug/cryptarithmetic.tlog/link.command.1.tlog \
    cryptarithmetic/Debug/cryptarithmetic.tlog/link.read.1.tlog \
    cryptarithmetic/Debug/cryptarithmetic.tlog/link.write.1.tlog \
    cryptarithmetic/cryptarithmetic.vcxproj \
    cryptarithmetic/cryptarithmetic.vcxproj.filters \
    cryptarithmetic/theory.vcxproj \
    cryptarithmetic/Debug/cryptarithmetic.log
