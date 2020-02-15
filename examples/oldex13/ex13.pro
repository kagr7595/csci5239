HEADERS = ex13viewer.h ex13opengl.h CUgl.h Object.h Type.h
SOURCES = ex13.cpp ex13viewer.cpp ex13opengl.cpp CUgl.cpp
QT += opengl
RESOURCES = ex13.qrc
win32:{LIBS += -lopengl32}
