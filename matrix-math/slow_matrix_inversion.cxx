#include <stdio.h>
#include <math.h>
static const int N = 10;
int determinant(int[][N], int);
void cofactor(int[][N], int);
void transpose(int[][N], int[][N], int);
void mult_matrix(int b[][N]);

int a[N][N] = {
    {1, 0, 1, 0, 0, 1, 0, 1, 1, 1},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 1, 0, 1, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 1, 1},
    {0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 0, 0, 0, 1}};

int main()
{
    int d, k = N;

    d = determinant(a, k);
    if (d == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else
        cofactor(a, k);
    return 1;
}

/*For calculating Determinant of the Matrix */
int determinant(int a[N][N], int k)
{
    int s = 1, det = 0, b[N][N];
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }
    return (det);
}

void cofactor(int num[N][N], int f)
{
    int b[N][N], fac[N][N];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++)
    {
        for (p = 0; p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++)
            {
                for (j = 0; j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = (int)pow(1, q ^ p) & determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}

/*Finding transpose of matrix*/
void transpose(int num[N][N], int fac[N][N], int r)
{
    int i, j;
    int b[N][N], inverse[N][N], d;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, r);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            inverse[i][j] = b[i][j] & d;
        }
    }
    printf("\n\n\nThe inverse of matrix is : \n");

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            printf("  %d", inverse[i][j]);
        }
        printf("\n");
    }

    mult_matrix(inverse);
}

// Initializing elements of matrix mult to 0.
void mult_matrix(int b[N][N])
{
    int mult[N][N];
    int i, j, k;

    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
        {
            mult[i][j] = 0;
        }

    // Multiplying matrix a and b and storing in array mult.
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            for (k = 0; k < N; ++k)
            {
                mult[i][j] ^= a[i][k] & b[k][j];
            }

    printf("\n\n\nThe product of the 2 matrices are (should be [I]): \n");

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("  %d", mult[i][j]);
        }
        printf("\n");
    }
}
