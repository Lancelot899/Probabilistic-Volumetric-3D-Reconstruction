/*  -- translated by f2c (version of 23 April 1993  18:34:30).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Modified by Peter Vanroose, June 2001: manual optimisation and clean-up */

/* Subroutine */ void zdscal_(n, da, zx, incx)
integer *n;
doublereal *da;
doublecomplex *zx;
integer *incx;
{
    /* Local variables */
    static integer i, ix;

/*     scales a vector by a constant. */
/*     jack dongarra, 3/11/78. */
/*     modified 3/93 to return if incx .le. 0. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */

    /* Function Body */

    if (*n <= 0 || *incx <= 0) {
        return;
    }
    if (*incx == 1) {
        for (i = 0; i < *n; ++i) {
            zx[i].r *= *da, zx[i].i *= *da;
        }
    }
    else {
        ix = 0;
        for (i = 0; i < *n; ++i) {
            zx[ix].r *= *da, zx[ix].i *= *da;
            ix += *incx;
        }
    }
} /* zdscal_ */

