#include <glib.h>
#include <gtk/gtk.h>

#include "../public/menubinding.h"
#include "../public/menuitem.h"
#include "../public/menushell.h"
#include "../public/popovermenu.h"
#include "../public/popovermenubar.h"

//
// PRIVATE ENUMS
//
enum
{
    PROP_NULL = 0,
    PROP_MENU_MODEL,
    N_PROPERTIES
};

//
// FORWARD DECLARATIONS
//
static void gxk_popover_menu_bar_menu_shell_interface_init(
    GxkMenuShellInterface* iface
);

static void gxk_popover_menu_bar_dispose(
    GObject* object
);
static void gxk_popover_menu_bar_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
);
static void gxk_popover_menu_bar_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
);

static void gxk_popover_menu_bar_append(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
);
static void gxk_popover_menu_bar_prepend(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
);
static void gxk_popover_menu_bar_insert(
    GxkMenuShell* menu_shell,
    GtkWidget*    child,
    gint          position
);

static void gxk_popover_menu_bar_set_active_item(
    GxkMenuShell* menu_shell,
    GxkMenuItem*  menu_item,
    gboolean      popup
);

static void on_event_leave(
    GtkEventControllerMotion* self,
    gpointer                  user_data
);
static void on_popover_unmap(
    GtkWidget* self,
    gpointer   user_data
);

//
// STATIC DATA
//
static GParamSpec* gxk_popover_menu_bar_properties[N_PROPERTIES] = { 0 };

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkPopoverMenuBar
{
    GtkWidget __parent__;

    // State
    //
    GxkMenuBinding* binding;
    GMenuModel*     model;

    GxkMenuItem* active_item;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE_WITH_CODE(
    GxkPopoverMenuBar,
    gxk_popover_menu_bar,
    GTK_TYPE_WIDGET,
    G_IMPLEMENT_INTERFACE(
        GXK_TYPE_MENU_SHELL,
        gxk_popover_menu_bar_menu_shell_interface_init
    )
)

static void gxk_popover_menu_bar_class_init(
    GxkPopoverMenuBarClass* klass
)
{
    GObjectClass*   object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    object_class->dispose      = gxk_popover_menu_bar_dispose;
    object_class->get_property = gxk_popover_menu_bar_get_property;
    object_class->set_property = gxk_popover_menu_bar_set_property;

    gxk_popover_menu_bar_properties[PROP_MENU_MODEL] =
        g_param_spec_object(
            "menu-model",
            "MenuModel",
            "The menu model to represent.",
            G_TYPE_MENU_MODEL,
            G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY
        );

    g_object_class_install_properties(
        object_class,
        N_PROPERTIES,
        gxk_popover_menu_bar_properties
    );

    gtk_widget_class_set_css_name(
        widget_class,
        "menubar"
    );
    gtk_widget_class_set_layout_manager_type(
        widget_class,
        GTK_TYPE_BOX_LAYOUT
    );
}

static void gxk_popover_menu_bar_init(
    GxkPopoverMenuBar* self
)
{
    GtkEventController* controller;

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
        "leave",
        G_CALLBACK(on_event_leave),
        NULL
    );

    gtk_widget_add_controller(GTK_WIDGET(self), controller);
}

static void gxk_popover_menu_bar_menu_shell_interface_init(
    GxkMenuShellInterface* iface
)
{
    iface->append  = gxk_popover_menu_bar_append;
    iface->prepend = gxk_popover_menu_bar_prepend;
    iface->insert  = gxk_popover_menu_bar_insert;

    iface->set_active_item = gxk_popover_menu_bar_set_active_item;
}

//
// CLASS VIRTUAL METHODS
//
static void gxk_popover_menu_bar_dispose(
    GObject* object
)
{
    GxkPopoverMenuBar* menu_bar = GXK_POPOVER_MENU_BAR(object);

    // Bin off child widgets
    //
    GtkWidget* child;

    while ((child = gtk_widget_get_first_child(GTK_WIDGET(object))))
    {
        gtk_widget_unparent(child);
    }

    // Clean up our state
    //
    g_clear_object(&(menu_bar->binding));
    g_clear_object(&(menu_bar->model));

    (G_OBJECT_CLASS(gxk_popover_menu_bar_parent_class))
        ->dispose(object);
}

static void gxk_popover_menu_bar_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
)
{
    GxkPopoverMenuBar* menu_bar = GXK_POPOVER_MENU_BAR(object);

    switch (prop_id)
    {
        case PROP_MENU_MODEL:
            g_value_set_object(value, menu_bar->model);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void gxk_popover_menu_bar_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
)
{
    GxkPopoverMenuBar* menu_bar = GXK_POPOVER_MENU_BAR(object);

    switch (prop_id)
    {
        case PROP_MENU_MODEL:
            gxk_popover_menu_bar_bind_model(
                menu_bar,
                G_MENU_MODEL(g_value_get_object(value))
            );
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

//
// INTERFACE METHODS (GxkMenuShell)
//
static void gxk_popover_menu_bar_append(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
)
{
    GtkWidget* menu_item = gxk_menu_item_from_widget(child);

    gtk_widget_insert_before(
        menu_item,
        GTK_WIDGET(menu_shell),
        NULL
    );
}

static void gxk_popover_menu_bar_prepend(
    GxkMenuShell* menu_shell,
    GtkWidget*    child
)
{
    GtkWidget* menu_item = gxk_menu_item_from_widget(child);

    gtk_widget_insert_after(
        menu_item,
        GTK_WIDGET(menu_shell),
        NULL
    );
}

static void gxk_popover_menu_bar_insert(
    GxkMenuShell* menu_shell,
    GtkWidget*    child,
    gint          position
)
{
    GtkWidget* menu_item = gxk_menu_item_from_widget(child);

    GtkWidget* sibling = gtk_widget_get_first_child(GTK_WIDGET(menu_shell));

    for (gint i = 0; i < position; i++)
    {
        sibling = gtk_widget_get_next_sibling(sibling);

        if (!sibling)
        {
            break;
        }
    }

    gtk_widget_insert_before(
        menu_item,
        GTK_WIDGET(menu_shell),
        sibling
    );
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_popover_menu_bar_new_from_model(
    GMenuModel* menu_model
)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_POPOVER_MENU_BAR,
            "menu-model", menu_model,
            NULL
        )
    );
}

void gxk_popover_menu_bar_bind_model(
    GxkPopoverMenuBar* menu_bar,
    GMenuModel*        menu_model
)
{
    // FIXME: Clear out old menu model first
    if (menu_bar->binding || menu_bar->model)
    {
        g_critical("%s", "gxk: menubar: need to clear out existing model!!");
        return;
    }

    // FIXME: This is temp stuff!
    //
    menu_bar->model = g_object_ref(menu_model);

    menu_bar->binding =
        gxk_menu_binding_new(
            GXK_MENU_SHELL(menu_bar),
            menu_model
        );
}

//
// INTERNAL FUNCTIONS
//
static void gxk_popover_menu_bar_set_active_item(
    GxkMenuShell* menu_shell,
    GxkMenuItem*  menu_item,
    gboolean      popup
)
{
    GxkPopoverMenuBar* menu_bar = GXK_POPOVER_MENU_BAR(menu_shell);

    gboolean changed      = menu_bar->active_item != menu_item;
    gboolean popup_active = FALSE;

    g_message("%s", "Enter");

    if (menu_bar->active_item)
    {
        popup_active =
            gxk_menu_item_get_submenu_popped(
                menu_bar->active_item
            );
    }

    if (changed && popup_active)
    {
        gxk_menu_item_set_submenu_popped(
            menu_bar->active_item,
            FALSE
        );
    }

    if (changed)
    {
        if (menu_bar->active_item)
        {
            gtk_widget_unset_state_flags(
                GTK_WIDGET(menu_bar->active_item),
                GTK_STATE_FLAG_SELECTED
            );
        }

        menu_bar->active_item = menu_item;

        if (menu_bar->active_item)
        {
            gtk_widget_set_state_flags(
                GTK_WIDGET(menu_item),
                GTK_STATE_FLAG_SELECTED,
                FALSE
            );
        }
    }

    if (menu_bar->active_item)
    {
        GtkStateFlags state =
            gtk_widget_get_state_flags(GTK_WIDGET(menu_bar));

        if (popup || (changed && popup_active))
        {
            gxk_menu_item_set_submenu_popped(
                menu_bar->active_item,
                TRUE
            );
        }
        else if (changed && (state & GTK_STATE_FLAG_FOCUS_WITHIN))
        {
            gtk_widget_grab_focus(GTK_WIDGET(menu_bar->active_item));
        }
    }
}

//
// CALLBACKS
//
static void on_event_leave(
    GtkEventControllerMotion* self,
    gpointer                  user_data
)
{
    GxkPopoverMenuBar* menu_bar =
        GXK_POPOVER_MENU_BAR(
            gtk_event_controller_get_widget(
                GTK_EVENT_CONTROLLER(self)
            )
        );

    if (
        menu_bar->active_item &&
        !gxk_menu_item_get_submenu_popped(
            menu_bar->active_item
        )
    )
    {
        gxk_popover_menu_bar_set_active_item(
            GXK_MENU_SHELL(menu_bar),
            NULL,
            FALSE
        );
    }
}

/*
static void on_popover_unmap(
    GtkWidget* self,
    gpointer   user_data
)
{
    GxkPopoverMenuBar* menu_bar = GXK_POPOVER_MENU_BAR(user_data);

    if (
        menu_bar->active_item &&
        gxk_popover_menu_bar_item_get_popover(menu_bar->active_item) == self
    )
    {
        gxk_popover_menu_bar_set_active_item(
            menu_bar,
            NULL,
            FALSE
        );
    }
}
*/
