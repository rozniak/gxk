#ifndef __GXK_MENU_SHELL_H__
#define __GXK_MENU_SHELL_H__

#include <glib.h>
#include <gtk/gtk.h>

#include "menuitem.h"

//
// PUBLIC ENUMS
//
typedef enum _GxkMenuShellKind
{
    GXK_MENU_SHELL_MENU_BAR,
    GXK_MENU_SHELL_MENU
} GxkMenuShellKind;

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
    GxkMenuShellKind (*get_kind) (
        GxkMenuShell* menu_shell
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
    void (*set_active_item) (
        GxkMenuShell* menu_shell,
        GxkMenuItem*  menu_item,
        gboolean      popup
    );
};

//
// INTERFACE METHODS
//
void gxk_menu_shell_append(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
);
GxkMenuShellKind gxk_menu_shell_get_kind(
    GxkMenuShell* menu_shell
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
void gxk_menu_shell_set_active_item(
    GxkMenuShell* menu_shell,
    GxkMenuItem*  menu_item,
    gboolean      popup
);

#endif
