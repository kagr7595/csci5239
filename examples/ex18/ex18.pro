HEADERS = ex18main.h ex18opengl.h
SOURCES = ex18.cpp ex18main.cpp ex18opengl.cpp
QT += opengl
RESOURCES = ex18.qrc
win32:{LIBS += -lopengl32}
