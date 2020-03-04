HEADERS = ex15viewer.h ex15opengl.h CUgl.h Type.h Object.h Sphere.h
SOURCES = ex15.cpp ex15viewer.cpp ex15opengl.cpp CUgl.cpp Object.cpp Sphere.cpp
QT += opengl
RESOURCES = ex15.qrc
win32:{LIBS += -lopengl32}
