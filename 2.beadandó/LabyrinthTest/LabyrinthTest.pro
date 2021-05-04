QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_labyrinthmodeltest.cpp \
    labyrinthload.cpp \
    labyrinthmodel.cpp

HEADERS += \
    labyrinthload.h \
    labyrinthloadmock.h \
    labyrinthmodel.h

RESOURCES += \
    Resource.qrc
