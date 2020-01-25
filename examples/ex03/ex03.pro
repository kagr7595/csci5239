HEADERS = ex03viewer.h ex03opengl.h CUgl.h Type.h Object.h Cube.h Icosahedron.h Sphere.h Teapot.h WaveOBJ.h
SOURCES = ex03.cpp ex03viewer.cpp ex03opengl.cpp CUgl.cpp Object.cpp Cube.cpp Icosahedron.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp
QT += opengl
RESOURCES = ex03.qrc
win32:{LIBS += -lopengl32}
