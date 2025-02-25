#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"
#include "shim.h"
#include "window.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkBoxingApplication
{
    GtkApplication __parent__;
};

//
// FORWARD DECLARATIONS
//
static void gxk_boxing_application_activate(
    GApplication* application
);

//
// GOBJECT TYPE DEFINITIONS & CTORS
//
G_DEFINE_TYPE(
    GxkBoxingApplication,
    gxk_boxing_application,
    GTK_TYPE_APPLICATION
)

static void gxk_boxing_application_class_init(
    GxkBoxingApplicationClass* klass
)
{
    GApplicationClass* application_class = G_APPLICATION_CLASS(klass);

    application_class->activate = gxk_boxing_application_activate;
}

static void gxk_boxing_application_init(
    GXK_UNUSED(GxkBoxingApplication* self)
) { }

//
// CLASS VIRTUAL METHODS
//
static void gxk_boxing_application_activate(
    GApplication* application
)
{
    GtkWidget* new_window =
        gxk_boxing_window_new(GXK_BOXING_APPLICATION(application));

    gtk_window_present(GTK_WINDOW(new_window));
}

//
// PUBLIC FUNCTIONS
//
GxkBoxingApplication* gxk_boxing_application_new(void)
{
    return GXK_BOXING_APPLICATION(
        g_object_new(
            gxk_boxing_application_get_type(),
            "application-id", "uk.oddmatics.gxk.samples.boxing",
            NULL
        )
    );
}
