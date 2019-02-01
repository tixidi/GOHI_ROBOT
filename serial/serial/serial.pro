QT -= gui
QT += serialport

CONFIG += c++11 console
CONFIG -= app_bundle



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS


#DEFINES +=BOOST_USE_LIB
#DEFINES += BOOST_THREAD_USE_LIB

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



message($$PWD)
include(./common.pri)



SOURCES += \
        main.cpp \
    mainwindow.cpp \
    mcmodbusrtu.cpp \
    paintwidget.cpp \
    cradar.cpp


HEADERS += \
    mainwindow.h \
    mcmodbusrtu.h \
    tabcrc.h \
    paintwidget.h \
    cradar.h

FORMS    += mainwindow.ui

#INCLUDEPATH += -I E:/boost/include/boost-1_67
#LIBS += -LE:/boost/lib -llibboost_thread-mgw53-mt-d-x32-1_67 -llibboost_system-mgw53-mt-d-x32-1_67 -llibboost_date_time-mgw53-mt-d-x32-1_67 -llibboost_filesystem-mgw53-mt-d-x32-1_67 -llibboost_signals-mgw53-mt-d-x32-1_67
#LIBS += -lws2_32

DISTFILES += \
    note

RESOURCES += \
    image.qrc \
    buttonsrc.qrc

