// Created to fix spurious warnings
#include "m_fixed.h"
/*
 * Fixed Point Multiplication
 */


/* CPhipps - made __inline__ to inline, as specified in the gcc docs
 * Also made const */

inline CONSTFUNC fixed_t FixedMul(fixed_t a, fixed_t b)
{
  return (fixed_t)((int64_t) a*b >> FRACBITS);
}

inline CONSTFUNC int64_t FixedMul64(int64_t a, int64_t b)
{
  return a * b >> FRACBITS;
}

/*
 * Fixed Point Division
 */
 CONSTFUNC fixed_t FixedDiv(fixed_t a, fixed_t b)
{
  return (D_abs(a)>>14) >= D_abs(b) ? ((a^b)>>31) ^ INT_MAX :
    (fixed_t)(((int64_t) a << FRACBITS) / b);
}

/* CPhipps -
 * FixedMod - returns a % b, guaranteeing 0<=a<b
 * (notice that the C standard for % does not guarantee this)
 */

inline CONSTFUNC fixed_t FixedMod(fixed_t a, fixed_t b)
{
  if (b & (b-1)) {
    fixed_t r = a % b;
    return ((r<0) ? r+b : r);
  } else
    return (a & (b-1));
}
 CONSTFUNC fixed_t Scale(fixed_t a, fixed_t b, fixed_t c)
{
	return (fixed_t)(((int64_t)a*b)/c);
}

