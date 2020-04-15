HEADERS = fprojviewer.h fprojopengl.h CUgl.h Object.h Type.h
SOURCES = fproj.cpp fprojviewer.cpp fprojopengl.cpp CUgl.cpp Object.cpp
QT += opengl
RESOURCES = fproj.qrc
win32:{LIBS += -lopengl32}

DISTFILES +=
