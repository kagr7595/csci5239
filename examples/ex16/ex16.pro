HEADERS = ex16viewer.h ex16opengl.h CUgl.h Type.h Object.h Cube.h Sphere.h Teapot.h WaveOBJ.h Noise.h
SOURCES = ex16.cpp ex16viewer.cpp ex16opengl.cpp CUgl.cpp Object.cpp Cube.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp Noise.cpp
QT += opengl
RESOURCES = ex16.qrc
win32:{LIBS += -lopengl32}
