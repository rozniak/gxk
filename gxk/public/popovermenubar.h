#ifndef __GXK_POPOVER_MENU_BAR_H__
#define __GXK_POPOVER_MENU_BAR_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_POPOVER_MENU_BAR (gxk_popover_menu_bar_get_type())

G_DECLARE_FINAL_TYPE(
    GxkPopoverMenuBar,
    gxk_popover_menu_bar,
    GXK,
    POPOVER_MENU_BAR,
    GtkWidget
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_popover_menu_bar_new_from_model(
    GMenuModel* menu_model
);

void gxk_popover_menu_bar_bind_model(
    GxkPopoverMenuBar* menu_bar,
    GMenuModel*        menu_model
);

#endif
