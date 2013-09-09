#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPS 1e-3

struct Pivot
{
    int enter, leave;
    double objective;
};

char command[1024];

int main()
{
    int i;
    struct Pivot p1, p2;
    FILE *file;
    for (i = 1; i <= 10; ++i)
    {
        sprintf(command, "Pivot dict%d dict%d.test", i, i);
        file = popen(command, "r");
        pclose(file);

        sprintf(command, "dict%d.test", i);
        file = fopen(command, "r");
        fscanf(file, "%d%d%lf", &p1.enter, &p1.leave, &p1.objective);
        fclose(file);

        sprintf(command, "dict%d.output", i);
        file = fopen(command, "r");
        fscanf(file, "%d%d%lf", &p2.enter, &p2.leave, &p2.objective);
        fclose(file);

        if (p1.enter != p2.enter ||
            p1.leave != p2.leave ||
            fabs(p1.objective - p2.objective) > EPS)
        {
            printf("No\n");
            printf("%d\t\t%d\n", p1.enter, p2.enter);
            printf("%d\t\t%d\n", p1.leave, p2.leave);
            printf("%.3lf\t\t%.3lf\n", p1.objective, p2.objective);
        }
        else
        {
            printf("Yes\n");
        }
        printf("\n");
    }
    return 0;
}
