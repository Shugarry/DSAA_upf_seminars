#include <stdio.h>

typedef struct clock
{
    int countdown;
    int restart;
} clk;

int main()
{
    clk clocks[3];

    for (int i = 0; i < 3; i++)
    {
        printf("restart for clock %d: ", i + 1);
        scanf("%d", &clocks[i].restart);
		clocks[i].countdown = clocks[i].restart;
    }
	for (int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			clocks[j].countdown--;
			if (clocks[j].countdown == 0)
			{
				printf("Time %d: Clock %d finished! restarting...\n", i + 1, j + 1);
				clocks[j].countdown=clocks[j].restart;
				for (int k = 0; k < 3; k++)
				{
					if (k != j)
						printf("Time %d: Clock %d countdown = %d\n", i + 1, k + 1, clocks[k].countdown);
				}
			}
		}
	}
}
