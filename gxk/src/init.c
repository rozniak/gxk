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

    S_INITIALIZED = TRUE;
}
