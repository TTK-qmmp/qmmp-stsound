include(../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/ym

HEADERS += decoderymfactory.h \
           decoder_ym.h

SOURCES += decoderymfactory.cpp \
           decoder_ym.cpp \
           libym/ym_digidrum.cpp \
           libym/ym_lzhlib.cpp \
           libym/ym_2149ex.cpp \
           libym/ym_load.cpp \
           libym/ym_music.cpp

INCLUDEPATH += $$PWD/libym

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libym.so
}
