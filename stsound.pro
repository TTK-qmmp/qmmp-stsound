include(../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/stsound

HEADERS += decoderstsoundfactory.h \
           decoder_stsound.h \
           stsoundhelper.h

SOURCES += decoderstsoundfactory.cpp \
           decoder_stsound.cpp \
           stsoundhelper.cpp \
           libstsound/ym_digidrum.cpp \
           libstsound/ym_lzhlib.cpp \
           libstsound/ym_2149ex.cpp \
           libstsound/ym_load.cpp \
           libstsound/ym_music.cpp

INCLUDEPATH += $$PWD/libstsound

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libstsound.so
}
