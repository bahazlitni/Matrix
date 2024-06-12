#include <stdio.h>
#include <stdlib.h>

void inv(double **A, int n)
{
    double **I = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        I[i] = (double *)calloc(n, sizeof(double));
        I[i][i] = 1.0;
    }

    double alpha, pivot;
    int i, j, k;
    for (int i = 0; i < n; i++)
    {
        j = i;
        while (!A[j][i])
        {
            j++;
            if (j == n)
            {
                for (i = 0; i < n; i++)
                {
                    free(I[i]);
                }
                free(I);
                return;
            }
        }

        if (j != i)
        {
            double *temp = A[i];
            A[i] = A[j];
            A[j] = temp;

            temp = I[i];
            I[i] = I[j];
            I[j] = temp;
        }
        pivot = A[i][i];
        for (j = 0; j < n; j++)
        {
            I[i][j] /= pivot;
            A[i][j] /= pivot;
        }

        for (j = 0; j < i; ++j)
        {
            alpha = A[j][i];
            for (k = 0; k < n; ++k)
            {
                A[j][k] -= alpha * A[i][k];
                I[j][k] -= alpha * I[i][k];
            }
        }
        for (j = i + 1; j < n; ++j)
        {
            alpha = A[j][i];
            for (k = 0; k < n; ++k)
            {
                A[j][k] -= alpha * A[i][k];
                I[j][k] -= alpha * I[i][k];
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        A[i] = I[i];
        free(I[i]);
    }
    free(I);
}