#include <cairo.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "application.h"
#include "shim.h"
#include "window.h"

//
// FORWARD DECLARATIONS
//
static void action_select_stuff(
    GSimpleAction* action,
    GVariant*      parameter,
    gpointer       user_data
);

static void cb_drawing_area_draw(
    GtkDrawingArea* drawing_area,
    cairo_t*        cr,
    gint            width,
    gint            height,
    gpointer        user_data
);

//
// STATIC DATA
//
static const GActionEntry S_ACTIONS[] = {
    {
        .name           = "select-stuff",
        .activate       = action_select_stuff,
        .parameter_type = NULL,
        .state          = NULL,
        .change_state   = NULL
    }
};

//
// GOBJECT CLASS/INSTANCE DEFINITIONS
//
struct _GxkDemoWindow
{
    GtkApplicationWindow __parent__;
};

//
// GOBJECT TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE(
    GxkDemoWindow,
    gxk_demo_window,
    GTK_TYPE_APPLICATION_WINDOW
)

static void gxk_demo_window_class_init(
    GXK_UNUSED(GxkDemoWindowClass* klass)
) {}

static void gxk_demo_window_init(
    GxkDemoWindow* self
)
{
    GtkBuilder* builder =
        gtk_builder_new_from_resource(
            "/uk/oddmatics/gxk/samples/demo/window.ui"
        );

    gtk_window_set_child(
        GTK_WINDOW(self),
        GTK_WIDGET(gtk_builder_get_object(builder, "main-box"))
    );
    gtk_window_set_default_size(
        GTK_WINDOW(self),
        450,
        350
    );

    gtk_drawing_area_set_draw_func(
        GTK_DRAWING_AREA(gtk_builder_get_object(builder, "drawing")),
        (GtkDrawingAreaDrawFunc) cb_drawing_area_draw,
        NULL,
        NULL
    );

    g_object_unref(builder);

    g_action_map_add_action_entries(
        G_ACTION_MAP(self),
        S_ACTIONS,
        G_N_ELEMENTS(S_ACTIONS),
        self
    );
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_demo_window_new(
    GxkDemoApplication* app
)
{
    return GTK_WIDGET(
        g_object_new(
            GXK_TYPE_DEMO_WINDOW,
            "application", GTK_APPLICATION(app),
            "title",       "GXK Demo",
            NULL
        )
    );
}

//
// CALLBACKS
//
static void action_select_stuff(
    GXK_UNUSED(GSimpleAction* action),
    GXK_UNUSED(GVariant*      parameter),
    gpointer user_data
)
{
    GtkBuilder* builder =
        gtk_builder_new_from_resource(
            "/uk/oddmatics/gxk/samples/demo/dlgstuff.ui"
        );

    GtkWidget* dialog = gtk_window_new();

    gtk_window_set_child(
        GTK_WINDOW(dialog),
        GTK_WIDGET(gtk_builder_get_object(builder, "main-box"))
    );
    gtk_window_set_transient_for(
        GTK_WINDOW(dialog),
        GTK_WINDOW(user_data)
    );

    g_object_unref(builder);

    gtk_widget_show(dialog);
}

static void cb_drawing_area_draw(
    GXK_UNUSED(GtkDrawingArea* drawing_area),
    cairo_t* cr,
    GXK_UNUSED(gint width),
    GXK_UNUSED(gint height),
    GXK_UNUSED(gpointer user_data)
)
{
    cairo_set_source_rgb(cr, 1.0f, 1.0f, 1.0f);
    cairo_paint(cr);
}
