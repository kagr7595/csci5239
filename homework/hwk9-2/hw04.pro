HEADERS = hw04viewer.h hw04opengl.h CUgl.h Object.h Type.h
SOURCES = hw04.cpp hw04viewer.cpp hw04opengl.cpp CUgl.cpp Object.cpp
QT += opengl
RESOURCES = hw04.qrc
win32:{LIBS += -lopengl32}

DISTFILES +=
