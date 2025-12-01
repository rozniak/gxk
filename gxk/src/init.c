#include <glib.h>
#include <gtk/gtk.h>

#include "../public/init.h"

//
// STATIC DATA
//
static gboolean S_INITIALIZED = FALSE;

//
// PUBLIC FUNCTIONS
//
void gxk_init(void)
{
    if (S_INITIALIZED)
    {
        return;
    }

    // TODO: Temporary, remove eventually
    //
    g_message("%s", "GXK lives!");

    gtk_init();

    // Add default styles
    //
    GtkCssProvider* css_provider = gtk_css_provider_new();

    gtk_css_provider_load_from_resource(
        css_provider,
        "/uk/oddmatics/gxk/gxk/appstyles.css"
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_FALLBACK
    );

    S_INITIALIZED = TRUE;
}
