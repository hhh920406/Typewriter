#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPS 1e-2

struct Pivot
{
    int enter, leave;
    double objective;
};

struct Answer
{
    double maximum;
    int stepNum;
};

char command[1024];

int main()
{
    int i;
    struct Answer a1, a2;
    FILE *file;
    for (i = 1; i <= 10; ++i)
    {
        sprintf(command, "Pivot dict%d dict%d.test", i, i);
        file = popen(command, "r");
        pclose(file);

        sprintf(command, "dict%d.test", i);
        file = fopen(command, "r");
        fscanf(file, "%lf%d", &a1.maximum, &a1.stepNum);
        fclose(file);

        sprintf(command, "dict%d.output", i);
        file = fopen(command, "r");
        fscanf(file, "%lf%d", &a2.maximum, &a2.stepNum);
        fclose(file);

        if (a1.stepNum != a2.stepNum || fabs(a1.maximum - a2.maximum) > EPS)
        {
            printf("No\n");
            printf("%lf\t\t%lf\n", a1.maximum, a2.maximum);
            printf("%d\t\t%d\n", a1.stepNum, a2.stepNum);
        }
        else
        {
            printf("Yes\n");
        }
        printf("\n");
    }
    return 0;
}
