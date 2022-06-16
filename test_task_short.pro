TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cutSphereMove.cpp \
		CalcSphereMovement.cpp \
    mwException.cpp \
    mwIdxRangeException.cpp


HEADERS += \
		CalcSphereMovement.hpp \
    mwDiscreteFunction.hpp \
    mwException.hpp \
    mwIdxRangeException.hpp \
    mwMathConstants.hpp \
    mwTPoint3d.hpp

