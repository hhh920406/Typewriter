#include <stdio.h>
#include <stdlib.h>

char command[1024];

int main()
{
    int i;
    FILE *file;
    for (i = 1; i <= 5; ++i)
    {
        sprintf(command, "Pivot part%d.dict part%d.output", i, i);
        file = popen(command, "r");
        pclose(file);
    }
    return 0;
}
