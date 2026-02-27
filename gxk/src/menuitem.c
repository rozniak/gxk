#include <glib.h>
#include <gtk/gtk.h>

#include "../public/menuitem.h"
#include "../public/menushell.h"
#include "../public/popovermenu.h"

//
// PRIVATE ENUMS
//
enum
{
    SIGNAL_POPPING_MENU = 0,
    N_SIGNALS
};

enum
{
    PROP_ACTION_NAME = 1,
    PROP_ACTION_TARGET
};

//
// FORWARD DECLARATIONS
//
static void gxk_menu_item_actionable_interface_init(
    GtkActionableInterface* iface
);

static void gxk_menu_item_dispose(
    GObject* object
);
static void gxk_menu_item_finalize(
    GObject* object
);
static void gxk_menu_item_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
);
static void gxk_menu_item_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
);

static const gchar* gxk_menu_item_get_action_name(
    GtkActionable* actionable
);
static void gxk_menu_item_set_action_name(
    GtkActionable* actionable,
    const gchar*   action_name
);
static GVariant* gxk_menu_item_get_action_target_value(
    GtkActionable* actionable
);
static void gxk_menu_item_set_action_target_value(
    GtkActionable* actionable,
    GVariant*      target_value
);

static void gxk_menu_item_open_submenu(
    GxkMenuItem* menu_item
);

static void on_event_contains_pointer(
    GObject*    self,
    GParamSpec* pspec,
    gpointer    user_data
);
static void on_event_pressed(
    GtkGestureClick* self,
    gint             n_press,
    gdouble          x,
    gdouble          y,
    gpointer         user_data
);

//
// STATIC DATA
//
static gint gxk_menu_item_signals[N_SIGNALS] = { 0 };

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkMenuItem
{
    GtkWidget __parent__;

    // UI
    //
    GtkWidget* popover;

    // GtkActionable
    //
    gchar*    action_name;
    GVariant* action_value;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE_WITH_CODE(
    GxkMenuItem,
    gxk_menu_item,
    GTK_TYPE_WIDGET,
    G_IMPLEMENT_INTERFACE(
        GTK_TYPE_ACTIONABLE,
        gxk_menu_item_actionable_interface_init
    )
)

static void gxk_menu_item_class_init(
    GxkMenuItemClass* klass
)
{
    GObjectClass*   object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    object_class->dispose      = gxk_menu_item_dispose;
    object_class->finalize     = gxk_menu_item_finalize;
    object_class->get_property = gxk_menu_item_get_property;
    object_class->set_property = gxk_menu_item_set_property;

    gxk_menu_item_signals[SIGNAL_POPPING_MENU] =
        g_signal_new(
            "popping-menu",
            G_TYPE_FROM_CLASS(object_class),
            G_SIGNAL_RUN_FIRST,
            0,
            NULL,
            NULL,
            g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,
            0
        );

    g_object_class_override_property(
        object_class,
        PROP_ACTION_NAME,
        "action-name"
    );
    g_object_class_override_property(
        object_class,
        PROP_ACTION_TARGET,
        "action-target"
    );

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
        "notify::contains-pointer",
        G_CALLBACK(on_event_contains_pointer),
        NULL
    );

    gtk_widget_add_controller(
        GTK_WIDGET(self),
        controller
    );
}

static void gxk_menu_item_actionable_interface_init(
    GtkActionableInterface* iface
)
{
    iface->get_action_name         = gxk_menu_item_get_action_name;
    iface->set_action_name         = gxk_menu_item_set_action_name;
    iface->get_action_target_value = gxk_menu_item_get_action_target_value;
    iface->set_action_target_value = gxk_menu_item_set_action_target_value;
}

//
// CLASS VIRTUAL METHODS
//
static void gxk_menu_item_dispose(
    GObject* object
)
{
    GxkMenuItem* menu_item = GXK_MENU_ITEM(object);

    GtkWidget* child = gtk_widget_get_first_child(GTK_WIDGET(object));

    if (child)
    {
        gtk_widget_unparent(child);
    }

    if (menu_item->action_value)
    {
        g_variant_unref(menu_item->action_value);
        menu_item->action_value = NULL;
    }

    (G_OBJECT_CLASS(gxk_menu_item_parent_class))
        ->dispose(object);
}

static void gxk_menu_item_finalize(
    GObject* object
)
{
    GxkMenuItem* menu_item = GXK_MENU_ITEM(object);

    g_clear_pointer(
        &(menu_item->action_name),
        (GDestroyNotify) g_free
    );

    (G_OBJECT_CLASS(gxk_menu_item_parent_class))
        ->finalize(object);
}

static void gxk_menu_item_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
)
{
    GxkMenuItem* menu_item = GXK_MENU_ITEM(object);

    switch (prop_id)
    {
        case PROP_ACTION_NAME:
            g_value_set_string(value, menu_item->action_name);
            break;

        case PROP_ACTION_TARGET:
            g_value_set_variant(value, menu_item->action_value);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void gxk_menu_item_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
)
{
    switch (prop_id)
    {
        case PROP_ACTION_NAME:
            gxk_menu_item_set_action_name(
                GTK_ACTIONABLE(object),
                g_value_get_string(value)
            );
            break;

        case PROP_ACTION_TARGET:
            gxk_menu_item_set_action_target_value(
                GTK_ACTIONABLE(object),
                g_value_get_variant(value)
            );
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

//
// INTERFACE METHODS (GtkActionable)
//
static const gchar* gxk_menu_item_get_action_name(
    GtkActionable* actionable
)
{
    return (GXK_MENU_ITEM(actionable))->action_name;
}

static void gxk_menu_item_set_action_name(
    GtkActionable* actionable,
    const gchar*   action_name
)
{
    GxkMenuItem* menu_item = GXK_MENU_ITEM(actionable);

    g_clear_pointer(
        &(menu_item->action_name),
        (GDestroyNotify) g_free
    );

    menu_item->action_name = g_strdup(action_name);
}

static GVariant* gxk_menu_item_get_action_target_value(
    GtkActionable* actionable
)
{
    return (GXK_MENU_ITEM(actionable))->action_value;
}

static void gxk_menu_item_set_action_target_value(
    GtkActionable* actionable,
    GVariant*      target_value
)
{
    GxkMenuItem* menu_item = GXK_MENU_ITEM(actionable);

    if (menu_item->action_value)
    {
        g_variant_unref(menu_item->action_value);
        menu_item->action_value = NULL;
    }

    if (target_value)
    {
        menu_item->action_value = g_variant_ref_sink(target_value);
    }
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

GtkWidget* gxk_menu_item_get_submenu(
    GxkMenuItem* menu_item
)
{
    return menu_item->popover;
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
        if (!GXK_IS_MENU_SHELL(submenu))
        {
            g_critical(
                "%s",
                "gxk: menu item submenu is a popover but not a menu shell"
            );
            return;
        }

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
    if (popped)
    {
        g_signal_emit(
            menu_item,
            gxk_menu_item_signals[SIGNAL_POPPING_MENU],
            0
        );
    }

    if (!menu_item->popover)
    {
        return;
    }

    // Set the popover direction if needed
    //
    GtkWidget* parent_shell =
        gtk_widget_get_ancestor(
            GTK_WIDGET(menu_item),
            GXK_TYPE_MENU_SHELL
        );

    if (parent_shell)
    {
        if (
            gxk_menu_shell_get_kind(GXK_MENU_SHELL(parent_shell))
                == GXK_MENU_SHELL_MENU_BAR
        )
        {
            gtk_popover_set_position(
                GTK_POPOVER(menu_item->popover),
                GTK_POS_BOTTOM
            );
        }
        else
        {
            gtk_popover_set_position(
                GTK_POPOVER(menu_item->popover),
                GTK_POS_RIGHT
            );
        }
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
static void on_event_contains_pointer(
    GObject*    self,
    GParamSpec* pspec,
    gpointer    user_data
)
{
    GtkEventControllerMotion* controller =
        GTK_EVENT_CONTROLLER_MOTION(self);

    GxkMenuItem* menu_item =
        GXK_MENU_ITEM(
            gtk_event_controller_get_widget(
                GTK_EVENT_CONTROLLER(controller)
            )
        );
    GxkMenuShell* menu_shell =
        GXK_MENU_SHELL(
            gtk_widget_get_ancestor(
                GTK_WIDGET(menu_item),
                GXK_TYPE_MENU_SHELL
            )
        );

    if (gtk_event_controller_motion_contains_pointer(controller))
    {
        if (gxk_menu_shell_get_kind(menu_shell) == GXK_MENU_SHELL_MENU)
        {
            gxk_menu_item_set_submenu_popped(menu_item, TRUE);
        }

        gxk_menu_shell_set_active_item(
            menu_shell,
            menu_item,
            FALSE
        );
    }
    else
    {
        if (menu_item->popover)
        {
            gxk_menu_shell_set_active_item(
                GXK_MENU_SHELL(menu_item->popover),
                NULL,
                FALSE
            );
        }
    }
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

    if (menu_item->action_name)
    {
        gtk_widget_activate_action_variant(
            GTK_WIDGET(menu_item),
            menu_item->action_name,
            menu_item->action_value
        );
    }
}
