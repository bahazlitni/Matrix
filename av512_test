#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h> // Include for AVX2 intrinsics
#include <time.h>

double *addArrays_AVX2(double *A, double *B, int size)
{
    double *result = (double *)_aligned_malloc(32, size * sizeof(double));

    for (int i = 0; i < size; i += 4)
    {
        _mm256_store_pd(
            &result[i],
            _mm256_add_pd(
                _mm256_load_pd(&A[i]),
                _mm256_load_pd(&B[i]))); // Store the result
    }

    return result;
}

double *addArrays_AVX512(double *A, double *B, int size)
{
    double *result = (double *)_aligned_malloc(64, size * sizeof(double));

    for (int i = 0; i < size; i += 8)
    {
        _mm512_store_pd(
            &result[i],
            _mm512_add_pd(
                _mm512_load_pd(&A[i]),
                _mm512_load_pd(&B[i]))); // Store the result
    }

    return result;
}

// Display function remains the same...
void displayArray(double *arr, int size, char *name)
{
    printf("%s: [", name);
    for (int i = 0; i < size; i++)
    {
        printf("%.2lf ", arr[i]);
    }
    printf("]\n");
}

double *createRandomArray(int n, double lowerBound, double upperBound)
{
    double *arr = (double *)malloc(n * sizeof(double));
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Seed the random number generator (important for different results each time)
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        // Generate a random double between lowerBound and upperBound
        double randomValue = lowerBound + (upperBound - lowerBound) * (double)rand() / RAND_MAX;
        arr[i] = randomValue;
    }

    return arr;
}

int main()
{
    int size = 64;
    printf("Size: %i\n", size);

    double *A = createRandomArray(size, -100.0, 100.0);
    double *B = createRandomArray(size, -100.0, 100.0);
    double *sum = addArrays_AVX512(A, B, size);

    displayArray(A, size, (char *)"A");
    displayArray(B, size, (char *)"B");
    displayArray(sum, size, (char *)"Sum (AVX2)");

    free(sum);
    system("pause"); // Wait for a key press
    return 0;
}
