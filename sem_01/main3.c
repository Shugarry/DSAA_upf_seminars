#include <stdio.h>

typedef struct clock{
    int countdown;
    int restart;
} c;

int main()
{
    c clocks[3];
    for (int i = 0; i < 3; i++)
    {
        printf("restart for clock %d", i + 1);
        scanf("%d", &clocks);
    }
}
