#include <glib.h>
#include <gtk/gtk.h>

#include "../public/popovermenu.h"

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
    GtkWidget* label;
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
    self->label = gtk_label_new("Hello world!");

    gtk_popover_set_child(
        GTK_POPOVER(self),
        self->label
    );
}

//
// CLASS VIRTUAL METHODS
//
static void gxk_popover_menu_dispose(
    GObject* object
)
{
    GxkPopoverMenu* popover = GXK_POPOVER_MENU(object);

    gtk_widget_unparent(popover->label);

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
