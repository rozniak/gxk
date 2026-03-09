#ifndef __GXK_EXT_WIDGET_H__
#define __GXK_EXT_WIDGET_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxkex_widget_get_nth_child(
    GtkWidget* widget,
    gint       n
);

#endif
