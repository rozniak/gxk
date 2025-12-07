#include <glib.h>
#include <gtk/gtk.h>

#include "../public/popovermenu.h"
#include "../public/menuitem.h"
#include "../public/menushell.h"

//
// FORWARD DECLARATIONS
//
static void gxk_popover_menu_menu_shell_interface_init(
    GxkMenuShellInterface* iface
);

static void gxk_popover_menu_dispose(
    GObject* object
);

static void gxk_popover_menu_append(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
);
static void gxk_popover_menu_close_open_menus(
    GxkMenuShell* menu_shell
);
static GxkMenuShellKind gxk_popover_menu_get_kind(
    GxkMenuShell* menu_shell
);
static void gxk_popover_menu_prepend(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
);
static void gxk_popover_menu_insert(
    GxkMenuShell* menu_shell,
    GtkWidget*    child,
    gint          position
);
static void gxk_popover_menu_set_active_item(
    GxkMenuShell* menu_shell,
    GxkMenuItem*  menu_item,
    gboolean      popup
);

static GtkWidget* gxk_popover_menu_make_menu_item(
    GxkPopoverMenu* menu,
    GtkWidget*      child
);

static void on_menu_item_popping_menu(
    GxkMenuItem* menu_item,
    gpointer     user_data
);

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkPopoverMenu
{
    GtkPopover __parent__;

    // UI
    //
    GxkMenuItem*  active_item;
    GxkMenuShell* active_submenu;
    GtkWidget*    box_menuitems;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE_WITH_CODE(
    GxkPopoverMenu,
    gxk_popover_menu,
    GTK_TYPE_POPOVER,
    G_IMPLEMENT_INTERFACE(
        GXK_TYPE_MENU_SHELL,
        gxk_popover_menu_menu_shell_interface_init
    )
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

    gtk_popover_set_has_arrow(
        GTK_POPOVER(self),
        FALSE
    );
    gtk_popover_set_position(
        GTK_POPOVER(self),
        GTK_POS_BOTTOM
    );
}

static void gxk_popover_menu_menu_shell_interface_init(
    GxkMenuShellInterface* iface
)
{
    iface->append           = gxk_popover_menu_append;
    iface->close_open_menus = gxk_popover_menu_close_open_menus;
    iface->get_kind         = gxk_popover_menu_get_kind;
    iface->prepend          = gxk_popover_menu_prepend;
    iface->insert           = gxk_popover_menu_insert;
    iface->set_active_item  = gxk_popover_menu_set_active_item;
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
// INTERFACE METHODS (GxkMenuShell)
//
static void gxk_popover_menu_append(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
)
{
    GxkPopoverMenu* menu = GXK_POPOVER_MENU(menu_shell);

    gtk_box_append(
        GTK_BOX(menu->box_menuitems),
        gxk_popover_menu_make_menu_item(menu, child)
    );
}

static void gxk_popover_menu_close_open_menus(
    GxkMenuShell* menu_shell
)
{
    GxkPopoverMenu* menu = GXK_POPOVER_MENU(menu_shell);

    if (!(menu->active_item) || !(menu->active_submenu))
    {
        return;
    }

    gxk_menu_item_set_submenu_popped(
        menu->active_item,
        FALSE
    );
}

static GxkMenuShellKind gxk_popover_menu_get_kind(
    GxkMenuShell* menu_shell
)
{
    return GXK_MENU_SHELL_MENU;
}

static void gxk_popover_menu_prepend(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
)
{
    GxkPopoverMenu* menu = GXK_POPOVER_MENU(menu_shell);

    gtk_box_prepend(
        GTK_BOX(menu->box_menuitems),
        gxk_popover_menu_make_menu_item(menu, child)
    );
}

static void gxk_popover_menu_insert(
    GxkMenuShell* menu_shell,
    GtkWidget*    child,
    gint          position
)
{
    GxkPopoverMenu* menu = GXK_POPOVER_MENU(menu_shell);

    GtkWidget* sibling = NULL;

    for (gint i = 0; i < position; i++)
    {
        GtkWidget* next;

        if (i == 0)
        {
            next = gtk_widget_get_first_child(menu->box_menuitems);
        }
        else
        {
            next = gtk_widget_get_next_sibling(sibling);
        }

        if (!next)
        {
            break;
        }

        sibling = next;
    }

    gtk_box_insert_child_after(
        GTK_BOX(menu->box_menuitems),
        gxk_popover_menu_make_menu_item(menu, child),
        sibling
    );
}

static void gxk_popover_menu_set_active_item(
    GxkMenuShell* menu_shell,
    GxkMenuItem*  menu_item,
    gboolean      popup
)
{
    GxkPopoverMenu* menu = GXK_POPOVER_MENU(menu_shell);

    if (menu->active_item == menu_item)
    {
        return;
    }

    if (menu->active_item)
    {
        gtk_widget_unset_state_flags(
            GTK_WIDGET(menu->active_item),
            GTK_STATE_FLAG_SELECTED
        );
    }

    menu->active_item = menu_item;

    if (menu->active_item)
    {
        gtk_widget_set_state_flags(
            GTK_WIDGET(menu->active_item),
            GTK_STATE_FLAG_SELECTED,
            FALSE
        );
    }
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

//
// PRIVATE FUNCTIONS
//
static GtkWidget* gxk_popover_menu_make_menu_item(
    GxkPopoverMenu* menu,
    GtkWidget*      child
)
{
    GtkWidget* menu_item = gxk_menu_item_from_widget(child);

    g_signal_connect(
        menu_item,
        "popping-menu",
        G_CALLBACK(on_menu_item_popping_menu),
        menu
    );

    return menu_item;
}

//
// CALLBACKS
//
static void on_menu_item_popping_menu(
    GxkMenuItem* menu_item,
    gpointer     user_data
)
{
    GxkPopoverMenu* menu = GXK_POPOVER_MENU(user_data);

    // Close existing popped menu
    //
    GtkWidget* submenu = gxk_menu_item_get_submenu(menu_item);

    if (!submenu || GXK_MENU_SHELL(submenu) != menu->active_submenu)
    {
        gxk_popover_menu_close_open_menus(GXK_MENU_SHELL(menu));
    }

    menu->active_submenu = GXK_MENU_SHELL(submenu);
}
