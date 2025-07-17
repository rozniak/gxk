#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <glib.h>
#include <gtk/gtk.h>
#include <gxk.h>

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_DEMO_APPLICATION (gxk_demo_application_get_type())

G_DECLARE_FINAL_TYPE(
    GxkDemoApplication,
    gxk_demo_application,
    GXK,
    DEMO_APPLICATION,
    GxkApplication
)

//
// PUBLIC FUNCTIONS
//
GxkDemoApplication* gxk_demo_application_new(void);

#endif
