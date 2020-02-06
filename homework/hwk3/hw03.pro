HEADERS = hw03viewer.h hw03opengl.h CUgl.h Type.h Object.h Cube.h Icosahedron.h Sphere.h Teapot.h WaveOBJ.h
SOURCES = hw03.cpp hw03viewer.cpp hw03opengl.cpp CUgl.cpp Object.cpp Cube.cpp Icosahedron.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp
QT += opengl
RESOURCES = hw03.qrc
win32:{LIBS += -lopengl32}
