/*  -- translated by f2c (version of 23 April 1993  18:34:30).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Modified by Peter Vanroose, June 2001: manual optimisation and clean-up */

/* Double Complex */ void zladiv_( ret_val, x, y)
doublecomplex * ret_val;
doublecomplex *x, *y;
{
    extern /* Subroutine */ void dladiv_();


/*  -- LAPACK auxiliary routine (version 2.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     October 31, 1992 */

/*  ===================================================================== */
/*                                                                        */
/*  Purpose                                                               */
/*  =======                                                               */
/*                                                                        */
/*  ZLADIV := X / Y, where X and Y are complex.  The computation of X / Y */
/*  will not overflow on an intermediary step unless the results          */
/*  overflows.                                                            */
/*                                                                        */
/*  Arguments                                                             */
/*  =========                                                             */
/*                                                                        */
/*  X       (input) COMPLEX*16                                            */
/*  Y       (input) COMPLEX*16                                            */
/*          The complex scalars X and Y.                                  */
/*                                                                        */
/*  ===================================================================== */

    dladiv_(&(x->r), &(x->i), &(y->r), &(y->i), &(ret_val->r), &(ret_val->i));
    return;

/*     End of ZLADIV */

} /* zladiv_ */

