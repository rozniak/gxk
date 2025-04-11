cmake_minimum_required(VERSION 3.5)

project(
    gxk-hello
    VERSION 1.0
    DESCRIPTION "GXK Hello Sample"
    LANGUAGES C
)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(GXK4 REQUIRED gxk4)

add_executable(
    gxk-hello
    src/application.c
    src/application.h
    src/main.c
    src/window.c
    src/window.h
)

target_include_directories(
    gxk-hello
    SYSTEM
    PRIVATE ${GLIB_INCLUDE_DIRS}
    PRIVATE ${GTK4_INCLUDE_DIRS}
    PRIVATE ${GXK4_INCLUDE_DIRS}
)

target_link_directories(
    gxk-hello
    PRIVATE ${GLIB_LIBRARY_DIRS}
    PRIVATE ${GTK4_LIBRARY_DIRS}
    PRIVATE ${GXK4_LIBRARY_DIRS}
)

target_link_libraries(
    gxk-hello
    PRIVATE ${GLIB_LIBRARIES}
    PRIVATE ${GTK4_LIBRARIES}
    PRIVATE ${GXK4_LIBRARIES}
)
