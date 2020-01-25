HEADERS = ex02viewer.h ex02opengl.h Type.h Object.h Cube.h Icosahedron.h Sphere.h Teapot.h WaveOBJ.h
SOURCES = ex02.cpp ex02viewer.cpp ex02opengl.cpp Object.cpp Cube.cpp Icosahedron.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp
QT += opengl
RESOURCES = ex02.qrc
win32:{LIBS += -lopengl32}
