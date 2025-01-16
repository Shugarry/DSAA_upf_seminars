#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(int ac, char **av)
{
    if (ac == 1)
        return (0);
    int flag;
    for (int i = 1; i < ac; i++)
    {
        for (int j = 0; j < strlen(av[i]); j++)
        {
            if (av[i][j] == 'A' || av[i][j] == 'a' || av[i][j] == 'E' || av[i][j] == 'e' || av[i][j] == 'I' || av[i][j] == 'i' || av[i][j] == 'O' || av[i][j] == 'o' || av[i][j] == 'U' || av[i][j] == 'u')
                flag = 1;
        }
        if (flag || strlen(av[i]) == 1)
            printf("Word %d = Human", i);
        else    
            printf("Word %d = Alien", i);
        flag = 0;
        printf("\n");
    }
    return (0);
}
