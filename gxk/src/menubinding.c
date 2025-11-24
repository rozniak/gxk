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
    PROP_MENU_SHELL = 1,
    PROP_MENU_MODEL
};

//
// PRIVATE STRUCTURES
//
typedef struct _GxkMenuBindingMenu
{
    GxkMenuBinding* menu_binding;

    GxkMenuShell* menu_shell;
    GMenuModel*   menu_model;

    GList* sections;

    gulong sigid_items_changed;
} GxkMenuBindingMenu;

typedef struct _GxkMenuBindingSection
{
    GxkMenuBindingMenu* parent_menu;

    GMenuModel* menu_model;
    gint        item_count;
} GxkMenuBindingSection;

//
// FORWARD DECLARATIONS
//
static void gxk_menu_binding_constructed(
    GObject* object
);
static void gxk_menu_binding_dispose(
    GObject* object
);
static void gxk_menu_binding_finalize(
    GObject* object
);
static void gxk_menu_binding_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
);
static void gxk_menu_binding_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
);

static GList* gxk_menu_binding_find_section_pos(
    GxkMenuBindingMenu* menu,
    gint                     dst_pos,
    gint*                    mid_pos
);
static void gxk_menu_binding_insert_item(
    GxkMenuBindingMenu* menu,
    GMenuModel*	             menu_model,
    gint                     src_pos,
    gint                     dst_pos
);
static void gxk_menu_binding_remove_item(
    GxkMenuBindingMenu* menu,
    GMenuModel*              menu_model,
    gint                     src_pos
);
static void gxk_menu_binding_track_menu(
    GxkMenuBinding* menu_binding,
    GxkMenuShell*   menu_shell,
    GMenuModel*     menu_model
);

static void gxk_menu_binding_menu_free(
    GxkMenuBindingMenu* menu
);

static void on_menu_model_menu_items_changed(
    GMenuModel* model,
    gint        position,
    gint        removed,
    gint        added,
    gpointer    user_data
);

//
// GTK OOP CLASS/INSTANCE DEFINITIONS
//
typedef struct _GxkMenuBinding
{
    GObject __parent__;

    GxkMenuShell* menu_shell;
    GMenuModel*   menu_model;

    GSList* tracked_menus;
} GxkMenuBinding;

//
// GTK TYPE DEFINITIONS & CTORS
//
G_DEFINE_TYPE(
    GxkMenuBinding,
    gxk_menu_binding,
    G_TYPE_OBJECT
)

static void gxk_menu_binding_class_init(
    GxkMenuBindingClass* klass
)
{
    GObjectClass* object_class = G_OBJECT_CLASS(klass);

    object_class->constructed  = gxk_menu_binding_constructed;
    object_class->dispose      = gxk_menu_binding_dispose;
    object_class->finalize     = gxk_menu_binding_finalize;
    object_class->get_property = gxk_menu_binding_get_property;
    object_class->set_property = gxk_menu_binding_set_property;

    g_object_class_install_property(
        object_class,
        PROP_MENU_SHELL,
        g_param_spec_object(
            "menu-shell",
            "MenuShell",
            "The GXK menu shell to manage.",
            GXK_TYPE_MENU_SHELL,
            G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY
        )
    );
    g_object_class_install_property(
        object_class,
        PROP_MENU_MODEL,
        g_param_spec_object(
            "menu-model",
            "MenuModel",
            "The menu model to bind to.",
            G_TYPE_MENU_MODEL,
            G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY
        )
    );
}

static void gxk_menu_binding_init(
    GxkMenuBinding* self
) {}

//
// CLASS VIRTUAL METHODS
//
static void gxk_menu_binding_constructed(
    GObject* object
)
{
    GxkMenuBinding* menu_binding = GXK_MENU_BINDING(object);

    // FIXME: Clear the menu bar first

    gxk_menu_binding_track_menu(
        menu_binding,
        menu_binding->menu_shell,
        menu_binding->menu_model
    );

    (G_OBJECT_CLASS(gxk_menu_binding_parent_class))
        ->constructed(object);
}

static void gxk_menu_binding_dispose(
    GObject* object
)
{
    GxkMenuBinding* menu_binding = GXK_MENU_BINDING(object);

    g_clear_object(&(menu_binding->menu_shell));
    g_clear_object(&(menu_binding->menu_model));

    (G_OBJECT_CLASS(gxk_menu_binding_parent_class))
        ->dispose(object);
}

static void gxk_menu_binding_finalize(
    GObject* object
)
{
    GxkMenuBinding* menu_binding = GXK_MENU_BINDING(object);

    g_clear_slist(
        &(menu_binding->tracked_menus),
        (GDestroyNotify) gxk_menu_binding_menu_free
    );

    (G_OBJECT_CLASS(gxk_menu_binding_parent_class))
        ->finalize(object);
}

static void gxk_menu_binding_get_property(
    GObject*    object,
    guint       prop_id,
    GValue*     value,
    GParamSpec* pspec
)
{
    switch (prop_id)
    {
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void gxk_menu_binding_set_property(
    GObject*      object,
    guint         prop_id,
    const GValue* value,
    GParamSpec*   pspec
)
{
    GxkMenuBinding* menu_binding = GXK_MENU_BINDING(object);

    switch (prop_id)
    {
        case PROP_MENU_SHELL:
            menu_binding->menu_shell =
                g_value_dup_object(value);

            break;

        case PROP_MENU_MODEL:
            menu_binding->menu_model =
                g_value_dup_object(value);

            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

//
// PUBLIC FUNCTIONS
//
GxkMenuBinding* gxk_menu_binding_new(
    GxkMenuShell* menu_shell,
    GMenuModel*   menu_model
)
{
    return GXK_MENU_BINDING(
        g_object_new(
            GXK_TYPE_MENU_BINDING,
            "menu-shell", menu_shell,
            "menu-model", menu_model,
            NULL
        )
    );
}

//
// PRIVATE FUNCTIONS
//
static GList* gxk_menu_binding_find_section_pos(
    GxkMenuBindingMenu* menu,
    gint                     dst_pos,
    gint*                    mid_pos
)
{
    gint   i    = 0;
    GList* iter = menu->sections;

    if (!iter)
    {
        *mid_pos = 0;
        return NULL;
    }

    for (; iter; iter = iter->next)
    {
        GxkMenuBindingSection* section =
            (GxkMenuBindingSection*) iter->data;

        // Have we hit our target?
        //
        if (i == dst_pos)
        {
            *mid_pos = 0;
            return iter;
        }

        if (!(section->menu_model))
        {
            // Check if section should be inserted in the middle of a fake
            // section
            //
            if (i + section->item_count > dst_pos)
            {
                *mid_pos = dst_pos - i;
                return iter;
            }

            // Progress num of items in the fake section
            //
            i += section->item_count;
        }
        else
        {
            // Progress only 1 as a real section is considered 1 item
            i++;
        }
    }

    *mid_pos = 0;
    return NULL;
}

static void gxk_menu_binding_insert_item(
    GxkMenuBindingMenu* menu,
    GMenuModel*	             menu_model,
    gint                     src_pos,
    gint                     dst_pos
)
{
    gboolean is_menubar = GXK_IS_POPOVER_MENU_BAR(menu->menu_shell);

    // If this is a section, get it set up - find where to insert it in the
    // list... it could be in the middle of normal menu items
    //
    GMenuModel* section =
        g_menu_model_get_item_link(
            menu_model,
            src_pos,
            G_MENU_LINK_SECTION
        );

    if (section)
    {
        // Create new section
        //
        GxkMenuBindingSection* new_section =
            g_new(GxkMenuBindingSection, 1);

        new_section->parent_menu = menu;
        new_section->menu_model  = section;
        new_section->item_count  = 0;

        // Find where to insert
        //
        gint   mid_pos    = 0;
        GList* target_li  =
            gxk_menu_binding_find_section_pos(menu, dst_pos, &mid_pos);

        if (!target_li)
        {
            menu->sections =
                g_list_append(menu->sections, new_section);
        }
        else
        {
            if (mid_pos)
            {
                GxkMenuBindingSection* target =
                    (GxkMenuBindingSection*) target_li->data;

                // Need to split up 'fake' section
                //
                GxkMenuBindingSection* new_subsection =
                    g_new(GxkMenuBindingSection, 1);

                new_subsection->parent_menu = menu;
                new_subsection->menu_model  = NULL;
                new_subsection->item_count  = target->item_count - mid_pos;

                target->item_count -= new_subsection->item_count;

                // Append the new section + the latter half of the split fake
                // section
                //
                menu->sections =
                    g_list_insert_before(
                        menu->sections,
                        target_li->next,
                        new_section
                    );
                menu->sections =
                    g_list_insert_before(
                        menu->sections,
                        target_li->next,
                        new_subsection
                    );
            }
            else
            {
                menu->sections =
                    g_list_insert_before(
                        menu->sections,
                        target_li,
                        new_section
                    );
            }
        }

        // Insert items from the section
        //
        gint n_items = g_menu_model_get_n_items(section);

        for (gint i = 0; i < n_items; i++)
        {
            gxk_menu_binding_insert_item(
                menu,
                section,
                i,
                i
            );
        }

        return;
    }

    // Actually have an item - pull its data
    //
    GIcon*    icon = NULL;
    GVariant* icon_var;
    gchar*    label = NULL;

    g_menu_model_get_item_attribute(
        menu_model,
        src_pos,
        G_MENU_ATTRIBUTE_LABEL,
        "s",
        &label
    );

    icon_var =
        g_menu_model_get_item_attribute_value(
            menu_model,
            src_pos,
            G_MENU_ATTRIBUTE_ICON,
            NULL
        );

    if (icon_var)
    {
        icon = g_icon_deserialize(icon_var);
        g_variant_unref(icon_var);
    }

    // Get action information
    //
    gchar*    action_name   = NULL;
    GVariant* action_target = NULL;

    if (
        g_menu_model_get_item_attribute(
            menu_model,
            src_pos,
            G_MENU_ATTRIBUTE_ACTION,
            "s",
            &action_name
        )
    )
    {
        action_target =
            g_menu_model_get_item_attribute_value(
                menu_model,
                src_pos,
                G_MENU_ATTRIBUTE_TARGET,
                NULL
            );
    }

    // Create the item
    //
    GtkWidget* box_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* menu_item     = gxk_menu_item_new();

    gxk_menu_item_set_child(
        GXK_MENU_ITEM(menu_item),
        box_container
    );

    if (!is_menubar) // Only add icons to submenus
    {
        GtkWidget* img_icon = gtk_image_new();

        gtk_widget_set_margin_end(img_icon, 6); // Got this from Mousepad
        gtk_widget_set_size_request(img_icon, 16, 16);

//        gtk_menu_item_set_reserve_indicator(
//            GXK_MENU_ITEM(menu_item),
//            TRUE
//        );

        if (icon)
        {
            gtk_image_set_from_gicon(
                GTK_IMAGE(img_icon),
                icon
//                GTK_ICON_SIZE_MENU
            );
            gtk_image_set_pixel_size(
                GTK_IMAGE(img_icon),
                16
            );

            g_object_unref(icon);
        }

        gtk_box_prepend(
            GTK_BOX(box_container),
            img_icon
        );
    }

    if (action_name)
    {
        gtk_actionable_set_action_name(
            GTK_ACTIONABLE(menu_item),
            action_name
        );
        gtk_actionable_set_action_target_value(
            GTK_ACTIONABLE(menu_item),
            action_target
        );

        g_free(action_name);
        g_variant_unref(action_target);
    }

    if (label)
    {
        GtkWidget* label_title = gtk_label_new(label);

        gtk_label_set_xalign(GTK_LABEL(label_title), 0.0f);

        gtk_box_prepend(
            GTK_BOX(box_container),
            label_title
        );

        g_free(label);
    }

    // Do we have a submenu for this item?
    //
    GMenuModel* submenu_model =
        g_menu_model_get_item_link(
            menu_model,
            src_pos,
            G_MENU_LINK_SUBMENU
        );

    if (submenu_model)
    {
        GtkWidget* submenu = gxk_popover_menu_new();

        //gtk_menu_set_reserve_toggle_size(GTK_MENU(submenu), FALSE);

        gxk_menu_binding_track_menu(
            menu->menu_binding,
            GXK_MENU_SHELL(submenu),
            submenu_model
        );

        gxk_menu_item_set_submenu(
            GXK_MENU_ITEM(menu_item),
            submenu
        );
    }

    //
    // Insert the item
    //
    GList* iter     = menu->sections;
    gint   real_pos = 0;

    // menu_model could either be the menu itself or one of its child sections
    //
    gboolean is_subsection = menu_model != menu->menu_model;

    // If its a subsection then locate it and append the item
    //
    if (is_subsection)
    {
        for (; iter; iter = iter->next)
        {
            GxkMenuBindingSection* check_section =
                (GxkMenuBindingSection*) iter->data;

            // Is this the correct section? If so, insert and move on
            //
            if (menu_model == check_section->menu_model)
            {
                check_section->item_count++;
                real_pos += dst_pos; // Location within the section

                gxk_menu_shell_insert(menu->menu_shell, menu_item, real_pos);

                return;
            }

            // No? Increment real_pos as needed
            //
            real_pos += check_section->item_count;
        }

        // This should never happen - an attempt to add an item within a
        // section into a menu which does not contain the section
        //
        g_critical(
            "%s",
            "ctl - menubind - section not found in menu for item?"
        );
        return;
    }

    // Continue - add the item directly into the menu
    //
    if (!iter)
    {
        // If there isn't yet any sections, then this must be the first item
        //
        if (dst_pos > 0)
        {
            g_warning(
                "ctl - menubind - first item not at 0? (wants %d)",
                dst_pos
            );
        }

        // Create fake section
        //
        GxkMenuBindingSection* fake_section =
            g_new(GxkMenuBindingSection, 1);

        fake_section->parent_menu = menu;
        fake_section->menu_model  = NULL;
        fake_section->item_count  = 1;

        menu->sections =
            g_list_append(menu->sections, fake_section);

        gxk_menu_shell_append(menu->menu_shell, menu_item);

        return;
    }

    // Need to iterate through sections to find where to add this item
    //
    gint i = 0;

    while (i < dst_pos && iter)
    {
        GxkMenuBindingSection* subsection =
            (GxkMenuBindingSection*) iter->data;

        // Check we're not overshooting - could be within a 'fake' section...
        //
        if (
            !(subsection->menu_model) &&
            i + subsection->item_count >= dst_pos
        )
        {
            real_pos += (dst_pos - i);
            break;
        }

        // Moving on...
        //
        iter      = iter->next;
        real_pos += subsection->item_count;

        if (subsection->menu_model)
        {
            i++;
        }
        else
        {
            i += subsection->item_count;
        }
    }

    // If we found where to insert, then get that sorted
    //
    if (iter)
    {
        GxkMenuBindingSection* found_section =
            (GxkMenuBindingSection*) iter->data;

        // If this is a real section, look for a fake section before it to
        // insert into instead
        //
        if (found_section->menu_model && iter->prev)
        {
            GxkMenuBindingSection* prev_section =
                (GxkMenuBindingSection*) iter->prev->data;

            if (!(prev_section->menu_model))
            {
                found_section = prev_section;
            }
        }

        // Do we have a fake section? If not, create a new one before the real
        // section
        //
        if (found_section->menu_model)
        {
            found_section = g_new(GxkMenuBindingSection, 1);

            found_section->parent_menu = menu;
            found_section->menu_model  = NULL;
            found_section->item_count  = 0; // Will be incremented in a moment

            menu->sections =
                g_list_insert_before(
                    menu->sections,
                    iter,
                    found_section
                );
        }

        found_section->item_count++;
        gxk_menu_shell_insert(menu->menu_shell, menu_item, real_pos);
        return;
    }

    // If we fell out, we need to add the item to the end of the menu
    //
    GxkMenuBindingSection* last_section =
        (GxkMenuBindingSection*) (g_list_last(menu->sections))->data;

    if (last_section->menu_model)
    {
        // If the last section is not fake, then we need to append a
        // fake section now with the item in it
        //
        last_section = g_new(GxkMenuBindingSection, 1);

        last_section->parent_menu = menu;
        last_section->menu_model  = NULL;
        last_section->item_count  = 0; // Will be incremented in a moment

        menu->sections =
            g_list_append(menu->sections, last_section);

        // FIXME: Probably append a separator here first
    }

    last_section->item_count++;
    gxk_menu_shell_append(menu->menu_shell, menu_item);
}

static void gxk_menu_binding_remove_item(
    GxkMenuBindingMenu* menu,
    GMenuModel*              menu_model,
    gint                     src_pos
)
{
    gboolean is_subsection = menu_model != menu->menu_model;

    // Let's fine the position of the item to bin!
    //
    gint real_pos = 0;

    if (is_subsection)
    {
        for (GList* iter = menu->sections; iter; iter = iter->next)
        {
            GxkMenuBindingSection* check_section =
                (GxkMenuBindingSection*) iter->data;

            if (!(check_section->menu_model))
            {
                real_pos += check_section->item_count;
                continue;
            }

            if (check_section->menu_model == menu_model)
            {
                real_pos += src_pos;

                check_section->item_count--;

                //
                // FIXME: GXK - THIS MUST BE IMPLEMENTED!!
                //
//                gtk_widget_destroy(
//                    wintc_container_get_nth_child(
//                        GTK_CONTAINER(menu->menu_shell),
//                        real_pos
//                    )
//                );

                // Handle when we just destroyed the last item in a section
                //
                if (!(check_section->item_count))
                {
                    menu->sections =
                        g_list_delete_link(
                            menu->sections,
                            iter
                        );
                }

                return;
            }
        }
    }
    else
    {
        gint i = 0;

        for (GList* iter = menu->sections; iter; iter = iter->next)
        {
            GxkMenuBindingSection* check_section =
                (GxkMenuBindingSection*) iter->data;

            if (i == src_pos)
            {
                // If the item referred to is the section itself, we need to
                // delete the entire section
                //
                if (check_section->menu_model)
                {
                    for (gint j = 0; j < check_section->item_count; j++)
                    {
                        //
                        // FIXME: DITTO!
                        //
//                        gtk_widget_destroy(
//                            wintc_container_get_nth_child(
//                                GTK_CONTAINER(menu->menu_shell),
//                                real_pos
//                            )
//                        );
                    }

                    menu->sections =
                        g_list_delete_link(
                            menu->sections,
                            iter
                        );

                    return;
                }
                else
                {
                    check_section->item_count--;

                    //
                    // FIXME: DITTO!!
                    //
//                    gtk_widget_destroy(
//                        wintc_container_get_nth_child(
//                            GTK_CONTAINER(menu->menu_shell),
//                            real_pos
//                        )
//                    );

                    if (!(check_section->item_count))
                    {
                        menu->sections =
                            g_list_delete_link(
                                menu->sections,
                                iter
                            );
                    }
                }

                return;
            }

            // Keep looking...
            //
            // If this section is real, then no fancy stuff is required - if
            // it's a 'fake' section then we need to check whether src_pos is
            // inside it
            //
            if (check_section->menu_model)
            {
                i++;
                real_pos += check_section->item_count;
            }
            else
            {
                if (i + check_section->item_count > src_pos)
                {
                    real_pos += src_pos - i; 

                    check_section->item_count--;

                    //
                    // FIXME: DITTO!!
                    //
//                    gtk_widget_destroy(
//                        wintc_container_get_nth_child(
//                            GTK_CONTAINER(menu->menu_shell),
//                            real_pos
//                        )
//                    );

                    return;
                }

                i        += check_section->item_count;
                real_pos += check_section->item_count;
            }
        }
    }

    g_critical(
        "%s",
        "gxk - menu binding - somehow failed to find menu item to delete?"
    );
}

static void gxk_menu_binding_track_menu(
    GxkMenuBinding* menu_binding,
    GxkMenuShell*        menu_shell,
    GMenuModel*          menu_model
)
{
    // Initialise new tracker
    //
    GxkMenuBindingMenu* tracker =
        g_new(GxkMenuBindingMenu, 1);

    tracker->menu_binding = menu_binding;
    tracker->menu_shell   = menu_shell;
    tracker->menu_model   = menu_model;
    tracker->sections     = NULL;

    g_message(
        "gxk - menu binding - new menu tracker: %p",
        (void*) tracker
    );

    tracker->sigid_items_changed =
        g_signal_connect(
            menu_model,
            "items-changed",
            G_CALLBACK(on_menu_model_menu_items_changed),
            tracker
        );

    menu_binding->tracked_menus =
        g_slist_append(
            menu_binding->tracked_menus,
            tracker
        );

    // Iterate over the menu model
    //
    gint n_menu_items = g_menu_model_get_n_items(menu_model);

    for (gint i = 0; i < n_menu_items; i++)
    {
        gxk_menu_binding_insert_item(
            tracker,
            tracker->menu_model,
            i,
            i
        );
    }
}

static void gxk_menu_binding_menu_free(
    GxkMenuBindingMenu* menu
)
{
    g_clear_list(&(menu->sections), (GDestroyNotify) g_free);
    g_free(menu);
}

//
// CALLBACKS
//
static void on_menu_model_menu_items_changed(
    GMenuModel* model,
    gint        position,
    gint        removed,
    gint        added,
    gpointer    user_data
)
{
    GxkMenuBindingMenu* menu = (GxkMenuBindingMenu*) user_data;

    g_message(
        "gxk - menubinding - update pos %d, remove %d, add %d",
        position,
        removed,
        added
    );

    // Removed items
    //
    for (gint i = position; i < position + removed; i++)
    {
        gxk_menu_binding_remove_item(menu, model, i);
    }

    // Added items
    //
    for (gint i = position; i < position + added; i++)
    {
        gxk_menu_binding_insert_item(menu, model, i, i);
    }
}
