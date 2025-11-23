#ifndef __GXK_POPOVER_MENU_H__
#define __GXK_POPOVER_MENU_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_POPOVER_MENU (gxk_popover_menu_get_type())

G_DECLARE_FINAL_TYPE(
    GxkPopoverMenu,
    gxk_popover_menu,
    GXK,
    POPOVER_MENU,
    GtkPopover
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_popover_menu_new(void);

void gxk_popover_menu_append_child(
    GxkPopoverMenu* menu,
    GtkWidget*      child
);

#endif
