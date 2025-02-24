#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"
#include "shim.h"
#include "window.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkHelloWindow
{
    GtkApplicationWindow __parent__;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkHelloWindow,
    gxk_hello_window,
    GTK_TYPE_APPLICATION_WINDOW
)

static void gxk_hello_window_class_init(
    GXK_UNUSED(GxkHelloWindowClass* klass)
) {}

static void gxk_hello_window_init(
    GxkHelloWindow* self
)
{
    gtk_window_set_default_size(
        GTK_WINDOW(self),
        320,
        200
    );

    gtk_window_set_child(
        GTK_WINDOW(self),
        gtk_label_new("Hello GXK!")
    );
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_hello_window_new(
    GxkHelloApplication* app
)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_HELLO_WINDOW,
            "application", GTK_APPLICATION(app),
            "title",       "Hello GXK!",
            NULL
        )
    );
}
