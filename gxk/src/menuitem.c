#include <glib.h>
#include <gtk/gtk.h>

#include "../public/menuitem.h"
#include "../public/menushell.h"
#include "../public/popovermenu.h"

//
// FORWARD DECLARATIONS
//
static void gxk_menu_item_dispose(
    GObject* object
);

static void on_event_enter(
    GtkEventControllerMotion* self,
    gdouble                   x,
    gdouble                   y,
    gpointer                  user_data
);
static void on_event_pressed(
    GtkGestureClick* self,
    gint             n_press,
    gdouble          x,
    gdouble          y,
    gpointer         user_data
);

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkMenuItem
{
    GtkWidget __parent__;

    // UI
    //
    GtkWidget* popover;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkMenuItem,
    gxk_menu_item,
    GTK_TYPE_WIDGET
)

static void gxk_menu_item_class_init(
    GxkMenuItemClass* klass
)
{
    GObjectClass*   object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    object_class->dispose = gxk_menu_item_dispose;

    gtk_widget_class_set_css_name(
        widget_class,
        "item"
    );
    gtk_widget_class_set_layout_manager_type(
        widget_class,
        GTK_TYPE_BIN_LAYOUT
    );
}

static void gxk_menu_item_init(
    GxkMenuItem* self
)
{
    GtkEventController* controller;

    gtk_widget_set_focusable(GTK_WIDGET(self), TRUE);

    // Clicked event
    //
    controller =
        GTK_EVENT_CONTROLLER(gtk_gesture_click_new());

    g_signal_connect(
        controller,
        "pressed",
        G_CALLBACK(on_event_pressed),
        NULL
    );

    gtk_widget_add_controller(
        GTK_WIDGET(self),
        controller
    );

    // Motion event
    //
    controller =
        GTK_EVENT_CONTROLLER(gtk_event_controller_motion_new());

    gtk_event_controller_set_propagation_limit(
        controller,
        GTK_LIMIT_NONE
    );

    g_signal_connect(
        controller,
        "enter",
        G_CALLBACK(on_event_enter),
        NULL
    );

    gtk_widget_add_controller(
        GTK_WIDGET(self),
        controller
    );
}

//
// CLASS VIRTUAL METHODS
//
static void gxk_menu_item_dispose(
    GObject* object
)
{
    GtkWidget* child = gtk_widget_get_first_child(GTK_WIDGET(object));

    if (child)
    {
        gtk_widget_unparent(child);
    }

    (G_OBJECT_CLASS(gxk_menu_item_parent_class))
        ->dispose(object);
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_menu_item_new(void)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_MENU_ITEM,
            NULL
        )
    );
}

GtkWidget* gxk_menu_item_from_widget(
    GtkWidget* child
)
{
    if (GXK_IS_MENU_ITEM(child))
    {
        return child;
    }

    GtkWidget* menu_item = gxk_menu_item_new();

    gxk_menu_item_set_child(
        GXK_MENU_ITEM(menu_item),
        child
    );

    return menu_item;
}

gboolean gxk_menu_item_get_submenu_popped(
    GxkMenuItem* menu_item
)
{
    return gtk_widget_get_mapped(menu_item->popover);
}

void gxk_menu_item_set_child(
    GxkMenuItem* menu_item,
    GtkWidget*   child
)
{
    // FIXME: Handle existing child
    //
    if (gtk_widget_get_first_child(GTK_WIDGET(menu_item)))
    {
        g_critical("%s", "gxk: menu item already has a child");
        return;
    }

    gtk_widget_set_parent(
        child,
        GTK_WIDGET(menu_item)
    );
}

void gxk_menu_item_set_submenu(
    GxkMenuItem* menu_item,
    GtkWidget*   submenu
)
{
    // FIXME: Handle existing menu
    //
    if (menu_item->popover)
    {
        g_critical("%s", "gxk: menu item already has a submenu");
        return;
    }

    if (GTK_IS_POPOVER(submenu))
    {
        menu_item->popover = submenu;
    }
    else
    {
        menu_item->popover = gxk_popover_menu_new();

        gxk_menu_shell_append(
            GXK_MENU_SHELL(menu_item->popover),
            submenu
        );
    }

    gtk_widget_set_parent(
        menu_item->popover,
        GTK_WIDGET(menu_item)
    );
}

void gxk_menu_item_set_submenu_popped(
    GxkMenuItem* menu_item,
    gboolean     popped
)
{
    if (!menu_item->popover)
    {
        return;
    }

    if (popped)
    {
        gtk_popover_popup(
            GTK_POPOVER(menu_item->popover)
        );
    }
    else
    {
        gtk_popover_popdown(
            GTK_POPOVER(menu_item->popover)
        );
    }
}

//
// CALLBACKS
//
static void on_event_enter(
    GtkEventControllerMotion* self,
    gdouble                   x,
    gdouble                   y,
    gpointer                  user_data
)
{
    GtkEventController* controller = GTK_EVENT_CONTROLLER(self);

    GxkMenuItem* menu_item =
        GXK_MENU_ITEM(
            gtk_event_controller_get_widget(controller)
        );
    GxkMenuShell* menu_shell =
        GXK_MENU_SHELL(
            gtk_widget_get_ancestor(
                GTK_WIDGET(menu_item),
                GXK_TYPE_MENU_SHELL
            )
        );

    gxk_menu_shell_set_active_item(
        menu_shell,
        menu_item,
        FALSE
    );
}

static void on_event_pressed(
    GtkGestureClick* self,
    gint             n_press,
    gdouble          x,
    gdouble          y,
    gpointer         user_data
)
{
    GtkEventController* controller = GTK_EVENT_CONTROLLER(self);

    GxkMenuItem* menu_item =
        GXK_MENU_ITEM(
            gtk_event_controller_get_widget(controller)
        );
    GxkMenuShell* menu_shell =
        GXK_MENU_SHELL(
            gtk_widget_get_ancestor(
                GTK_WIDGET(menu_item),
                GXK_TYPE_MENU_SHELL
            )
        );

    gxk_menu_shell_set_active_item(
        menu_shell,
        menu_item,
        TRUE
    );
}
