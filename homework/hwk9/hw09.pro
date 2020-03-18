HEADERS = hw09viewer.h hw09opengl.h Type.h Object.h Cube.h Sphere.h Teapot.h WaveOBJ.h CUgl.h
SOURCES = hw09.cpp hw09viewer.cpp hw09opengl.cpp Object.cpp Cube.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp CUgl.cpp
QT += opengl
RESOURCES = hw09.qrc
win32:{LIBS += -lopengl32}
