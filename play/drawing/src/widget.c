#include <glib.h>
#include <graphene.h>
#include <gtk/gtk.h>

#include "widget.h"

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkCustomWidget
{
    GtkWidget __parent__;
};

//
// FORWARD DECLARATIONS
//
static void gxk_custom_widget_measure(
    GtkWidget*     widget,
    GtkOrientation orientation,
    int            for_size,
    int*           minimum,
    int*           natural,
    int*           minimum_baseline,
    int*           natural_baseline
);
static void gxk_custom_widget_snapshot(
    GtkWidget*   widget,
    GtkSnapshot* snapshot
);

//
// GOBJECT TYPE DEFINITIONS & CTORS
//
G_DEFINE_TYPE(
    GxkCustomWidget,
    gxk_custom_widget,
    GTK_TYPE_WIDGET
)

static void gxk_custom_widget_class_init(
    GxkCustomWidgetClass* klass
)
{
    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    widget_class->measure  = gxk_custom_widget_measure;
    widget_class->snapshot = gxk_custom_widget_snapshot;
}

static void gxk_custom_widget_init(
    GxkCustomWidget* self
) {}

//
// CLASS VIRTUAL METHODS
//
static void gxk_custom_widget_measure(
    GtkWidget*     widget,
    GtkOrientation orientation,
    int            for_size,
    int*           minimum,
    int*           natural,
    int*           minimum_baseline,
    int*           natural_baseline
)
{
    *minimum = 64;
    *natural = 64;
}

static void gxk_custom_widget_snapshot(
    GtkWidget*   widget,
    GtkSnapshot* snapshot
)
{
    GtkAllocation alloc;

    gtk_widget_get_allocation(widget, &alloc);

    // Fill entire rect
    //
    graphene_rect_t rect;
    GdkRGBA         rgba = { 1.0, 0.0, 0.0, 1.0 };

    graphene_rect_init(&rect, alloc.x, alloc.y, alloc.width, alloc.height);

    gtk_snapshot_append_color(
        snapshot,
        &rgba,
        &rect
    );

    // Draw smiley face
    //
    GdkTexture* tex =
        gdk_texture_new_from_resource(
            "/uk/oddmatics/gxk/samples/drawing/smile.png"
        );

    gint x = (alloc.width  / 2) - 32;
    gint y = (alloc.height / 2) - 32;

    graphene_rect_init(&rect, x, y, 64, 64);

    gtk_snapshot_append_texture(
        snapshot,
        tex,
        &rect
    );
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_custom_widget_new(void)
{
    return GTK_WIDGET(
        g_object_new(GXK_TYPE_CUSTOM_WIDGET, NULL)
    );
}
