cmake_minimum_required(VERSION 3.0)

project(stsound)

set(HEADERS
    ym_stsoundlibrary.h
    ym_digidrum.h
    ym_2149ex.h
    ym_load.h
    ym_music.h
    ym_types.h
)

set(SOURCES
    ym_stsoundlibrary.cpp
    ym_digidrum.cpp
    ym_lzhlib.cpp
    ym_2149ex.cpp
    ym_load.cpp
    ym_music.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${STATIC_LIB_SUFFIX})

install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/lib${PROJECT_NAME})
