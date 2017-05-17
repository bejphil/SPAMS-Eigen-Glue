TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#Force use of c++11
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS -= -std=gnu++11
QMAKE_CXXFLAGS -= -std=c++0x

CONFIG += c++11

# Pass flags for bebugging
# Override Qt's default -O2 flag in release mode
CONFIG(debug, debug|release) {
    DEFINES += "DEBUG"
} else {
    DEFINES += "NDEBUG"
    CONFIG += optimize_full
#    QMAKE_CXXFLAGS *= -Ofast
    QMAKE_CXXFLAGS_RELEASE *= -mtune=native
    QMAKE_CXXFLAGS_RELEASE *= -march=native
}

# Eigen
INCLUDEPATH += /usr/include/eigen3

# SPAMS
INCLUDEPATH +=  ../spams/src \
                ../spams/src/spams/dictLearn \
                ../spams/src/spams/decomp \
                ../spams/src/spams/linalg \
                ../spams/src/spams/prox \

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

# SPAMS has unused parameters in source -- surpress warnings
QMAKE_CXXFLAGS+= -Wno-unused-parameter

# for FISTA
LIBS += -lstdc++ \
        -lblas \
        -llapack

# Armadillo
LIBS += -larmadillo

HEADERS += spams_eigen_glue.h \
    test_fista.h

SOURCES += main.cpp
