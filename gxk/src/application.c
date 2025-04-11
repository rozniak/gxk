#include <glib.h>
#include <gtk/gtk.h>

#include "../public/application.h"
#include "../public/init.h"

//
// FORWARD DECLARATIONS
//
static void gxk_application_startup(
    GApplication* application
);

//
// GOBJECT BOILERPLATE
//
G_DEFINE_TYPE(
    GxkApplication,
    gxk_application,
    GTK_TYPE_APPLICATION
)

static void gxk_application_init(
    GxkApplication* self
) {}

static void gxk_application_class_init(
    GxkApplicationClass* klass
)
{
    GApplicationClass* application_class = G_APPLICATION_CLASS(klass);

    application_class->startup = gxk_application_startup;
}

//
// CLASS VIRTUAL METHODS
//
static void gxk_application_startup(
    GApplication* application
)
{
    gxk_init();

    (G_APPLICATION_CLASS(gxk_application_parent_class))->startup(application);
}

//
// PUBLIC FUNCTIONS
//
GxkApplication* gxk_application_new(
    const gchar*      application_id,
    GApplicationFlags flags
)
{
    return g_object_new(
        GXK_TYPE_APPLICATION,
        "application-id", application_id,
        "flags",          flags,
        NULL
    );
}
