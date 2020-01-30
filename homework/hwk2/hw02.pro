HEADERS = hw02viewer.h hw02opengl.h CUgl.h Type.h Object.h Cube.h Icosahedron.h Sphere.h Teapot.h WaveOBJ.h
SOURCES = hw02.cpp hw02viewer.cpp hw02opengl.cpp CUgl.cpp Object.cpp Cube.cpp Icosahedron.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp
QT += opengl
RESOURCES = hw02.qrc
win32:{LIBS += -lopengl32}
