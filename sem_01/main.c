#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    int remainder;
    int num;
   
    if (ac != 2)
        return (0);
    num = atoi(av[1]);
    remainder = num % 7;
    switch (remainder)
    {
        case 0:
            printf("Wednesday"); break;
        case 1:
            printf(" Thursday"); break;
        case 2:
            printf("Friday"); break;
        case 3:
            printf("Saturday"); break;
        case 4:
            printf("Sunday"); break;
        case 5:
            printf("Monday"); break;
        case 6:
            printf("Tuesday"); break;
    }
    printf("\n");
    return (0);    
}
