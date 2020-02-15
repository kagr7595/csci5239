HEADERS = ex06viewer.h ex06opengl.h CUgl.h Object.h Type.h
SOURCES = ex06.cpp ex06viewer.cpp ex06opengl.cpp CUgl.cpp Object.cpp
QT += opengl
RESOURCES = ex06.qrc
win32:{LIBS += -lopengl32}
