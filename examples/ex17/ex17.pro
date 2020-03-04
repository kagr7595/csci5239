HEADERS = ex17viewer.h ex17opengl.h Type.h CUgl.h Object.h Cube.h Sphere.h Teapot.h WaveOBJ.h Noise.h
SOURCES = ex17.cpp ex17viewer.cpp ex17opengl.cpp CUgl.cpp Object.cpp Cube.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp Noise.cpp
QT += opengl
RESOURCES = ex17.qrc
win32:{LIBS += -lopengl32}
