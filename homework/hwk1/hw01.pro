HEADERS = hw01viewer.h hw01opengl.h Type.h Object.h Cube.h Sphere.h Teapot.h Icosahedron.h WaveOBJ.h
SOURCES = hw01.cpp hw01viewer.cpp hw01opengl.cpp Object.cpp Cube.cpp Sphere.cpp Teapot.cpp Icosahedron.cpp WaveOBJ.cpp
QT += opengl
RESOURCES = hw01.qrc
win32:{LIBS += -lopengl32}
