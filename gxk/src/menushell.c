#include <glib.h>
#include <gtk/gtk.h>

#include "../public/menushell.h"

//
// GOBJECT INTERFACE DEFINITIONS & CTORS
//
G_DEFINE_INTERFACE(
    GxkMenuShell,
    gxk_menu_shell,
    G_TYPE_OBJECT
)

static void gxk_menu_shell_default_init(
    GxkMenuShellInterface* iface
) {}

//
// INTERFACE METHODS
//
void gxk_menu_shell_append(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
)
{
    GxkMenuShellInterface* iface =
        GXK_MENU_SHELL_GET_IFACE(menu_shell);

    iface->append(menu_shell, child);
}

void gxk_menu_shell_prepend(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
)
{
    GxkMenuShellInterface* iface =
        GXK_MENU_SHELL_GET_IFACE(menu_shell);

    iface->prepend(menu_shell, child);
}

void gxk_menu_shell_insert(
    GxkMenuShell* menu_shell,
    GtkWidget*    child,
    gint          position
)
{
    GxkMenuShellInterface* iface =
        GXK_MENU_SHELL_GET_IFACE(menu_shell);

    iface->insert(menu_shell, child, position);
}
