#include <glib.h>

#include "application.h"

int main(
    int   argc,
    char* argv[]
)
{
    GxkBoxingApplication* app = gxk_boxing_application_new();
    int                  status;

    g_set_application_name("Hello");

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
