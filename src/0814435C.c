#include "ffta.h"

/* Complete [0x0814435C, 0x08144378): 28 bytes, 14 instructions.
 * 994203db994207dc904201d2002004e0904201d8012000e002207047
 *
 * libgcc2 __cmpdi2, verbatim from pret/agbcc libgcc/libgcc2.c (L_cmpdi2,
 * with its DIstruct and DIunion); only the function name and the
 * mode-attribute integer typedefs are adapted.  That libgcc Makefile builds
 * it with old_agbcc -O2.  The ROM body returns with a bare bx lr at
 * 0x08144376; agbcc saves lr around the same comparison (push {lr} ...
 * pop {r1}; bx r1), old_agbcc does not.
 */
typedef s32 SItype;
typedef u32 USItype;
typedef long long DItype;
typedef s32 word_type;

struct DIstruct {SItype low, high;};

typedef union
{
  struct DIstruct s;
  DItype ll;
} DIunion;

word_type
func_0814435C (DItype a, DItype b)
{
  DIunion au, bu;

  au.ll = a, bu.ll = b;

  if (au.s.high < bu.s.high)
    return 0;
  else if (au.s.high > bu.s.high)
    return 2;
  if ((USItype) au.s.low < (USItype) bu.s.low)
    return 0;
  else if ((USItype) au.s.low > (USItype) bu.s.low)
    return 2;
  return 1;
}
