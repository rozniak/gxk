#ifndef __GXK_MENU_BIND_H__
#define __GXK_MENU_BIND_H__

#include <glib.h>
#include <gtk/gtk.h>

#include "menushell.h"

//
// GTK OOP BOILERPLATE
//
#define GXK_TYPE_MENU_BINDING (gxk_menu_binding_get_type())

G_DECLARE_FINAL_TYPE(
    GxkMenuBinding,
    gxk_menu_binding,
    GXK,
    MENU_BINDING,
    GObject
)

//
// PUBLIC FUNCTIONS
//
GxkMenuBinding* gxk_menu_binding_new(
    GxkMenuShell* menu_shell,
    GMenuModel*   menu_model
);

#endif
