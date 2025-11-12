#ifndef __GXK_POPOVER_MENU_BAR_ITEM_H__
#define __GXK_POPOVER_MENU_BAR_ITEM_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT BOILERPLAE
//
#define GXK_TYPE_POPOVER_MENU_BAR_ITEM (gxk_popover_menu_bar_item_get_type())

G_DECLARE_FINAL_TYPE(
    GxkPopoverMenuBarItem,
    gxk_popover_menu_bar_item,
    GXK,
    POPOVER_MENU_BAR_ITEM,
    GtkWidget
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_popover_menu_bar_item_new(void);

GtkWidget* gxk_popover_menu_bar_item_get_popover(
    GxkPopoverMenuBarItem* bar_item
);
gboolean gxk_popover_menu_bar_item_get_popover_popped(
    GxkPopoverMenuBarItem* bar_item
);
void gxk_popover_menu_bar_item_set_label(
    GxkPopoverMenuBarItem* bar_item,
    const gchar*           label
);
void gxk_popover_menu_bar_item_set_popover_popped(
    GxkPopoverMenuBarItem* bar_item,
    gboolean               pop
);

#endif
