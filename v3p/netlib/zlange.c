/*  -- translated by f2c (version of 23 April 1993  18:34:30).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Modified by Peter Vanroose, June 2001: manual optimisation and clean-up */

/* Table of constant values */

static integer c__1 = 1;

doublereal zlange_(norm, m, n, a, lda, work, norm_len)
char *norm;
integer *m, *n;
doublecomplex *a;
integer *lda;
doublereal *work;
ftnlen norm_len;
{
    /* Builtin functions */
    double z_abs(), sqrt();

    /* Local variables */
    static integer i, j;
    static doublereal scale;
    extern logical lsame_();
    static doublereal value;
    extern /* Subroutine */ void zlassq_();
    static doublereal sum;


/*  -- LAPACK auxiliary routine (version 2.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     October 31, 1992 */

/* ===================================================================== */
/*                                                                       */
/*  Purpose                                                              */
/*  =======                                                              */
/*                                                                       */
/*  ZLANGE  returns the value of the one norm,  or the Frobenius norm, or*/
/*  the  infinity norm,  or the  element of  largest absolute value  of a*/
/*  complex matrix A.                                                    */
/*                                                                       */
/*  Description                                                          */
/*  ===========                                                          */
/*                                                                       */
/*  ZLANGE returns the value                                             */
/*                                                                       */
/*     ZLANGE = ( max(abs(A(i,j))), NORM = 'M' or 'm'                    */
/*              (                                                        */
/*              ( norm1(A),         NORM = '1', 'O' or 'o'               */
/*              (                                                        */
/*              ( normI(A),         NORM = 'I' or 'i'                    */
/*              (                                                        */
/*              ( normF(A),         NORM = 'F', 'f', 'E' or 'e'          */
/*                                                                       */
/*  where norm1  denotes the  one norm of a matrix (maximum column sum), */
/*  normI  denotes the  infinity norm of a matrix  (maximum row sum) and */
/*  normF denotes the  Frobenius norm of a matrix (square root of sum of */
/*  squares).  Note that  max(abs(A(i,j)))  is not a  matrix norm.       */
/*                                                                       */
/*  Arguments                                                            */
/*  =========                                                            */
/*                                                                       */
/*  NORM    (input) CHARACTER*1                                          */
/*          Specifies the value to be returned in ZLANGE as described    */
/*          above.                                                       */
/*                                                                       */
/*  M       (input) INTEGER                                              */
/*          The number of rows of the matrix A.  M >= 0.  When M = 0,    */
/*          ZLANGE is set to zero.                                       */
/*                                                                       */
/*  N       (input) INTEGER                                              */
/*          The number of columns of the matrix A.  N >= 0.  When N = 0, */
/*          ZLANGE is set to zero.                                       */
/*                                                                       */
/*  A       (input) COMPLEX*16 array, dimension (LDA,N)                  */
/*          The m by n matrix A.                                         */
/*                                                                       */
/*  LDA     (input) INTEGER                                              */
/*          The leading dimension of the array A.  LDA >= max(M,1).      */
/*                                                                       */
/*  WORK    (workspace) DOUBLE PRECISION array, dimension (LWORK),       */
/*          where LWORK >= M when NORM = 'I'; otherwise, WORK is not     */
/*          referenced.                                                  */
/*                                                                       */
/* ===================================================================== */

    /* Function Body */

    if (min(*m,*n) == 0) {
        value = 0.;
    } else if (lsame_(norm, "M", 1L, 1L)) {

/*        Find max(abs(A(i,j))). */

        value = 0.;
        for (j = 0; j < *n; ++j) {
            for (i = 0; i < *m; ++i) {
                value = max(value, z_abs(&a[i + j * *lda]));
            }
        }
    } else if (lsame_(norm, "O", 1L, 1L) || *norm == '1') {

/*        Find norm1(A). */

        value = 0.;
        for (j = 0; j < *n; ++j) {
            sum = 0.;
            for (i = 0; i < *m; ++i) {
                sum += z_abs(&a[i + j * *lda]);
            }
            value = max(value,sum);
        }
    } else if (lsame_(norm, "I", 1L, 1L)) {

/*        Find normI(A). */

        for (i = 0; i < *m; ++i) {
            work[i] = 0.;
        }
        for (j = 0; j < *n; ++j) {
            for (i = 0; i < *m; ++i) {
                work[i] += z_abs(&a[i + j * *lda]);
            }
        }
        value = 0.;
        for (i = 0; i < *m; ++i) {
            value = max(value, work[i]);
        }
    } else if (lsame_(norm, "F", 1L, 1L) || lsame_(norm, "E", 1L, 1L)) {

/*        Find normF(A). */

        scale = 0.;
        sum = 1.;
        for (j = 0; j < *n; ++j) {
            zlassq_(m, &a[j * *lda], &c__1, &scale, &sum);
        }
        value = scale * sqrt(sum);
    }

    return value;

/*     End of ZLANGE */

} /* zlange_ */

