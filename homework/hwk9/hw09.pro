HEADERS = hw09viewer.h hw09opengl.h CUgl.h Object.h Type.h
SOURCES = hw09.cpp hw09viewer.cpp hw09opengl.cpp CUgl.cpp Object.cpp
QT += opengl
RESOURCES = hw09.qrc
win32:{LIBS += -lopengl32}

DISTFILES +=
