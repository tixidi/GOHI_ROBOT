INCLUDEPATH += $$PWD


SOURCES += \
    $$PWD/myopengl.cpp \
    $$PWD/grids.cpp \
    $$PWD/t3dmap.cpp \
    $$PWD/tools.cpp

HEADERS += \
    $$PWD/myopengl.h \
    $$PWD/grids.h \
    $$PWD/t3dmap.h \
    $$PWD/tools.h \
    $$PWD/gpoint3d.h


QT       += opengl
LIBS += -lopengl32 \
        -lglu32 \

