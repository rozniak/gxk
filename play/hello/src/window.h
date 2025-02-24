#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_HELLO_WINDOW (gxk_hello_window_get_type())

G_DECLARE_FINAL_TYPE(
    GxkHelloWindow,
    gxk_hello_window,
    GXK,
    HELLO_WINDOW,
    GtkApplicationWindow
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_hello_window_new(
    GxkHelloApplication* app
);

#endif
