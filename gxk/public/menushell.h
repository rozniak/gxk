#ifndef __GXK_MENU_SHELL_H__
#define __GXK_MENU_SHELL_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT INTERFACE DEFINITIONS
//
#define GXK_TYPE_MENU_SHELL (gxk_menu_shell_get_type())

G_DECLARE_INTERFACE(
    GxkMenuShell,
    gxk_menu_shell,
    GXK,
    MENU_SHELL,
    GObject
)

struct _GxkMenuShellInterface
{
    GTypeInterface base_iface;

    void (*append) (
        GxkMenuShell* menu_shell,
        GtkWidget*    child
    );
    void (*prepend) (
        GxkMenuShell* menu_shell,
        GtkWidget*    child
    );
    void (*insert) (
        GxkMenuShell* menu_shell,
        GtkWidget*    child,
        gint          position
    );
};

//
// INTERFACE METHODS
//
void gxk_menu_shell_append(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
);
void gxk_menu_shell_prepend(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
);
void gxk_menu_shell_insert(
    GxkMenuShell* menu_shell,
    GtkWidget*    child,
    gint          position
);

#endif
