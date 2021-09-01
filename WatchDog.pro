TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Class1.cpp \
        Class2.cpp \
        MultiThreadWatchdog.cpp \
        Tracker.cpp \
        Wrapper.cpp \
        main.cpp

LIBS += -lpthread

HEADERS += \
    Class1.h \
    Class2.h \
    MultiThreadWatchdog.h \
    Tracker.h \
    Wrapper.h
