/*  -- translated by f2c (version of 23 April 1993  18:34:30).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Modified by Peter Vanroose, June 2001: manual optimisation and clean-up */

/* Table of constant values */

static doublecomplex c_b2 = {0.,0.};
static doublecomplex c_b15 = {1.,0.};
static integer c__1 = 1;

/* Subroutine */ void zlarfx_(side, m, n, v, tau, c, ldc, work, side_len)
char *side;
integer *m, *n;
doublecomplex *v, *tau, *c;
integer *ldc;
doublecomplex *work;
ftnlen side_len;
{
    /* System generated locals */
    integer i__1;
    doublecomplex z__1;

    /* Builtin functions */
    void d_cnjg();

    /* Local variables */
    static integer j;
    extern logical lsame_();
    extern /* Subroutine */ void zgerc_(), zgemv_();
    static doublecomplex t1, t2, t3, t4, t5, t6, t7, t8, t9, v1, v2, v3, v4,
            v5, v6, v7, v8, v9, t10, v10, sum;


/*  -- LAPACK auxiliary routine (version 2.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     September 30, 1994 */

/*  ===================================================================== */
/*                                                                        */
/*  Purpose                                                               */
/*  =======                                                               */
/*                                                                        */
/*  ZLARFX applies a complex elementary reflector H to a complex m by n   */
/*  matrix C, from either the left or the right. H is represented in the  */
/*  form                                                                  */
/*                                                                        */
/*        H = I - tau * v * v'                                            */
/*                                                                        */
/*  where tau is a complex scalar and v is a complex vector.              */
/*                                                                        */
/*  If tau = 0, then H is taken to be the unit matrix                     */
/*                                                                        */
/*  This version uses inline code if H has order < 11.                    */
/*                                                                        */
/*  Arguments                                                             */
/*  =========                                                             */
/*                                                                        */
/*  SIDE    (input) CHARACTER*1                                           */
/*          = 'L': form  H * C                                            */
/*          = 'R': form  C * H                                            */
/*                                                                        */
/*  M       (input) INTEGER                                               */
/*          The number of rows of the matrix C.                           */
/*                                                                        */
/*  N       (input) INTEGER                                               */
/*          The number of columns of the matrix C.                        */
/*                                                                        */
/*  V       (input) COMPLEX*16 array, dimension (M) if SIDE = 'L'         */
/*                                        or (N) if SIDE = 'R'            */
/*          The vector v in the representation of H.                      */
/*                                                                        */
/*  TAU     (input) COMPLEX*16                                            */
/*          The value tau in the representation of H.                     */
/*                                                                        */
/*  C       (input/output) COMPLEX*16 array, dimension (LDC,N)            */
/*          On entry, the m by n matrix C.                                */
/*          On exit, C is overwritten by the matrix H * C if SIDE = 'L',  */
/*          or C * H if SIDE = 'R'.                                       */
/*                                                                        */
/*  LDC     (input) INTEGER                                               */
/*          The leading dimension of the array C. LDA >= max(1,M).        */
/*                                                                        */
/*  WORK    (workspace) COMPLEX*16 array, dimension (N) if SIDE = 'L'     */
/*                                            or (M) if SIDE = 'R'        */
/*          WORK is not referenced if H has order < 11.                   */
/*                                                                        */
/*  ===================================================================== */

    /* Function Body */

/*     Quick return if possible */
    if (tau->r == 0. && tau->i == 0.) {
        return;
    }
    if (lsame_(side, "L", 1L, 1L)) {

/*        Form  H * C, where H has order m. */

        switch ((int)*m) {
            case 1:  goto L10;
            case 2:  goto L30;
            case 3:  goto L50;
            case 4:  goto L70;
            case 5:  goto L90;
            case 6:  goto L110;
            case 7:  goto L130;
            case 8:  goto L150;
            case 9:  goto L170;
            case 10:  goto L190;
        }

/*        Code for general M */

/*        w := C'*v */

        zgemv_("Conjugate transpose", m, n, &c_b15, c, ldc, v,
               &c__1, &c_b2, work, &c__1, 19L);

/*        C := C - tau * v * w' */

        z__1.r = -tau->r, z__1.i = -tau->i;
        zgerc_(m, n, &z__1, v, &c__1, work, &c__1, c, ldc);
        return; /* exit zlarfx */
L10:

/*        Special code for 1 x 1 Householder */

        z__1.r = tau->r * v[0].r - tau->i * v[0].i,
        z__1.i = tau->r * v[0].i + tau->i * v[0].r;
        t1.r = 1. - z__1.r * v[0].r - z__1.i * v[0].i,
        t1.i = 0. + z__1.r * v[0].i - z__1.i * v[0].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            z__1.r = t1.r * c[i__1].r - t1.i * c[i__1].i,
            z__1.i = t1.r * c[i__1].i + t1.i * c[i__1].r;
            c[i__1].r = z__1.r, c[i__1].i = z__1.i;
        }
        return; /* exit zlarfx */
L30:

/*        Special code for 2 x 2 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
        }
        return; /* exit zlarfx */
L50:

/*        Special code for 3 x 3 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
        }
        return; /* exit zlarfx */
L70:

/*        Special code for 4 x 4 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        d_cnjg(&v4, &v[3]);
        t4.r = tau->r * v[3].r - tau->i * v[3].i,
        t4.i = tau->r * v[3].i + tau->i * v[3].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            ++i__1;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            ++i__1;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
        }
        return; /* exit zlarfx */
L90:

/*        Special code for 5 x 5 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        d_cnjg(&v4, &v[3]);
        t4.r = tau->r * v[3].r - tau->i * v[3].i,
        t4.i = tau->r * v[3].i + tau->i * v[3].r;
        d_cnjg(&v5, &v[4]);
        t5.r = tau->r * v[4].r - tau->i * v[4].i,
        t5.i = tau->r * v[4].i + tau->i * v[4].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            ++i__1;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            ++i__1;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            ++i__1;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            ++i__1;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
        }
        return; /* exit zlarfx */
L110:

/*        Special code for 6 x 6 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        d_cnjg(&v4, &v[3]);
        t4.r = tau->r * v[3].r - tau->i * v[3].i,
        t4.i = tau->r * v[3].i + tau->i * v[3].r;
        d_cnjg(&v5, &v[4]);
        t5.r = tau->r * v[4].r - tau->i * v[4].i,
        t5.i = tau->r * v[4].i + tau->i * v[4].r;
        d_cnjg(&v6, &v[5]);
        t6.r = tau->r * v[5].r - tau->i * v[5].i,
        t6.i = tau->r * v[5].i + tau->i * v[5].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            ++i__1;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            ++i__1;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            ++i__1;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            ++i__1;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            ++i__1;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            ++i__1;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
        }
        return; /* exit zlarfx */
L130:

/*        Special code for 7 x 7 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        d_cnjg(&v4, &v[3]);
        t4.r = tau->r * v[3].r - tau->i * v[3].i,
        t4.i = tau->r * v[3].i + tau->i * v[3].r;
        d_cnjg(&v5, &v[4]);
        t5.r = tau->r * v[4].r - tau->i * v[4].i,
        t5.i = tau->r * v[4].i + tau->i * v[4].r;
        d_cnjg(&v6, &v[5]);
        t6.r = tau->r * v[5].r - tau->i * v[5].i,
        t6.i = tau->r * v[5].i + tau->i * v[5].r;
        d_cnjg(&v7, &v[6]);
        t7.r = tau->r * v[6].r - tau->i * v[6].i,
        t7.i = tau->r * v[6].i + tau->i * v[6].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            ++i__1;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            ++i__1;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            ++i__1;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            ++i__1;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            ++i__1;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            ++i__1;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            ++i__1;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            ++i__1;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
        }
        return; /* exit zlarfx */
L150:

/*        Special code for 8 x 8 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        d_cnjg(&v4, &v[3]);
        t4.r = tau->r * v[3].r - tau->i * v[3].i,
        t4.i = tau->r * v[3].i + tau->i * v[3].r;
        d_cnjg(&v5, &v[4]);
        t5.r = tau->r * v[4].r - tau->i * v[4].i,
        t5.i = tau->r * v[4].i + tau->i * v[4].r;
        d_cnjg(&v6, &v[5]);
        t6.r = tau->r * v[5].r - tau->i * v[5].i,
        t6.i = tau->r * v[5].i + tau->i * v[5].r;
        d_cnjg(&v7, &v[6]);
        t7.r = tau->r * v[6].r - tau->i * v[6].i,
        t7.i = tau->r * v[6].i + tau->i * v[6].r;
        d_cnjg(&v8, &v[7]);
        t8.r = tau->r * v[7].r - tau->i * v[7].i,
        t8.i = tau->r * v[7].i + tau->i * v[7].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            ++i__1;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            ++i__1;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            ++i__1;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            ++i__1;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            ++i__1;
            sum.r += v8.r * c[i__1].r - v8.i * c[i__1].i,
            sum.i += v8.r * c[i__1].i + v8.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            ++i__1;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            ++i__1;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            ++i__1;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            ++i__1;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
            ++i__1;
            c[i__1].r -= sum.r * t8.r - sum.i * t8.i,
            c[i__1].i -= sum.r * t8.i + sum.i * t8.r;
        }
        return; /* exit zlarfx */
L170:

/*        Special code for 9 x 9 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        d_cnjg(&v4, &v[3]);
        t4.r = tau->r * v[3].r - tau->i * v[3].i,
        t4.i = tau->r * v[3].i + tau->i * v[3].r;
        d_cnjg(&v5, &v[4]);
        t5.r = tau->r * v[4].r - tau->i * v[4].i,
        t5.i = tau->r * v[4].i + tau->i * v[4].r;
        d_cnjg(&v6, &v[5]);
        t6.r = tau->r * v[5].r - tau->i * v[5].i,
        t6.i = tau->r * v[5].i + tau->i * v[5].r;
        d_cnjg(&v7, &v[6]);
        t7.r = tau->r * v[6].r - tau->i * v[6].i,
        t7.i = tau->r * v[6].i + tau->i * v[6].r;
        d_cnjg(&v8, &v[7]);
        t8.r = tau->r * v[7].r - tau->i * v[7].i,
        t8.i = tau->r * v[7].i + tau->i * v[7].r;
        d_cnjg(&v9, &v[8]);
        t9.r = tau->r * v[8].r - tau->i * v[8].i,
        t9.i = tau->r * v[8].i + tau->i * v[8].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            ++i__1;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            ++i__1;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            ++i__1;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            ++i__1;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            ++i__1;
            sum.r += v8.r * c[i__1].r - v8.i * c[i__1].i,
            sum.i += v8.r * c[i__1].i + v8.i * c[i__1].r;
            ++i__1;
            sum.r += v9.r * c[i__1].r - v9.i * c[i__1].i,
            sum.i += v9.r * c[i__1].i + v9.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            ++i__1;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            ++i__1;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            ++i__1;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            ++i__1;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
            ++i__1;
            c[i__1].r -= sum.r * t8.r - sum.i * t8.i,
            c[i__1].i -= sum.r * t8.i + sum.i * t8.r;
            ++i__1;
            c[i__1].r -= sum.r * t9.r - sum.i * t9.i,
            c[i__1].i -= sum.r * t9.i + sum.i * t9.r;
        }
        return; /* exit zlarfx */
L190:

/*        Special code for 10 x 10 Householder */

        d_cnjg(&v1, v);
        t1.r = tau->r * v[0].r - tau->i * v[0].i,
        t1.i = tau->r * v[0].i + tau->i * v[0].r;
        d_cnjg(&v2, &v[1]);
        t2.r = tau->r * v[1].r - tau->i * v[1].i,
        t2.i = tau->r * v[1].i + tau->i * v[1].r;
        d_cnjg(&v3, &v[2]);
        t3.r = tau->r * v[2].r - tau->i * v[2].i,
        t3.i = tau->r * v[2].i + tau->i * v[2].r;
        d_cnjg(&v4, &v[3]);
        t4.r = tau->r * v[3].r - tau->i * v[3].i,
        t4.i = tau->r * v[3].i + tau->i * v[3].r;
        d_cnjg(&v5, &v[4]);
        t5.r = tau->r * v[4].r - tau->i * v[4].i,
        t5.i = tau->r * v[4].i + tau->i * v[4].r;
        d_cnjg(&v6, &v[5]);
        t6.r = tau->r * v[5].r - tau->i * v[5].i,
        t6.i = tau->r * v[5].i + tau->i * v[5].r;
        d_cnjg(&v7, &v[6]);
        t7.r = tau->r * v[6].r - tau->i * v[6].i,
        t7.i = tau->r * v[6].i + tau->i * v[6].r;
        d_cnjg(&v8, &v[7]);
        t8.r = tau->r * v[7].r - tau->i * v[7].i,
        t8.i = tau->r * v[7].i + tau->i * v[7].r;
        d_cnjg(&v9, &v[8]);
        t9.r = tau->r * v[8].r - tau->i * v[8].i,
        t9.i = tau->r * v[8].i + tau->i * v[8].r;
        d_cnjg(&v10, &v[9]);
        t10.r = tau->r * v[9].r - tau->i * v[9].i,
        t10.i = tau->r * v[9].i + tau->i * v[9].r;
        for (j = 0; j < *n; ++j) {
            i__1 = j * *ldc;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            ++i__1;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            ++i__1;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            ++i__1;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            ++i__1;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            ++i__1;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            ++i__1;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            ++i__1;
            sum.r += v8.r * c[i__1].r - v8.i * c[i__1].i,
            sum.i += v8.r * c[i__1].i + v8.i * c[i__1].r;
            ++i__1;
            sum.r += v9.r * c[i__1].r - v9.i * c[i__1].i,
            sum.i += v9.r * c[i__1].i + v9.i * c[i__1].r;
            ++i__1;
            sum.r += v10.r * c[i__1].r - v10.i * c[i__1].i,
            sum.i += v10.r * c[i__1].i + v10.i * c[i__1].r;
            i__1 = j * *ldc;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            ++i__1;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            ++i__1;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            ++i__1;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            ++i__1;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            ++i__1;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            ++i__1;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
            ++i__1;
            c[i__1].r -= sum.r * t8.r - sum.i * t8.i,
            c[i__1].i -= sum.r * t8.i + sum.i * t8.r;
            ++i__1;
            c[i__1].r -= sum.r * t9.r - sum.i * t9.i,
            c[i__1].i -= sum.r * t9.i + sum.i * t9.r;
            ++i__1;
            c[i__1].r -= sum.r * t10.r - sum.i * t10.i,
            c[i__1].i -= sum.r * t10.i + sum.i * t10.r;
        }
        return; /* exit zlarfx */
    } else {

/*        Form  C * H, where H has order n. */

        switch ((int)*n) {
            case 1:  goto L210;
            case 2:  goto L230;
            case 3:  goto L250;
            case 4:  goto L270;
            case 5:  goto L290;
            case 6:  goto L310;
            case 7:  goto L330;
            case 8:  goto L350;
            case 9:  goto L370;
            case 10:  goto L390;
        }

/*        Code for general N */

/*        w := C * v */

        zgemv_("No transpose", m, n, &c_b15, c, ldc, v, &c__1, &c_b2, work, &c__1, 12L);

/*        C := C - tau * w * v' */

        z__1.r = -tau->r, z__1.i = -tau->i;
        zgerc_(m, n, &z__1, work, &c__1, v, &c__1, c, ldc);
        return; /* exit zlarfx */
L210:

/*        Special code for 1 x 1 Householder */

        z__1.r = tau->r * v[0].r - tau->i * v[0].i,
        z__1.i = tau->r * v[0].i + tau->i * v[0].r;
        t1.r = 1. - z__1.r * v[0].r - z__1.i * v[0].i,
        t1.i = 0. + z__1.r * v[0].i - z__1.i * v[0].r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            z__1.r = t1.r * c[i__1].r - t1.i * c[i__1].i,
            z__1.i = t1.r * c[i__1].i + t1.i * c[i__1].r;
            c[i__1].r = z__1.r,
            c[i__1].i = z__1.i;
        }
        return; /* exit zlarfx */
L230:

/*        Special code for 2 x 2 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
        }
        return; /* exit zlarfx */
L250:

/*        Special code for 3 x 3 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
        }
        return; /* exit zlarfx */
L270:

/*        Special code for 4 x 4 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        v4.r = v[3].r, v4.i = v[3].i;
        d_cnjg(&z__1, &v4);
        t4.r = tau->r * z__1.r - tau->i * z__1.i,
        t4.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
        }
        return; /* exit zlarfx */
L290:

/*        Special code for 5 x 5 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        v4.r = v[3].r, v4.i = v[3].i;
        d_cnjg(&z__1, &v4);
        t4.r = tau->r * z__1.r - tau->i * z__1.i,
        t4.i = tau->r * z__1.i + tau->i * z__1.r;
        v5.r = v[4].r, v5.i = v[4].i;
        d_cnjg(&z__1, &v5);
        t5.r = tau->r * z__1.r - tau->i * z__1.i,
        t5.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
        }
        return; /* exit zlarfx */
L310:

/*        Special code for 6 x 6 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        v4.r = v[3].r, v4.i = v[3].i;
        d_cnjg(&z__1, &v4);
        t4.r = tau->r * z__1.r - tau->i * z__1.i,
        t4.i = tau->r * z__1.i + tau->i * z__1.r;
        v5.r = v[4].r, v5.i = v[4].i;
        d_cnjg(&z__1, &v5);
        t5.r = tau->r * z__1.r - tau->i * z__1.i,
        t5.i = tau->r * z__1.i + tau->i * z__1.r;
        v6.r = v[5].r, v6.i = v[5].i;
        d_cnjg(&z__1, &v6);
        t6.r = tau->r * z__1.r - tau->i * z__1.i,
        t6.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
        }
        return; /* exit zlarfx */
L330:

/*        Special code for 7 x 7 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        v4.r = v[3].r, v4.i = v[3].i;
        d_cnjg(&z__1, &v4);
        t4.r = tau->r * z__1.r - tau->i * z__1.i,
        t4.i = tau->r * z__1.i + tau->i * z__1.r;
        v5.r = v[4].r, v5.i = v[4].i;
        d_cnjg(&z__1, &v5);
        t5.r = tau->r * z__1.r - tau->i * z__1.i,
        t5.i = tau->r * z__1.i + tau->i * z__1.r;
        v6.r = v[5].r, v6.i = v[5].i;
        d_cnjg(&z__1, &v6);
        t6.r = tau->r * z__1.r - tau->i * z__1.i,
        t6.i = tau->r * z__1.i + tau->i * z__1.r;
        v7.r = v[6].r, v7.i = v[6].i;
        d_cnjg(&z__1, &v7);
        t7.r = tau->r * z__1.r - tau->i * z__1.i,
        t7.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
        }
        return; /* exit zlarfx */
L350:

/*        Special code for 8 x 8 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        v4.r = v[3].r, v4.i = v[3].i;
        d_cnjg(&z__1, &v4);
        t4.r = tau->r * z__1.r - tau->i * z__1.i,
        t4.i = tau->r * z__1.i + tau->i * z__1.r;
        v5.r = v[4].r, v5.i = v[4].i;
        d_cnjg(&z__1, &v5);
        t5.r = tau->r * z__1.r - tau->i * z__1.i,
        t5.i = tau->r * z__1.i + tau->i * z__1.r;
        v6.r = v[5].r, v6.i = v[5].i;
        d_cnjg(&z__1, &v6);
        t6.r = tau->r * z__1.r - tau->i * z__1.i,
        t6.i = tau->r * z__1.i + tau->i * z__1.r;
        v7.r = v[6].r, v7.i = v[6].i;
        d_cnjg(&z__1, &v7);
        t7.r = tau->r * z__1.r - tau->i * z__1.i,
        t7.i = tau->r * z__1.i + tau->i * z__1.r;
        v8.r = v[7].r, v8.i = v[7].i;
        d_cnjg(&z__1, &v8);
        t8.r = tau->r * z__1.r - tau->i * z__1.i,
        t8.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v8.r * c[i__1].r - v8.i * c[i__1].i,
            sum.i += v8.r * c[i__1].i + v8.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t8.r - sum.i * t8.i,
            c[i__1].i -= sum.r * t8.i + sum.i * t8.r;
        }
        return; /* exit zlarfx */
L370:

/*        Special code for 9 x 9 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        v4.r = v[3].r, v4.i = v[3].i;
        d_cnjg(&z__1, &v4);
        t4.r = tau->r * z__1.r - tau->i * z__1.i,
        t4.i = tau->r * z__1.i + tau->i * z__1.r;
        v5.r = v[4].r, v5.i = v[4].i;
        d_cnjg(&z__1, &v5);
        t5.r = tau->r * z__1.r - tau->i * z__1.i,
        t5.i = tau->r * z__1.i + tau->i * z__1.r;
        v6.r = v[5].r, v6.i = v[5].i;
        d_cnjg(&z__1, &v6);
        t6.r = tau->r * z__1.r - tau->i * z__1.i,
        t6.i = tau->r * z__1.i + tau->i * z__1.r;
        v7.r = v[6].r, v7.i = v[6].i;
        d_cnjg(&z__1, &v7);
        t7.r = tau->r * z__1.r - tau->i * z__1.i,
        t7.i = tau->r * z__1.i + tau->i * z__1.r;
        v8.r = v[7].r, v8.i = v[7].i;
        d_cnjg(&z__1, &v8);
        t8.r = tau->r * z__1.r - tau->i * z__1.i,
        t8.i = tau->r * z__1.i + tau->i * z__1.r;
        v9.r = v[8].r, v9.i = v[8].i;
        d_cnjg(&z__1, &v9);
        t9.r = tau->r * z__1.r - tau->i * z__1.i,
        t9.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v8.r * c[i__1].r - v8.i * c[i__1].i,
            sum.i += v8.r * c[i__1].i + v8.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v9.r * c[i__1].r - v9.i * c[i__1].i,
            sum.i += v9.r * c[i__1].i + v9.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t8.r - sum.i * t8.i,
            c[i__1].i -= sum.r * t8.i + sum.i * t8.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t9.r - sum.i * t9.i,
            c[i__1].i -= sum.r * t9.i + sum.i * t9.r;
        }
        return; /* exit zlarfx */
L390:

/*        Special code for 10 x 10 Householder */

        v1.r = v[0].r, v1.i = v[0].i;
        d_cnjg(&z__1, &v1);
        t1.r = tau->r * z__1.r - tau->i * z__1.i,
        t1.i = tau->r * z__1.i + tau->i * z__1.r;
        v2.r = v[1].r, v2.i = v[1].i;
        d_cnjg(&z__1, &v2);
        t2.r = tau->r * z__1.r - tau->i * z__1.i,
        t2.i = tau->r * z__1.i + tau->i * z__1.r;
        v3.r = v[2].r, v3.i = v[2].i;
        d_cnjg(&z__1, &v3);
        t3.r = tau->r * z__1.r - tau->i * z__1.i,
        t3.i = tau->r * z__1.i + tau->i * z__1.r;
        v4.r = v[3].r, v4.i = v[3].i;
        d_cnjg(&z__1, &v4);
        t4.r = tau->r * z__1.r - tau->i * z__1.i,
        t4.i = tau->r * z__1.i + tau->i * z__1.r;
        v5.r = v[4].r, v5.i = v[4].i;
        d_cnjg(&z__1, &v5);
        t5.r = tau->r * z__1.r - tau->i * z__1.i,
        t5.i = tau->r * z__1.i + tau->i * z__1.r;
        v6.r = v[5].r, v6.i = v[5].i;
        d_cnjg(&z__1, &v6);
        t6.r = tau->r * z__1.r - tau->i * z__1.i,
        t6.i = tau->r * z__1.i + tau->i * z__1.r;
        v7.r = v[6].r, v7.i = v[6].i;
        d_cnjg(&z__1, &v7);
        t7.r = tau->r * z__1.r - tau->i * z__1.i,
        t7.i = tau->r * z__1.i + tau->i * z__1.r;
        v8.r = v[7].r, v8.i = v[7].i;
        d_cnjg(&z__1, &v8);
        t8.r = tau->r * z__1.r - tau->i * z__1.i,
        t8.i = tau->r * z__1.i + tau->i * z__1.r;
        v9.r = v[8].r, v9.i = v[8].i;
        d_cnjg(&z__1, &v9);
        t9.r = tau->r * z__1.r - tau->i * z__1.i,
        t9.i = tau->r * z__1.i + tau->i * z__1.r;
        v10.r = v[9].r, v10.i = v[9].i;
        d_cnjg(&z__1, &v10);
        t10.r = tau->r * z__1.r - tau->i * z__1.i,
        t10.i = tau->r * z__1.i + tau->i * z__1.r;
        for (j = 0; j < *m; ++j) {
            i__1 = j;
            sum.r = v1.r * c[i__1].r - v1.i * c[i__1].i,
            sum.i = v1.r * c[i__1].i + v1.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v2.r * c[i__1].r - v2.i * c[i__1].i,
            sum.i += v2.r * c[i__1].i + v2.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v3.r * c[i__1].r - v3.i * c[i__1].i,
            sum.i += v3.r * c[i__1].i + v3.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v4.r * c[i__1].r - v4.i * c[i__1].i,
            sum.i += v4.r * c[i__1].i + v4.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v5.r * c[i__1].r - v5.i * c[i__1].i,
            sum.i += v5.r * c[i__1].i + v5.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v6.r * c[i__1].r - v6.i * c[i__1].i,
            sum.i += v6.r * c[i__1].i + v6.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v7.r * c[i__1].r - v7.i * c[i__1].i,
            sum.i += v7.r * c[i__1].i + v7.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v8.r * c[i__1].r - v8.i * c[i__1].i,
            sum.i += v8.r * c[i__1].i + v8.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v9.r * c[i__1].r - v9.i * c[i__1].i,
            sum.i += v9.r * c[i__1].i + v9.i * c[i__1].r;
            i__1 += *ldc;
            sum.r += v10.r * c[i__1].r - v10.i * c[i__1].i,
            sum.i += v10.r * c[i__1].i + v10.i * c[i__1].r;
            i__1 = j;
            c[i__1].r -= sum.r * t1.r - sum.i * t1.i,
            c[i__1].i -= sum.r * t1.i + sum.i * t1.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t2.r - sum.i * t2.i,
            c[i__1].i -= sum.r * t2.i + sum.i * t2.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t3.r - sum.i * t3.i,
            c[i__1].i -= sum.r * t3.i + sum.i * t3.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t4.r - sum.i * t4.i,
            c[i__1].i -= sum.r * t4.i + sum.i * t4.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t5.r - sum.i * t5.i,
            c[i__1].i -= sum.r * t5.i + sum.i * t5.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t6.r - sum.i * t6.i,
            c[i__1].i -= sum.r * t6.i + sum.i * t6.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t7.r - sum.i * t7.i,
            c[i__1].i -= sum.r * t7.i + sum.i * t7.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t8.r - sum.i * t8.i,
            c[i__1].i -= sum.r * t8.i + sum.i * t8.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t9.r - sum.i * t9.i,
            c[i__1].i -= sum.r * t9.i + sum.i * t9.r;
            i__1 += *ldc;
            c[i__1].r -= sum.r * t10.r - sum.i * t10.i,
            c[i__1].i -= sum.r * t10.i + sum.i * t10.r;
        }
        return; /* exit zlarfx */
    }

/*     End of ZLARFX */

} /* zlarfx_ */

