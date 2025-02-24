#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_DRAWING_WINDOW (gxk_drawing_window_get_type())

G_DECLARE_FINAL_TYPE(
    GxkDrawingWindow,
    gxk_drawing_window,
    GXK,
    DRAWING_WINDOW,
    GtkApplicationWindow
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_drawing_window_new(
    GxkDrawingApplication* app
);

#endif
