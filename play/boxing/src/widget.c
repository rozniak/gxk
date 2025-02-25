#include <glib.h>
#include <graphene.h>
#include <gtk/gtk.h>

#include "widget.h"

//
// PRIVATE ENUMS
//
typedef enum
{
    GXK_BUTTON_BOX_BODY = 0,
    GXK_BUTTON_BOX_SIDE_B,
    GXK_BUTTON_BOX_SIDE_L,
    GXK_BUTTON_BOX_SIDE_R,
    GXK_BUTTON_BOX_SIDE_T,
    GXK_BUTTON_BOX_CORNER_BL,
    GXK_BUTTON_BOX_CORNER_BR,
    GXK_BUTTON_BOX_CORNER_TL,
    GXK_BUTTON_BOX_CORNER_TR,

    GXK_BUTTON_BOX_N_PARTS
} GxkButtonBoxPart;

//
// PRIVATE STRUCTURES
//
typedef struct
{
    gint top;
    gint right;
    gint bottom;
    gint left;
} GxkThemeSlices;

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

static void init_button_slices();

//
// STATIC DATA
//
static gboolean    S_INIT = FALSE;

static GdkPixbuf*  S_PIXBUF_SRC = NULL;
static GdkPixbuf*  S_PIXBUF_BUTTON[GXK_BUTTON_BOX_N_PARTS];
static GdkTexture* S_TEX_BUTTON[GXK_BUTTON_BOX_N_PARTS];

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
)
{
    if (!S_INIT)
    {
        init_button_slices();
        S_INIT = TRUE;
    }
}

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

    // Draw button
    //
    graphene_rect_t rect;

    graphene_rect_init(
        &rect,
        alloc.x,
        alloc.y,
        alloc.width,
        alloc.height
    );

    gtk_snapshot_append_texture(
        snapshot,
        S_TEX_BUTTON[GXK_BUTTON_BOX_BODY],
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

//
// PRIVATE FUNCTIONS
//
static void init_button_slices()
{
    // Hard coded slices - 5px a side
    //
    GxkThemeSlices slices = { 5, 5, 5, 5 };

    // Load the main image
    //
    S_PIXBUF_SRC =
        gdk_pixbuf_new_from_resource(
            "/uk/oddmatics/gxk/samples/boxing/button.png",
            NULL // Ignore errors for the time being
        );

    // Slice the image up
    //
    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_BODY] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            slices.left,
            slices.top,
            gdk_pixbuf_get_width(S_PIXBUF_SRC) - slices.left - slices.right,
            gdk_pixbuf_get_height(S_PIXBUF_SRC) - slices.top - slices.bottom
        );

    // Create textures
    //
    S_TEX_BUTTON[GXK_BUTTON_BOX_BODY] =
        gdk_texture_new_for_pixbuf(S_PIXBUF_BUTTON[GXK_BUTTON_BOX_BODY]);
}
