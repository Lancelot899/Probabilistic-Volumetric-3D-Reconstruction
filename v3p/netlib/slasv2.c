/* slasv2.f -- translated by f2c (version of 4 June 1993  1:43:59).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static real c_b3 = 2.f;
static real c_b4 = 1.f;

/* Subroutine */ void slasv2_(real *f, real *g, real *h, real *ssmin, real *
        ssmax, real *snr, real *csr, real *snl, real *csl)
{
    /* System generated locals */
    real r__1;

    /* Builtin functions */
    double sqrt(doublereal), r_sign(real *, real *);

    /* Local variables */
    static integer pmax;
    static real temp;
    static logical swap;
    static real a, d, l, m, r, s, t, tsign, fa, ga, ha, ft, gt, ht, mm;
    static logical gasmal;
    extern doublereal slamch_(char *);
    static real tt, clt, crt, slt, srt;


/*  -- LAPACK auxiliary routine (version 2.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     October 31, 1992 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SLASV2 computes the singular value decomposition of a 2-by-2 */
/*  triangular matrix */
/*     [  F   G  ] */
/*     [  0   H  ]. */
/*  On return, abs(SSMAX) is the larger singular value, abs(SSMIN) is the
*/
/*  smaller singular value, and (CSL,SNL) and (CSR,SNR) are the left and
*/
/*  right singular vectors for abs(SSMAX), giving the decomposition */

/*     [ CSL  SNL ] [  F   G  ] [ CSR -SNR ]  =  [ SSMAX   0   ] */
/*     [-SNL  CSL ] [  0   H  ] [ SNR  CSR ]     [  0    SSMIN ]. */

/*  Arguments */
/*  ========= */

/*  F       (input) REAL */
/*          The (1,1) element of the 2-by-2 matrix. */

/*  G       (input) REAL */
/*          The (1,2) element of the 2-by-2 matrix. */

/*  H       (input) REAL */
/*          The (2,2) element of the 2-by-2 matrix. */

/*  SSMIN   (output) REAL */
/*          abs(SSMIN) is the smaller singular value. */

/*  SSMAX   (output) REAL */
/*          abs(SSMAX) is the larger singular value. */

/*  SNL     (output) REAL */
/*  CSL     (output) REAL */
/*          The vector (CSL, SNL) is a unit left singular vector for the
*/
/*          singular value abs(SSMAX). */

/*  SNR     (output) REAL */
/*  CSR     (output) REAL */
/*          The vector (CSR, SNR) is a unit right singular vector for the
*/
/*          singular value abs(SSMAX). */

/*  Further Details */
/*  =============== */

/*  Any input parameter may be aliased with any output parameter. */

/*  Barring over/underflow and assuming a guard digit in subtraction, all
*/
/*  output quantities are correct to within a few units in the last */
/*  place (ulps). */

/*  In IEEE arithmetic, the code works correctly if one matrix element is
*/
/*  infinite. */

/*  Overflow will not occur unless the largest singular value itself */
/*  overflows or is within a few ulps of overflow. (On machines with */
/*  partial overflow, like the Cray, overflow may occur if the largest */
/*  singular value is within a factor of 2 of overflow.) */

/*  Underflow is harmless if underflow is gradual. Otherwise, results */
/*  may correspond to a matrix modified by perturbations of size near */
/*  the underflow threshold. */

/* =====================================================================
*/

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    ft = *f;
    fa = abs(ft);
    ht = *h;
    ha = abs(*h);

/*     PMAX points to the maximum absolute element of matrix */
/*       PMAX = 1 if F largest in absolute values */
/*       PMAX = 2 if G largest in absolute values */
/*       PMAX = 3 if H largest in absolute values */

    pmax = 1;
    swap = ha > fa;
    if (swap) {
        pmax = 3;
        temp = ft;
        ft = ht;
        ht = temp;
        temp = fa;
        fa = ha;
        ha = temp;

/*        Now FA .ge. HA */

    }
    gt = *g;
    ga = abs(gt);
    if (ga == 0.f) {

/*        Diagonal matrix */

        *ssmin = ha;
        *ssmax = fa;
        clt = 1.f;
        crt = 1.f;
        slt = 0.f;
        srt = 0.f;
    } else {
        gasmal = TRUE_;
        if (ga > fa) {
            pmax = 2;
            if (fa / ga < slamch_("EPS")) {

/*              Case of very large GA */

                gasmal = FALSE_;
                *ssmax = ga;
                if (ha > 1.f) {
                    *ssmin = fa / (ga / ha);
                } else {
                    *ssmin = fa / ga * ha;
                }
                clt = 1.f;
                slt = ht / gt;
                srt = 1.f;
                crt = ft / gt;
            }
        }
        if (gasmal) {

/*           Normal case */

            d = fa - ha;
            if (d == fa) {

/*              Copes with infinite F or H */

                l = 1.f;
            } else {
                l = d / fa;
            }

/*           Note that 0 .le. L .le. 1 */

            m = gt / ft;

/*           Note that abs(M) .le. 1/macheps */

            t = 2.f - l;

/*           Note that T .ge. 1 */

            mm = m * m;
            tt = t * t;
            s = sqrt(tt + mm);

/*           Note that 1 .le. S .le. 1 + 1/macheps */

            if (l == 0.f) {
                r = abs(m);
            } else {
                r = sqrt(l * l + mm);
            }

/*           Note that 0 .le. R .le. 1 + 1/macheps */

            a = (s + r) * .5f;

/*           Note that 1 .le. A .le. 1 + abs(M) */

            *ssmin = ha / a;
            *ssmax = fa * a;
            if (mm == 0.f) {

/*              Note that M is very tiny */

                if (l == 0.f) {
                    t = r_sign(&c_b3, &ft) * r_sign(&c_b4, &gt);
                } else {
                    t = gt / r_sign(&d, &ft) + m / t;
                }
            } else {
                t = (m / (s + t) + m / (r + l)) * (a + 1.f);
            }
            l = sqrt(t * t + 4.f);
            crt = 2.f / l;
            srt = t / l;
            clt = (crt + srt * m) / a;
            slt = ht / ft * srt / a;
        }
    }
    if (swap) {
        *csl = srt;
        *snl = crt;
        *csr = slt;
        *snr = clt;
    } else {
        *csl = clt;
        *snl = slt;
        *csr = crt;
        *snr = srt;
    }

/*     Correct signs of SSMAX and SSMIN */

    if (pmax == 1) {
        tsign = r_sign(&c_b4, csr) * r_sign(&c_b4, csl) * r_sign(&c_b4, f);
    }
    if (pmax == 2) {
        tsign = r_sign(&c_b4, snr) * r_sign(&c_b4, csl) * r_sign(&c_b4, g);
    }
    if (pmax == 3) {
        tsign = r_sign(&c_b4, snr) * r_sign(&c_b4, snl) * r_sign(&c_b4, h);
    }
    *ssmax = r_sign(ssmax, &tsign);
    r__1 = tsign * r_sign(&c_b4, f) * r_sign(&c_b4, h);
    *ssmin = r_sign(ssmin, &r__1);

/*     End of SLASV2 */

} /* slasv2_ */

