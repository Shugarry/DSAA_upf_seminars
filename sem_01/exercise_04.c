#include <stdio.h>

typedef struct //player type object with name, left and right hand values.
{
	int		left;
	int		right;
	char	name[20];
} player;

int main()
{
	player  alice = {1, 1, Alice};
    player  bob = {1, 1, Bob};
    int     turns;
    char    turn_doer[3];


    printf("Please input amount of turns: ");
    scanf("%d\n", &turns);
    
    for (int i = 0; i < turns; i++)
    {
        scanf("%c %c %c\n", turn_doer[0], turn_doer[1], turn_doer[2]);
    }
}
