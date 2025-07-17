#include <glib.h>
#include <gtk/gtk.h>
#include <gxk.h>

#include "application.h"
#include "shim.h"
#include "window.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkDemoApplication
{
    GxkApplication __parent__;
};

//
// FORWARD DECLARATIONS
//
static void gxk_demo_application_activate(
    GApplication* application
);

//
// GOBJECT TYPE DEFINITIONS & CTORS
//
G_DEFINE_TYPE(
    GxkDemoApplication,
    gxk_demo_application,
    GXK_TYPE_APPLICATION
)

static void gxk_demo_application_class_init(
    GxkDemoApplicationClass* klass
)
{
    GApplicationClass* application_class = G_APPLICATION_CLASS(klass);

    application_class->activate = gxk_demo_application_activate;
}

static void gxk_demo_application_init(
    GXK_UNUSED(GxkDemoApplication* self)
) { }

//
// CLASS VIRTUAL METHODS
//
static void gxk_demo_application_activate(
    GApplication* application
)
{
    GtkWidget* new_window =
        gxk_demo_window_new(GXK_DEMO_APPLICATION(application));

    gtk_window_present(GTK_WINDOW(new_window));
}

//
// PUBLIC FUNCTIONS
//
GxkDemoApplication* gxk_demo_application_new(void)
{
    return GXK_DEMO_APPLICATION(
        g_object_new(
            gxk_demo_application_get_type(),
            "application-id", "uk.oddmatics.gxk.samples.demo",
            NULL
        )
    );
}
