#ifndef __GXK_MENU_ITEM_H__
#define __GXK_MENU_ITEM_H__

#include <glib.h>
#include <gtk/gtk.h>

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_MENU_ITEM (gxk_menu_item_get_type())

G_DECLARE_FINAL_TYPE(
    GxkMenuItem,
    gxk_menu_item,
    GXK,
    MENU_ITEM,
    GtkWidget
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_menu_item_new(void);
GtkWidget* gxk_menu_item_from_widget(
    GtkWidget* child
);

GtkWidget* gxk_menu_item_get_submenu(
    GxkMenuItem* menu_item
);
gboolean gxk_menu_item_get_submenu_popped(
    GxkMenuItem* menu_item
);

void gxk_menu_item_set_child(
    GxkMenuItem* menu_item,
    GtkWidget*   child
);
void gxk_menu_item_set_submenu(
    GxkMenuItem* menu_item,
    GtkWidget*   submenu
);
void gxk_menu_item_set_submenu_popped(
    GxkMenuItem* menu_item,
    gboolean     popped
);

#endif
