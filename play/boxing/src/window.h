#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_BOXING_WINDOW (gxk_boxing_window_get_type())

G_DECLARE_FINAL_TYPE(
    GxkBoxingWindow,
    gxk_boxing_window,
    GXK,
    BOXING_WINDOW,
    GtkApplicationWindow
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_boxing_window_new(
    GxkBoxingApplication* app
);

#endif
