#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"
#include "shim.h"
#include "widget.h"
#include "window.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkDrawingWindow
{
    GtkApplicationWindow __parent__;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkDrawingWindow,
    gxk_drawing_window,
    GTK_TYPE_APPLICATION_WINDOW
)

static void gxk_drawing_window_class_init(
    GXK_UNUSED(GxkDrawingWindowClass* klass)
) {}

static void gxk_drawing_window_init(
    GxkDrawingWindow* self
)
{
    gtk_window_set_default_size(
        GTK_WINDOW(self),
        320,
        200
    );

    gtk_window_set_child(
        GTK_WINDOW(self),
        gxk_custom_widget_new()
    );
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_drawing_window_new(
    GxkDrawingApplication* app
)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_DRAWING_WINDOW,
            "application", GTK_APPLICATION(app),
            "title",       "GXK Drawing Test",
            NULL
        )
    );
}
