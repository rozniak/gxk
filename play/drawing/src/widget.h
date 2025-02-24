#ifndef __WIDGET_H__
#define __WIDGET_H__

//
// GOBJECT BOILERPLATE
//
#define GXK_TYPE_CUSTOM_WIDGET (gxk_custom_widget_get_type())

G_DECLARE_FINAL_TYPE(
    GxkCustomWidget,
    gxk_custom_widget,
    GXK,
    CUSTOM_WIDGET,
    GtkWidget
)

//
// PUBLIC FUNCTIONS
//
GtkWidget* gxk_custom_widget_new(void);

#endif
