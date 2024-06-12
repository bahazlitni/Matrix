#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double det(double **A, int n)
{
    double alpha, diag, ln_d = 0.0;
    int sign = 1;
    int k, i, j;
    for (int k = 0; k < n; ++k)
    {
        if (!A[k][k])
        {
            j = k;
            for (i = k + 1; i < n; ++i)
            {
                if (fabs(A[i][k]) > fabs(A[j][k]))
                    j = i;
            }
            if (j == k)
                return 0;
            double *temp = A[k];
            A[k] = A[j];
            A[j] = temp;
        }
        sign = -sign;
        diag = A[k][k];

        for (i = k + 1; i < n; ++i)
        {
            alpha = A[i][k] / diag;
            for (j = k + 1; j < n; ++j)
                A[i][j] -= alpha * A[k][j];
        }
        if (diag < 0)
        {
            sign = -sign;
            ln_d += log(-diag);
        }
        else
            ln_d += log(diag);
    }

    return exp(ln_d) * sign;
}
