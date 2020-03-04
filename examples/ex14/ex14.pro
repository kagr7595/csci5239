HEADERS = ex14viewer.h ex14opengl.h CUgl.h Object.h Type.h Teapot.h
SOURCES = ex14.cpp ex14viewer.cpp ex14opengl.cpp CUgl.cpp Object.cpp Teapot.cpp
QT += opengl
RESOURCES = ex14.qrc
win32:{LIBS += -lopengl32}
