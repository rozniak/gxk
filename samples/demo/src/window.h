#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_DEMO_WINDOW (gxk_demo_window_get_type())

G_DECLARE_FINAL_TYPE(
    GxkDemoWindow,
    gxk_demo_window,
    GXK,
    DEMO_WINDOW,
    GtkApplicationWindow
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_demo_window_new(
    GxkDemoApplication* app
);

#endif
