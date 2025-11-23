#include <glib.h>
#include <gtk/gtk.h>

#include "../public/popovermenu.h"
#include "../public/menuitem.h"

//
// FORWARD DECLARATIONS
//
static void gxk_popover_menu_dispose(
    GObject* object
);

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkPopoverMenu
{
    GtkPopover __parent__;

    // UI
    //
    GtkWidget* box_menuitems;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkPopoverMenu,
    gxk_popover_menu,
    GTK_TYPE_POPOVER
)

static void gxk_popover_menu_class_init(
    GxkPopoverMenuClass* klass
)
{
    GObjectClass* object_class = G_OBJECT_CLASS(klass);

    object_class->dispose = gxk_popover_menu_dispose;
}

static void gxk_popover_menu_init(
    GxkPopoverMenu* self
)
{
    self->box_menuitems =
        gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_popover_set_child(
        GTK_POPOVER(self),
        self->box_menuitems
    );
}

//
// CLASS VIRTUAL METHODS
//
static void gxk_popover_menu_dispose(
    GObject* object
)
{
//    GtkWidget* child;

//    while ((child = gtk_widget_get_first_child(GTK_WIDGET(object))))
//    {
//        gtk_widget_unparent(child);
//    }

    (G_OBJECT_CLASS(gxk_popover_menu_parent_class))
        ->dispose(object);
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_popover_menu_new(void)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_POPOVER_MENU,
            NULL
        )
    );
}

void gxk_popover_menu_append_child(
    GxkPopoverMenu* menu,
    GtkWidget*      child
)
{
    GtkWidget* menu_item;

    if (GXK_IS_MENU_ITEM(child))
    {
        menu_item = child;
    }
    else
    {
        menu_item = gxk_menu_item_new();

        gxk_menu_item_set_child(
            GXK_MENU_ITEM(menu_item),
            child
        );
    }

    gtk_box_append(
        GTK_BOX(menu->box_menuitems),
        menu_item
    );
}
