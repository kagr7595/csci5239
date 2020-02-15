HEADERS = ex04viewer.h ex04opengl.h CUgl.h Type.h Object.h Cube.h Icosahedron.h Sphere.h Teapot.h WaveOBJ.h
SOURCES = ex04.cpp ex04viewer.cpp ex04opengl.cpp CUgl.cpp Object.cpp Cube.cpp Icosahedron.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp
QT += opengl
RESOURCES = ex04.qrc
win32:{LIBS += -lopengl32}
