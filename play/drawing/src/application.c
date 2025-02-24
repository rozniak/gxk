#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"
#include "shim.h"
#include "window.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkDrawingApplication
{
    GtkApplication __parent__;
};

//
// FORWARD DECLARATIONS
//
static void gxk_drawing_application_activate(
    GApplication* application
);

//
// GOBJECT TYPE DEFINITIONS & CTORS
//
G_DEFINE_TYPE(
    GxkDrawingApplication,
    gxk_drawing_application,
    GTK_TYPE_APPLICATION
)

static void gxk_drawing_application_class_init(
    GxkDrawingApplicationClass* klass
)
{
    GApplicationClass* application_class = G_APPLICATION_CLASS(klass);

    application_class->activate = gxk_drawing_application_activate;
}

static void gxk_drawing_application_init(
    GXK_UNUSED(GxkDrawingApplication* self)
) { }

//
// CLASS VIRTUAL METHODS
//
static void gxk_drawing_application_activate(
    GApplication* application
)
{
    GtkWidget* new_window =
        gxk_drawing_window_new(GXK_DRAWING_APPLICATION(application));

    gtk_window_present(GTK_WINDOW(new_window));
}

//
// PUBLIC FUNCTIONS
//
GxkDrawingApplication* gxk_drawing_application_new(void)
{
    return GXK_DRAWING_APPLICATION(
        g_object_new(
            gxk_drawing_application_get_type(),
            "application-id", "uk.oddmatics.gxk.samples.drawing",
            NULL
        )
    );
}
