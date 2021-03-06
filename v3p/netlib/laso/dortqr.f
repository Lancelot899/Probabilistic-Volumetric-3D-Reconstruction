C
C ------------------------------------------------------------------
C
      SUBROUTINE DORTQR(NZ, N, NBLOCK, Z, B)
C
      INTEGER NZ, N, NBLOCK
      DOUBLE PRECISION Z(NZ,1), B(NBLOCK,1)
C
C THIS SUBROUTINE COMPUTES THE QR FACTORIZATION OF THE N X NBLOCK
C MATRIX Z.  Q IS FORMED IN PLACE AND RETURNED IN Z.  R IS
C RETURNED IN B.
C
      INTEGER I, J, K, LENGTH, M
      DOUBLE PRECISION SIGMA, TAU, TEMP, DDOT, DNRM2, DSIGN
      EXTERNAL DAXPY, DDOT, DNRM2, DSCAL
C
C THIS SECTION REDUCES Z TO TRIANGULAR FORM.
C
      DO 30 I=1,NBLOCK
C
C THIS FORMS THE ITH REFLECTION.
C
         LENGTH = N - I + 1
         SIGMA = DSIGN(DNRM2(LENGTH,Z(I,I),1),Z(I,I))
         B(I,I) = -SIGMA
         Z(I,I) = Z(I,I) + SIGMA
         TAU = SIGMA*Z(I,I)
         IF (I.EQ.NBLOCK) GO TO 30
         J = I + 1
C
C THIS APPLIES THE ROTATION TO THE REST OF THE COLUMNS.
C
         DO 20 K=J,NBLOCK
            IF (TAU.EQ.0.0D0) GO TO 10
            TEMP = -DDOT(LENGTH,Z(I,I),1,Z(I,K),1)/TAU
            CALL DAXPY(LENGTH, TEMP, Z(I,I), 1, Z(I,K), 1)
   10       B(I,K) = Z(I,K)
            Z(I,K) = 0.0D0
   20    CONTINUE
   30 CONTINUE
C
C THIS ACCUMULATES THE REFLECTIONS IN REVERSE ORDER.
C
      DO 70 M=1,NBLOCK
C
C THIS RECREATES THE ITH = NBLOCK-M+1)TH REFLECTION.
C
         I = NBLOCK + 1 - M
         SIGMA = -B(I,I)
         TAU = Z(I,I)*SIGMA
         IF (TAU.EQ.0.0D0) GO TO 60
         LENGTH = N - NBLOCK + M
         IF (I.EQ.NBLOCK) GO TO 50
         J = I + 1
C
C THIS APPLIES IT TO THE LATER COLUMNS.
C
         DO 40 K=J,NBLOCK
            TEMP = -DDOT(LENGTH,Z(I,I),1,Z(I,K),1)/TAU
            CALL DAXPY(LENGTH, TEMP, Z(I,I), 1, Z(I,K), 1)
   40    CONTINUE
   50    CALL DSCAL(LENGTH, -1.0D0/SIGMA, Z(I,I), 1)
   60    Z(I,I) = 1.0D0 + Z(I,I)
   70 CONTINUE
      RETURN
      END
