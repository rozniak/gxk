#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_BOXING_APPLICATION (gxk_boxing_application_get_type())

G_DECLARE_FINAL_TYPE(
    GxkBoxingApplication,
    gxk_boxing_application,
    GXK,
    BOXING_APPLICATION,
    GtkApplication
)

//
// PUBLIC FUNCTIONS
//
GxkBoxingApplication* gxk_boxing_application_new(void);

#endif
