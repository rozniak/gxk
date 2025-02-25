#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.resources"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[1417]; const double alignment; void * const ptr;}  resources_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\344\000\000\000\000\000\000\050\007\000\000\000"
  "\000\000\000\000\001\000\000\000\002\000\000\000\003\000\000\000"
  "\006\000\000\000\006\000\000\000\006\000\000\000\014\367\007\233"
  "\003\000\000\000\344\000\000\000\012\000\166\000\360\000\000\000"
  "\107\005\000\000\003\325\170\174\002\000\000\000\107\005\000\000"
  "\003\000\114\000\114\005\000\000\120\005\000\000\324\265\002\000"
  "\377\377\377\377\120\005\000\000\001\000\114\000\124\005\000\000"
  "\130\005\000\000\235\223\147\245\005\000\000\000\130\005\000\000"
  "\007\000\114\000\140\005\000\000\144\005\000\000\143\200\032\354"
  "\006\000\000\000\144\005\000\000\004\000\114\000\150\005\000\000"
  "\154\005\000\000\047\324\207\375\004\000\000\000\154\005\000\000"
  "\010\000\114\000\164\005\000\000\170\005\000\000\352\023\204\141"
  "\001\000\000\000\170\005\000\000\012\000\114\000\204\005\000\000"
  "\210\005\000\000\142\165\164\164\157\156\056\160\156\147\000\000"
  "\107\004\000\000\000\000\000\000\211\120\116\107\015\012\032\012"
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
  "\016\303\001\307\157\250\144\000\000\002\200\111\104\101\124\170"
  "\332\355\133\275\116\303\060\020\276\213\042\025\211\001\301\302"
  "\102\141\351\053\040\044\006\170\134\026\136\202\021\361\012\235"
  "\020\013\060\060\061\260\324\304\377\347\070\345\047\155\342\344"
  "\354\253\324\272\256\332\372\073\337\335\167\167\116\020\116\336"
  "\004\144\054\265\172\276\174\110\275\216\064\362\164\253\025\200"
  "\120\201\130\277\002\174\174\246\136\322\070\162\174\010\270\072"
  "\005\151\372\225\204\017\210\371\200\227\042\261\112\314\015\366"
  "\132\275\250\067\132\360\152\225\172\171\203\212\170\134\153\234"
  "\006\163\015\112\003\225\321\210\031\163\026\212\023\125\020\104"
  "\365\260\124\200\200\275\177\173\016\102\161\012\351\002\201\126"
  "\332\143\316\342\134\100\215\053\245\023\077\346\054\041\316\332"
  "\261\100\113\063\354\305\262\200\326\011\141\001\346\061\240\215"
  "\323\260\000\202\303\315\335\002\050\116\311\002\212\003\032\177"
  "\300\114\142\000\305\211\216\005\002\263\147\156\001\055\234\206"
  "\005\110\014\340\356\002\055\234\206\005\074\015\262\317\004\003"
  "\234\250\203\040\222\040\310\336\002\050\116\204\022\003\164\055"
  "\220\155\046\130\152\001\337\017\360\371\001\157\005\120\234\162"
  "\254\131\000\010\013\100\036\056\140\061\227\124\130\217\113\042"
  "\004\371\046\102\220\173\071\254\336\145\114\203\162\200\244\053"
  "\314\071\021\022\142\023\315\061\115\205\273\217\073\243\215\106"
  "\234\177\042\044\104\027\330\277\140\230\033\013\164\230\257\132"
  "\356\077\067\254\043\023\234\126\036\320\275\243\260\307\215\351"
  "\240\301\064\061\140\233\237\216\363\377\301\331\240\156\016\140"
  "\360\301\136\241\366\366\323\101\125\140\024\340\142\200\235\337"
  "\301\324\366\344\247\303\342\046\033\335\267\026\030\336\117\307"
  "\120\104\024\003\134\174\244\120\273\277\073\245\035\355\213\337"
  "\067\104\360\207\354\157\376\100\267\143\242\265\000\235\236\223"
  "\031\357\002\337\235\014\225\206\210\055\015\115\164\144\151\366"
  "\261\006\160\020\032\234\223\004\015\221\011\245\302\243\341\307"
  "\250\041\342\316\214\122\257\155\150\350\001\116\322\026\267\222"
  "\211\013\100\071\034\045\207\243\071\273\200\277\104\306\316\363"
  "\166\201\070\021\012\246\333\143\316\022\135\042\063\134\077\140"
  "\132\022\342\254\165\112\130\021\333\340\355\002\001\116\054\211"
  "\320\157\375\000\216\022\225\303\141\077\200\073\013\204\070\313"
  "\045\062\346\144\310\074\000\370\227\303\024\247\076\030\261\055"
  "\361\054\033\042\110\157\230\260\363\071\305\200\122\013\370\233"
  "\246\374\307\334\025\100\161\072\026\360\146\377\176\177\227\172"
  "\155\043\151\300\272\200\351\007\054\226\027\360\365\362\234\172"
  "\131\243\310\342\354\234\366\003\164\064\074\272\276\111\275\256"
  "\004\322\070\302\301\162\223\365\355\363\337\032\242\065\044\340"
  "\345\210\144\000\000\000\000\111\105\116\104\256\102\140\202\000"
  "\000\050\165\165\141\171\051\165\153\057\000\000\006\000\000\000"
  "\057\000\000\000\001\000\000\000\142\157\170\151\156\147\057\000"
  "\000\000\000\000\147\170\153\057\005\000\000\000\163\141\155\160"
  "\154\145\163\057\003\000\000\000\157\144\144\155\141\164\151\143"
  "\163\057\000\000\004\000\000\000" };

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
