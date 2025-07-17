#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"
#include "shim.h"
#include "window.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkDemoWindow
{
    GtkApplicationWindow __parent__;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkDemoWindow,
    gxk_demo_window,
    GTK_TYPE_APPLICATION_WINDOW
)

static void gxk_demo_window_class_init(
    GXK_UNUSED(GxkDemoWindowClass* klass)
) {}

static void gxk_demo_window_init(
    GxkDemoWindow* self
)
{
    GtkBuilder* builder =
        gtk_builder_new_from_resource(
            "/uk/oddmatics/gxk/samples/demo/window.ui"
        );

    gtk_window_set_child(
        GTK_WINDOW(self),
        GTK_WIDGET(gtk_builder_get_object(builder, "main-box"))
    );

    g_object_unref(builder);
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_demo_window_new(
    GxkDemoApplication* app
)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_DEMO_WINDOW,
            "application", GTK_APPLICATION(app),
            "title",       "GXK Demo",
            NULL
        )
    );
}
