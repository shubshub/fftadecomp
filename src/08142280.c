#include "ffta.h"

/* GCC libgcc2.c L_divdi3 and longlong.h. Copyright 1989-1998 Free Software
 * Foundation, Inc. GPL-2.0-or-later with the libgcc exception. */
typedef signed long long s64;
typedef unsigned long long u64;

typedef union {
    struct {
        s32 low;
        s32 high;
    } s;
    s64 ll;
} DIunion;

#define SI_TYPE_SIZE 32
#define __ll_B (1L << 16)
#define __ll_lowpart(t) ((u32)(t) % __ll_B)
#define __ll_highpart(t) ((u32)(t) / __ll_B)

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
  do { \
    u32 __x; \
    __x = (al) - (bl); \
    (sh) = (ah) - (bh) - (__x > (al)); \
    (sl) = __x; \
  } while (0)

#define umul_ppmm(w1, w0, u, v) \
  do { \
    u32 __x0, __x1, __x2, __x3; \
    u32 __ul, __vl, __uh, __vh; \
 \
    __ul = __ll_lowpart (u); \
    __uh = __ll_highpart (u); \
    __vl = __ll_lowpart (v); \
    __vh = __ll_highpart (v); \
 \
    __x0 = (u32) __ul * __vl; \
    __x1 = (u32) __ul * __vh; \
    __x2 = (u32) __uh * __vl; \
    __x3 = (u32) __uh * __vh; \
 \
    __x1 += __ll_highpart (__x0); \
    __x1 += __x2; \
    if (__x1 < __x2) \
      __x3 += __ll_B; \
 \
    (w1) = __x3 + __ll_highpart (__x1); \
    (w0) = __ll_lowpart (__x1) * __ll_B + __ll_lowpart (__x0); \
  } while (0)

#define udiv_qrnnd(q, r, n1, n0, d) \
  do { \
    u32 __d1, __d0, __q1, __q0; \
    u32 __r1, __r0, __m; \
    __d1 = __ll_highpart (d); \
    __d0 = __ll_lowpart (d); \
 \
    __r1 = (n1) % __d1; \
    __q1 = (n1) / __d1; \
    __m = (u32) __q1 * __d0; \
    __r1 = __r1 * __ll_B | __ll_highpart (n0); \
    if (__r1 < __m) \
      { \
	__q1--, __r1 += (d); \
	if (__r1 >= (d)) /* i.e. we didn't get carry when adding to __r1 */\
	  if (__r1 < __m) \
	    __q1--, __r1 += (d); \
      } \
    __r1 -= __m; \
 \
    __r0 = __r1 % __d1; \
    __q0 = __r1 / __d1; \
    __m = (u32) __q0 * __d0; \
    __r0 = __r0 * __ll_B | __ll_lowpart (n0); \
    if (__r0 < __m) \
      { \
	__q0--, __r0 += (d); \
	if (__r0 >= (d)) \
	  if (__r0 < __m) \
	    __q0--, __r0 += (d); \
      } \
    __r0 -= __m; \
 \
    (q) = (u32) __q1 * __ll_B | __q0; \
    (r) = __r0; \
  } while (0)

/* Bit length of each possible high byte of a nonzero divisor. */
static const u8 __clz_tab[] =
{
  0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};

#define count_leading_zeros(count, x) \
    do { \
        u32 value = (x); \
        u32 shift = value < (1u << 16) \
            ? (value < (1u << 8) ? 0 : 8) \
            : (value < (1u << 24) ? 16 : 24); \
        (count) = 32 - (__clz_tab[value >> shift] + shift); \
    } while (0)

static inline s64 negate_words(s64 u)
{
  DIunion w;
  DIunion uu;

  uu.ll = u;

  w.s.low = -uu.s.low;
  w.s.high = -uu.s.high - ((u32) w.s.low > 0);

  return w.ll;
}

static inline u64 unsigned_quotient(u64 n, u64 d, u64 *rp)
{
  DIunion ww;
  DIunion nn, dd;
  DIunion rr;
  u32 d0, d1, n0, n1, n2;
  u32 q0, q1;
  u32 b, bm;

  nn.ll = n;
  dd.ll = d;

  d0 = dd.s.low;
  d1 = dd.s.high;
  n0 = nn.s.low;
  n1 = nn.s.high;

  if (d1 == 0)
    {
      if (d0 > n1)
	{
	  /* 0q = nn / 0D */

	  count_leading_zeros (bm, d0);

	  if (bm != 0)
	    {
	      /* Normalize, i.e. make the most significant bit of the
		 denominator set.  */

	      d0 = d0 << bm;
	      n1 = (n1 << bm) | (n0 >> (SI_TYPE_SIZE - bm));
	      n0 = n0 << bm;
	    }

	  udiv_qrnnd (q0, n0, n1, n0, d0);
	  q1 = 0;

	  /* Remainder in n0 >> bm.  */
	}
      else
	{
	  /* qq = NN / 0d */

	  if (d0 == 0)
	    d0 = 1 / d0;	/* Divide intentionally by zero.  */

	  count_leading_zeros (bm, d0);

	  if (bm == 0)
	    {
	      /* From (n1 >= d0) /\ (the most significant bit of d0 is set),
		 conclude (the most significant bit of n1 is set) /\ (the
		 leading quotient digit q1 = 1).

		 This special case is necessary, not an optimization.
		 (Shifts counts of SI_TYPE_SIZE are undefined.)  */

	      n1 -= d0;
	      q1 = 1;
	    }
	  else
	    {
	      /* Normalize.  */

	      b = SI_TYPE_SIZE - bm;

	      d0 = d0 << bm;
	      n2 = n1 >> b;
	      n1 = (n1 << bm) | (n0 >> b);
	      n0 = n0 << bm;

	      udiv_qrnnd (q1, n1, n2, n1, d0);
	    }

	  /* n1 != d0...  */

	  udiv_qrnnd (q0, n0, n1, n0, d0);

	  /* Remainder in n0 >> bm.  */
	}

      if (rp != 0)
	{
	  rr.s.low = n0 >> bm;
	  rr.s.high = 0;
	  *rp = rr.ll;
	}
    }

  else
    {
      if (d1 > n1)
	{
	  /* 00 = nn / DD */

	  q0 = 0;
	  q1 = 0;

	  /* Remainder in n1n0.  */
	  if (rp != 0)
	    {
	      rr.s.low = n0;
	      rr.s.high = n1;
	      *rp = rr.ll;
	    }
	}
      else
	{
	  /* 0q = NN / dd */

	  count_leading_zeros (bm, d1);
	  if (bm == 0)
	    {
	      /* From (n1 >= d1) /\ (the most significant bit of d1 is set),
		 conclude (the most significant bit of n1 is set) /\ (the
		 quotient digit q0 = 0 or 1).

		 This special case is necessary, not an optimization.  */

	      /* The condition on the next line takes advantage of that
		 n1 >= d1 (true due to program flow).  */
	      if (n1 > d1 || n0 >= d0)
		{
		  q0 = 1;
		  sub_ddmmss (n1, n0, n1, n0, d1, d0);
		}
	      else
		q0 = 0;

	      q1 = 0;

	      if (rp != 0)
		{
		  rr.s.low = n0;
		  rr.s.high = n1;
		  *rp = rr.ll;
		}
	    }
	  else
	    {
	      u32 m1, m0;
	      /* Normalize.  */

	      b = SI_TYPE_SIZE - bm;

	      d1 = (d1 << bm) | (d0 >> b);
	      d0 = d0 << bm;
	      n2 = n1 >> b;
	      n1 = (n1 << bm) | (n0 >> b);
	      n0 = n0 << bm;

	      udiv_qrnnd (q0, n1, n2, n1, d1);
	      umul_ppmm (m1, m0, q0, d0);

	      if (m1 > n1 || (m1 == n1 && m0 > n0))
		{
		  q0--;
		  sub_ddmmss (m1, m0, m1, m0, d1, d0);
		}

	      q1 = 0;

	      /* Remainder in (n1n0 - m1m0) >> bm.  */
	      if (rp != 0)
		{
		  sub_ddmmss (n1, n0, n1, n0, m1, m0);
		  rr.s.low = (n1 << b) | (n0 >> bm);
		  rr.s.high = n1 >> bm;
		  *rp = rr.ll;
		}
	    }
	}
    }

  ww.s.low = q0;
  ww.s.high = q1;
  return ww.ll;
}

s64 func_08142280(s64 u, s64 v)
{
  s32 c = 0;
  DIunion uu, vv;
  s64 w;

  uu.ll = u;
  vv.ll = v;

  if (uu.s.high < 0)
    c = ~c,
    uu.ll = negate_words(uu.ll);
  if (vv.s.high < 0)
    c = ~c,
    vv.ll = negate_words(vv.ll);

  w = unsigned_quotient(uu.ll, vv.ll, (u64 *) 0);
  if (c)
    w = negate_words(w);

  return w;
}
