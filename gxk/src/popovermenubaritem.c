#include <glib.h>
#include <gtk/gtk.h>

#include "popovermenubaritem.h"

//
// PRIVATE ENUMS
//
enum
{
    PROP_NULL = 0,
    PROP_LABEL,
    N_PROPERTIES
};

//
// FORWARD DECLARATIONS
//
static void gxk_popover_menu_bar_item_dispose(
    GObject* object
);
static void gxk_popover_menu_bar_item_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
);
static void gxk_popover_menu_bar_item_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
);

//
// STATIC DATA
//
static GParamSpec* gxk_popover_menu_bar_item_properties[N_PROPERTIES] = { 0 };

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkPopoverMenuBarItem
{
    GtkWidget __parent__;

    // UI
    //
    GtkWidget* label;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkPopoverMenuBarItem,
    gxk_popover_menu_bar_item,
    GTK_TYPE_WIDGET
)

static void gxk_popover_menu_bar_item_class_init(
    GxkPopoverMenuBarItemClass* klass
)
{
    GObjectClass*   object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    object_class->dispose      = gxk_popover_menu_bar_item_dispose;
    object_class->get_property = gxk_popover_menu_bar_item_get_property;
    object_class->set_property = gxk_popover_menu_bar_item_set_property;

    gxk_popover_menu_bar_item_properties[PROP_LABEL] =
        g_param_spec_object(
            "label",
            "Label",
            "The text to display on the menu item",
            GTK_TYPE_LABEL,
            G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY
        );

    g_object_class_install_properties(
        object_class,
        N_PROPERTIES,
        gxk_popover_menu_bar_item_properties
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

static void gxk_popover_menu_bar_item_init(
    GxkPopoverMenuBarItem* self
)
{
    self->label = gtk_label_new(NULL);

    gtk_widget_set_parent(
        self->label,
        GTK_WIDGET(self)
    );
}

//
// CLASS VIRTUAL METHODS
//
static void gxk_popover_menu_bar_item_dispose(
    GObject* object
)
{
    GxkPopoverMenuBarItem* bar_item = GXK_POPOVER_MENU_BAR_ITEM(object);

    gtk_widget_unparent(bar_item->label);

    (G_OBJECT_CLASS(gxk_popover_menu_bar_item_parent_class))
        ->dispose(object);
}

static void gxk_popover_menu_bar_item_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
)
{
    GxkPopoverMenuBarItem* bar_item = GXK_POPOVER_MENU_BAR_ITEM(object);

    switch (prop_id)
    {
        case PROP_LABEL:
            g_value_set_string(
                value,
                gtk_label_get_text(GTK_LABEL(bar_item->label))
            );
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void gxk_popover_menu_bar_item_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
)
{
    GxkPopoverMenuBarItem* bar_item = GXK_POPOVER_MENU_BAR_ITEM(object);

    switch (prop_id)
    {
        case PROP_LABEL:
            gxk_popover_menu_bar_item_set_label(
                bar_item,
                g_value_get_string(value)
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
GtkWidget* gxk_popover_menu_bar_item_new(void)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_POPOVER_MENU_BAR_ITEM,
            NULL
        )
    );
}

void gxk_popover_menu_bar_item_set_label(
    GxkPopoverMenuBarItem* bar_item,
    const gchar*           label
)
{
    gtk_label_set_text(GTK_LABEL(bar_item->label), label);

    g_object_notify_by_pspec(
        G_OBJECT(bar_item),
        gxk_popover_menu_bar_item_properties[PROP_LABEL]
    );
}
