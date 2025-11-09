#include <glib.h>
#include <gtk/gtk.h>

#include "../public/popovermenubar.h"
#include "popovermenubar-int.h"
#include "popovermenubaritem.h"

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
    GMenuModel* model;

    GxkPopoverMenuBarItem* active_item;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkPopoverMenuBar,
    gxk_popover_menu_bar,
    GTK_TYPE_WIDGET
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
) {}

//
// CLASS VIRTUAL METHODS
//
static void gxk_popover_menu_bar_dispose(
    GObject* object
)
{
    GtkWidget* child;

    while ((child = gtk_widget_get_first_child(GTK_WIDGET(object))))
    {
        gtk_widget_unparent(child);
    }

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
    if (menu_bar->model)
    {
        g_critical("%s", "gxk: menubar: need to clear out existing model!!");
        return;
    }

    // FIXME: This is temp stuff!
    //
    menu_bar->model = g_object_ref(menu_model);

    gint n_items = g_menu_model_get_n_items(menu_model);

    for (gint i = 0; i < n_items; i++)
    {
        gchar* text = NULL;

        g_menu_model_get_item_attribute(
            menu_model,
            i,
            G_MENU_ATTRIBUTE_LABEL,
            "s",
            &text
        );

        GtkWidget* bar_item = gxk_popover_menu_bar_item_new();

        gxk_popover_menu_bar_item_set_label(
            GXK_POPOVER_MENU_BAR_ITEM(bar_item),
            text
        );

        gtk_widget_set_parent(bar_item, GTK_WIDGET(menu_bar));

        g_free(text);
    }
}

//
// INTERNAL FUNCTIONS
//
void gxk_popover_menu_bar_set_active_item(
    GxkPopoverMenuBar*     menu_bar,
    GxkPopoverMenuBarItem* bar_item
)
{
    gboolean changed = menu_bar->active_item != bar_item;

    if (!changed)
    {
        return;
    }

    if (menu_bar->active_item)
    {
        gtk_widget_unset_state_flags(
            GTK_WIDGET(menu_bar->active_item),
            GTK_STATE_FLAG_SELECTED
        );
    }

    menu_bar->active_item = bar_item;

    if (menu_bar->active_item)
    {
        gtk_widget_set_state_flags(
            GTK_WIDGET(bar_item),
            GTK_STATE_FLAG_SELECTED,
            FALSE
        );
    }
}
