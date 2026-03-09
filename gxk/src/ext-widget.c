#include <glib.h>
#include <gtk/gtk.h>

#include "../public/ext-widget.h"

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxkex_widget_get_nth_child(
    GtkWidget* widget,
    gint       n
)
{
    GtkWidget* child = gtk_widget_get_first_child(widget);

    for (gint i = 0; i < n; i++)
    {
        if (!child)
        {
            return NULL;
        }

        child = gtk_widget_get_next_sibling(child);
    }

    return child;
}
