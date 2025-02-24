#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.resources"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[2173]; const double alignment; void * const ptr;}  resources_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\344\000\000\000\000\000\000\050\007\000\000\000"
  "\000\000\000\000\001\000\000\000\003\000\000\000\004\000\000\000"
  "\006\000\000\000\006\000\000\000\006\000\000\000\017\353\103\352"
  "\002\000\000\000\344\000\000\000\011\000\166\000\360\000\000\000"
  "\074\010\000\000\003\325\170\174\003\000\000\000\074\010\000\000"
  "\003\000\114\000\100\010\000\000\104\010\000\000\042\177\040\335"
  "\005\000\000\000\104\010\000\000\010\000\114\000\114\010\000\000"
  "\120\010\000\000\324\265\002\000\377\377\377\377\120\010\000\000"
  "\001\000\114\000\124\010\000\000\130\010\000\000\143\200\032\354"
  "\006\000\000\000\130\010\000\000\004\000\114\000\134\010\000\000"
  "\140\010\000\000\047\324\207\375\004\000\000\000\140\010\000\000"
  "\010\000\114\000\150\010\000\000\154\010\000\000\352\023\204\141"
  "\001\000\000\000\154\010\000\000\012\000\114\000\170\010\000\000"
  "\174\010\000\000\163\155\151\154\145\056\160\156\147\000\000\000"
  "\074\007\000\000\000\000\000\000\211\120\116\107\015\012\032\012"
  "\000\000\000\015\111\110\104\122\000\000\000\100\000\000\000\100"
  "\010\006\000\000\000\252\151\161\336\000\000\001\155\151\103\103"
  "\120\151\143\143\000\000\050\221\165\221\273\113\303\120\024\306"
  "\177\246\212\342\253\203\035\104\034\062\124\161\120\020\005\161"
  "\324\072\270\024\051\265\202\257\045\211\175\010\151\014\111\213"
  "\210\253\340\342\040\070\210\056\276\006\377\003\135\005\127\005"
  "\101\120\004\021\127\127\137\213\110\074\267\055\124\304\336\160"
  "\163\176\174\367\176\207\223\057\240\305\155\053\357\327\217\101"
  "\336\051\170\311\311\230\076\073\067\257\067\276\240\321\111\204"
  "\166\332\014\313\167\307\023\211\070\065\327\347\035\165\252\336"
  "\016\250\136\265\357\375\273\132\226\322\276\005\165\115\302\043"
  "\226\353\025\204\145\032\342\253\005\127\361\226\160\304\312\031"
  "\113\302\207\302\375\236\014\050\174\245\164\263\314\317\212\263"
  "\145\176\127\354\245\222\023\240\251\236\172\366\027\233\277\330"
  "\312\171\171\341\076\341\150\336\056\132\225\171\324\227\264\246"
  "\235\231\151\251\135\262\273\361\111\062\111\014\035\223\042\313"
  "\330\024\030\220\352\110\146\377\373\006\113\276\051\126\304\143"
  "\311\333\145\015\117\034\131\162\342\355\027\265\050\135\323\122"
  "\063\242\247\345\261\131\123\271\377\315\323\317\014\017\225\273"
  "\267\306\240\341\051\010\336\172\240\161\007\276\267\203\340\353"
  "\050\010\276\217\041\364\010\027\116\325\277\042\071\215\176\210"
  "\276\135\325\242\007\020\336\200\263\313\252\146\356\302\371\046"
  "\164\076\270\206\147\224\244\220\154\055\223\201\327\123\150\233"
  "\203\216\033\150\136\050\147\125\071\347\344\036\122\353\362\213"
  "\256\141\157\037\172\345\176\170\361\007\326\125\147\366\316\034"
  "\247\204\000\000\000\011\160\110\131\163\000\000\016\303\000\000"
  "\016\303\001\307\157\250\144\000\000\005\165\111\104\101\124\170"
  "\332\355\133\133\154\024\125\030\376\166\273\335\356\266\164\273"
  "\273\122\013\122\135\250\115\005\102\251\227\124\305\033\106\211"
  "\044\002\151\122\051\017\304\370\242\306\010\021\021\023\211\306"
  "\024\015\251\006\105\214\370\000\221\160\111\224\220\050\217\032"
  "\175\100\013\126\115\024\041\306\160\011\322\332\102\113\357\335"
  "\155\167\205\135\366\352\071\333\231\146\166\166\146\347\354\314"
  "\354\215\355\227\264\073\327\177\376\357\233\063\347\077\227\377"
  "\030\220\171\304\064\336\157\310\244\163\272\033\367\206\353\015"
  "\066\123\167\124\260\257\311\036\261\045\264\155\044\373\132\005"
  "\315\214\000\304\071\033\161\156\112\017\322\112\142\020\373\125"
  "\144\333\233\027\002\020\147\234\304\231\211\114\022\117\041\304"
  "\155\144\333\235\023\001\270\342\030\311\046\361\024\102\224\010"
  "\077\273\214\013\100\036\130\117\036\170\071\127\304\245\204\340"
  "\174\352\111\367\136\243\012\362\033\362\211\074\347\023\025\241"
  "\233\374\266\245\173\057\163\011\310\207\042\257\004\065\237\004"
  "\223\000\304\240\231\030\274\231\257\304\245\204\040\276\226\221"
  "\337\240\146\001\012\215\174\272\042\044\011\040\042\032\057\366"
  "\205\106\136\044\102\011\331\214\012\217\245\024\100\204\130\241"
  "\222\027\021\226\345\051\033\005\150\155\237\153\347\365\002\341"
  "\262\136\356\234\101\346\206\274\212\363\132\221\252\235\040\125"
  "\007\024\364\167\257\040\102\122\170\064\112\134\250\231\174\367"
  "\077\041\135\234\336\364\322\050\234\226\036\324\057\350\305\241"
  "\057\246\064\331\342\032\113\021\361\161\203\210\154\274\143\243"
  "\126\200\213\027\202\170\276\155\030\227\057\005\121\063\257\004"
  "\373\016\326\140\325\352\162\125\266\276\074\354\305\346\227\107"
  "\147\366\055\026\003\372\047\352\120\126\246\276\377\306\225\002"
  "\047\331\364\360\307\114\242\260\240\232\074\105\307\016\167\234"
  "\074\305\310\160\004\073\333\047\124\013\160\245\057\234\260\037"
  "\010\304\160\245\067\204\206\305\146\325\376\161\245\200\366\036"
  "\147\124\064\012\116\332\124\133\346\060\062\234\350\364\330\150"
  "\104\245\245\314\202\160\255\114\022\200\016\146\334\152\025\237"
  "\014\171\010\007\123\214\334\301\214\216\273\345\043\170\316\161"
  "\001\150\150\050\206\267\057\040\017\076\034\246\075\036\160\253"
  "\141\126\000\350\330\341\031\032\312\317\132\137\012\034\347\230"
  "\256\045\300\347\115\034\204\131\124\127\232\153\236\212\320\115"
  "\200\323\277\007\340\161\047\226\200\271\325\045\271\346\227\075"
  "\001\316\375\235\074\360\322\164\137\131\256\371\145\117\000\161"
  "\053\220\342\221\307\255\271\346\227\075\001\244\140\055\317\357"
  "\366\025\251\010\173\213\075\014\332\212\135\200\312\142\027\240"
  "\350\133\202\076\335\004\150\154\112\014\171\166\207\021\215\313"
  "\325\207\301\147\327\125\044\354\077\320\154\321\064\030\042\003"
  "\057\155\251\274\367\166\273\123\263\245\206\173\246\235\353\277"
  "\032\206\313\125\212\017\166\127\143\361\022\365\016\317\277\303"
  "\204\025\217\131\141\064\032\260\362\051\053\366\037\274\035\146"
  "\263\276\121\205\364\010\035\324\142\301\117\176\150\020\240\350"
  "\353\200\131\001\212\136\000\276\126\051\272\172\200\237\064\055"
  "\372\022\060\053\000\375\307\115\210\062\337\164\362\047\077\326"
  "\257\033\104\353\232\101\374\360\335\365\134\163\110\033\334\024"
  "\131\234\273\260\145\301\124\017\114\172\242\130\132\327\207\377"
  "\174\323\303\137\245\245\006\234\071\177\027\026\146\171\370\353"
  "\374\271\040\354\166\043\026\324\232\124\011\300\163\027\116\215"
  "\125\261\224\202\256\123\376\031\362\024\241\120\014\257\157\032"
  "\313\052\371\226\325\203\130\161\357\125\054\131\330\207\035\357"
  "\114\244\115\136\070\015\050\234\032\143\312\275\135\326\230\334"
  "\274\355\074\161\003\117\077\072\200\237\117\372\063\116\376\363"
  "\075\223\350\374\361\306\314\376\247\037\171\060\072\222\336\150"
  "\064\341\352\343\267\125\115\217\277\371\332\030\016\354\223\236"
  "\257\177\361\225\052\264\357\164\302\341\324\177\100\364\257\263"
  "\067\343\102\323\122\047\304\331\013\056\324\067\050\177\202\122"
  "\323\343\122\275\013\246\272\140\355\252\153\262\157\234\176\227"
  "\037\177\126\215\265\055\025\212\166\130\061\320\037\306\032\362"
  "\314\336\236\304\344\213\007\037\266\340\304\057\265\114\066\244"
  "\022\246\222\302\040\227\106\242\150\354\350\361\371\150\176\310"
  "\042\171\356\332\100\030\033\237\033\302\356\017\075\212\166\130"
  "\360\375\267\327\361\314\312\201\044\362\024\333\266\073\230\311"
  "\163\051\163\011\220\113\222\272\233\313\275\125\064\274\367\223"
  "\111\354\352\160\047\115\212\360\240\143\002\157\020\047\133\132"
  "\053\342\021\203\005\336\251\050\376\374\043\200\137\273\374\370"
  "\255\153\372\127\012\257\156\261\143\327\236\271\254\344\331\222"
  "\244\004\042\264\221\033\276\146\021\341\337\356\020\072\336\167"
  "\343\233\143\076\331\153\150\137\236\316\023\054\135\046\077\106"
  "\160\351\142\020\043\244\102\223\172\323\142\264\266\315\301\221"
  "\143\363\130\311\123\056\307\245\316\353\232\050\171\370\200\027"
  "\357\156\037\227\055\015\172\141\343\013\225\330\177\250\206\351"
  "\132\245\104\111\335\123\145\351\024\331\133\133\307\161\346\164"
  "\100\167\342\164\224\150\313\066\073\066\157\265\063\223\327\232"
  "\052\253\072\131\232\246\265\355\045\061\233\176\036\132\261\274"
  "\251\014\255\033\346\060\127\170\002\362\351\047\113\353\051\002"
  "\305\251\116\077\276\072\342\215\307\160\372\215\053\341\116\227"
  "\011\265\044\214\066\335\157\041\025\250\031\117\074\151\205\153"
  "\121\172\315\154\135\323\345\005\042\150\136\060\101\123\335\242"
  "\221\324\253\336\312\053\324\167\120\063\266\140\102\044\004\163"
  "\164\310\046\224\152\173\335\004\340\104\140\156\047\144\221\274"
  "\252\105\123\263\313\346\264\072\101\036\356\340\027\057\346\140"
  "\341\044\355\274\151\152\157\027\352\322\131\233\260\113\233\027"
  "\002\010\204\050\316\305\323\051\220\344\060\315\314\240\334\310"
  "\037\237\264\114\337\046\035\220\031\047\004\233\263\351\343\377"
  "\171\314\223\277\266\044\225\266\000\000\000\000\111\105\116\104"
  "\256\102\140\202\000\000\050\165\165\141\171\051\165\153\057\000"
  "\006\000\000\000\144\162\141\167\151\156\147\057\000\000\000\000"
  "\057\000\000\000\001\000\000\000\147\170\153\057\005\000\000\000"
  "\163\141\155\160\154\145\163\057\002\000\000\000\157\144\144\155"
  "\141\164\151\143\163\057\000\000\004\000\000\000" };

static GStaticResource static_resource = { resources_resource_data.data, sizeof (resources_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *resources_get_resource (void);
GResource *resources_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resourcesresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resourcesresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resourcesresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resourcesresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resourcesresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resourcesresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
