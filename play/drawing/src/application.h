#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_DRAWING_APPLICATION (gxk_drawing_application_get_type())

G_DECLARE_FINAL_TYPE(
    GxkDrawingApplication,
    gxk_drawing_application,
    GXK,
    DRAWING_APPLICATION,
    GtkApplication
)

//
// PUBLIC FUNCTIONS
//
GxkDrawingApplication* gxk_drawing_application_new(void);

#endif
