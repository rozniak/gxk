#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"
#include "shim.h"
#include "window.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkHelloApplication
{
    GtkApplication __parent__;
};

//
// FORWARD DECLARATIONS
//
static void gxk_hello_application_activate(
    GApplication* application
);

//
// GOBJECT TYPE DEFINITIONS & CTORS
//
G_DEFINE_TYPE(
    GxkHelloApplication,
    gxk_hello_application,
    GTK_TYPE_APPLICATION
)

static void gxk_hello_application_class_init(
    GxkHelloApplicationClass* klass
)
{
    GApplicationClass* application_class = G_APPLICATION_CLASS(klass);

    application_class->activate = gxk_hello_application_activate;
}

static void gxk_hello_application_init(
    GXK_UNUSED(GxkHelloApplication* self)
) { }

//
// CLASS VIRTUAL METHODS
//
static void gxk_hello_application_activate(
    GApplication* application
)
{
    GtkWidget* new_window =
        gxk_hello_window_new(GXK_HELLO_APPLICATION(application));

    gtk_window_present(GTK_WINDOW(new_window));
}

//
// PUBLIC FUNCTIONS
//
GxkHelloApplication* gxk_hello_application_new(void)
{
    return GXK_HELLO_APPLICATION(
        g_object_new(
            gxk_hello_application_get_type(),
            "application-id", "uk.oddmatics.gxk.samples.hello",
            NULL
        )
    );
}
