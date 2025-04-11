#ifndef __GXK_APPLICATION_H__
#define __GXK_APPLICATION_H__

#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_APPLICATION (gxk_application_get_type())

G_DECLARE_DERIVABLE_TYPE(
    GxkApplication,
    gxk_application,
    GXK,
    APPLICATION,
    GtkApplication
)

struct _GxkApplicationClass
{
    GtkApplicationClass __parent__;
};

//
// PUBLIC FUNCTIONS
//
GxkApplication* gxk_application_new(
    const gchar*      application_id,
    GApplicationFlags flags
);

G_END_DECLS

#endif
