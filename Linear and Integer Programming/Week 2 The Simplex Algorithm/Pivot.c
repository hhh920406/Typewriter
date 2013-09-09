#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPS 1e-8

typedef struct
{
    int n, m;
    int *B, *N;
    double *b, **a, z0, *c;
} Dict;
typedef Dict* PDict;

PDict createDict()
{
    PDict dict = (Dict*)malloc(sizeof(Dict));
    dict->B = 0L;
    dict->N = 0L;
    dict->b = 0L;
    dict->a = 0L;
    dict->c = 0L;
    return dict;
}

void releaseDict(PDict dict)
{
    int i;
    if (0L != dict->B)
    {
        free(dict->B);
    }
    if (0L != dict->N)
    {
        free(dict->N);
    }
    if (0L != dict->b)
    {
        free(dict->b);
    }
    if (0L != dict->a)
    {
        for (i = 0; i < dict->m; ++i)
        {
            free(dict->a[i]);
        }
        free(dict->a);
    }
    if (0L != dict->c)
    {
        free(dict->c);
    }
}

void readDict(PDict dict)
{
    int i, j;
    releaseDict(dict);
    scanf("%d%d", &dict->m, &dict->n);
    dict->B = (int*)malloc(dict->m * sizeof(int));
    for (i = 0; i < dict->m; ++i)
    {
        scanf("%d", &dict->B[i]);
    }
    dict->N = (int*)malloc(dict->n * sizeof(int));
    for (i = 0; i < dict->n; ++i)
    {
        scanf("%d", &dict->N[i]);
    }
    dict->b = (double*)malloc(dict->m * sizeof(double));
    for (i = 0; i < dict->m; ++i)
    {
        scanf("%lf", &dict->b[i]);
    }
    dict->a = (double**)malloc(dict->m * sizeof(double*));
    for (i = 0; i < dict->m; ++i)
    {
        dict->a[i] = (double*)malloc(dict->n * sizeof(double));
        for (j = 0; j < dict->n; ++j)
        {
            scanf("%lf", &dict->a[i][j]);
        }
    }
    scanf("%lf", &dict->z0);
    dict->c = (double*)malloc(dict->n * sizeof(double));
    for (i = 0; i < dict->n; ++i)
    {
        scanf("%lf", &dict->c[i]);
    }
}

void printDict(PDict dict)
{
    int i, j;
    printf("Dictionary: \n");
    for (i = 0; i < dict->m; ++i)
    {
        printf("x%d\t| ", dict->B[i]);
        if (fabs(dict->b[i]) > EPS)
        {
            printf("%.1lf", dict->b[i]);
        }
        for (j = 0; j < dict->n; ++j)
        {
            putchar('\t');
            if (dict->a[i][j] > 0)
            {
                putchar('+');
            }
            if (fabs(dict->a[i][j]) > EPS)
            {
                printf("%.1lfx%d", dict->a[i][j], dict->N[j]);
            }
        }
        putchar('\n');
    }
    for (i = 0; i <= dict->n + 1; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            putchar('-');
        }
    }
    putchar('\n');
    printf("z\t| ");
    if (fabs(dict->z0) > EPS)
    {
        printf("%.1lf", dict->z0);
    }
    for (i = 0; i < dict->n; ++i)
    {
        putchar('\t');
        if (dict->c[i] > 0)
        {
            putchar('+');
        }
        if (fabs(dict->c[i]) > EPS)
        {
            printf("%.1lfx%d", dict->c[i], dict->N[i]);
        }
    }
    putchar('\n');
    putchar('\n');
}

int getEnteringIndex(PDict dict)
{
    int i, j, index = -1;
    for (i = 0; i < dict->n; ++i)
    {
        if (dict->c[i] > EPS)
        {
            for (j = 0; j < dict->m; ++j)
            {
                if (dict->a[j][i] < -EPS)
                {
                    break;
                }
            }
            if (j != dict->m)
            {
                if (index == -1)
                {
                    index = i;
                }
                else if (dict->N[i] < dict->N[index])
                {
                    index = i;
                }
            }
        }
    }
    return index;
}

int getLeavingIndex(PDict dict, int enterIndex)
{
    int i, index = -1;
    for (i = 0; i < dict->m; ++i)
    {
        if (dict->a[i][enterIndex] < -EPS)
        {
            if (-1 == index)
            {
                index = i;
            }
            else if (dict->b[i] / dict->a[i][enterIndex] -
                      dict->b[index] / dict->a[index][enterIndex] > EPS)
            {
                index = i;
            }
            else if (fabs(dict->b[i] / dict->a[i][enterIndex] -
                           dict->b[index] / dict->a[index][enterIndex]) < EPS)
            {
                if (dict->B[i] < dict->B[index])
                {
                    index = i;
                }
            }
        }
    }
    return index;
}

void transformDict(PDict dict, int enterIndex, int leaveIndex)
{
    int i, j;
    double temp;
    temp = - dict->a[leaveIndex][enterIndex];
    dict->b[leaveIndex] /= temp;
    for (i = 0; i < dict->n; ++i)
    {
        dict->a[leaveIndex][i] /= temp;
    }
    dict->a[leaveIndex][enterIndex] = -1.0 / temp;
    for (i = 0; i < dict->m; ++i)
    {
        if (i != leaveIndex)
        {
            temp = dict->a[i][enterIndex];
            dict->a[i][enterIndex] = 0;
            dict->b[i] += temp * dict->b[leaveIndex];
            for (j = 0; j < dict->n; ++j)
            {
                dict->a[i][j] += temp * dict->a[leaveIndex][j];
            }
        }
    }
    temp = dict->c[enterIndex];
    dict->c[enterIndex] = 0;
    dict->z0 += temp * dict->b[leaveIndex];
    for (i = 0; i < dict->n; ++i)
    {
        dict->c[i] += temp * dict->a[leaveIndex][i];
    }
    temp = dict->N[enterIndex];
    dict->N[enterIndex] = dict->B[leaveIndex];
    dict->B[leaveIndex] = temp;
}

void pivot(PDict dict)
{
    int enterIndex, leaveIndex;
    //printDict(dict);
    enterIndex = getEnteringIndex(dict);
    leaveIndex = getLeavingIndex(dict, enterIndex);
    printf("%d\n%d\n", dict->N[enterIndex], dict->B[leaveIndex]);
    transformDict(dict, enterIndex, leaveIndex);
    printf("%lf\n", dict->z0);
    //printDict(dict);
}

int isUnbounded(PDict dict)
{
    int i, j;
    for (i = 0; i < dict->n; ++i)
    {
        if (dict->c[i] > EPS)
        {
            for (j = 0; j < dict->m; ++j)
            {
                if (dict->a[j][i] < -EPS)
                {
                    break;
                }
            }
            if (j == dict->m)
            {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    PDict dict = createDict();
    if (3 == argc)
    {
        freopen(argv[1], "r", stdin);
        freopen(argv[2], "w", stdout);
        readDict(dict);
        if (isUnbounded(dict))
        {
            printf("UNBOUNDED\n");
        }
        else
        {
            pivot(dict);
        }
        releaseDict(dict);
    }
    return 0;
}
