cmake_minimum_required(VERSION 3.5)

project(
    gxk-drawing
    VERSION 1.0
    DESCRIPTION "GXK Drawing Sample"
    LANGUAGES C
)

include(GNUInstallDirs)

include(../../cmake/glib-compile-resources.cmake)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GTK4 REQUIRED gtk4)

gxk_glib_compile_resources()

add_executable(
    gxk-drawing
    src/application.c
    src/application.h
    src/main.c
    src/resources.c
    src/widget.c
    src/widget.h
    src/window.c
    src/window.h
)

target_include_directories(
    gxk-drawing
    SYSTEM
    PRIVATE ${GLIB_INCLUDE_DIRS}
    PRIVATE ${GTK4_INCLUDE_DIRS}
)

target_link_directories(
    gxk-drawing
    PRIVATE ${GLIB_LIBRARY_DIRS}
    PRIVATE ${GTK4_LIBRARY_DIRS}
)

target_link_libraries(
    gxk-drawing
    PRIVATE ${GLIB_LIBRARIES}
    PRIVATE ${GTK4_LIBRARIES}
)
