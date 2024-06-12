#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 1000 // Adjust based on your needs

double** MemoryAllocationFailure() {
    fprintf(stderr, "[FATAL ERROR]: Memory Allocation Failure.\n");
    return NULL;
}


// Gaussian elimination with partial pivoting
double** inv(double** A, int n)
{
    double** I = (double**)malloc(n * sizeof(double*));

    if (I == NULL)
        return MemoryAllocationFailure();

    int* rows = (int*)malloc(n * sizeof(int));

    if (rows == NULL)
        return MemoryAllocationFailure();

    for (int i = 0; i < n; i++)
    {
        rows[i] = i;
        I[i] = (double*)malloc(n * sizeof(double));

        if (I[i] == NULL)
            return MemoryAllocationFailure();

        for (int j = 0; j < n; j++)
            I[i][j] = (double)(i == j);
    }

    for (int i = 0; i < n; i++)
    {
        int maxRow = i;
        double div = fabs(A[rows[i]][i]);
        for (int j = i + 1; j < n; j++)
        {
            double v = fabs(A[rows[j]][i]);
            if (v > div)
            {
                maxRow = j;
                div = v;
            }
        }
        if (div == 0)
            return NULL;

        int temp = rows[i];
        rows[i] = maxRow;
        rows[maxRow] = temp;

        for (int j = 0; j < n; j++)
        {
            A[rows[i]][j] /= div;
            I[rows[i]][j] /= div;
        }

        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            double alpha = A[rows[j]][i];
            for (int k = 0; k < n; k++)
            {
                A[rows[j]][k] -= alpha * A[rows[i]][k];
                I[rows[j]][k] -= alpha * I[rows[i]][k];
            }
        }
    }

    free(rows);
    return I;
}

void displayMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Example Usage (Replace with your matrix input and handling)
int main()
{
    int n = 3;
    double A[][MAX_SIZE] = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0} };
    double** invA = inv((double**)A, n);

    if (invA == NULL)
    {
        printf("Singular matrix!\n");
    }
    else
    {
        displayMatrix(invA, n);
    }
    return 0;
}