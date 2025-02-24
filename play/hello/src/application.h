#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_HELLO_APPLICATION (gxk_hello_application_get_type())

G_DECLARE_FINAL_TYPE(
    GxkHelloApplication,
    gxk_hello_application,
    GXK,
    HELLO_APPLICATION,
    GtkApplication
)

//
// PUBLIC FUNCTIONS
//
GxkHelloApplication* gxk_hello_application_new(void);

#endif
