HEADERS = ex20viewer.h ex20opengl.h CUgl.h Type.h Object.h
SOURCES = ex20.cpp ex20viewer.cpp ex20opengl.cpp CUgl.cpp Object.cpp
QT += opengl
RESOURCES = ex20.qrc
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
win32:{LIBS += -lopengl32}
