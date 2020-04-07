
HEADERS += decoderymfactory.h \
           decoder_ym.h \
           ym_digidrum.h \
           ym_lzh.h \
           ym_2149ex.h \
           ym_load.h \
           ym_music.h \
           ym_types.h

SOURCES += decoderymfactory.cpp \
           decoder_ym.cpp \
           ym_digidrum.cpp \
           ym_lzhlib.cpp \
           ym_2149ex.cpp \
           ym_load.cpp \
           ym_music.cpp

CONFIG += warn_on plugin link_pkgconfig c++11

TEMPLATE = lib

QMAKE_CLEAN += lib$${TARGET}.so

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += qmmp

  QMMP_PREFIX = $$system(pkg-config qmmp --variable=prefix)
  PLUGIN_DIR = $$system(pkg-config qmmp --variable=plugindir)/Input
  LOCAL_INCLUDES = $${QMMP_PREFIX}/include
  LOCAL_INCLUDES -= $$QMAKE_DEFAULT_INCDIRS
  INCLUDEPATH += $$LOCAL_INCLUDES

  plugin.path = $${PLUGIN_DIR}
  plugin.files = lib$${TARGET}.so
  INSTALLS += plugin
}
