cmake_minimum_required(VERSION 3.12)

project(
    gxk-4
    VERSION 1.0
    DESCRIPTION "Library for developing XApps with GTK 4."
    LANGUAGES C
)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GTK4 REQUIRED gtk4)

add_library(
    gxk-4
    src/application.c
    public/application.h
    src/init.c
    public/init.h
    src/popovermenu.c
    public/popovermenu.h
    src/popovermenubar.c
    public/popovermenubar.h
    src/popovermenubar-int.h
    src/popovermenubaritem.c
    src/popovermenubaritem.h
)

target_include_directories(
    gxk-4
    SYSTEM
    PRIVATE ${GLIB_INCLUDE_DIRS}
    PRIVATE ${GTK4_INCLUDE_DIRS}
)

target_link_directories(
    gxk-4
    PRIVATE ${GLIB_LIBRARY_DIRS}
    PRIVATE ${GTK4_LIBRARY_DIRS}
)

target_link_libraries(
    gxk-4
    PRIVATE ${GLIB_LIBRARIES}
    PRIVATE ${GTK4_LIBRARIES}
)

# Installation
#
configure_file(gxk4.pc.in gxk4.pc @ONLY)

install(
    DIRECTORY public/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gxk-4.0/gxk
)
install(
    FILES gxk.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gxk-4.0
)
install(
    FILES ${CMAKE_BINARY_DIR}/gxk4.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
install(
    TARGETS gxk-4
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
