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
static void append_texture_aio(
    GtkSnapshot* snapshot,
    gint         x,
    gint         y,
    gint         width,
    gint         height,
    GdkTexture*  tex
);

//
// STATIC DATA
//
static const GxkThemeSlices K_SLICES = { 5, 5, 5, 5 };

static gboolean S_INIT = FALSE;

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

    // Body
    //
    append_texture_aio(
        snapshot,
        alloc.x + K_SLICES.left,
        alloc.y + K_SLICES.top,
        alloc.width - K_SLICES.left - K_SLICES.right,
        alloc.height - K_SLICES.top - K_SLICES.bottom,
        S_TEX_BUTTON[GXK_BUTTON_BOX_BODY]
    );

    // Sides
    //
    append_texture_aio(
        snapshot,
        alloc.x + K_SLICES.left,
        alloc.y,
        alloc.width - K_SLICES.left - K_SLICES.right,
        K_SLICES.top,
        S_TEX_BUTTON[GXK_BUTTON_BOX_SIDE_T]
    );
    append_texture_aio(
        snapshot,
        alloc.x + alloc.width - K_SLICES.right,
        alloc.y + K_SLICES.top,
        K_SLICES.right,
        alloc.height - K_SLICES.top - K_SLICES.bottom,
        S_TEX_BUTTON[GXK_BUTTON_BOX_SIDE_R]
    );
    append_texture_aio(
        snapshot,
        alloc.x + K_SLICES.left,
        alloc.y + alloc.height - K_SLICES.bottom,
        alloc.width - K_SLICES.left - K_SLICES.right,
        K_SLICES.bottom,
        S_TEX_BUTTON[GXK_BUTTON_BOX_SIDE_B]
    );
    append_texture_aio(
        snapshot,
        alloc.x,
        alloc.y + K_SLICES.top,
        K_SLICES.left,
        alloc.height - K_SLICES.top - K_SLICES.bottom,
        S_TEX_BUTTON[GXK_BUTTON_BOX_SIDE_L]
    );

    // Corners
    //
    append_texture_aio(
        snapshot,
        alloc.x,
        alloc.y,
        K_SLICES.left,
        K_SLICES.top,
        S_TEX_BUTTON[GXK_BUTTON_BOX_CORNER_TL]
    );
    append_texture_aio(
        snapshot,
        alloc.x + alloc.width - K_SLICES.right,
        alloc.y,
        K_SLICES.right,
        K_SLICES.top,
        S_TEX_BUTTON[GXK_BUTTON_BOX_CORNER_TR]
    );
    append_texture_aio(
        snapshot,
        alloc.x,
        alloc.y + alloc.height - K_SLICES.bottom,
        K_SLICES.left,
        K_SLICES.bottom,
        S_TEX_BUTTON[GXK_BUTTON_BOX_CORNER_BL]
    );
    append_texture_aio(
        snapshot,
        alloc.x + alloc.width - K_SLICES.right,
        alloc.y + alloc.height - K_SLICES.bottom,
        K_SLICES.right,
        K_SLICES.bottom,
        S_TEX_BUTTON[GXK_BUTTON_BOX_CORNER_BR]
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
            K_SLICES.left,
            K_SLICES.top,
            gdk_pixbuf_get_width(S_PIXBUF_SRC) - K_SLICES.left - K_SLICES.right,
            gdk_pixbuf_get_height(S_PIXBUF_SRC) - K_SLICES.top - K_SLICES.bottom
        );

    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_SIDE_T] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            K_SLICES.left,
            0,
            gdk_pixbuf_get_width(S_PIXBUF_SRC) - K_SLICES.left - K_SLICES.right,
            K_SLICES.top
        );
    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_SIDE_R] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            gdk_pixbuf_get_width(S_PIXBUF_SRC) - K_SLICES.right,
            K_SLICES.top,
            K_SLICES.right,
            gdk_pixbuf_get_height(S_PIXBUF_SRC) - K_SLICES.top - K_SLICES.bottom
        );
    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_SIDE_B] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            K_SLICES.left,
            gdk_pixbuf_get_height(S_PIXBUF_SRC) - K_SLICES.bottom,
            gdk_pixbuf_get_width(S_PIXBUF_SRC) - K_SLICES.left - K_SLICES.right,
            K_SLICES.bottom
        );
    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_SIDE_L] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            0,
            K_SLICES.top,
            K_SLICES.left,
            gdk_pixbuf_get_height(S_PIXBUF_SRC) - K_SLICES.top - K_SLICES.bottom
        );

    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_CORNER_TL] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            0,
            0,
            K_SLICES.left,
            K_SLICES.top
        );
    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_CORNER_TR] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            gdk_pixbuf_get_width(S_PIXBUF_SRC) - K_SLICES.right,
            0,
            K_SLICES.right,
            K_SLICES.top
        );
    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_CORNER_BL] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            0,
            gdk_pixbuf_get_height(S_PIXBUF_SRC) - K_SLICES.bottom,
            K_SLICES.left,
            K_SLICES.bottom
        );
    S_PIXBUF_BUTTON[GXK_BUTTON_BOX_CORNER_BR] =
        gdk_pixbuf_new_subpixbuf(
            S_PIXBUF_SRC,
            gdk_pixbuf_get_width(S_PIXBUF_SRC) - K_SLICES.right,
            gdk_pixbuf_get_height(S_PIXBUF_SRC) - K_SLICES.bottom,
            K_SLICES.right,
            K_SLICES.bottom
        );

    // Create textures
    //
    for (gint i = 0; i < GXK_BUTTON_BOX_N_PARTS; i++)
    {
        S_TEX_BUTTON[i] = gdk_texture_new_for_pixbuf(S_PIXBUF_BUTTON[i]);
    }
}

static void append_texture_aio(
    GtkSnapshot* snapshot,
    gint         x,
    gint         y,
    gint         width,
    gint         height,
    GdkTexture*  tex
)
{
    graphene_rect_t rect;

    graphene_rect_init(&rect, x, y, width, height);

    gtk_snapshot_append_texture(snapshot, tex, &rect);
}
