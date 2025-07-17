cmake_minimum_required(VERSION 3.5)

project(
    gxk-demo
    VERSION 1.0
    DESCRIPTION "GXK Demo Application"
    LANGUAGES C
)

include(GNUInstallDirs)

include(../../cmake/glib-compile-resources.cmake)

find_package(PkgConfig REQUIRED)

pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(GLIB  REQUIRED glib-2.0)
pkg_check_modules(GTK4  REQUIRED gtk4)
pkg_check_modules(GXK4  REQUIRED gxk4)

gxk_glib_compile_resources()

add_executable(
    gxk-demo
    src/application.c
    src/application.h
    src/main.c
    src/resources.c
    src/window.c
    src/window.h
)

target_include_directories(
    gxk-demo
    SYSTEM
    PRIVATE ${CAIRO_INCLUDE_DIRS}
    PRIVATE ${GLIB_INCLUDE_DIRS}
    PRIVATE ${GTK4_INCLUDE_DIRS}
    PRIVATE ${GXK4_INCLUDE_DIRS}
)

target_link_directories(
    gxk-demo
    PRIVATE ${CAIRO_LIBRARY_DIRS}
    PRIVATE ${GLIB_LIBRARY_DIRS}
    PRIVATE ${GTK4_LIBRARY_DIRS}
    PRIVATE ${GXK4_LIBRARY_DIRS}
)

target_link_libraries(
    gxk-demo
    PRIVATE ${CAIRO_LIBRARIES}
    PRIVATE ${GLIB_LIBRARIES}
    PRIVATE ${GTK4_LIBRARIES}
    PRIVATE ${GXK4_LIBRARIES}
)
